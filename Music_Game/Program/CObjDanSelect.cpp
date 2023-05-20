#include "CObjDanSelect.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"
#include <filesystem>
#include "GameL\UserData.h"

//初期化
CObjDanSelect::CObjDanSelect()
{
	LoadDirectory("Fumen/");
	FumenListCreate();
}

void CObjDanSelect::Init()
{
	for (int i = 0; i < MusicGame::DanSelect::TEXT_COUNT; i++)
	{
		m_ani_text_fade_in[i].LoadData("Animation/DanSelect/TextFadeIn");
	}
	m_ani_fusuma.LoadData("Animation/DanSelect/Fusuma");
	m_ani_text_fade_out.LoadData("Animation/DanSelect/TextFadeOut");
	m_ani_text_dan.LoadData("Animation/DanSelect/Text_Dan");
	m_ani_text_i.LoadData("Animation/DanSelect/Text_I");
	m_ani_text_do.LoadData("Animation/DanSelect/Text_Do");
	m_ani_text_jo.LoadData("Animation/DanSelect/Text_Jo");
	m_ani_fusuma_open.LoadData("Animation/DanSelect/FusumaOpen");
	m_ani_fade.LoadData("Animation/DanSelect/FadeIn");
	m_ani_bg_scale.LoadData("Animation/DanSelect/BGScale");
	for (int i = 0; i < MusicGame::DanSelect::BAR_MAX_AMOUNT; i++)
	{
		m_st_dan_bar[i].ani_bar_appear.LoadData("Animation/DanSelect/BarAppear");

		if (i < 5)
			m_st_dan_bar[i].color = MusicGame::DanSelect::DAN_BAR_KYU;
		else if (i < 10)
			m_st_dan_bar[i].color = MusicGame::DanSelect::DAN_BAR_BLUE;
		else if (i < 15)
			m_st_dan_bar[i].color = MusicGame::DanSelect::DAN_BAR_RED;
		else if (i < 18)
			m_st_dan_bar[i].color = MusicGame::DanSelect::DAN_BAR_SILVER;
		else if (i < 19)
			m_st_dan_bar[i].color = MusicGame::DanSelect::DAN_BAR_GOLD;
		else if (i < 20)
			m_st_dan_bar[i].color = MusicGame::DanSelect::DAN_BAR_GREEN;

	}
	m_ani_info_slide.LoadData("Animation/DanSelect/InfoSlide");

	m_num_exam.SetTex(tex_DANSELECT_INFO_EXAM_NUMBER, MusicGame::DanSelect::RECT_EXAM_NUMBER.m_width, MusicGame::DanSelect::RECT_EXAM_NUMBER.m_height);
	m_num_gauge.SetTex(tex_DANSELECT_INFO_GAUGE_NUMBER, MusicGame::DanSelect::RECT_GAUGE_NUMBER.m_width, MusicGame::DanSelect::RECT_GAUGE_NUMBER.m_height);

	//for (int i = 0; i < m_vec_dan_bar.size() && i + tex_DANSELECT_DAN_PLATE < SCENE_IMG_MAX; i++)
	//{
	//	wchar_t wcr[64];
	//	wstring str = MusicGame::StringToWString(m_vec_dan_bar[i].data.fumen.fumen_path + "/../Dan_Plate.png");
	//	swprintf_s(wcr, L"%s", str.c_str());
	//	Draw::LoadImageW(wcr, tex_DANSELECT_DAN_PLATE + i, TEX_SIZE_64);
	//}

	m_ct_in_anime.Start(0, MusicGame::DanSelect::IN_ANIME_TIME, 1);
	Audio::Start(se_DANSELECT_IN);

	m_direction = 1;//最初は右からくるように設定
	m_bgm_flag = true;
	m_now_select = 0;
}
//進行
void CObjDanSelect::Action()
{
	for (int i = 0; i < MusicGame::DanSelect::TEXT_COUNT; i++)
	{
		m_ani_text_fade_in[i].Action();
	}
	m_ani_fusuma.Action();
	m_ani_text_fade_out.Action();
	m_ani_text_dan.Action();
	m_ani_text_i.Action();
	m_ani_text_do.Action();
	m_ani_text_jo.Action();
	m_ani_fusuma_open.Action();
	m_ani_fade.Action();
	m_ani_bg_scale.Action();
	m_ct_in_anime.Action();
	m_ct_bar_delay.Action(); 
	for (int i = 0; i < MusicGame::DanSelect::BAR_MAX_AMOUNT; i++)
	{
		m_st_dan_bar[i].ani_bar_appear.Action();
	}
	m_ani_info_slide.Action();
	m_ct_bgm_delay.Action();

	//テキストフェードイン
	for (int i = 0; i < MusicGame::DanSelect::TEXT_COUNT; i++)
	{
		if (m_ct_in_anime.NowValue >= MusicGame::DanSelect::FADE_START_DELAY[i])
		{
			if (!m_ani_text_fade_in[i].GetStart())
				m_ani_text_fade_in[i].Start();
		}
	}

	//テキスト揺れ
	for (int i = 0; i < MusicGame::DanSelect::TEXT_COUNT; i++)
	{
		if (m_ani_text_fade_in[i].GetEnd())
		{
			switch (i)
			{
			case 0:
				if (!m_ani_text_dan.GetStart())
				{
					m_ani_text_dan.Start();
					m_ani_fusuma.Start();
				}
				break;
			case 1:
				if (!m_ani_text_i.GetStart())
				{
					m_ani_text_i.Start();
					m_ani_fusuma.Start();
				}
				break;
			case 2:
				if (!m_ani_text_do.GetStart())
				{
					m_ani_text_do.Start();
					m_ani_fusuma.Start();
				}
				break;
			case 3:
				if (!m_ani_text_jo.GetStart())
				{
					m_ani_text_jo.Start();
					m_ani_fusuma.Start();
				}
				break;
			}
		}


	}

	//テキストフェードアウト
	if (m_ct_in_anime.NowValue >= MusicGame::DanSelect::FADE_OUT_DELAY && !m_ani_text_fade_out.GetStart())
	{
		m_ani_text_fade_out.Start();
		m_ani_fusuma_open.Start();
		m_ani_bg_scale.Start();
		m_ani_fade.Start();
	}

	//バー登場アニメーション
	if (m_ct_in_anime.NowValue >= MusicGame::DanSelect::BAR_START_DELAY && !m_ct_bar_delay.GetProgress())
	{
		m_ct_bar_delay.Start(0, MusicGame::DanSelect::BAR_MAX_AMOUNT * MusicGame::DanSelect::BAR_APPEAR_INTERVAL, 1);
	}

	for (int i = 0; i < MusicGame::DanSelect::BAR_MAX_AMOUNT; i++)
	{
		if (m_ct_bar_delay.GetProgress() &&
			m_ct_bar_delay.NowValue >= i * MusicGame::DanSelect::BAR_APPEAR_INTERVAL &&
			!m_st_dan_bar[i].ani_bar_appear.GetStart())
		{
			m_st_dan_bar[i].ani_bar_appear.Start();
		}
	}
	if (m_ct_in_anime.NowValue >= MusicGame::DanSelect::INFO_SLIDE_DELAY &&
		!m_ani_info_slide.GetStart())
	{
		m_ani_info_slide.Start();
	}
	

	//キー入力
	CObjDanSelectConfirm* confirm = (CObjDanSelectConfirm*)Objs::GetObj(OBJ_DANSELECT_CONFIRM);

	if (!m_ct_bgm_delay.GetProgress() &&
		m_ct_in_anime.GetEndValueReached() && m_ct_in_anime.GetProgress())
	{
		Audio::Start(bgm_IN);
		m_ct_bgm_delay.Start(0, MusicGame::DanSelect::BGM_LOOP_START_DELAY, 1);
	}
	else if (m_ct_bgm_delay.GetProgress() && m_ct_bgm_delay.GetEndValueReached() && m_bgm_flag == true)
	{
		Audio::Start(bgm_MUSIC);
		m_bgm_flag = false;
	}


	if (!m_ct_in_anime.GetEndValueReached() || confirm != nullptr)return;

	//操作可能

	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	if (system->GetInput(LEFT_KA,0))
	{
		Audio::Start(se_KA);
		PreviousSong();
		m_ani_info_slide.Start();

		m_direction = -1;
	}
	if (system->GetInput(RIGHT_KA,0))
	{
		Audio::Start(se_KA);
		NextSong();
		m_ani_info_slide.Start();

		m_direction = 1;
	}
	if (system->GetInput(LEFT_DON,0) || 
		system->GetInput(RIGHT_DON,0))
	{
		Audio::Start(se_DANSELECT_CONFIRM);

		CObjDanSelectConfirm* confir = new CObjDanSelectConfirm();
		Objs::InsertObj(confir, OBJ_DANSELECT_CONFIRM, PRIO_DANSELECT_CONFIRM);
		//ChallengeStart();

	}
}
//描画
void CObjDanSelect::Draw()
{
	//背景の描画
	Draw::SetScaleX(tex_DANSELECT_BG, m_ani_bg_scale.GetValue().scale_x);
	Draw::SetScaleY(tex_DANSELECT_BG, m_ani_bg_scale.GetValue().scale_y);
	Draw::CenterDraw(tex_DANSELECT_BG, WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2);

	//ふすまの描画
	float scale_x = m_ani_fusuma_open.GetValue().scale_x;
	float left_x = 0 - m_ani_fusuma_open.GetValue().x;
	float right_x = MusicGame::DanSelect::RECT_FUSUMA_RIGHT.m_x + MusicGame::DanSelect::RECT_FUSUMA_RIGHT.m_width - MusicGame::DanSelect::RECT_FUSUMA_RIGHT.m_width * scale_x + m_ani_fusuma_open.GetValue().x;
	Draw::SetScaleX(tex_DANSELECT_FUSUMA, scale_x);

	//左側を手前に描画
	Draw::Draw(tex_DANSELECT_FUSUMA, right_x, m_ani_fusuma.GetValue().y, MusicGame::DanSelect::RECT_FUSUMA_RIGHT);
	Draw::Draw(tex_DANSELECT_FUSUMA, left_x, m_ani_fusuma.GetValue().y, MusicGame::DanSelect::RECT_FUSUMA_LEFT);

	//フェードの描画
	Draw::SetOpacity(tex_TILE, m_ani_fade.GetValue().opacity);
	DrawFill(tex_TILE, MusicGame::RECT_TILE_BLACK);

	//[段位道場]テキストの描画
	for (int i = 0; i < MusicGame::DanSelect::TEXT_COUNT; i++)
	{
		float scale = m_ani_text_fade_in[i].GetValue().scale_x;
		float opacity = m_ani_text_fade_in[i].GetValue().opacity * m_ani_text_fade_out.GetValue().opacity;
		float x = 0.0f;
		float y = 0.0f;

		switch (i)
		{
		case 0:
			x = m_ani_text_dan.GetValue().x;
			y = m_ani_text_dan.GetValue().y;
			break;
		case 1:
			x = m_ani_text_i.GetValue().x;
			y = m_ani_text_i.GetValue().y;
			break;
		case 2:
			x = m_ani_text_do.GetValue().x;
			y = m_ani_text_do.GetValue().y;
			break;
		case 3:
			x = m_ani_text_jo.GetValue().x;
			y = m_ani_text_jo.GetValue().y;
			break;
		}

		Draw::SetScaleX(tex_DANSELECT_TEXT, scale);
		Draw::SetScaleY(tex_DANSELECT_TEXT, scale);
		Draw::SetOpacity(tex_DANSELECT_TEXT, opacity);
		Draw::CenterDraw(tex_DANSELECT_TEXT, MusicGame::DanSelect::TEXT_POS[i].x + x, MusicGame::DanSelect::TEXT_POS[i].y + y, MusicGame::DanSelect::RECT_TEXT[i]);
	}

	for (int i = 0; i < MusicGame::DanSelect::BAR_MAX_AMOUNT; i++)
	{
		float x = MusicGame::DanSelect::BAR_POS.x + i * MusicGame::DanSelect::BAR_WIDTH;
		float y = MusicGame::DanSelect::BAR_POS.y + m_st_dan_bar[i].ani_bar_appear.GetValue().y;
		Draw::Draw(tex_DANSELECT_BAR, x, y, MusicGame::DanSelect::RECT_DANBAR[m_st_dan_bar[i].color]);
	}

	float slide_x = m_ani_info_slide.GetValue().x * m_direction;

	for (int i = 0; i < 3; i++)
	{
		if (i != 1 && !m_ct_in_anime.GetEndValueReached())continue;

		int num = m_now_select - 1 + i;

		if (num < 0)num = m_vec_dan_bar.size() - num;
		if (num >= m_vec_dan_bar.size())num = num - m_vec_dan_bar.size();

		float x = slide_x + MusicGame::DanSelect::PANEL_X[i];

		//パネルの描画
		Draw::Draw(tex_DANSELECT_INFO_BACK, x, 0, MusicGame::DanSelect::RECT_DAN_INFO[MusicGame::DanSelect::DAN_BAR_KYU]);
		Draw::Draw(tex_DANSELECT_INFO_SONG, x, 0, MusicGame::DanSelect::RECT_DAN_INFO[MusicGame::DanSelect::DAN_BAR_KYU]);

		Draw::Draw(tex_DANSELECT_INFO_PERCENT, x + MusicGame::DanSelect::PERCENT_POS.x, MusicGame::DanSelect::PERCENT_POS.y);
		Draw::Draw(tex_DANSELECT_INFO_GAUGE, x + MusicGame::DanSelect::GAUGE_POS.x, MusicGame::DanSelect::GAUGE_POS.y);
		Draw::Draw(tex_DANSELECT_INFO_GAUGE_RANGE, x + MusicGame::DanSelect::GAUGE_RANGE_POS.x, MusicGame::DanSelect::GAUGE_RANGE_POS.y, MusicGame::DanSelect::RECT_GAUGE_MORE);
		m_num_gauge.Draw(m_vec_dan_bar[num].data.gauge_norma[0], x + MusicGame::DanSelect::GAUGE_NUMBER_POS.x, MusicGame::DanSelect::GAUGE_NUMBER_POS.y, MusicGame::DanSelect::GAUGE_NUMBER_PADDING);

		for (int j = 0; j < m_vec_dan_bar[num].data.vec_song.size(); j++)
		{
			float title_x = x + MusicGame::DanSelect::TITLE_POS.x;
			float title_y = MusicGame::DanSelect::TITLE_POS.y + j * MusicGame::DanSelect::SONG_HEIGHT;
		
			wchar_t wcr[64];
			wstring str = MusicGame::StringToWString(m_vec_dan_bar[num].data.vec_song[j].title);
			swprintf_s(wcr, L"%s", str.c_str());
			Font::StrDraw(wcr, title_x, title_y, MusicGame::DanSelect::SONG_FONT_SIZE,ColorA::Black);
		}

		for (int j = 0; j < m_vec_dan_bar[num].data.vec_info.size(); j++)
		{
			float base_x = x + MusicGame::DanSelect::INFO_POS.x;
			float base_y = MusicGame::DanSelect::INFO_POS.y + j * MusicGame::DanSelect::INFO_HEIGHT;

			//土台を描画
			Draw::Draw(tex_DANSELECT_INFO_INFO, base_x, base_y, MusicGame::DanSelect::RECT_INFO_BASE);

			//共通か個別
			RECT_F rect_info = m_vec_dan_bar[num].data.vec_info[j].m_common == true ? MusicGame::DanSelect::RECT_INFO_SINGLE : MusicGame::DanSelect::RECT_INFO_TRIPLE;
			Draw::Draw(tex_DANSELECT_INFO_INFO, base_x, base_y, rect_info);

			//条件タイプの描画
			RECT_F rect_type = MusicGame::DanSelect::RECT_EXAM_TYPE; 
			rect_type.m_y = (float)m_vec_dan_bar[num].data.vec_info[j].m_type * MusicGame::DanSelect::RECT_EXAM_TYPE.m_height;
			Draw::Draw(tex_DANSELECT_INFO_EXAM_TYPE, base_x + MusicGame::DanSelect::EXAM_TYPE_OFFSET.x, base_y + MusicGame::DanSelect::EXAM_TYPE_OFFSET.y, rect_type);

			int amount = m_vec_dan_bar[num].data.vec_info[j].m_common == true ? 1 : MusicGame::DAN_MAX_SONG;
			for (int k = 0; k < amount; k++)
			{
				base_x = x + MusicGame::DanSelect::INFO_POS.x + k * MusicGame::DanSelect::INFO_WIDTH;
				m_num_exam.Draw(m_vec_dan_bar[num].data.vec_info[j].m_norma[k][0], base_x + MusicGame::DanSelect::EXAM_NUMBER_OFFSET.x, base_y + MusicGame::DanSelect::EXAM_NUMBER_OFFSET.y, MusicGame::DanSelect::EXAM_NUMBER_PADDING);

				RECT_F rect_range = m_vec_dan_bar[num].data.vec_info[j].m_range == MusicGame::DanC::RANGE_MORE ? MusicGame::DanSelect::RECT_EXAM_MORE: MusicGame::DanSelect::RECT_EXAM_LESS;
				Draw::Draw(tex_DANSELECT_INFO_EXAM_RANGE, base_x + MusicGame::DanSelect::EXAM_RANGE_OFFSET.x, base_y + MusicGame::DanSelect::EXAM_RANGE_OFFSET.y, rect_range);
			}
		}

//		Draw::Draw(tex_DANSELECT_DAN_PLATE + num, x + MusicGame::DanSelect::DAN_PLATE_POS.x, MusicGame::DanSelect::DAN_PLATE_POS.y);
	}
}

void CObjDanSelect::LoadDirectory(string path)
{
	using std::filesystem::recursive_directory_iterator;

	for (const auto& file : recursive_directory_iterator(path))
	{
		//tjaファイルのみリスインする
		if (file.path().string().find(".tja") != -1)
		{
			m_vec_fumen_path.push_back(file.path().string());
		}
	}
	return;
}

void CObjDanSelect::FumenListCreate()
{
	//譜面リストを作成
	for (int i = 0; i < m_vec_fumen_path.size(); i++)
	{
		ST_DAN_BAR bar;

		string str_fumen_command;
		list<string> str_split_fumen_command;

		string fumen_path = m_vec_fumen_path[i];

		//ファイルを開く
		ifstream ifs(fumen_path);
		if (!ifs)
		{
			//	MessageBox(NULL, TEXT("やりなおしてください"),
			//		TEXT("譜面ファイル読み込み失敗"), MB_OK);
			ifs.close();
			continue;
		}


		bar.data.fumen.fumen_path = fumen_path;



		while (getline(ifs, str_fumen_command))
		{
			str_split_fumen_command.push_back(str_fumen_command);
		}

		//ヘッダの読み込み。
		for (auto itr = str_split_fumen_command.begin(); itr != str_split_fumen_command.end(); itr++)
		{
			bar.data.fumen.FumenHeaderLoad(*itr);
		}
			//譜面パスにフォルダパスが含まれているか検索する。
		if (bar.data.fumen.diff_fumen_use[E_DIFFCULTY::DIFF_DAN] == true)
		{
			bar.data.DanFumenDataLoad(str_split_fumen_command);
			
			m_vec_dan_bar.push_back(bar);
		}
	}

}

void CObjDanSelect::ST_DAN_FUMEN::DanFumenDataLoad(list<string>& command_param)
{

	bool load_notes = false;
	E_DIFFCULTY now_diffculty;

	//段位道場用
	vector<ST_DAN_SONG> vec_dan_song;
	vector<MusicGame::DanC> vec_dan;
	ST_DAN_SONG dan_song;
	bool load_dansong = false;

	for (auto itr = command_param.begin(); itr != command_param.end(); itr++)
	{
		if (*itr == "")continue;

		if (itr->find("COURSE:") != -1)
		{
			string str = itr->substr(7);
			now_diffculty = MusicGame::StrToDiffculty(str);
		}
		else if (itr->find("EXAM1:") != -1 ||
			itr->find("EXAM2:") != -1 ||
			itr->find("EXAM3:") != -1 ||
			itr->find("EXAM4:") != -1)
		{
			string command = itr->substr(6);
			vector<string> command_strsplit;
			string str;
			MusicGame::DanC dan;

			int count = 0;
			for (int i = 0; i < command.size(); i++)
			{
				if (command[i] == ',')
				{
					command_strsplit.push_back(str);
					str = "";
				}
				else
				{
					str += command[i];

				}
			}
			command_strsplit.push_back(str);

			E_DAN_TYPE type;
			MusicGame::DanC::E_DAN_RANGE range;

			for (int i = 0; i < command_strsplit.size(); i++)
			{
				switch (i)
				{
				case 0:
					if (command_strsplit[i] == "g")dan.m_type = E_DAN_TYPE::TYPE_GAUGE;
					else if (command_strsplit[i] == "jp")dan.m_type = E_DAN_TYPE::TYPE_GREAT;
					else if (command_strsplit[i] == "jg")dan.m_type = E_DAN_TYPE::TYPE_GOOD;
					else if (command_strsplit[i] == "jb")dan.m_type = E_DAN_TYPE::TYPE_MISS;
					else if (command_strsplit[i] == "s")dan.m_type = E_DAN_TYPE::TYPE_SCORE;
					else if (command_strsplit[i] == "r")dan.m_type = E_DAN_TYPE::TYPE_ROLL;
					else if (command_strsplit[i] == "h")dan.m_type = E_DAN_TYPE::TYPE_HIT;
					else if (command_strsplit[i] == "c")dan.m_type = E_DAN_TYPE::TYPE_COMBO;
					else dan.m_type = E_DAN_TYPE::TYPE_GAUGE;
					break;
				case 1:
					dan.m_norma[0][0] = atoi(command_strsplit[i].c_str());
					break;
				case 2:
					dan.m_norma[0][1] = atoi(command_strsplit[i].c_str());
					break;
				case 3:
					if (command_strsplit[i] == "m")dan.m_range = MusicGame::DanC::RANGE_MORE;
					else if (command_strsplit[i] == "l")dan.m_range = MusicGame::DanC::RANGE_LESS;
					else range = MusicGame::DanC::RANGE_MORE;
					break;
				case 4:
					dan.m_norma[1][0] = atoi(command_strsplit[i].c_str());
					dan.m_common = false;
					break;
				case 5:
					dan.m_norma[1][1] = atoi(command_strsplit[i].c_str());
					break;
				case 6:
					dan.m_norma[2][0] = atoi(command_strsplit[i].c_str());
					break;
				case 7:
					dan.m_norma[2][1] = atoi(command_strsplit[i].c_str());
					break;
				}
			}

			//ゲージの場合追加しない
			if (dan.m_type == E_DAN_TYPE::TYPE_GAUGE)
			{
				gauge_norma[0] = dan.m_norma[0][0];
				gauge_norma[1] = dan.m_norma[0][1];
			}
			else
			{
				vec_dan.push_back(dan);
			}
		}
		else if (itr->find("NORMA:") != -1)
		{
			string command = itr->substr(6);
			vector<string> command_strsplit;
			string str;
			int count = 0;
			for (int i = 0; i < command.size(); i++)
			{
				if (command[i] == ',')
				{
					command_strsplit.push_back(str);
					str = "";
				}
				else
				{
					str += command[i];

				}
			}
			command_strsplit.push_back(str);

			gauge_norma[0] = atoi(command_strsplit[0].c_str());
			gauge_norma[1] = atoi(command_strsplit[1].c_str());
		}

		//開始から終了まで
		if (itr->find("#START") != -1 &&
			load_notes == false &&
			now_diffculty == DIFF_DAN)
		{
			load_notes = true;
		}


		//譜面データ読み込み中
		if (load_notes == true)
		{
			//小節の合間にBPM変化を挿入できるように変更

			for (auto itrs = command_param.begin(); itrs != command_param.end(); itrs++)
			{

				if (itrs->find("#END") != -1)
				{
					//終了
					load_notes = false;
					break;
				}
				else if (itrs->find("#NEXTSONG") != -1)
				{
					if (load_dansong == true)
					{
						vec_dan_song.push_back(dan_song);
						dan_song = ST_DAN_SONG();
					}
					else
					{
						load_dansong = true;
					}

					string command = itrs->substr(10);
					vector<string> command_strsplit;
					string str;

					int count = 0;
					for (int i = 0; i < command.size(); i++)
					{
						if (command[i] == ',')
						{
							command_strsplit.push_back(str);
							str = "";
						}
						else
						{
							str += command[i];

						}
					}
					command_strsplit.push_back(str);

					//曲情報を追加
					for (int i = 0; i < command_strsplit.size(); i++)
					{
						switch (i)
						{
						case 0:
							dan_song.title = command_strsplit[i];
							break;
						//case 1:
						//	dan_song.sub_title = command_strsplit[i];
						//	break;
						//case 2:
						//	dan_song.genre = MusicGame::StrToGenre(command_strsplit[i]);
						//	break;
						//case 3:
						//	dan_song.wave_file = m_fumen.fumen_path + "/../" + command_strsplit[i];
						//	break;
						//case 4:
						//	dan_song.score_add = atoi(command_strsplit[i].c_str());
						//	break;
						default:
							break;
						}
					}


				}
			}

			if (load_notes == false)break;
		}

	}
	if (load_dansong == true)
	{
		vec_dan_song.push_back(dan_song);
	}

	vec_info = vec_dan;
	vec_song = vec_dan_song;
}

void CObjDanSelect::PreviousSong()
{
	m_now_select--;

	if (m_now_select < 0)
		m_now_select = m_vec_dan_bar.size() - 1;

}

void CObjDanSelect::NextSong()
{
	m_now_select++;

	if (m_now_select >= m_vec_dan_bar.size())
		m_now_select = 0;

}

void CObjDanSelect::ChallengeStart()
{
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
	((UserData*)Save::GetData())->m_now_select_diffculty[0] = DIFF_DAN;

	Audio::Stop(bgm_MUSIC);
	system->DanSelectEnd();
	system->EnsoStart(m_vec_dan_bar[m_now_select].data.fumen.fumen_path,m_enso_option);
}