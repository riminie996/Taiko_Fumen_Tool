#include "CObjDanResultPanel.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

//初期化
void CObjDanResultPanel::Init()
{
	m_ani_statepanel_slide.Start();
	m_ani_statepanel_fade.Start();

	Audio::Start(se_DANRESULT_STATEPANEL_SLIDE);

	m_num_song_judge.SetTex(tex_DANRESULT_SONGPANEL_NUMBER, MusicGame::DanResult::RECT_DANRESULT_NUMBER.m_width, MusicGame::DanResult::RECT_DANRESULT_NUMBER.m_height);
	m_num_score.SetTex(tex_DANRESULT_SCORE_NUMBER, MusicGame::Result::RECT_SCORE_NUMBER.m_width, MusicGame::Result::RECT_SCORE_NUMBER.m_height);

	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);
	m_vec_anime.resize(dan->m_vec_dan.size());


	for (int i = 0; i < m_vec_anime.size(); i++)
	{
		//終了値を設定する
		int end = MusicGame::DanResult::DANRESULT_ACT_TIME;
		float gauge_time = 0;

		if (dan->m_vec_dan[i].m_common == true)
		{
		
			gauge_time = dan->m_vec_dan[i].GetValueToPercent(0);

			m_vec_anime[i].ct_gauge[0] = { CTimeCounter(0,gauge_time * 100,MusicGame::DanResult::DANRESULT_GAUGE_INTERVAL) };
			m_vec_anime[i].ct_gauge[0].Stop();
		}
		else
		{
			for (int j = 0; j <= dan->GetSongNumber(); j++)
			{
				float time = 0;

				time = dan->m_vec_dan[i].GetValueToPercent(j);

				m_vec_anime[i].ct_gauge[j] = { CTimeCounter(0,time * 100,MusicGame::DanResult::DANRESULT_GAUGE_INTERVAL) };
				m_vec_anime[i].ct_gauge[j].Stop();

				if (time > gauge_time)gauge_time = time;
			}
		}
		
		
		end += MusicGame::DanResult::DANRESULT_GAUGE_INTERVAL * gauge_time;
	
		

		//全体的な進行カウンターを設定
		m_vec_anime[i].ct_act = { CTimeCounter(0,end,1) };

		//アニメーションタイプを設定
		for (int j = 0; j < MusicGame::DAN_MAX_SONG; j++)
		{
			m_vec_anime[i].ani_number_appear[j].LoadData("Animation/DanResult/NumberAppear");
		}
		m_vec_anime[i].ani_fade.LoadData("Animation/DanResult/GaugeFade");
	}

	m_ani_gauge_number.LoadData("Animation/DanResult/NumberAppear");
	m_num_dan.SetTex(tex_DAN_NUMBER, MusicGame::Dan::RECT_NUMBER.m_width, MusicGame::Dan::RECT_NUMBER.m_height, 0, 0);
	m_num_dan_rainbow.SetTex(tex_DAN_NUMBER, MusicGame::Dan::RECT_NUMBER.m_width, MusicGame::Dan::RECT_NUMBER.m_height, 0, MusicGame::Dan::RECT_NUMBER.m_height);
	m_num_exam.SetTex(tex_DAN_SMALL_NUMBER, MusicGame::Dan::RECT_EXAM_NUMBER.m_width, MusicGame::Dan::RECT_EXAM_NUMBER.m_height);
	m_num_exam_triple.SetTex(tex_DANRESULT_EXAMNUMBER_TRIPLE, MusicGame::DanResult::RECT_TRIPLE_EXAMNUMBER.m_width, MusicGame::DanResult::RECT_TRIPLE_EXAMNUMBER.m_height);

}
//進行
void CObjDanResultPanel::Action()
{
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	m_ani_statepanel_slide.Action();
	m_ani_statepanel_fade.Action();
	m_ani_gauge_number.Action();
	m_ct_result_gauge.Action();
	m_ct_act.Action();

	if (m_ct_result_gauge.GetEndValueReached() && m_ct_result_gauge.GetProgress())
	{
		if (m_ct_result_gauge.NowValue < 50)
		{
			Audio::Stop(se_RESULT_GAUGE);
			Audio::Start(se_DON);
		}
		if (!m_ani_gauge_number.GetStart())
			m_ani_gauge_number.Start();

		m_ct_result_gauge.Stop();
	}

	if (system->GetInput(LEFT_DON, 0) || system->GetInput(RIGHT_DON, 0))
	{
		if (!m_ct_act.GetEndValueReached())
		{
			m_ct_act.NowValue = m_ct_act.EndValue;
			m_ct_result_gauge.NowValue = m_ct_result_gauge.EndValue;
			m_ani_statepanel_fade.End();
			m_ani_statepanel_slide.End();
			AnimeSkip();
		}
	}

}
//描画
void CObjDanResultPanel::Draw()
{
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);
	CObjDanResult* result = (CObjDanResult*)Objs::GetObj(OBJ_DANRESULT);

	int  panel_x = 0 + m_ani_statepanel_slide.GetValue().x;
	Draw::Draw(tex_DANRESULT_STATEPANEL_BG, panel_x, 0);

	Draw::SetOpacity(tex_DANRESULT_STATEPANEL, m_ani_statepanel_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_SCORE_NUMBER, m_ani_statepanel_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_SONGPANEL_NUMBER, m_ani_statepanel_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_STATEPANEL_NUMBER, m_ani_statepanel_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_GAUGE_BG, m_ani_statepanel_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_NORMAGAUGE_BG, m_ani_statepanel_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_NORMAGAUGE_BASE, m_ani_statepanel_fade.GetValue().opacity);
	Draw::SetOpacity(tex_SOUL, m_ani_statepanel_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DAN_EXAM_TYPE, m_ani_statepanel_fade.GetValue().opacity);

	Draw::Draw(tex_DANRESULT_STATEPANEL, 0, 0);
	Draw::Draw(tex_DANRESULT_GAUGE_BG, MusicGame::DanResult::GAUGE_BASE_POS.x, MusicGame::DanResult::GAUGE_BASE_POS.y, MusicGame::DanResult::RECT_GAUGE_BG);
	Draw::Draw(tex_DANRESULT_NORMAGAUGE_BG, 0, 0);
	Draw::Draw(tex_DANRESULT_NORMAGAUGE_BASE, MusicGame::DanResult::NORMAGAUGE_BASE_POS.x, MusicGame::DanResult::NORMAGAUGE_BASE_POS.y, MusicGame::Enso::RECT_GAUGE_BASE);
	Draw::Draw(tex_SOUL, MusicGame::DanResult::SOUL_POS.x, MusicGame::DanResult::SOUL_POS.y, MusicGame::Enso::RECT_SOUL);

	//スコア+判定の描画
	m_num_score.Draw(result->GetScore().score, MusicGame::DanResult::STATE_SCORE_POS.x, MusicGame::DanResult::STATE_SCORE_POS.y, MusicGame::DanResult::SCORE_NUMBER_PADDING);

	for (int i = 0; i < JUDGE_COUNT; i++)
	{
		m_num_song_judge.Draw(result->GetScore().judge[i], MusicGame::DanResult::STATE_JUDGE_POS[i].x, MusicGame::DanResult::STATE_JUDGE_POS[i].y, MusicGame::DanResult::JUDGE_NUMBER_PADDING);
	}
	m_num_song_judge.Draw(result->GetScore().max_combo, MusicGame::DanResult::STATE_COMBO_POS.x, MusicGame::DanResult::STATE_COMBO_POS.y, MusicGame::DanResult::JUDGE_NUMBER_PADDING);

	int hit =
		result->GetScore().judge[JUST] +
		result->GetScore().judge[HIT] +
		result->GetScore().judge[ROLL];
	m_num_song_judge.Draw(hit, MusicGame::DanResult::STATE_HIT_POS.x, MusicGame::DanResult::STATE_HIT_POS.y, MusicGame::DanResult::JUDGE_NUMBER_PADDING);


	for (int i = 0; i < m_ct_result_gauge.NowValue; i++)
	{
		Draw::Draw(tex_DANRESULT_NORMAGAUGE, MusicGame::DanResult::NORMAGAUGE_BASE_POS.x + i * MusicGame::DanResult::RECT_GAUGE.m_width, MusicGame::DanResult::NORMAGAUGE_BASE_POS.y, MusicGame::DanResult::RECT_GAUGE);
	}

	Draw::SetScaleX(tex_DAN_NUMBER, MusicGame::DanResult::DANRESULT_PERCENT_NUMBER_SCALE);
	Draw::SetScaleY(tex_DAN_NUMBER, MusicGame::DanResult::DANRESULT_PERCENT_NUMBER_SCALE);
	Draw::SetOpacity(tex_DAN_NUMBER, m_ani_gauge_number.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_PERCENT, m_ani_gauge_number.GetValue().opacity);

	float num_y = m_ani_gauge_number.GetValue().y;

	if ((int)result->GetScore().ct_gauge.NowValue >= 100)
	{
		Draw::SetColor(tex_DAN_NUMBER, Color::White);
		Draw::SetColor(tex_DANRESULT_PERCENT, Color::White);
		m_num_dan_rainbow.Draw((int)result->GetScore().ct_gauge.NowValue, MusicGame::DanResult::DANRESULT_PERCENT_NUMBER_POS.x, MusicGame::DanResult::DANRESULT_PERCENT_NUMBER_POS.y + num_y, MusicGame::DanResult::DANRESULT_PERCENT_NUMBER_PADDING);
		Draw::Draw(tex_DANRESULT_PERCENT, MusicGame::DanResult::DANRESULT_PERCENT_POS.x, MusicGame::DanResult::DANRESULT_PERCENT_POS.y + num_y, MusicGame::DanResult::RECT_PERCENT_GOLD);
	}
	else
	{
		COLOR number_color = { 0.5f,0.5f,0.5f };

		if ((int)result->GetScore().ct_gauge.NowValue >= dan->GetGaugeNorma())
			number_color = Color::Yellow;
		else if ((int)result->GetScore().ct_gauge.NowValue > 0)
			number_color = Color::Red;


		Draw::SetColor(tex_DAN_NUMBER, number_color);
		Draw::SetColor(tex_DANRESULT_PERCENT, number_color);
		
		m_num_dan.Draw((int)result->GetScore().ct_gauge.NowValue, MusicGame::DanResult::DANRESULT_PERCENT_NUMBER_POS.x, MusicGame::DanResult::DANRESULT_PERCENT_NUMBER_POS.y + num_y, MusicGame::DanResult::DANRESULT_PERCENT_NUMBER_PADDING);
		Draw::Draw(tex_DANRESULT_PERCENT, MusicGame::DanResult::DANRESULT_PERCENT_POS.x, MusicGame::DanResult::DANRESULT_PERCENT_POS.y + num_y, MusicGame::DanResult::RECT_PERCENT_NORMAL);

	}

	if (m_ct_act.NowValue >= MusicGame::DanResult::DANRESULT_EXAM_DELAY + m_ct_result_gauge.EndValue * MusicGame::DanResult::DANRESULT_GAUGE_INTERVAL)
	{
		for (int i = 0; i < dan->m_vec_dan.size(); i++)
		{
			int num = DrawExam(i);
			if (num == i)break;

			if (num == dan->m_vec_dan.size())
			{
				result->AnimeStart();
			}
		}
	}

}
void CObjDanResultPanel::AnimeStart()
{
	CObjDanResult* result = (CObjDanResult*)Objs::GetObj(OBJ_DANRESULT);

	if (!m_ct_act.GetProgress())
	{
		Audio::Start(se_RESULT_GAUGE);
		m_ct_act.Start(0, MusicGame::DanResult::DANRESULT_STATEPANEL_ACT_TIME, 1);
		m_ct_result_gauge.Start(0, (int)result->GetScore().ct_gauge.NowValue / 2, MusicGame::Result::GAUGE_MEMORI_TIME);
	}
}

int CObjDanResultPanel::DrawExam(int num)
{
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);
	CObjDanResult* result = (CObjDanResult*)Objs::GetObj(OBJ_DANRESULT);

	int song = dan->m_vec_dan[num].m_common == true ? 0 : dan->GetSongNumber();
	int delay = 0;

	//	DANRESULT_ACT_TIME
	if (!m_vec_anime[num].ct_act.GetProgress())
	{
		m_vec_anime[num].ct_act.Start(0, m_vec_anime[num].ct_act.EndValue, 1);
		m_vec_anime[num].ani_fade.Start();
	}

	m_vec_anime[num].ct_act.Action();
	for (int i = 0; i <= song; i++)
	{
		m_vec_anime[num].ct_gauge[i].Action();
		m_vec_anime[num].ani_number_appear[i].Action();
	}
	m_vec_anime[num].ani_fade.Action();

	delay += MusicGame::DanResult::DANRESULT_EXAM_GAUGE_DELAY;

	if (m_vec_anime[num].ct_act.NowValue >= delay)
	{
		for (int i = 0; i <= song; i++)
		{
			if (!m_vec_anime[num].ct_gauge[i].GetProgress())
			{
				m_vec_anime[num].ct_gauge[i].Start(0, m_vec_anime[num].ct_gauge[i].EndValue, MusicGame::DanResult::DANRESULT_GAUGE_INTERVAL);
			
				Audio::Stop(se_DANRESULT_GAUGE);
				Audio::Start(se_DANRESULT_GAUGE);
			}

		}
	}

	if (dan->m_vec_dan[num].m_common == true)
	{
		delay += m_vec_anime[num].ct_gauge[0].EndValue * MusicGame::DanResult::DANRESULT_GAUGE_INTERVAL;
		if (m_vec_anime[num].ct_act.NowValue >= delay)
		{
			if (!m_vec_anime[num].ani_number_appear[0].GetStart())
			{
				Audio::Start(se_DON);
				m_vec_anime[num].ani_number_appear[0].Start();
				Audio::Stop(se_DANRESULT_GAUGE);
			}
		}
	}
	else
	{
		int gauge_time = 0;
		for (int i = 0; i <= song; i++)
		{
			if (gauge_time < m_vec_anime[num].ct_gauge[i].EndValue * MusicGame::DanResult::DANRESULT_GAUGE_INTERVAL)
				gauge_time = m_vec_anime[num].ct_gauge[i].EndValue * MusicGame::DanResult::DANRESULT_GAUGE_INTERVAL;
		}

		delay += gauge_time;


		for (int i = 0; i <= song; i++)
		{
			if (i > 0)
				delay += MusicGame::DanResult::DANRESULT_NUMBER_DELAY;

			if (m_vec_anime[num].ct_act.NowValue >= delay)
			{
				if (!m_vec_anime[num].ani_number_appear[i].GetStart())
				{
					Audio::Start(se_DON);
					m_vec_anime[num].ani_number_appear[i].Start();
					Audio::Stop(se_DANRESULT_GAUGE);
				}

			}
		}
	
	}
	Draw::SetOpacity(tex_DAN_GAUGE, m_vec_anime[num].ani_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_GAUGE_BG, m_vec_anime[num].ani_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_GAUGE_BASE, m_vec_anime[num].ani_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_GAUGE_BASE_TRIPLE, m_vec_anime[num].ani_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_GAUGE_TRIPLE, m_vec_anime[num].ani_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_EXAMNUMBER_TRIPLE, m_vec_anime[num].ani_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DANRESULT_EXAMRANGE_TRIPLE, m_vec_anime[num].ani_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DAN_EXAM_NUMBER, m_vec_anime[num].ani_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DAN_EXAM_RANGE, m_vec_anime[num].ani_fade.GetValue().opacity);
	Draw::SetOpacity(tex_DAN_EXAM_TYPE, m_vec_anime[num].ani_fade.GetValue().opacity);

	//ここから条件の描画
	float x = MusicGame::DanResult::GAUGE_BASE_POS.x;
	//すでノルマゲージの分が描画されているので1つ位置をずらす。
	float y = MusicGame::DanResult::GAUGE_BASE_POS.y + (num + 1) * MusicGame::DanResult::GAUGE_BASE_HEIGHT;

	RECT_F rect_bg = dan->m_vec_dan[num].m_common == true ? MusicGame::DanResult::RECT_GAUGE_BG : MusicGame::DanResult::RECT_GAUGE_BG_TRIPLE;
	Draw::Draw(tex_DANRESULT_GAUGE_BG, x, y, rect_bg);

	RECT_F rect_type = MusicGame::Dan::RECT_EXAM_TYPE;
	rect_type.m_y = dan->m_vec_dan[num].m_type * rect_type.m_height;
	Draw::Draw(tex_DAN_EXAM_TYPE,x + MusicGame::DanResult::EXAM_TYPE_OFFSET.x, y + MusicGame::DanResult::EXAM_TYPE_OFFSET.y, rect_type);







	if (dan->m_vec_dan[num].m_common == true)
	{
		int gauge_color = 0;
		int width = 0;
		RECT_F rect_gauge = MusicGame::Dan::RECT_GAUGE[gauge_color];
		int value = 0;

		if (dan->m_vec_dan[num].m_range == MusicGame::DanC::RANGE_MORE)
		{
			width = m_vec_anime[num].ct_gauge[0].NowValue;

			if (width >= 100)
				gauge_color = MusicGame::Dan::GAUGE_CLEAR;
			else if (width >= 50)
				gauge_color = MusicGame::Dan::GAUGE_REACH;
			else
				gauge_color = MusicGame::Dan::GAUGE_NORMAL;

			value = dan->m_vec_dan[num].m_value[0];
		}
		else if (dan->m_vec_dan[num].m_range == MusicGame::DanC::RANGE_LESS)
		{
			width = 100 - m_vec_anime[num].ct_gauge[0].NowValue;

			if (width <= 40)
				gauge_color = MusicGame::Dan::GAUGE_LOW;
			else
				gauge_color = MusicGame::Dan::GAUGE_CLEAR;

			value = dan->m_vec_dan[num].m_norma[0][0] - dan->m_vec_dan[num].m_value[0];
		}


		if (width < 0.0f)width = 0.0f;
		if (width >= 100.0f) width = 100.0f;

		rect_gauge.m_width = (float)(width) * rect_gauge.m_width / 100.0f;	
		rect_gauge.m_y = gauge_color * rect_gauge.m_height;

		Draw::Draw(tex_DANRESULT_GAUGE_BASE, x + MusicGame::DanResult::GAUGE_BASE_OFFSET.x, y + MusicGame::DanResult::GAUGE_BASE_OFFSET.y);
		Draw::Draw(tex_DAN_GAUGE, x + MusicGame::DanResult::GAUGE_OFFSET.x, y + MusicGame::DanResult::GAUGE_OFFSET.y, rect_gauge);

		Draw::SetOpacity(tex_DAN_NUMBER, m_vec_anime[num].ani_number_appear[0].GetValue().opacity);


		float num_x = x + MusicGame::DanResult::DANRESULT_VALUE_NUMBER_OFFSET.x + numOfDigit(value) * MusicGame::Dan::NUMBER_PADDING;
	
		Draw::SetScaleX(tex_DAN_NUMBER, 1.0f);
		Draw::SetScaleY(tex_DAN_NUMBER, 1.0f);

		//色を変更
		Draw::SetColor(tex_DAN_NUMBER, Color::White);



		if (dan->m_vec_dan[num].GetStatus(0) == MusicGame::DanC::DANC_GOLD)
		{
			m_num_dan_rainbow.Draw(value, num_x, y + MusicGame::DanResult::DANRESULT_VALUE_NUMBER_OFFSET.y + m_vec_anime[num].ani_number_appear[0].GetValue().y, MusicGame::Dan::NUMBER_PADDING);
		}
		else
		{
			if (value <= 0)
			{
				value = 0;
				COLOR col = { 0.5f,0.5f,0.5f };
				Draw::SetColor(tex_DAN_NUMBER, col);
			}

			m_num_dan.Draw(value, num_x, y + MusicGame::DanResult::DANRESULT_VALUE_NUMBER_OFFSET.y + m_vec_anime[num].ani_number_appear[0].GetValue().y, MusicGame::Dan::NUMBER_PADDING);
		}
		//条件の描画
		m_num_exam.Draw(dan->m_vec_dan[num].m_norma[0][0], x + MusicGame::DanResult::EXAM_NUMBER_OFFSET.x, y + MusicGame::DanResult::EXAM_NUMBER_OFFSET.y, MusicGame::Dan::EXAM_NUMBER_PADDING);

		RECT_F rect_range = dan->m_vec_dan[num].m_range == MusicGame::DanC::RANGE_MORE ? MusicGame::Dan::RECT_EXAM_RANGE_MORE : MusicGame::Dan::RECT_EXAM_RANGE_LESS;
		Draw::Draw(tex_DAN_EXAM_RANGE, x + MusicGame::DanResult::EXAM_RANGE_OFFSET.x, y + MusicGame::DanResult::EXAM_RANGE_OFFSET.y, rect_range);
	}
	else
	{
		for (int j = 0; j <= song; j++)
		{
			int gauge_color = 0;
			float width = 0;
			RECT_F rect_gauge = MusicGame::DanResult::RECT_GAUGE_TRIPLE[gauge_color];
			int value = 0;

			if (dan->m_vec_dan[num].m_range == MusicGame::DanC::RANGE_MORE)
			{
				width = m_vec_anime[num].ct_gauge[j].NowValue;

				if (width >= 100)
					gauge_color = MusicGame::Dan::GAUGE_CLEAR;
				else if (width >= 50)
					gauge_color = MusicGame::Dan::GAUGE_REACH;
				else
					gauge_color = MusicGame::Dan::GAUGE_NORMAL;

				value = dan->m_vec_dan[num].m_value[j];
			}
			else if (dan->m_vec_dan[num].m_range == MusicGame::DanC::RANGE_LESS)
			{
				width = 100 - m_vec_anime[num].ct_gauge[j].NowValue;

				if (width <= 40)
					gauge_color = MusicGame::Dan::GAUGE_LOW;
				else
					gauge_color = MusicGame::Dan::GAUGE_CLEAR;

				value = dan->m_vec_dan[num].m_norma[j][0] - dan->m_vec_dan[num].m_value[j];
			}

			if (width < 0.0f)width = 0.0f;
			if (width >= 100.0f) width = 100.0f;

			rect_gauge.m_width = (width)*rect_gauge.m_width / 100.0f;
			rect_gauge.m_y = gauge_color * rect_gauge.m_height;

			Draw::Draw(tex_DANRESULT_GAUGE_BASE_TRIPLE, x + MusicGame::DanResult::GAUGE_BASE_TRIPLE_OFFSET.x + j * MusicGame::DanResult::GAUGE_BASE_TRIPLE_WIDTH, y + MusicGame::DanResult::GAUGE_BASE_TRIPLE_OFFSET.y);
			Draw::Draw(tex_DANRESULT_GAUGE_TRIPLE, x + MusicGame::DanResult::GAUGE_TRIPLE_OFFSET.x + j * MusicGame::DanResult::GAUGE_BASE_TRIPLE_WIDTH, y + MusicGame::DanResult::GAUGE_TRIPLE_OFFSET.y, rect_gauge);

			float num_x = x + MusicGame::DanResult::DANRESULT_TRIPLE_VALUE_NUMBER_OFFSET.x + numOfDigit(value) * MusicGame::DanResult::DANRESULT_TRIPLE_VALUE_PADDING
				+ j * MusicGame::DanResult::GAUGE_BASE_TRIPLE_WIDTH;

			Draw::SetScaleX(tex_DAN_NUMBER, MusicGame::DanResult::DANRESULT_TRIPLE_VALUE_SCALE);
			Draw::SetScaleY(tex_DAN_NUMBER, MusicGame::DanResult::DANRESULT_TRIPLE_VALUE_SCALE);
			Draw::SetOpacity(tex_DAN_NUMBER, m_vec_anime[num].ani_number_appear[j].GetValue().opacity);

			//色を変更
			Draw::SetColor(tex_DAN_NUMBER, Color::White);

	
			if (dan->m_vec_dan[num].GetStatus(j) == MusicGame::DanC::DANC_GOLD)
			{
				m_num_dan_rainbow.Draw(value, num_x, y + MusicGame::DanResult::DANRESULT_TRIPLE_VALUE_NUMBER_OFFSET.y + m_vec_anime[num].ani_number_appear[j].GetValue().y, MusicGame::DanResult::DANRESULT_TRIPLE_VALUE_PADDING);
			
			}
			else
			{
				if (value <= 0)
				{
					COLOR col = { 0.5f,0.5f,0.5f };
					Draw::SetColor(tex_DAN_NUMBER, col);
				}
				m_num_dan.Draw(value, num_x, y + MusicGame::DanResult::DANRESULT_TRIPLE_VALUE_NUMBER_OFFSET.y + m_vec_anime[num].ani_number_appear[j].GetValue().y, MusicGame::DanResult::DANRESULT_TRIPLE_VALUE_PADDING);
			}
			//条件の描画
			m_num_exam_triple.Draw(dan->m_vec_dan[num].m_norma[j][0], x + MusicGame::DanResult::EXAM_NUMBER_TRIPLE_OFFSET.x + j * MusicGame::DanResult::GAUGE_BASE_TRIPLE_WIDTH, y + MusicGame::DanResult::EXAM_NUMBER_TRIPLE_OFFSET.y, MusicGame::DanResult::EXAM_NUMBER_TRIPLE_PADDING);

			RECT_F rect_range = dan->m_vec_dan[num].m_range == MusicGame::DanC::RANGE_MORE ? MusicGame::DanResult::RECT_TRIPLE_EXAMRANGE_MORE : MusicGame::DanResult::RECT_TRIPLE_EXAMRANGE_LESS;
			Draw::Draw(tex_DANRESULT_EXAMRANGE_TRIPLE, x + MusicGame::DanResult::EXAM_RANGE_TRIPLE_OFFSET.x + j * MusicGame::DanResult::GAUGE_BASE_TRIPLE_WIDTH, y + MusicGame::DanResult::EXAM_RANGE_TRIPLE_OFFSET.y, rect_range);

		
		}
	}
	delay += MusicGame::DanResult::DANRESULT_ANIME_END_DELAY;
	if (m_vec_anime[num].ct_act.NowValue > delay)
		return num + 1;

	return num;
}

void CObjDanResultPanel::AnimeSkip()
{
	CObjDanResult* result = (CObjDanResult*)Objs::GetObj(OBJ_DANRESULT);

	m_ct_result_gauge.Start((int)result->GetScore().ct_gauge.NowValue / 2, (int)result->GetScore().ct_gauge.NowValue / 2, MusicGame::Result::GAUGE_MEMORI_TIME);


	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);

	for (int i = 0; i < dan->m_vec_dan.size(); i++)
	{


		int song = dan->m_vec_dan[i].m_common == true ? 0 : dan->GetSongNumber();


		if (dan->m_vec_dan[i].m_common == true)
		{

			m_vec_anime[i].ani_fade.End();
			m_vec_anime[i].ct_act.NowValue = m_vec_anime[i].ct_act.EndValue;
			m_vec_anime[i].ct_gauge[0].NowValue = m_vec_anime[i].ct_gauge[0].EndValue;
			m_vec_anime[i].ani_number_appear[0].Start();
		}
		else
		{

			for (int j = 0; j <= song; j++)
			{
				m_vec_anime[i].ani_fade.End();
				m_vec_anime[i].ct_act.NowValue = m_vec_anime[i].ct_act.EndValue;
				m_vec_anime[i].ct_gauge[j].NowValue = m_vec_anime[i].ct_gauge[j].EndValue;
				m_vec_anime[i].ani_number_appear[j].Start();
			}

		}
	}
}