#include "CObjEnsoEndEffect.h"
#include "GameHead.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"
//初期化
void CObjEnsoEndEffect::Init()
{
	for (int i = 0; i < ARRAY_LENGTH(m_tex_bachio_L); i++)
	{
		m_tex_bachio_L[i].LoadTexture("Graphics/3_Enso/9_End/Bachio/L_" + to_string(i) + ".png");
		m_tex_bachio_R[i].LoadTexture("Graphics/3_Enso/9_End/Bachio/R_" + to_string(i) + ".png");
	}
	for (int i = 0; i < ARRAY_LENGTH(m_tex_bachio_effect_L); i++)
	{
		m_tex_bachio_effect_L[i].LoadTexture("Graphics/3_Enso/9_End/Bachio/EffectL_" + to_string(i) + ".png");
		m_tex_bachio_effect_R[i].LoadTexture("Graphics/3_Enso/9_End/Bachio/EffectR_" + to_string(i) + ".png");
	}
	m_tex_cleared.LoadTexture("Graphics/3_Enso/9_End/Clear/Clear_Text.png");
	m_tex_star.LoadTexture("Graphics/3_Enso/9_End/Star.png");
	m_ani_cleared.LoadData("Animation/Enso/End/StageCleared");
	m_ani_fullcombo.LoadData("Animation/Enso/End/StageFullcombo");
	m_ani_dondafullcombo.LoadData("Animation/Enso/End/StageDondaFullcombo");
	m_default_star.LoadData("Animation/Enso/End/Star");


	for (int i = 0; i < CLEAR_TEXT_MOJI; i++)
	{
		m_ani_cleared_text[i].LoadData("Animation/Enso/End/StageClearedText");
	}
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjCharacter* chara = (CObjCharacter*)Objs::GetObj(OBJ_CHARACTER);
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);
	CObjNormaGauge* gauge = (CObjNormaGauge*)Objs::GetObj(OBJ_GAUGE);


	//
	if (((UserData*)Save::GetData())->m_now_select_diffculty[0] == DIFF_DAN)
	{
		if (dan->GetResult() == RESULT_FAILURE)
		{
			m_phase[0] = E_PHASE_ENSO_END::FAILED;
		}
		else
		{
			m_phase[0] = E_PHASE_ENSO_END::CLEARED;
			if (chara != nullptr)
				chara->Act10ComboMax(0);
		}
	}
	else
	{
		for (int i = 0; i < USER_DATA->m_player_amount; i++)
		{
			//後々難易度によって変える。
			if (enso->m_enso[i].m_score_data.ct_gauge.NowValue >= gauge->GetNorma(i) &&
				enso->m_enso[i].m_score_data.judge[MISS] == 0 &&
				enso->m_enso[i].m_score_data.judge[HIT] == 0)
			{
				m_phase[i] = E_PHASE_ENSO_END::DONDAFULLCOMBO;
				enso->m_enso[i].m_score_data.crown = E_CROWN::CROWN_DONDAFULLCOMBO;

			}
			else if (enso->m_enso[i].m_score_data.ct_gauge.NowValue >= gauge->GetNorma(i) &&
				enso->m_enso[i].m_score_data.judge[MISS] == 0)
			{
				m_phase[i] = E_PHASE_ENSO_END::FULLCOMBO;
				enso->m_enso[i].m_score_data.crown = E_CROWN::CROWN_FULLCOMBO;
			}
			else if (enso->m_enso[i].m_score_data.ct_gauge.NowValue >= gauge->GetNorma(i))
			{
				m_phase[i] = E_PHASE_ENSO_END::CLEARED;
				enso->m_enso[i].m_score_data.crown = E_CROWN::CROWN_CLEAR;
			}
			else
			{
				m_phase[i] = E_PHASE_ENSO_END::FAILED;
				enso->m_enso[i].m_score_data.crown = E_CROWN::CROWN_NONE;
			}


		}
	}
	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		switch (m_phase[i])
		{
		case E_PHASE_ENSO_END::FAILED:
			Draw::LoadImageW(L"Graphics/3_Enso/9_End/Failed/Failed_Bachio.png", tex_END_BACHIO, TEX_SIZE_64);
			Draw::LoadImageW(L"Graphics/3_Enso/9_End/Failed/Failed_Text.png", tex_END_TEXT, TEX_SIZE_64);
			m_ct_sound_delay = { CCounter(0.0f,0.0f,VOICE_FAILED_DELAY,STOP) };
			Audio::LoadAudio2(voice_END, "Sound/3_Enso/End/Failed.ogg", SOUND_TYPE::EFFECT);
			break;

		case E_PHASE_ENSO_END::CLEARED:

			m_ct_sound_delay = { CCounter(0.0f,0.0f,VOICE_CLEARED_DELAY,STOP) };
			Audio::LoadAudio2(voice_END, "Sound/3_Enso/End/Clear.ogg", SOUND_TYPE::EFFECT);
			//for (int i = 0; i < ARRAY_LENGTH(CLEARED_STAR); i++)
			//{
			//	ST_STAR star = ST_STAR(CLEARED_STAR[i][0], CLEARED_STAR[i][1], CLEARED_STAR[i][2]);
			//	star.ani = m_default_star;
			//	m_vec_star.push_back(star);
			//}

			if (chara != nullptr)
				chara->Act10Combo(i);
			break;

		case E_PHASE_ENSO_END::FULLCOMBO:
			m_tex_fullcombo_text.LoadTexture("Graphics/3_Enso/9_End/FullCombo/FullCombo_Text.png");

			Draw::LoadImageW(L"Graphics/3_Enso/9_End/Uchiwa.png", tex_END_UCHIWA, TEX_SIZE_64);
			m_ct_sound_delay = { CCounter(0.0f,0.0f,VOICE_FULLCOMBO_DELAY,STOP) };
			Audio::LoadAudio2(voice_END, "Sound/3_Enso/End/Fullcombo.ogg", SOUND_TYPE::EFFECT);

			if (chara != nullptr)
				chara->Act10Combo(i);
			break;

		case E_PHASE_ENSO_END::DONDAFULLCOMBO:
			m_tex_fullcombo_text.LoadTexture("Graphics/3_Enso/9_End/DondaFullCombo/DondaFullCombo_Text.png");
			Draw::LoadImageW(L"Graphics/3_Enso/9_End/Uchiwa.png", tex_END_UCHIWA, TEX_SIZE_64);
			Draw::LoadImageW(L"Graphics/3_Enso/9_End/DondaFullCombo/bg.png", tex_END_BG, TEX_SIZE_64);
			m_ct_sound_delay = { CCounter(0.0f,0.0f,VOICE_DONDAFULLCOMBO_DELAY,STOP) };
			Audio::LoadAudio2(voice_END, "Sound/3_Enso/End/DondaFullcombo.ogg", SOUND_TYPE::EFFECT);

			if (chara != nullptr)
				chara->Act10Combo(i);
			break;
		}
	}

	m_sound_play = true;

	first_action = true;
	m_ct_uchiwa_loop = { CTimeCounter(4,5,48) };
	m_ct_paper_in = { CCounter(0.0f,0.0f,PAPER_IN_PATTERN,STOP) };
	m_ct_paper_loop = { CCounter(0.0f,0.0f,PAPER_LOOP_PATTERN,LOOP) };

}
//進行
void CObjEnsoEndEffect::Action()
{

	m_ani_failed_bachio_L.Action();
	m_ani_failed_bachio_R.Action();
	m_ani_failed_text.Action();
	for(int i = 0;i<CLEAR_TEXT_MOJI;i++)
	m_ani_cleared_text[i].Action();
	m_ani_fullcombo_uchiwa.Action();
	m_ct_uchiwa_loop.ActionLoop();


	m_ct_sound_delay.Add(1);
	//CAnime3
	m_ani_cleared.Action();
	m_ani_fullcombo.Action();
	m_ani_dondafullcombo.Action();
	//m_ct_star.Action();
	//for (int i = 0; i < m_vec_star.size(); i++)
	//{
	//	if (!m_vec_star[i].ani.GetStart() && m_ct_star.NowValue >= m_vec_star[i].delay_ms)
	//		m_vec_star[i].ani.Start();

	//	m_vec_star[i].ani.Action();
	//}

	//Paper
	if (m_ani_fullcombo_uchiwa.GetEnd())
		m_ct_paper_in.Add(1);
	if (m_ct_paper_in.GetMaxReached())
		m_ct_paper_loop.Add(1);

	if (first_action == true)
	{
		first_action = false;
		for (int i = 0; i < USER_DATA->m_player_amount; i++)
		{
			switch (m_phase[i])
			{
			case FAILED:
				m_ani_failed_bachio_L.Start();
				m_ani_failed_bachio_R.Start();
				m_ani_failed_text.Start();
				break;
			case CLEARED:
				m_ani_cleared.Start();

				break;
			case FULLCOMBO:

				m_ani_fullcombo_uchiwa.Start();

				m_ani_fullcombo.Start();
				break;
			case DONDAFULLCOMBO:
				m_ani_dondafullcombo_bachio_L.Start();
				m_ani_dondafullcombo_bg.Start();

				//	m_ani_cleared_text_effect.Start();
				m_ani_fullcombo_uchiwa.Start();
				m_ani_fullcombo.Start();
				m_ani_dondafullcombo.Start();
				m_ani_dondafullcombo_bachio_effect.Start();
				break;
			}
		}

	}

	for (int i = 0; i < CLEAR_TEXT_MOJI; i++)
	{
		if (!m_ani_cleared_text[i].GetStart() && m_ani_cleared_text[0].GetNowFrame() >=0.040f* i)
			m_ani_cleared_text[i].Start();
	}
	if (m_ct_sound_delay.GetMaxReached() && m_sound_play == true)
	{
		m_sound_play = false;
		Audio::Start(voice_END);
	}
}
//描画
void CObjEnsoEndEffect::Draw()
{
	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		if (m_phase[i] == E_PHASE_ENSO_END::FAILED)
		{
			//RECT_F rect_bachio_L = RECT_BACHIO;
			//RECT_F rect_bachio_R = RECT_BACHIO;
			//rect_bachio_R.m_y = (int)m_ani_failed_bachio_L.GetValue().pattern * RECT_BACHIO.m_height;
			//rect_bachio_L.m_y = (int)m_ani_failed_bachio_L.GetValue().pattern * RECT_BACHIO.m_height;
			//rect_bachio_R.m_x = RECT_BACHIO.m_width;

			Draw::SetRotationZ(tex_END_TEXT, m_ani_failed_text.GetValue().rotate_z);
			Draw::SetOpacity(tex_END_TEXT, m_ani_failed_text.GetValue().opacity);
			Draw::SetOpacity(tex_END_BACHIO, m_ani_failed_bachio_L.GetValue().opacity);

			//文字の描画
			Draw::Draw(tex_END_TEXT, FAILED_TEXT_POS.x, FAILED_TEXT_POS.y);

			//バチお描画
			//Draw::SetRotationZ(tex_END_BACHIO, m_ani_failed_bachio_L.GetValue().rotate_z);
			//Draw::Draw(tex_END_BACHIO, m_ani_failed_bachio_L.GetValue().x, m_ani_failed_bachio_L.GetValue().y,rect_bachio_L);
			//Draw::SetRotationZ(tex_END_BACHIO, m_ani_failed_bachio_R.GetValue().rotate_z);
			//Draw::Draw(tex_END_BACHIO, m_ani_failed_bachio_R.GetValue().x, m_ani_failed_bachio_R.GetValue().y,rect_bachio_R);
		}
		else if (m_phase[i] == E_PHASE_ENSO_END::CLEARED)
		{

			//文字の描画
			for (int j = 0; j < CLEAR_TEXT_MOJI; j++)
			{
				RECT_N rect_text = RECT_CLEAR_TEXT;
				rect_text.m_x = RECT_CLEAR_TEXT.m_width * j;
				m_tex_cleared.m_scale_y = m_ani_cleared_text[j].GetValue().scale_y;
				m_tex_cleared.m_opacity = m_ani_cleared_text[j].GetValue().opacity;
				float y = CLEAR_TEXT_POS.y - (rect_text.m_height * m_ani_cleared_text[j].GetValue().scale_y - rect_text.m_height);
				m_tex_cleared.Draw(CLEAR_TEXT_POS.x + CLEAR_MOJI_OFFSET[j], y + i * MusicGame::P2_HEIGHT , rect_text);
			}

			//元に戻す
			m_tex_cleared.m_scale_y = 1.0f;

			m_tex_cleared.m_opacity = m_ani_cleared.GetValue("Text").opacity;
			m_tex_cleared.Draw(CLEAR_TEXT_POS.x, CLEAR_TEXT_POS.y + i * MusicGame::P2_HEIGHT, RECT_CLEAR_TEXT_ALL);

			m_tex_cleared.m_opacity = m_ani_cleared.GetValue("Light").opacity;
			m_tex_cleared.Draw(CLEAR_TEXT_POS.x, CLEAR_TEXT_POS.y + i * MusicGame::P2_HEIGHT, RECT_CLEAR_TEXT_LIGHT);
			////バチお描画
			int pattern = (int)m_ani_cleared.GetValue("BachioL").pattern;
			int L_x = BACHIO_LEFT_POS.x + m_ani_cleared.GetValue("BachioL").x;
			int R_x = BACHIO_RIGHT_POS.x - m_ani_cleared.GetValue("BachioL").x;
			int y = BACHIO_LEFT_POS.y + m_ani_cleared.GetValue("BachioL").y + i * MusicGame::P2_HEIGHT;
			m_tex_bachio_L[pattern].m_opacity = m_ani_cleared.GetValue("BachioL").opacity;
			m_tex_bachio_R[pattern].m_opacity = m_ani_cleared.GetValue("BachioL").opacity;
			m_tex_bachio_L[pattern].m_scale_x = m_ani_cleared.GetValue("BachioL").scale_x;
			m_tex_bachio_R[pattern].m_scale_x = m_ani_cleared.GetValue("BachioL").scale_x;
			m_tex_bachio_L[pattern].Draw(L_x, y, ref_Left, ref_Bottom);
			m_tex_bachio_R[pattern].Draw(R_x, y, ref_Right, ref_Bottom);
		}
		else if (m_phase[i] == E_PHASE_ENSO_END::FULLCOMBO ||
			m_phase[i] == E_PHASE_ENSO_END::DONDAFULLCOMBO)
		{
			Draw::SetOpacity(tex_END_BG, m_ani_dondafullcombo.GetValue("Background").opacity);
			Draw::Draw(tex_END_BG, BG_POS.x, BG_POS.y + i * MusicGame::P2_HEIGHT);

			RECT_F rect_paper = RECT_PAPER;

			if (m_ct_paper_in.GetMaxReached())
			{
				rect_paper.m_y = m_ct_paper_loop.NowValue * RECT_PAPER.m_height;
				Draw::Draw(tex_PAPER_LOOP, PAPER_LEFT_POS.x, PAPER_LEFT_POS.y + i * MusicGame::P2_HEIGHT, rect_paper);
				Draw::Draw(tex_PAPER_LOOP, PAPER_RIGHT_POS.x, PAPER_RIGHT_POS.y + i * MusicGame::P2_HEIGHT, rect_paper, true);
			}
			else if (m_ani_fullcombo_uchiwa.GetEnd())
			{
				rect_paper.m_y = m_ct_paper_in.NowValue * RECT_PAPER.m_height;
				Draw::Draw(tex_PAPER_IN, PAPER_LEFT_POS.x, PAPER_LEFT_POS.y + i * MusicGame::P2_HEIGHT, rect_paper);
				Draw::Draw(tex_PAPER_IN, PAPER_RIGHT_POS.x, PAPER_RIGHT_POS.y + i * MusicGame::P2_HEIGHT, rect_paper, true);
			}

			RECT_F rect_uchiwa = RECT_UCHIWA;

			if (!m_ani_fullcombo_uchiwa.GetEnd())
				rect_uchiwa.m_y = RECT_UCHIWA.m_height * (int)m_ani_fullcombo_uchiwa.GetValue().pattern;
			else
				rect_uchiwa.m_y = RECT_UCHIWA.m_height * (int)m_ct_uchiwa_loop.NowValue;
			Draw::SetOpacity(tex_END_UCHIWA, m_ani_fullcombo_uchiwa.GetValue().opacity);
			Draw::Draw(tex_END_UCHIWA, UCHIWA_LEFT_POS.x, UCHIWA_LEFT_POS.y + i * MusicGame::P2_HEIGHT, rect_uchiwa);
			rect_uchiwa.m_x = RECT_UCHIWA.m_width;
			Draw::Draw(tex_END_UCHIWA, UCHIWA_RIGHT_POS.x, UCHIWA_RIGHT_POS.y + i * MusicGame::P2_HEIGHT, rect_uchiwa);


			//文字の描画
			for (int j = 0; j < CLEAR_TEXT_MOJI; j++)
			{
				RECT_N rect_text = RECT_CLEAR_TEXT;
				rect_text.m_x = RECT_CLEAR_TEXT.m_width * j;
				m_tex_cleared.m_scale_y = m_ani_cleared_text[j].GetValue().scale_y;
				m_tex_cleared.m_opacity = m_ani_cleared_text[j].GetValue().opacity * m_ani_fullcombo.GetValue("ClearText").opacity;
				float y = CLEAR_TEXT_POS.y - (rect_text.m_height * m_ani_cleared_text[j].GetValue().scale_y - rect_text.m_height);
				m_tex_cleared.Draw(CLEAR_TEXT_POS.x + CLEAR_MOJI_OFFSET[j], y + i * MusicGame::P2_HEIGHT, rect_text);
			}
			//元に戻す
			m_tex_cleared.m_scale_y = 1.0f;


			m_tex_cleared.m_opacity = m_ani_fullcombo.GetValue("ClearTextLight").opacity;
			m_tex_cleared.Draw(CLEAR_TEXT_POS.x, CLEAR_TEXT_POS.y + i * MusicGame::P2_HEIGHT, RECT_CLEAR_TEXT_LIGHT);

			float scale_y = m_ani_fullcombo.GetValue("FullComboText").scale_y;
			float y_offset = FULLCOMBO_TEXT_OFFSET * scale_y - FULLCOMBO_TEXT_OFFSET;
			int text_x = FULLCOMBO_TEXT_POS.x + m_ani_fullcombo.GetValue("FullComboText").x;
			int text_y = FULLCOMBO_TEXT_POS.y + m_ani_fullcombo.GetValue("FullComboText").y - y_offset;
			m_tex_fullcombo_text.m_scale_y = m_ani_fullcombo.GetValue("FullComboText").scale_y;

			//エフェクト
			m_tex_fullcombo_text.m_opacity = m_ani_fullcombo.GetValue("FullComboTextEffect").opacity;
			if (m_phase[i] == E_PHASE_ENSO_END::FULLCOMBO)
				m_tex_fullcombo_text.m_blend = E_BLEND_MODE::ADDITIONALPHA;
			m_tex_fullcombo_text.Draw(text_x, text_y + i * MusicGame::P2_HEIGHT, RECT_FULLCOMBO_TEXT_EFFECT);

			//文字
			m_tex_fullcombo_text.m_blend = E_BLEND_MODE::NORMAL;
			m_tex_fullcombo_text.m_opacity = m_ani_fullcombo.GetValue("FullComboText").opacity;
			m_tex_fullcombo_text.Draw(text_x, text_y + i * MusicGame::P2_HEIGHT, RECT_FULLCOMBO_TEXT);

			//光
			m_tex_fullcombo_text.m_opacity = m_ani_fullcombo.GetValue("FullComboTextLight").opacity;
			m_tex_fullcombo_text.Draw(text_x, text_y + i * MusicGame::P2_HEIGHT, RECT_FULLCOMBO_TEXT_LIGHT);

			////バチお描画
			int pattern = (int)m_ani_fullcombo.GetValue("BachioL").pattern;
			int L_x = BACHIO_LEFT_POS.x + m_ani_fullcombo.GetValue("BachioL").x;
			int R_x = BACHIO_RIGHT_POS.x - m_ani_fullcombo.GetValue("BachioL").x;
			int y = BACHIO_LEFT_POS.y + m_ani_fullcombo.GetValue("BachioL").y + i * MusicGame::P2_HEIGHT;

			if (m_phase[i] == E_PHASE_ENSO_END::DONDAFULLCOMBO)
				pattern = (int)m_ani_dondafullcombo.GetValue("BachioL").pattern;

			m_tex_bachio_L[pattern].m_opacity = m_ani_fullcombo.GetValue("BachioL").opacity;
			m_tex_bachio_R[pattern].m_opacity = m_ani_fullcombo.GetValue("BachioL").opacity;
			m_tex_bachio_L[pattern].m_scale_x = m_ani_fullcombo.GetValue("BachioL").scale_x;
			m_tex_bachio_R[pattern].m_scale_x = m_ani_fullcombo.GetValue("BachioL").scale_x;
			m_tex_bachio_L[pattern].m_scale_y = m_ani_fullcombo.GetValue("BachioL").scale_y;
			m_tex_bachio_R[pattern].m_scale_y = m_ani_fullcombo.GetValue("BachioL").scale_y;
			m_tex_bachio_L[pattern].Draw(L_x, y, ref_Left, ref_Bottom);
			m_tex_bachio_R[pattern].Draw(R_x, y, ref_Right, ref_Bottom);

			//ばちおエフェクト描画(ドンダフルコンボのみ)
			pattern = (int)m_ani_dondafullcombo.GetValue("BachioEffect").pattern;

			m_tex_bachio_effect_L[pattern].m_opacity = m_ani_dondafullcombo.GetValue("BachioEffect").opacity;
			m_tex_bachio_effect_R[pattern].m_opacity = m_ani_dondafullcombo.GetValue("BachioEffect").opacity;
			m_tex_bachio_effect_L[pattern].Draw(L_x, y, ref_Left, ref_Bottom);
			m_tex_bachio_effect_R[pattern].Draw(R_x, y, ref_Right, ref_Bottom);
		}
	}
}
