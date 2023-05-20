#include "CObjDanC.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"

//初期化
CObjDanC::CObjDanC(vector<ST_DAN_SONG> song, vector<MusicGame::DanC> dan, int gauge_norma, int gauge_gold)
{ 
	m_vec_song = song; m_vec_dan = dan; 




	m_song_number = -1;//最初にNEXTSONGが挿入されインクリメントされて0になるようにする
	for (int i = 0; i < m_vec_song.size(); i++)
	{
		if (m_vec_song.size() > i)
		{
			Audio::LoadAudio2(bgm_SONG1 + i, m_vec_song[i].wave_file.c_str(), EFFECT);
		
		}
	}
	m_norma_gauge[0] = gauge_norma;
	m_norma_gauge[1] = gauge_gold;



	m_ct_rainbow.Start(0, MusicGame::Dan::RAINBOW_PATTERN - 1, MusicGame::Dan::RAINBOW_TIMER / MusicGame::Dan::RAINBOW_PATTERN);
}

void CObjDanC::Init()
{
	for (int i = 0; i < m_vec_dan.size(); i++)
	{
		ST_DAN_ANIME anime;
		anime.before_gauge = GAUGE_CLEAR;
		anime.ani_number_scale.LoadData("Animation/DanEnso/NumberScale");
		anime.ani_gauge_change_effect.LoadData("Animation/DanEnso/GaugeChangeEffect");
		anime.ani_gauge_effect.LoadData("Animation/DanEnso/GaugeEffectLoop");
		anime.ani_gauge_effect_fast.LoadData("Animation/DanEnso/GaugeEffectFastLoop");

		anime.ani_gauge_change_effect.Start();
		anime.ani_gauge_effect.Start();
		anime.ani_gauge_effect_fast.Start();

		m_vec_anime.push_back(anime);
	}
	for (int i = 0; i < m_vec_song.size(); i++)
	{
		ST_DAN_SONG_SCORE score;
		for (int j = 0; j < JUDGE_COUNT; j++)
			score.judge[j] = 0;
		score.score = 0;
		score.combo = 0;
		score.max_combo = 0;

		m_vec_score.push_back(score);
	}
	m_num_value.SetTex(tex_DAN_NUMBER, RECT_NUMBER.m_width, RECT_NUMBER.m_height, 0, 0);
	m_num_value_rainbow.SetTex(tex_DAN_NUMBER, RECT_NUMBER.m_width, RECT_NUMBER.m_height, 0, RECT_NUMBER.m_height);
	m_num_exam_num.SetTex(tex_DAN_EXAM_NUMBER, RECT_EXAM_NUMBER.m_width, RECT_EXAM_NUMBER.m_height);
	m_num_mini_value.SetTex(tex_DAN_NUMBER_MINI, RECT_MINI_NUMBER.m_width, RECT_MINI_NUMBER.m_height);
	m_num_mini_value_rainbow.SetTex(tex_DAN_NUMBER_MINI, RECT_MINI_NUMBER.m_width, RECT_MINI_NUMBER.m_height, 0, RECT_MINI_NUMBER.m_height);

	m_music_play = false;
	m_first_action = true;
	m_triple_show_number = 0;
}
//進行
void CObjDanC::Action()
{
	CObjDanResult* result = (CObjDanResult*)Objs::GetObj(OBJ_DANRESULT);
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);

	//更新しない
	if (result != nullptr)return;

	if (m_first_action == true)
	{
		m_first_action = false;
		wchar_t wcr[64];
		wstring str = MusicGame::StringToWString(enso->m_enso[0].m_fumen.fumen_path + "/../Dan_Plate.png");
		swprintf_s(wcr, L"%s", str.c_str());
		Draw::LoadImageW(wcr, tex_DAN_PLATE, TEX_SIZE_64);
	}

	for (int i = 0; i < m_vec_anime.size(); i++)
	{
		m_vec_anime[i].ani_number_scale.Action();
		m_vec_anime[i].ani_gauge_change_effect.Action();
		m_vec_anime[i].ani_gauge_effect.ActionLoop();
		m_vec_anime[i].ani_gauge_effect_fast.ActionLoop();
	}
	m_ani_exam_gauge_fade.Action();
	m_ani_exam_number_fade.Action();

	m_ct_music_delay.Action();
	m_ani_nextsong_screen.Action();
	m_ct_triple_change_delay.Action();

	m_ct_rainbow.ActionLoop();


	int song = GetSongNumber();
	if (m_vec_song[song].music_start_time <= enso->m_enso[0].GetNowTime() && m_music_play == false)
	{
		m_music_play = true;

		if (m_song_number < MusicGame::DAN_MAX_SONG)
		{
			Audio::Start(bgm_SONG1 + m_song_number);

			//演奏タイマーをリセットする
			enso->m_enso[0].SetTime(m_vec_song[song].music_start_time);
		}
	}

	if (m_ct_triple_change_delay.GetEndValueReached())
	{
		CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
		CObjTitlePanel* title = (CObjTitlePanel*)Objs::GetObj(OBJ_TITLEPANEL);
		title->SetTitleString(m_vec_song[m_triple_show_number].title, m_vec_song[m_triple_show_number].genre);

		if (m_triple_show_number != GetSongNumber())
		{
		

			system->AddSongNumber();
			m_triple_show_number = GetSongNumber();
			
			Update();
		}
	}
}
//描画
void CObjDanC::Draw()
{
	float screen_x = m_ani_nextsong_screen.GetValue().x;
	Draw::Draw(tex_DAN_SCREEN, DAN_SCREEN_OFFSET.x - screen_x, DAN_SCREEN_OFFSET.y,RECT_SCREEN_LEFT);
	Draw::Draw(tex_DAN_SCREEN, DAN_SCREEN_OFFSET.x + screen_x + RECT_SCREEN_LEFT.m_width, DAN_SCREEN_OFFSET.y,RECT_SCREEN_RIGHT);

	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	if (enso == nullptr)return;


	int notes_max = enso->m_enso[0].m_fumen.notes_count[BRANCH_NONE];


	int notes_remain = notes_max -
		enso->m_enso[0].m_score_data.judge[JUST] -
		enso->m_enso[0].m_score_data.judge[HIT] -
		enso->m_enso[0].m_score_data.judge[MISS];

	int song = m_triple_show_number;

	int song_notes_max = m_vec_song[song].notes_count[BRANCH_NONE];
	int song_notes_remain = m_vec_song[song].notes_count[BRANCH_NONE] -
		m_vec_score[song].judge[JUST] -
		m_vec_score[song].judge[HIT] -
		m_vec_score[song].judge[MISS];

	//背景の描画
	Draw::Draw(tex_DAN_BACKGROUND, 0, 0);

	Draw::SetOpacity(tex_DAN_EXAM_RANGE, 1.0f);
	Draw::SetOpacity(tex_DAN_EXAM_NUMBER, 1.0f);

	Draw::Draw(tex_DAN_GAUGE_ASSIGNMENT, GAUGE_ASSIGNMENT_POS.x + (int)((m_norma_gauge[0] - 1) / 2) * GAUGE_MEMORI_WIDTH, GAUGE_ASSIGNMENT_POS.y);
	m_num_exam_num.Draw(m_norma_gauge[0], GAUGE_ASSIGNMENT_NUMBER_POS.x + (int)((m_norma_gauge[0] - 1) / 2) * GAUGE_MEMORI_WIDTH, GAUGE_ASSIGNMENT_NUMBER_POS.y, EXAM_NUMBER_PADDING);

	for (int i = 0; i < m_vec_dan.size(); i++)
	{
		int song_num = m_vec_dan[i].m_common == true ? 0 : song;

		float exam_opacity = 1.0f;
		float gauge_opacity = 1.0f;

		//1曲個別の条件の場合、アニメーションを行う
		if (m_vec_dan[i].m_common == false && GetSongNumber() > 0)
		{
			exam_opacity = m_ani_exam_number_fade.GetValue().opacity;
			gauge_opacity = m_ani_exam_gauge_fade.GetValue().opacity;
		}

		//透明度変更処理
		Draw::SetOpacity(tex_DAN_EXAM_RANGE, exam_opacity);
		Draw::SetOpacity(tex_DAN_EXAM_NUMBER, exam_opacity);
		Draw::SetOpacity(tex_DAN_GAUGE_TRIPLE, gauge_opacity);
		Draw::SetOpacity(tex_DAN_NUMBER, gauge_opacity);
		Draw::SetOpacity(tex_DAN_GAUGE_BASE_MINI, gauge_opacity);
		Draw::SetOpacity(tex_DAN_GAUGE_MINI, gauge_opacity);
		Draw::SetOpacity(tex_DAN_NUMBER_MINI, gauge_opacity);



		//ゲージの土台を描画。
		if (m_vec_dan[i].m_common == true)
		{
			Draw::SetOpacity(tex_DAN_GAUGE, 1.0f);
			Draw::Draw(tex_DAN_GAUGE_BASE, GAUGE_BASE_POS.x, GAUGE_BASE_POS.y + i * GAUGE_BASE_HEIGHT, RECT_GAUGE_BASE);
			Draw::Draw(tex_DAN_GAUGE, GAUGE_BASE_POS.x + GAUGE_OFFSET.x, GAUGE_BASE_POS.y + GAUGE_OFFSET.y + i * GAUGE_BASE_HEIGHT, RECT_GAUGE_FLUSH);
		}
		else
		{
			RECT_F rect_base = RECT_GAUGE_FLUSH;
			rect_base.m_width = GAUGE_TRIPLE_WIDTH;
			Draw::Draw(tex_DAN_GAUGE_BASE, GAUGE_BASE_POS.x, GAUGE_BASE_POS.y + i * GAUGE_BASE_HEIGHT, RECT_GAUGE_BASE_TRIPLE);
			Draw::Draw(tex_DAN_GAUGE_TRIPLE, GAUGE_BASE_POS.x + GAUGE_OFFSET.x, GAUGE_BASE_POS.y + GAUGE_OFFSET.y + i * GAUGE_BASE_HEIGHT, rect_base);
		}
		//条件の描画。
		RECT_F rect_type = RECT_EXAM_TYPE;
		rect_type.m_y = m_vec_dan[i].m_type * RECT_EXAM_TYPE.m_height;
		Draw::Draw(tex_DAN_EXAM_TYPE, GAUGE_BASE_POS.x + EXAM_TYPE_OFFSET.x, GAUGE_BASE_POS.y + EXAM_TYPE_OFFSET.y + i * GAUGE_BASE_HEIGHT, rect_type);

		//以上 / 未満の描画
		RECT_F rect_range = RECT_EXAM_RANGE_MORE;
		if (m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_MORE)
			;
		else
			rect_range = RECT_EXAM_RANGE_LESS;
		Draw::Draw(tex_DAN_EXAM_RANGE, GAUGE_BASE_POS.x + EXAM_RANGE_OFFSET.x, GAUGE_BASE_POS.y + EXAM_RANGE_OFFSET.y + i * GAUGE_BASE_HEIGHT, rect_range);

		//条件の数字を描画
		m_num_exam_num.Draw(m_vec_dan[i].m_norma[song_num][0], GAUGE_BASE_POS.x + EXAM_NUMBER_OFFSET.x, GAUGE_BASE_POS.y + EXAM_NUMBER_OFFSET.y + i * GAUGE_BASE_HEIGHT, EXAM_NUMBER_PADDING);

		//ゲージの色を決定する
		E_DAN_GAUGE_COLOR gauge_color = m_vec_anime[i].before_gauge;

		//以上
		if (m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_MORE)
		{
			if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_PINCH)
				gauge_color = GAUGE_LOW;
			else if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_GOLD)
				gauge_color = GAUGE_RAINBOW;
			else if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_CLEAR)
				gauge_color = GAUGE_CLEAR;
			else if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_REACH)
			{
				if (m_vec_dan[i].GetValueToPercent(song_num) >= 0.5f)
					gauge_color = GAUGE_REACH;
				else
					gauge_color = GAUGE_NORMAL;
			}
		}
		//未満
		else// if(m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_LESS)
		{
			if (notes_remain == 0 || (song_notes_remain == 0 && m_vec_dan[i].m_common == false))
			{
				if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_GOLD)
					gauge_color = GAUGE_RAINBOW;
				else if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_CLEAR)
					gauge_color = GAUGE_CLEAR;

			}
			//0の場合は強制的にクリア
			else if (m_vec_dan[i].m_value[song_num] == 0)
			{
				gauge_color = GAUGE_CLEAR;
			}
			//値が5未満、または20%以下の時、強制的に点滅ゲージにする
			else if (m_vec_dan[i].m_norma[song_num][0] - m_vec_dan[i].m_value[song_num] < 5 || 1.0f - m_vec_dan[i].GetValueToPercent(song_num) <= 0.2f)
			{
				gauge_color = GAUGE_LOW;
			}
			//else if ((float)notes_remain / (float)notes_max < 0.04f || 
			//	((float)song_notes_remain / (float)song_notes_max < 0.04f && m_vec_dan[i].m_common == false))
			//{
			//	if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_GOLD)
			//		gauge_color = GAUGE_CLEAR;
			//	else if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_CLEAR)
			//		gauge_color = GAUGE_REACH;
			//}
			else
			{
				if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_GOLD)
					gauge_color = GAUGE_CLEAR;
				else if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_CLEAR)
				{
					if (1.0f - m_vec_dan[i].GetValueToPercent(song_num) <= 0.4f)
						gauge_color = GAUGE_LOW;
					else
						gauge_color = GAUGE_REACH;
				}
			}
		}
		//ゲージの描画。
		RECT_F rect_gauge = RECT_GAUGE[gauge_color];
		RECT_F rect_gauge_loop = gauge_color != GAUGE_LOW ? RECT_GAUGE_EFFECT : RECT_GAUGE_FLUSH;
		RECT_F rect_gauge_effect = RECT_GAUGE_EFFECT;
		RECT_F rect_gauge_rainbow = RECT_GAUGE[0];

		int gauge_tex = tex_DAN_GAUGE;
		
		if (m_vec_dan[i].m_common == false)
		{
			gauge_tex = tex_DAN_GAUGE_TRIPLE;

			rect_gauge.m_width = GAUGE_TRIPLE_WIDTH;
		}
		float width = 0.0f;
		//描画する幅を決定
		if (m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_MORE)
			width = (int)(m_vec_dan[i].GetValueToPercent(song_num) * 100.0f) * rect_gauge.m_width / 100.0f;
		else// if(m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_LESS)gaugr
			width = (int)(100.0f - m_vec_dan[i].GetValueToPercent(song_num) * 100.0f)  * rect_gauge.m_width / 100.0f;

		
		if (width >= rect_gauge.m_width)width = rect_gauge.m_width;

		rect_gauge.m_width = width;
		rect_gauge_effect.m_width = width;
		rect_gauge_loop.m_width = width;
		rect_gauge_rainbow.m_width = width;

		//達成失敗している場合はゲージの描画はしない
		if (m_vec_dan[i].GetStatus(song_num) != MusicGame::DanC::DANC_FAILED)
		{

			if (m_vec_anime[i].before_gauge != gauge_color)
			{
				m_vec_anime[i].before_gauge = gauge_color;
				m_vec_anime[i].ani_gauge_change_effect.Start();
			}
			Draw::SetOpacity(gauge_tex, gauge_opacity);
			Draw::Draw(gauge_tex, GAUGE_BASE_POS.x + GAUGE_OFFSET.x, GAUGE_BASE_POS.y + GAUGE_OFFSET.y + i * GAUGE_BASE_HEIGHT, rect_gauge);

			int effect_speed = 0;
			//ゲージエフェクトの描画
			if (gauge_color == GAUGE_RAINBOW)
			{
				;//エフェクトの描画しない
			}
			else if (gauge_color == GAUGE_LOW)
			{
				//以上
				if (m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_MORE)
				{
					if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_PINCH)
						effect_speed = 1;
				}
				//未満
				else// if(m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_LESS)
				{
					if (m_vec_dan[i].m_norma[song_num][0] - m_vec_dan[i].m_value[song_num] < 5 || 1.0f - m_vec_dan[i].GetValueToPercent(song_num) <= 0.2f)
						effect_speed = 1;

				}
			}
			else if (m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_MORE)
			{
				if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_CLEAR)
				{
					int diff = m_vec_dan[i].m_norma[song_num][1] - m_vec_dan[i].m_norma[song_num][0];
					float percent = (float)(m_vec_dan[i].m_value[song_num] - m_vec_dan[i].m_norma[song_num][0]) / diff;

					if (percent >= 0.70f)
						effect_speed = 2;
					else if (percent >= 0.40f)
						effect_speed = 1;
				}
				else if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_REACH)
				{
					if (m_vec_dan[i].GetValueToPercent(song_num) >= 0.95f)
						effect_speed = 1;
				}
			}
			else// if(m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_LESS)
			{
				if (m_song_number + 1 >= m_vec_song.size() || m_vec_dan[i].m_common == false)
				{
					float percent_remain = m_vec_dan[i].m_common == true ? 
						(float)notes_remain / (float)notes_max:
						(float)song_notes_remain / (float)song_notes_max;

					if (notes_remain == 0 || song_notes_remain == 0)
						effect_speed = 0;
					else if (percent_remain <= 0.02f)
						effect_speed = 2;
					else if (percent_remain <= 0.04f)
						effect_speed = 1;
				}
			}

			switch (effect_speed)
			{
			case 0:
				Draw::SetOpacity(gauge_tex, 0.0f);
				break;
			case 1:
				Draw::SetOpacity(gauge_tex, m_vec_anime[i].ani_gauge_effect.GetValue().opacity);
				break;
			case 2:
				Draw::SetOpacity(gauge_tex, m_vec_anime[i].ani_gauge_effect_fast.GetValue().opacity);
				break;
			}

			Draw::Draw(gauge_tex, GAUGE_BASE_POS.x + GAUGE_OFFSET.x, GAUGE_BASE_POS.y + GAUGE_OFFSET.y + i * GAUGE_BASE_HEIGHT, rect_gauge_loop);
			
			if (gauge_color == GAUGE_RAINBOW)
			{
				rect_gauge_rainbow.m_y = m_ct_rainbow.NowValue * rect_gauge_rainbow.m_height;
				Draw::Draw(tex_DAN_RAINBOW, GAUGE_BASE_POS.x + GAUGE_OFFSET.x, GAUGE_BASE_POS.y + GAUGE_OFFSET.y + i * GAUGE_BASE_HEIGHT, rect_gauge_rainbow);
			}
		}


		//ゲージ変化エフェクトの描画
		Draw::SetOpacity(gauge_tex, m_vec_anime[i].ani_gauge_change_effect.GetValue().opacity);
		Draw::Draw(gauge_tex, GAUGE_BASE_POS.x + GAUGE_OFFSET.x, GAUGE_BASE_POS.y + GAUGE_OFFSET.y + i * GAUGE_BASE_HEIGHT, rect_gauge_effect);

		//数字の描画。
		int value = m_vec_dan[i].m_range == m_vec_dan[i].RANGE_MORE ? 
			m_vec_dan[i].m_value[song_num] : 
			m_vec_dan[i].m_norma[song_num][0] - m_vec_dan[i].m_value[song_num];

		if (value < 0)value = 0;

		float y_move = RECT_NUMBER.m_height * m_vec_anime[i].ani_number_scale.GetValue().scale_y - RECT_NUMBER.m_height;
		Draw::SetScaleY(tex_DAN_NUMBER, m_vec_anime[i].ani_number_scale.GetValue().scale_y);

		Draw::SetColor(tex_DAN_NUMBER, Color::White);

		if (gauge_color == GAUGE_RAINBOW)
		{
			m_num_value_rainbow.Draw(value, GAUGE_BASE_POS.x + NUMBER_OFFSET.x + numOfDigit(value) * NUMBER_PADDING, GAUGE_BASE_POS.y + NUMBER_OFFSET.y + i * GAUGE_BASE_HEIGHT - y_move, NUMBER_PADDING);
		}
		else 
		{
			if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_FAILED || value <= 0)
			{
				COLOR col = { 0.5f,0.5f,0.5f };
				Draw::SetColor(tex_DAN_NUMBER, col);
			}
			m_num_value.Draw(value, GAUGE_BASE_POS.x + NUMBER_OFFSET.x + numOfDigit(value) * NUMBER_PADDING, GAUGE_BASE_POS.y + NUMBER_OFFSET.y + i * GAUGE_BASE_HEIGHT - y_move, NUMBER_PADDING);
		}

		//達成失敗　文字
		if (m_vec_dan[i].GetStatus(song_num) == MusicGame::DanC::DANC_FAILED)
		{
			Draw::Draw(tex_DAN_FAILED, GAUGE_BASE_POS.x + GAUGE_OFFSET.x, GAUGE_BASE_POS.y + GAUGE_OFFSET.y + i * GAUGE_BASE_HEIGHT, RECT_FAILED);
		}

		if (m_vec_dan[i].m_common == false)
		{
			for (int j = 0; j < m_triple_show_number; j++)
			{
				int num = j;

				float x = GAUGE_BASE_POS.x + MINI_GAUGE_BASE_OFFSET.x;
				float y = GAUGE_BASE_POS.y + MINI_GAUGE_BASE_OFFSET.y + i * GAUGE_BASE_HEIGHT+  num * GAUGE_BASE_MINI_HEIGHT;
				Draw::Draw(tex_DAN_GAUGE_BASE_MINI,x, y);
				
				x = GAUGE_BASE_POS.x + MINI_GAUGE_OFFSET.x;
				y = GAUGE_BASE_POS.y + MINI_GAUGE_OFFSET.y + i * GAUGE_BASE_HEIGHT + num * GAUGE_BASE_MINI_HEIGHT;

				float width = 0.0f;

				RECT_F rect_mini = m_vec_dan[i].GetStatus(num) == MusicGame::DanC::DANC_GOLD ?  
					RECT_GAUGE_MINI[GAUGE_RAINBOW] : RECT_GAUGE_MINI[GAUGE_CLEAR];

				int val = 0;
				//描画する幅を決定
				if (m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_MORE)
				{
					width = m_vec_dan[i].GetValueToPercent(num);
					val = m_vec_dan[i].m_value[num];
				}

				else// if(m_vec_dan[i].m_range == MusicGame::DanC::E_DAN_RANGE::RANGE_LESS)
				{
					width = 1.0f - m_vec_dan[i].GetValueToPercent(num);
					val = m_vec_dan[i].m_norma[num][0] - m_vec_dan[i].m_value[num];
				}
				if (width > 1.0f)width = 1.0f;
				if (width < 0.0f)width = 0.0f;

				rect_mini.m_width = width * rect_mini.m_width;

				Draw::Draw(tex_DAN_GAUGE_MINI,x, y, rect_mini);

				if (val < 0)val = 0;

				
				x = GAUGE_BASE_POS.x + MINI_NUMBER_OFFSET.x + numOfDigit(val) * NUMBER_MINI_PADDING;
				y = GAUGE_BASE_POS.y + MINI_NUMBER_OFFSET.y + i * GAUGE_BASE_HEIGHT + num * GAUGE_BASE_MINI_HEIGHT;

				if (m_vec_dan[i].GetStatus(num) == MusicGame::DanC::DANC_GOLD)
				{
					m_num_mini_value_rainbow.Draw(val, x, y, NUMBER_MINI_PADDING);
				}
				else
				{
					m_num_mini_value.Draw(val, x, y, NUMBER_MINI_PADDING);
				}
			}

		}
	}


	Draw::CenterDraw(tex_DAN_PLATE, DAN_PLATE_POS.x, DAN_PLATE_POS.y);

	//デバッグ用　1曲ごとの判定数を表示
	//m_num_exam_num.Draw(song_notes_remain, 64, 0, 16);
	//m_num_exam_num.Draw(m_vec_song[GetSongNumber()].roll_remain, 64, 30, 16);
	//m_num_exam_num.Draw(enso->GetRollRemain(), 64, 60, 16);
	//m_num_exam_num.Draw(m_vec_score[song].judge[MISS], 64, 90, 16);
	//m_num_exam_num.Draw(m_vec_score[song].judge[ROLL], 64, 120, 16);
	//m_num_exam_num.Draw(m_vec_score[song].combo, 64, 150, 16);
	//m_num_exam_num.Draw(m_vec_score[song].max_combo, 64, 180, 16);
	//m_num_exam_num.Draw(m_vec_score[song].score, 64, 210, 16);
	//m_num_exam_num.Draw(m_vec_song[song].roll_remain, 64, 240, 16);
	//m_num_exam_num.Draw(m_vec_song[song].roll_time * 100, 64, 270, 16);
}

void CObjDanC::NextSong()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjTitlePanel* title = (CObjTitlePanel*)Objs::GetObj(OBJ_TITLEPANEL);

	if (GetFailure() == true)
	{

		enso->EnsoStop();
			return;
	}
	
	//次の曲へ
	title->DisableShowing();

	m_song_number++;


	enso->m_enso[0].m_score_add = m_vec_song[m_song_number].score_add;

	m_ct_music_delay.Start(0, MusicGame::DAN_NEXTSONG_TIME, 1);
	m_music_play = false;

	Audio::Start(se_DAN_NEXTSONG);

	m_ani_nextsong_screen.Start();
	m_ani_exam_gauge_fade.Start();
	m_ani_exam_number_fade.Start();

	m_ct_triple_change_delay.Start(0, NEXTSONG_SHOW_CHANGE_TIME, 1);
}

void CObjDanC::Update()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	for (int i = 0; i < m_vec_dan.size(); i++)
	{
		bool is_changed = false;
		int song = m_vec_dan[i].m_common == true ? 0 : m_song_number;

		//3曲共通スコア
		if (m_vec_dan[i].m_common == true)
		{
			switch (m_vec_dan[i].m_type)
			{
			case TYPE_GAUGE:
				is_changed = m_vec_dan[i].Update(enso->m_enso[0].m_score_data.ct_gauge.NowValue, song);
				break;
			case TYPE_GREAT:
				is_changed = m_vec_dan[i].Update(enso->m_enso[0].m_score_data.judge[JUST], song);
				break;
			case TYPE_GOOD:
				is_changed = m_vec_dan[i].Update(enso->m_enso[0].m_score_data.judge[HIT], song);
				break;
			case TYPE_MISS:
				is_changed = m_vec_dan[i].Update(enso->m_enso[0].m_score_data.judge[MISS], song);
				break;
			case TYPE_SCORE:
				is_changed = m_vec_dan[i].Update(enso->m_enso[0].m_score_data.score, song);
				break;
			case TYPE_ROLL:
				is_changed = m_vec_dan[i].Update(enso->m_enso[0].m_score_data.judge[ROLL], song);
				break;
			case TYPE_HIT:
				is_changed = m_vec_dan[i].Update(enso->m_enso[0].m_score_data.judge[JUST] +
					enso->m_enso[0].m_score_data.judge[HIT] +
					enso->m_enso[0].m_score_data.judge[ROLL], song);
				break;
			case TYPE_COMBO:
				is_changed = m_vec_dan[i].Update(enso->m_enso[0].m_score_data.max_combo, song);
				break;
			default:
				break;
			}
		}
		//1曲ごとのスコア
		else
		{
			switch (m_vec_dan[i].m_type)
			{
			case TYPE_GAUGE:
				break;
			case TYPE_GREAT:
				is_changed = m_vec_dan[i].Update(m_vec_score[song].judge[JUST], song);
				break;
			case TYPE_GOOD:
				is_changed = m_vec_dan[i].Update(m_vec_score[song].judge[HIT], song);
				break;
			case TYPE_MISS:
				is_changed = m_vec_dan[i].Update(m_vec_score[song].judge[MISS], song);
				break;
			case TYPE_SCORE:
				is_changed = m_vec_dan[i].Update(m_vec_score[song].score, song);
				break;
			case TYPE_ROLL:
				is_changed = m_vec_dan[i].Update(m_vec_score[song].judge[ROLL], song);
				break;
			case TYPE_HIT:
				is_changed = m_vec_dan[i].Update(m_vec_score[song].judge[JUST] +
					m_vec_score[song].judge[HIT] +
					m_vec_score[song].judge[ROLL], song);
				break;
			case TYPE_COMBO:
				is_changed = m_vec_dan[i].Update(m_vec_score[song].max_combo, song);
				break;
			default:
				break;
			}
		}

		if (is_changed == true)m_vec_anime[i].ani_number_scale.Start();

	}
}

void CObjDanC::AddSongJudge(E_JUDGE judge)
{
	m_vec_score[m_song_number].judge[judge]++;
}
void CObjDanC::AddSongCombo()
{
	m_vec_score[m_song_number].combo++;
	if (m_vec_score[m_song_number].max_combo <= m_vec_score[m_song_number].combo)
	{
		m_vec_score[m_song_number].max_combo = m_vec_score[m_song_number].combo;
	}
}
void CObjDanC::AddSongScore(int add)
{
	m_vec_score[m_song_number].score += add;
}
ST_DAN_SONG CObjDanC::GetNowSong()
{
	 int num = m_song_number < 0 ? 0 : m_song_number; 
	 return m_vec_song[num];
}
int CObjDanC::GetSongJudge(E_JUDGE judge)
{
	int num = m_song_number < 0 ? 0 : m_song_number;
	return m_vec_score[num].judge[judge];
}
int CObjDanC::GetSongJudge(E_JUDGE judge,int song)
{
	return m_vec_score[song].judge[judge];
}
void CObjDanC::SubRollTime(float time) 
{ 
	m_vec_song[m_song_number].roll_remain--;
	m_vec_song[m_song_number].roll_time -= time;
	Update();//連打チェック
}

/// <summary>
/// 現時点で条件の達成失敗していないか調べる。
/// 失敗している場合、trueを返す。
/// </summary>
/// <returns></returns>
bool CObjDanC::GetFailure()
{
	for (int i = 0; i < m_vec_dan.size(); i++)
	{
		if (m_vec_dan[i].GetReached() == true)
		{
			return true;
		}
	}
	return false;
}

bool CObjDanC::GetGoldReached()
{
	for (int i = 0; i < m_vec_dan.size(); i++)
	{
		if (m_vec_dan[i].m_common == true)
		{
			if (m_vec_dan[i].GetStatus(0) != MusicGame::DanC::DANC_GOLD)
				return false;
		}
		else
		{
			for (int j = 0; j < m_vec_song.size(); j++)
			{
				if (m_vec_dan[i].GetStatus(j) != MusicGame::DanC::DANC_GOLD)
					return false;
			}
		}
	}
	return true;
}

E_DANRESULT_STATUS CObjDanC::GetResult()
{
	bool failed = false;
	bool gold = true;
	for (int i = 0; i < m_vec_dan.size(); i++)
	{
		int num = m_vec_dan[i].m_common == true ? 0 : GetSongNumber();

		for (int j = 0; j <= num; j++)
		{
			if (m_vec_dan[i].m_range == MusicGame::DanC::RANGE_MORE)
			{
				if (m_vec_dan[i].m_value[j] < m_vec_dan[i].m_norma[j][1])
					gold = false;

				if (m_vec_dan[i].m_value[j] < m_vec_dan[i].m_norma[j][0])
					return RESULT_FAILURE;
			}
			else //if (m_vec_dan[i].m_range == MusicGame::DanC::RANGE_LESS)
			{
				if (m_vec_dan[i].m_value[j] >= m_vec_dan[i].m_norma[j][1])
					gold = false;

				if (m_vec_dan[i].m_value[j] >= m_vec_dan[i].m_norma[j][0])
					return RESULT_FAILURE;
			}
		}

	}
	return gold == true ? RESULT_GOLDCLEARED : RESULT_CLEARED;
}