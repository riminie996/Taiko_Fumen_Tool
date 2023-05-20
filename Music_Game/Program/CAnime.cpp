
#include "CAnime.h"
#include <list>

#include <fstream>
#include <sstream>
#include <math.h>


namespace Rimi
{
	const float PI = 3.14f;
}

using namespace std;
CAnime::CAnime()
{
	Init();

}

CAnime::CAnime(string entry_name)
{

	m_str_entry_name = entry_name;
	list<string> list_str = LoadFile(entry_name + Rimi::FILE_FORMAT_ANIME);

	ST_ANIME anime;
	int now_anime_type;

	for (auto itr = list_str.begin(); itr != list_str.end(); itr++)
	{
		string str_split;

		if (itr->find("MAX_FRAME:") != -1)
		{
			str_split = itr->substr(10);
			m_max_frame = atof(str_split.c_str());
		}
		else if (itr->find("FRAME:") != -1)
		{
			str_split = itr->substr(6);
			anime.frame = atof(str_split.c_str());
		}
		else if (itr->find("PARAM:") != -1)
		{
			str_split = itr->substr(6);
			anime.value = atof(str_split.c_str());
		}
		//else if (itr->find("ANIME_TYPE:") != -1)
		//{
		//	str_split = itr->substr(11);

		//	for (int i = 0; i < AnimeTypeCounter; i++)
		//	{
		//		if (str_split == STR_ANIME_TYPE[i])
		//			now_anime_type = i;
		//	}
		//	
		//}
		else if (itr->find("MOVE_TYPE:") != -1)
		{
			str_split = itr->substr(10);

			for (int i = 0; i < MoveTypeCounter; i++)
			{
				if (str_split == STR_MOVE_TYPE[i])
					anime.anime_type = (E_ANIME_TYPE)i;
			}
		}
		//アニメ情報をエントリに追加する
		else if (itr->find("#PUSH") != -1)
		{
			m_vec_anime.push_back(anime);
		}
	}


	Init();
}

void CAnime::Init()
{
	m_now_frame = 0.0f;
	m_value = m_vec_anime.front().value;
	m_flag_start = false;

	//m_now_info.pos_x = 0.0f;
	//m_now_info.pos_y = 0.0f;
	//m_now_info.scale_x = 0.0f;
	//m_now_info.scale_y = 0.0f;
	//m_now_info.color_r = 1.0f;
	//m_now_info.color_g = 1.0f;
	//m_now_info.color_b = 1.0f;
	//m_now_info.color_a = 1.0f;
	//m_now_info.rotate_z = 0.0f;
}

CAnime::~CAnime()
{
	//for (int i = 0; i < AnimeTypeCounter; i++)
	//{
	m_vec_anime.clear();
	m_vec_anime.shrink_to_fit();
	//}
}

void CAnime::Action()
{
	if (m_flag_start == false)return;

	m_now_frame += 1.0f;//1フレーム文増加

	if (m_now_frame >= m_max_frame)
	{
		m_now_frame = m_max_frame;
		m_value = m_vec_anime.back().value;
		return;
	}
	//for (int i = 0; i < AnimeTypeCounter; i++)
	//{
	for (int i = 0; i < m_vec_anime.size(); i++)
	{

		float next_frame = i + 1 < m_vec_anime.size() ? m_vec_anime[i + 1].frame : m_vec_anime[i].frame;
		float next_value = i + 1 < m_vec_anime.size() ? m_vec_anime[i + 1].value : m_vec_anime[i].value;

		//次の要素がある場合、現在のパラメータ値と次のパラメータ値の間で
		// 現在のフレーム数を考慮して位置を調整する

		//現在のフレーム数より次のエントリの値が大きくなるまでスキップ
		if (m_now_frame <= next_frame)
		{
			float percent;
			//現在のフレーム数 - 1つ前の指定フレーム
			float frame = m_now_frame - m_vec_anime[i].frame;
			//指定フレームと次の指定フレームの差
			float max_frame = next_frame - m_vec_anime[i].frame;

			//ゼロ除算を避けるため、frame数が0の時は瞬間移動する。
			if (max_frame == 0.0f)
			{
				percent = 1.0f;
			}
			else
			{
				percent = frame / max_frame;
			}

			//5 + (8 - 5)
			float value = 0.0f;

			switch (m_vec_anime[i].anime_type)
			{
			case MOVE_NORMAL:
			case MOVE_ACC_DEC:
				value = m_vec_anime[i].value +
					(next_value - m_vec_anime[i].value) * percent;
				break;
			case MOVE_ACCELE:
				value = m_vec_anime[i].value +
					(next_value - m_vec_anime[i].value) * (1.0f - cos(percent * Rimi::PI / 2.0f));
				break;
			case MOVE_DECELE:
				value = m_vec_anime[i].value +
					(next_value - m_vec_anime[i].value) * sin(percent * Rimi::PI / 2.0f);
				break;
			}
			m_value = value;
			//移動してから
			break;
		}
	}
	//}
}

void CAnime::ActionLoop()
{
	Action();
	if (m_now_frame == m_max_frame)
	{
		m_now_frame = m_now_frame - m_max_frame;
	}
}

void CAnime::Start()
{
	m_now_frame = m_vec_anime.begin()->frame;
	m_value = m_vec_anime.begin()->value;
	m_flag_start = true;
}

void CAnime::End()
{
	m_flag_start = false;
}