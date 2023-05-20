#include "CObjResult.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameL/WinInputs.h"
#include "GameHead.h"
//スコア保存用
#include <fstream>


//初期化
void CObjResult::Init()
{

	m_fade_in.m_color = Color::Black;
	m_fade_out.m_color = Color::Black;
	m_fade_in.m_fade_type = CFIFO::FadeIn;
	m_fade_out.m_fade_type = CFIFO::FadeOut;
	m_fade_in.Start();

	Audio::Start(bgm_IN);
	m_ct_bgm_delay.Start(0, RESULT_BGM_DELAY, 1);


	m_judge_num.SetTex(tex_RESULT_NUMBER, RECT_NUM.m_width, RECT_NUM.m_height);
	m_score_num.SetTex(tex_RESULT_SCORE_NUMBER, RECT_SCORE_NUM.m_width, RECT_SCORE_NUM.m_height);

	for (int i = 0; i < 5; i++)
		m_ani_judge_num[i].LoadData("Animation/Result/JudgeNumberScale");

	int end = GAUGE_START_DELAY + ((int)m_score.ct_gauge.NowValue / 2 * GAUGE_MEMORI_TIME) + RESULT_END_DELAY;

	if (m_score.crown > E_CROWN::CROWN_NONE)
		end += CROWN_START_DELAY;
	if (m_score.score_rank > E_SCORE_RANK::RANK_NONE)
		end += RANK_START_DELAY;

	m_ct_result.Start(0,end , 1);

	m_bgm_play = false;

	m_ct_fire.Start(0, 6, FIRE_ANIME_TIME);
	m_ct_rainbow.Start(0, 40, RAINBOW_ANIME_TIME);

	for (int i = 0; i < TAIKO_FLUSH_Count; i++)
		m_key_flag[i] = false;

	ScoreDataImport();

	if (USER_DATA->m_auto_play[0] == false && USER_DATA->m_save_score == true)
		ScoreSave();

	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	if (enso != nullptr && system != nullptr)
	{
		//履歴前面に追加
		system->m_list_history_fumen_path.push_front(enso->m_enso->m_fumen.fumen_path);

		std::ofstream writing_file;
		std::string filename = SONG_HISTORY_PATH;
		writing_file.open(filename, std::ios::out);
		std::string writing_text = "";

		for (auto itr = system->m_list_history_fumen_path.begin(); itr != system->m_list_history_fumen_path.end(); itr++)
		{
			writing_text += *itr + "\n";
		}
		writing_file << writing_text;
		//書きだし
		writing_file.close();

	}
	Save::Seve();
}
//進行
void CObjResult::Action()
{
	m_ct_gauge.Action();
	m_ct_result.Action();
	for (int i = 0; i < 5; i++)
		m_ani_judge_num[i].Action();
	m_ani_score_num.Action();
	m_ani_score_rank.Action();
	m_ani_crown.Action();
	m_ct_bgm_delay.Action();
	m_ct_wait.Action();
	m_ct_fire.ActionLoop();
	m_ct_rainbow.ActionLoop();

	if (m_ct_bgm_delay.GetEndValueReached() && m_bgm_play == false)
	{
		Audio::Start(bgm_MUSIC);
		m_bgm_play = true;
	}

	//リザルト進行---------------------------------------------
	int delay = GAUGE_START_DELAY;
	if (m_ct_result.NowValue >= delay)
	{
		if (!m_ct_gauge.GetProgress())
		{
			Audio::Start(se_RESULT_GAUGE);
			m_ct_gauge.Start(0, (int)m_score.ct_gauge.NowValue / 2, GAUGE_MEMORI_TIME);
		}
	}

	if (m_ct_gauge.GetEndValueReached() && m_ct_gauge.NowValue < 50)
	{
		Audio::Stop(se_RESULT_GAUGE);
	}

	delay += ((int)m_score.ct_gauge.NowValue / 2 * GAUGE_MEMORI_TIME) + NUMBER_START_DELAY;

	for (int i = 0; i < 5; i++)
	{
		if (m_ct_result.NowValue >= delay)
		{
			if (!m_ani_judge_num[i].GetStart())
			{
				Audio::Start(se_RESULT_PON);
				m_ani_judge_num[i].Start();
			}
		}
		delay += NUMBER_INTERVAL;
	}

	delay += SCORE_NUMBER_START_DELAY;

	if (m_ct_result.NowValue >= delay)
	{
		if (!m_ani_score_num.GetStart())
		{
			Audio::Start(se_DON);
			m_ani_score_num.Start();
		}
	}

	if (m_score.score_rank > E_SCORE_RANK::RANK_NONE)
	{
		delay += RANK_START_DELAY;
		if (m_ct_result.NowValue >= delay)
		{
			if (!m_ani_score_rank.GetStart())
			{
				Audio::Start(se_RESULT_RANK);
				m_ani_score_rank.Start();
			}
		}
	}


	if (m_score.crown > E_CROWN::CROWN_NONE)
	{
		delay += CROWN_START_DELAY;
		if (m_ct_result.NowValue >= delay)
		{
			if (!m_ani_crown.GetStart())
			{
				Audio::Start(se_RESULT_CROWN);
				m_ani_crown.Start();
			}
		}
	}

	//フェードアウト開始
	if (m_ct_result.GetEndValueReached() && !m_ct_wait.GetProgress())
	{
		m_ct_wait.Start(0, RESULT_WAIT_TIME, 1);
		if (m_ct_gauge.NowValue >= 40.0f)
		{
			CObjResultBg* bg = (CObjResultBg*)Objs::GetObj(OBJ_RESULT_BG);
			bg->FadeStart();
		}
	}

	if (m_ct_wait.GetEndValueReached() && m_ct_wait.GetProgress())
	{
		m_fade_out.Start();
		Audio::Stop(bgm_MUSIC);
	}


	if (m_fade_out.GetEnd())
	{
		CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
		system->ResultEnd();
		system->SongSelectStart();
	}

	//操作について
	//ゲージの進行が開始してから操作可能
	if (!m_ct_result.GetProgress())return;

	if (Input::GetVKey('F'))
	{
		if (m_key_flag[LEFT_DON] == true)
			Decide();
		m_key_flag[LEFT_DON] = false;
	}
	else
		m_key_flag[LEFT_DON] = true;

	if (Input::GetVKey('J'))
	{
		if (m_key_flag[RIGHT_DON] == true)
			Decide();
		m_key_flag[RIGHT_DON] = false;
	}
	else
		m_key_flag[RIGHT_DON] = true;

	if (Input::GetVKey('D'))
		;
	else
		m_key_flag[LEFT_KA] = true;

	if (Input::GetVKey('K'))
		;
	else
		m_key_flag[RIGHT_KA] = true;
}
//描画
void CObjResult::Draw()
{

	//パラメーターパネルの描画
	Draw::Draw(tex_RESULT_PANEL, PARAMATER_PANEL_POS.x, PARAMATER_PANEL_POS.y);
	
	//難易度の描画
	RECT_F rect_diffculty = RECT_DIFFCULTY;
	rect_diffculty.m_y = ((UserData*)Save::GetData())->m_now_select_diffculty[0] * RECT_DIFFCULTY.m_height;
	
	//パネルとゲージの土台の描画。
	float x = PARAMATER_PANEL_POS.x;
	float y = PARAMATER_PANEL_POS.y;
	Draw::Draw(tex_RESULT_PANEL_DIFFCULTY, x + PARAMATER_DIFFCULTY_OFFSET.x, y + PARAMATER_DIFFCULTY_OFFSET.y,rect_diffculty);
//	Draw::Draw(tex_RESULT_GAUGE_BASE, x, y);

//	//ゲージの描画
//	RECT_F rect_gauge = RECT_GAUGE_MEMORI;
//	rect_gauge.m_width = m_ct_gauge.NowValue * RECT_GAUGE_MEMORI.m_width;
////	Draw::Draw(tex_RESULT_GAUGE, PARAMATER_GAUGE_POS.x, PARAMATER_GAUGE_POS.y, rect_gauge);
//
//
//	//魂　の描画
//	RECT_F rect_soul = RECT_SOUL;
//	if (m_ct_gauge.NowValue >= 50)
//	{
//		RECT_F rect_rainbow = RECT_RAINBOW;
//		rect_rainbow.m_y = m_ct_rainbow.NowValue * RECT_RAINBOW.m_height;
////		Draw::Draw(tex_RESULT_RAINBOW, PARAMATER_RAINBOW_POS.x, PARAMATER_RAINBOW_POS.y, rect_rainbow);
//
//
//		rect_soul.m_x = RECT_SOUL.m_width * 2.0f;
//
//		RECT_F rect_fire = RECT_FIRE;
//		rect_fire.m_x = RECT_FIRE.m_width * m_ct_fire.NowValue;
//		Draw::Draw(tex_RESULT_FIRE, x + PARAM_SOUL_FIRE_OFFSET.x, y + PARAM_SOUL_FIRE_OFFSET.y, rect_fire);
//	}
//
//	else if (m_ct_gauge.NowValue >= 40)
//		rect_soul.m_x = RECT_SOUL.m_width * 1.0f;
//
//
//	Draw::Draw(tex_RESULT_SOUL, x + PARAM_SOUL_OFFSET.x, y + PARAM_SOUL_OFFSET.y, rect_soul);

	CObjNormaGauge* gauge = (CObjNormaGauge*)Objs::GetObj(OBJ_GAUGE);
	gauge->GaugeDraw(m_ct_gauge.NowValue * 2, PARAMATER_GAUGE_POS.x, PARAMATER_GAUGE_POS.y, 0.7f, 0.7f, 0, false);

	for (int i = 0; i < JUDGE_COUNT + 1; i++)
	{
		if (!m_ani_judge_num[i].GetStart())break;
		float scale = m_ani_judge_num[i].GetValue().scale_x;

		float x = PARAM_JUDGE_NUM_POS[i].x - (RECT_NUM.m_width * scale - RECT_NUM.m_width) / 2;
		float y = PARAM_JUDGE_NUM_POS[i].y - (RECT_NUM.m_height * scale - RECT_NUM.m_height)/ 2;


		Draw::SetScaleX(tex_RESULT_NUMBER,scale);
		Draw::SetScaleY(tex_RESULT_NUMBER,scale);

		switch (i)
		{
		case JUST:
			m_judge_num.Draw(m_score.judge[JUST], x, y, NUM_PADDING);
			break;
		case HIT:
			m_judge_num.Draw(m_score.judge[HIT], x, y, NUM_PADDING);
			break;
		case MISS:
			m_judge_num.Draw(m_score.judge[MISS], x, y, NUM_PADDING);
			break;
		case ROLL:
			m_judge_num.Draw(m_score.judge[ROLL], x, y, NUM_PADDING);
			break;
		case 4://最大コンボ数
			m_judge_num.Draw(m_score.max_combo, x, y, NUM_PADDING);
			break;
		}
	}

	if (m_ani_score_num.GetStart())
	{
		float scale = m_ani_score_num.GetValue().scale_x;
		float x = PARAM_SCORE_NUM_POS.x - (RECT_SCORE_NUM.m_width * scale - RECT_SCORE_NUM.m_width) / 2;
		float y = PARAM_SCORE_NUM_POS.y - (RECT_SCORE_NUM.m_height * scale - RECT_SCORE_NUM.m_height) / 2;


		Draw::SetScaleX(tex_RESULT_SCORE_NUMBER, scale);
		Draw::SetScaleY(tex_RESULT_SCORE_NUMBER, scale);

		m_score_num.Draw(m_score.score, x, y, SCORE_NUM_PADDING);
	}
	if (m_ani_score_rank.GetStart() && m_score.score_rank > E_SCORE_RANK::RANK_NONE)
	{
		float scale = m_ani_score_rank.GetValue().scale_x;
		float x = PARAM_SCORE_RANK_POS.x;
		float y = PARAM_SCORE_RANK_POS.y;
		RECT_F rect_rank = RECT_RANK;
		rect_rank.m_x = RECT_RANK.m_width * (int)m_score.score_rank;



		Draw::SetScaleX(tex_RESULT_RANK, scale);
		Draw::SetScaleY(tex_RESULT_RANK, scale);
		Draw::SetOpacity(tex_RESULT_RANK, m_ani_score_rank.GetValue().opacity);

		Draw::CenterDraw(tex_RESULT_RANK, x, y, rect_rank);
	}
	if (m_ani_crown.GetStart() && m_score.crown > E_CROWN::CROWN_NONE)
	{
		float scale = m_ani_crown.GetValue().scale_x;
		float x = PARAM_CROWN_POS.x;
		float y = PARAM_CROWN_POS.y;
		RECT_F rect_crown = RECT_CROWN;
		rect_crown.m_x = RECT_CROWN.m_width * (int)m_score.crown;



		Draw::SetScaleX(tex_RESULT_CROWN, scale);
		Draw::SetScaleY(tex_RESULT_CROWN, scale);
		Draw::SetOpacity(tex_RESULT_CROWN, m_ani_crown.GetValue().opacity);

		Draw::CenterDraw(tex_RESULT_CROWN, x, y, rect_crown);
	}
	m_fade_in.ActionDraw();
	m_fade_out.ActionDraw();
}

void CObjResult::Decide()
{
	if (!m_ct_result.GetEndValueReached() && m_ct_gauge.GetProgress())
	{
		Audio::Start(se_DON);
		Audio::Stop(se_RESULT_GAUGE);
		m_ct_result.NowValue = m_ct_result.EndValue;
		m_ct_gauge.NowValue = m_ct_gauge.EndValue;
		for (int i = 0; i < 5; i++)
		{
			if (!m_ani_judge_num[i].GetStart())
				m_ani_judge_num[i].Start();
		}
		if (!m_ani_score_num.GetStart())
		{
			m_ani_score_num.Start();
		}
		if (!m_ani_score_rank.GetStart())
		{
			m_ani_score_rank.Start();
		}
		if (!m_ani_crown.GetStart() )
		{
			m_ani_crown.Start();
		}
	}
	if (m_ct_wait.GetProgress() && !m_ct_wait.GetEndValueReached())
	{
		Audio::Start(se_DON);
		m_ct_wait.NowValue = m_ct_wait.EndValue;
	}
}

void CObjResult::ScoreSave()
{
	ST_SCORE_DATA score = m_best_score[((UserData*)Save::GetData())->m_now_select_diffculty[0]];

	//スコアの更新
	if (m_score.score > score.score)
	{
		score.score = m_score.score;
		for (int i = 0; i < JUDGE_COUNT; i++)
			score.judge[i] = m_score.judge[i];
		score.max_combo = m_score.max_combo;
		score.st_option = m_score.st_option;
	}
	//王冠の更新
	if (m_score.crown > score.crown)
	{
		//もともと王冠があった場合
		if (score.crown > E_CROWN::CROWN_NONE)
		{
			MusicGame::g_player_status.crown_count[USER_DATA->m_now_select_diffculty[0]][(int)score.crown]--;
		}
		score.crown = m_score.crown;
		MusicGame::g_player_status.crown_count[USER_DATA->m_now_select_diffculty[0]][(int)score.crown]++;
	}
	//スコアランクの更新
	if (m_score.score_rank > score.score_rank)
	{
		if (score.score_rank > E_SCORE_RANK::RANK_NONE)
		{
			MusicGame::g_player_status.rank_count[USER_DATA->m_now_select_diffculty[0]][(int)score.score_rank]--;
		}
		score.score_rank = m_score.score_rank;
		MusicGame::g_player_status.rank_count[USER_DATA->m_now_select_diffculty[0]][(int)score.score_rank]++;
	}

	score.playcount++;

	ScoreDataExport(score);

	MusicGame::SongSelect::g_vec_all_fumen_bar[MusicGame::g_confirm_song_id].ScoreSet(score,(E_DIFFCULTY)USER_DATA->m_now_select_diffculty[0]);
}
void CObjResult::ScoreDataImport()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);

	string str_score;
	list<string> list_str_score_command;

	//ファイルを開く
	ifstream ifs(enso->m_enso[0].m_fumen.fumen_path + SCOREFILE_STR);
	if (!ifs)
	{
		//ファイルが存在しない
		m_best_score[((UserData*)Save::GetData())->m_now_select_diffculty[0]] = m_score;
		ifs.close();
		return;
	}	
	
	for (int i = 0; i < DIFF_Count; i++)
	{
		for (int j = 0; j < MusicGame::Result::SCORE_Count; j++)
		{
			getline(ifs, str_score);

			switch (j)
			{
			case MusicGame::Result::SCORE_SCORE:
				m_best_score[i].score = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_CROWN:
				m_best_score[i].crown = (E_CROWN)atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_RANK:
				m_best_score[i].score_rank = (E_SCORE_RANK)atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_GREAT:
				m_best_score[i].judge[JUST] = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_GOOD:
				m_best_score[i].judge[HIT] = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_MISS:
				m_best_score[i].judge[MISS] = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_ROLL:
				m_best_score[i].judge[ROLL] = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_MAXCOMBO:
				m_best_score[i].max_combo = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_PLAYCOUNT:
				m_best_score[i].playcount = atoi(str_score.c_str());
				break;
			default:
				break;
			}
		}
	}
}
void CObjResult::ScoreDataExport(ST_SCORE_DATA score)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	std::ofstream writing_file;
	std::string filename = enso->m_enso[0].m_fumen.fumen_path + SCOREFILE_STR;
	writing_file.open(filename, std::ios::out);
	std::string writing_text = "";

	ST_SCORE_DATA diff_score;


	for (int i = 0; i < DIFF_Count; i++)
	{
		//現在の難易度のみ
		if (i == ((UserData*)Save::GetData())->m_now_select_diffculty[0])
		{
			diff_score = score;
		}
		else
		{
			diff_score = m_best_score[i];
		}

		for (int j = 0; j < MusicGame::Result::SCORE_Count; j++)
		{
			switch (j)
			{
			case MusicGame::Result::SCORE_SCORE:
				writing_text += to_string(diff_score.score);
				break;
			case MusicGame::Result::SCORE_CROWN:
				writing_text += to_string((int)diff_score.crown);
				break;
			case MusicGame::Result::SCORE_RANK:
				writing_text += to_string((int)diff_score.score_rank);
				break;
			case MusicGame::Result::SCORE_GREAT:
				writing_text += to_string(diff_score.judge[JUST]);
				break;
			case MusicGame::Result::SCORE_GOOD:
				writing_text += to_string(diff_score.judge[HIT]);
				break;
			case MusicGame::Result::SCORE_MISS:
				writing_text += to_string(diff_score.judge[MISS]);
				break;
			case MusicGame::Result::SCORE_ROLL:
				writing_text += to_string(diff_score.judge[ROLL]);
				break;
			case MusicGame::Result::SCORE_MAXCOMBO:
				writing_text += to_string(diff_score.max_combo);
				break;
			case MusicGame::Result::SCORE_PLAYCOUNT:
				writing_text += to_string(diff_score.playcount);
				break;
			default:
				break;
			}
			writing_text += "\n";
		}
	}
	writing_file << writing_text << std::endl;
	writing_file.close();
}