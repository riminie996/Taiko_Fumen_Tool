#include "CObjCombo.h"
#include "GameHead.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

//初期化
void CObjCombo::Init()
{

	m_combo_num[0].SetTex(tex_COMBO, RECT_COMBO_NUM.m_width, RECT_COMBO_NUM.m_height);
	m_combo_num[1].SetTex(tex_COMBO_SILVER, RECT_COMBO_NUM.m_width, RECT_COMBO_NUM.m_height);
	m_combo_num[2].SetTex(tex_COMBO_GOLD, RECT_COMBO_NUM.m_width, RECT_COMBO_NUM.m_height);

	for (int i = 0; i < COMBO_RAME_AMOUNT; i++)
		m_ani_combo_rame[i].LoadData("Animation/Enso/ComboRame");

	m_first_action = true;

	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{

		if (MusicGame::g_mode == E_GAME_MODE::ENSO)
		{
			m_lyt_combo[i].LoadData("Layout/Enso/combo/Combo_" + to_string(i + 1) + "P");
			m_lyt_combo_text[i].LoadData("Layout/Enso/combo/ComboText_" + to_string(i + 1) + "P");
		}
		else if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
		{
			m_lyt_combo[i].LoadData("Layout/Battle/combo/Combo_" + to_string(i + 1) + "P");
			m_lyt_combo_text[i].LoadData("Layout/Battle/combo/ComboText_" + to_string(i + 1) + "P");
		}

		m_ani_combo_scale[i].LoadData("Animation/Enso/ComboScale");
	}
}
//進行
void CObjCombo::Action()
{
	if (m_first_action == true)
	{
		m_ct_rame_delay.Start(0, COMBO_RAME_LOOPTIME, 1);
		m_first_action = false;
	}
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_ani_combo_scale[i].Action();
	}
	m_ct_rame_delay.Action();
	for (int i = 0; i < COMBO_RAME_AMOUNT; i++)
	{
		if (m_ct_rame_delay.NowValue >= COMBO_RAME_DELAY[i] && !m_ani_combo_rame[i].GetStart())
			m_ani_combo_rame[i].Start();

		m_ani_combo_rame[i].ActionLoop();
	}
}
//描画
void CObjCombo::Draw()
{

	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);

	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{

		float scale_y = m_ani_combo_scale[i].GetValue(0).scale_y;
		float y_move = RECT_COMBO_NUM.m_height * scale_y - RECT_COMBO_NUM.m_height;
		Draw::SetScaleY(tex_COMBO, scale_y);
		Draw::SetScaleY(tex_COMBO_SILVER, scale_y);
		Draw::SetScaleY(tex_COMBO_GOLD, scale_y);

		E_COMBO_COLOR color = GetComboColor(i);

		int combo = enso->m_enso[i].m_score_data.combo;

		float padding = enso->m_enso[i].m_score_data.combo >= 1000 ? NUM_PADDING_1000COMBO : NUM_PADDING;
		float scale_x = enso->m_enso[i].m_score_data.combo >= 1000 ? NUM_SCALE_X_1000COMBO : 1.0f;
		float num_x = m_lyt_combo[i].GetPos().x - (RECT_COMBO_NUM.m_width * scale_x) * 0.5f + padding * (numOfDigit(combo) - 1) * 0.5f;
		if (color != E_COMBO_COLOR::NOT)//表示しない
		{
			Draw::SetScaleX(tex_COMBO_GOLD, scale_x);
			m_combo_num[(int)color].Draw(enso->m_enso[i].m_score_data.combo, num_x, m_lyt_combo[i].GetPos().y - y_move , padding);
			Draw::Draw(tex_COMBO_TEXT, m_lyt_combo_text[i].GetPos().x, m_lyt_combo_text[i].GetPos().y );
		}
		if (color >= E_COMBO_COLOR::SILVER)
		{
			for (int j = 0; j < numOfDigit(combo); j++)
			{
				for (int k = 0; k < COMBO_RAME_AMOUNT; k++)
				{
					float x = num_x + COMBO_RAME_OFFSET[k].x - (padding * j);
					float y = m_lyt_combo[i].GetPos().y + COMBO_RAME_OFFSET[k].y + m_ani_combo_rame[k].GetValue().y;

					Draw::SetOpacity(tex_COMBO_EFFECT, m_ani_combo_rame[k].GetValue().opacity);
					Draw::SetScaleX(tex_COMBO_EFFECT, m_ani_combo_rame[k].GetValue().scale_x);
					Draw::SetScaleY(tex_COMBO_EFFECT, m_ani_combo_rame[k].GetValue().scale_x);
					Draw::CenterDraw(tex_COMBO_EFFECT, x, y , RECT_COMBO_RAME);
				}
			}
		}
	}
}

void CObjCombo::Add(int player)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);

	enso->m_enso[player].m_score_data.combo++;
	if (enso->m_enso[player].m_score_data.max_combo <= enso->m_enso[player].m_score_data.combo)
	{
		enso->m_enso[player].m_score_data.max_combo = enso->m_enso[player].m_score_data.combo;
	}
	m_ani_combo_scale[player].Start();
	if (dan != nullptr)
		dan->AddSongCombo();

	//元々統一していたけど、コンボボイスを再生するために分けた。
	CObjComboBalloon* cballoon = (CObjComboBalloon*)Objs::GetObj(OBJ_COMBOBALLOON);
	if (cballoon != nullptr)
	{
		if (enso->m_enso[player].m_score_data.combo == 50)
		{
			cballoon->AnimeStart(enso->m_enso[player].m_score_data.combo, player);
		}
		if (enso->m_enso[player].m_score_data.combo % 100 == 0)
		{
			cballoon->AnimeStart(enso->m_enso[player].m_score_data.combo, player);
		}
	}
	if (enso->m_enso[player].m_score_data.combo % 10 == 0)
	{
		CObjCharacter* chara = (CObjCharacter*)Objs::GetObj(OBJ_CHARACTER);
		if (chara != nullptr)
			chara->Act10Combo(player);
	}


	if (enso->m_enso[player].m_option.voice == true)
		ComboVoiceStart(enso->m_enso[player].m_score_data.combo,player);
}
void CObjCombo::Reset(int player)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	enso->m_enso[player].m_score_data.combo = 0;

	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);
	if (dan != nullptr)
		dan->ResetSongCombo();
}

void CObjCombo::ComboVoiceStart(int combo, int player)
{
	if (player % 2 == 0)
	{
		if (combo == 50)
			Audio::Start(voice_50);
		else if (combo % 100 == 0 && combo <= 5000)
			Audio::Start(voice_50 + combo / 100);
	}
	else if (player % 2 == 1)
	{
		if (combo == 50)
			Audio::Start(voice_50_2);
		else if (combo % 100 == 0 && combo <= 5000)
			Audio::Start(voice_50_2 + combo / 100);
	}
}

E_COMBO_COLOR CObjCombo::GetComboColor(int player)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	E_COMBO_COLOR color = E_COMBO_COLOR::NORMAL;

	switch (((UserData*)Save::GetData())->m_now_select_diffculty[player])
	{
	case DIFF_EDIT:
	case DIFF_ONI:
		if (enso->m_enso[player].m_score_data.combo >= 100)
			color = E_COMBO_COLOR::GOLD;
		else if (enso->m_enso[player].m_score_data.combo >= 50)
			color = E_COMBO_COLOR::SILVER;
		else if (enso->m_enso[player].m_score_data.combo < 10)
			color = E_COMBO_COLOR::NOT;//そもそも表示しない
		break;
	case DIFF_HARD:
		if (enso->m_enso[player].m_score_data.combo >= 50)
			color = E_COMBO_COLOR::GOLD;
		else if (enso->m_enso[player].m_score_data.combo >= 30)
			color = E_COMBO_COLOR::SILVER;
		else if (enso->m_enso[player].m_score_data.combo < 10)
			color = E_COMBO_COLOR::NOT;//そもそも表示しない
		break;
	case DIFF_NORMAL:
	case DIFF_EASY:
		if (enso->m_enso[player].m_score_data.combo >= 30)
			color = E_COMBO_COLOR::GOLD;
		else if (enso->m_enso[player].m_score_data.combo >= 10)
			color = E_COMBO_COLOR::SILVER;
		else if (enso->m_enso[player].m_score_data.combo < 5)
			color = E_COMBO_COLOR::NOT;//そもそも表示しない
		break;
	default:
		if (enso->m_enso[player].m_score_data.combo >= 100)
			color = E_COMBO_COLOR::GOLD;
		else if (enso->m_enso[player].m_score_data.combo >= 50)
			color = E_COMBO_COLOR::SILVER;
		else if (enso->m_enso[player].m_score_data.combo < 10)
			color = E_COMBO_COLOR::NOT;//そもそも表示しない
		break;
	}

	return color;
}