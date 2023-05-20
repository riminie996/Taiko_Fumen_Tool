
#include "CAnime2.h"
#include <list>

#include <fstream>
#include <sstream>
#include <math.h>


namespace Rimi
{
	const float PI = 3.14f;
}

using namespace std;
CAnime2::CAnime2()
{
	m_flag_start = false;
	m_vec_anime.resize(AnimeTypeCounter);
	Init();
}

CAnime2::CAnime2(string entry_name)
{
	m_flag_start = false;
	m_vec_anime.resize(AnimeTypeCounter);


	LoadData(entry_name);

	Init();
}

void CAnime2::LoadData(string entry_name)
{
	list<string> list_str = LoadFile(entry_name + Rimi::FILE_FORMAT_ANIME);

	ST_ANIME anime;
	int now_anime_type;
	int max_time = 0.0f;

	for (auto itr = list_str.begin(); itr != list_str.end(); itr++)
	{
		string str_split;

		if (itr->find("MAX_TIME:") != -1)
		{
			str_split = itr->substr(9);
			max_time = atof(str_split.c_str()) * 1000;//小数点からmsに変換
		}
		else if (itr->find("TIME:") != -1)
		{
			str_split = itr->substr(5);
			anime.time = atof(str_split.c_str()) * 1000;//小数点からmsに変換
		}
		else if (itr->find("PARAM:") != -1)
		{
			str_split = itr->substr(6);
			anime.value = atof(str_split.c_str());
		}
		else if (itr->find("TYPE:") != -1)
		{
			str_split = itr->substr(5);

			for (int i = 0; i < AnimeTypeCounter; i++)
			{
				if (str_split == STR_ANIME_TYPE[i])
					now_anime_type = i;
			}

		}
		else if (itr->find("MOVE:") != -1)
		{
			str_split = itr->substr(5);

			for (int i = 0; i < MoveTypeCounter; i++)
			{
				if (str_split == STR_MOVE_TYPE[i])
					anime.anime_type = (E_ANIME_TYPE)i;
			}
		}
		//アニメ情報をエントリに追加する
		else if (itr->find("#PUSH") != -1)
		{
			//	m_vec_anime.push_back(anime);
			m_vec_anime[now_anime_type].push_back(anime);
		}
	}
	m_ct_time = { CTimeCounter(0,max_time,1) };


	Init();
}

void CAnime2::Init()
{
	for (int i = 0; i < AnimeTypeCounter; i++)
	{

		if (m_vec_anime[i].size() == 0)continue;

		float* p_value;
		switch ((E_ANIME_TYPE)i)
		{
		case POS_X:
		default:
			p_value = &m_value.x;
			break;
		case POS_Y:
			p_value = &m_value.y;
			break;
		case SCALE_X:
			p_value = &m_value.scale_x;
			break;
		case SCALE_Y:
			p_value = &m_value.scale_y;
			break;
		case COLOR_R:
			p_value = &m_value.r;
			break;
		case COLOR_G:
			p_value = &m_value.g;
			break;
		case COLOR_B:
			p_value = &m_value.b;
			break;
		case ROTATE_Z:
			p_value = &m_value.rotate_z;
			break;
		case OPACITY:
			p_value = &m_value.opacity;
			break;
		case PATTERN:
			p_value = &m_value.pattern;
			break;
		}

		if (m_vec_anime[i].size() > 0)
			*p_value = m_vec_anime[i].front().value;


	}
}

CAnime2::~CAnime2()
{
	m_vec_anime.clear();
	m_vec_anime.shrink_to_fit();
	
}

void CAnime2::Action()
{
	if (m_flag_start == false)return;

	m_ct_time.Action();//1フレーム文増加

	Update();
}

void CAnime2::ActionLoop()
{

	if (m_flag_start == false)return;

	m_ct_time.ActionLoop();//1フレーム文増加


	Update();
}

void CAnime2::Start()
{
	m_ct_time.Start(0, m_ct_time.EndValue, 1);
	m_flag_start = true;
	//全ての値をリセットする
	Init();
}

void CAnime2::End()
{
	m_flag_start = false;
}

void CAnime2::Update()
{
	for (int i = 0; i < AnimeTypeCounter; i++)
	{
		if (m_vec_anime[i].size() == 0)continue;



		float* p_value;
		switch ((E_ANIME_TYPE)i)
		{
		case POS_X:
		default:
			p_value = &m_value.x;
			break;
		case POS_Y:
			p_value = &m_value.y;
			break;
		case SCALE_X:
			p_value = &m_value.scale_x;
			break;
		case SCALE_Y:
			p_value = &m_value.scale_y;
			break;
		case COLOR_R:
			p_value = &m_value.r;
			break;
		case COLOR_G:
			p_value = &m_value.g;
			break;
		case COLOR_B:
			p_value = &m_value.b;
			break;
		case ROTATE_Z:
			p_value = &m_value.rotate_z;
			break;
		case OPACITY:
			p_value = &m_value.opacity;
			break;
		case PATTERN:
			p_value = &m_value.pattern;
			break;
		}

		if (m_ct_time.GetProgress() && m_ct_time.GetEndValueReached())
		{
			*p_value = m_vec_anime[i].back().value;
			continue;
		}

		//Actionが一度実行された場合、
		// 一度最終の値にしてから調べることで
		//最終フレームに到達している場合最後の値に設定する
		*p_value = m_vec_anime[i].front().value;

		for (int j = 0; j < m_vec_anime[i].size(); j++)
		{
			//次のフレームがない
			if (j + 1 == m_vec_anime[i].size())
			{
				*p_value = m_vec_anime[i].back().value;
				break;
			}

			if (m_ct_time.NowValue < m_vec_anime[i][j + 1].time)
			{


				int next_time = m_vec_anime[i][j + 1].time;
				float next_value = m_vec_anime[i][j + 1].value;


				float percent;
				//アニメーションを行う最大のフレーム数
				int now_time = m_ct_time.NowValue - m_vec_anime[i][j].time;
				//指定フレームと次の指定フレームの差
				int time = next_time - m_vec_anime[i][j].time;

				//ゼロ除算を避けるため、frame数が0の時は瞬間移動する。
				if (time == 0.0f || m_vec_anime[i][j].value == next_value)
				{
					percent = 1.0f;
				}
				else
				{
					percent = (float)now_time / (float)time;
				}

				//5 + (8 - 5)
				float value = 0.0f;

				switch (m_vec_anime[i][j].anime_type)
				{
				case MOVE_NORMAL:
				case MOVE_ACC_DEC:
					value = m_vec_anime[i][j].value +
						(next_value - m_vec_anime[i][j].value) * percent;
					break;
				case MOVE_ACCELE:
					value = m_vec_anime[i][j].value +
						(next_value - m_vec_anime[i][j].value) * (1.0f - cos(percent * Rimi::PI / 2.0f));
					break;
				case MOVE_DECELE:
					value = m_vec_anime[i][j].value +
						(next_value - m_vec_anime[i][j].value) * sin(percent * Rimi::PI / 2.0f);
					break;
				case MOVE_TELEPORT:
					value = m_vec_anime[i][j].value;
					break;
				}
				*p_value = value;
				//移動してから
				break;
			}


		}
	}
}