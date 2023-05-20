#include "CObjNormaGauge.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//初期化
void CObjNormaGauge::Init()
{
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_gauge_update[i] = 0;
		m_ani_gauge_update[i].LoadData("Animation/Enso/GaugeUpdateEffect");
		m_lyt_gauge_base[i].LoadData("Layout/Enso/GaugeBase_" + to_string(i + 1) + "P");
		m_lyt_gauge_line[i].LoadData("Layout/Enso/GaugeLine_" + to_string(i + 1) + "P");
		m_lyt_gauge_rainbow[i].LoadData("Layout/Enso/GaugeRainbow_" + to_string(i + 1) + "P");
		m_lyt_soul[i].LoadData("Layout/Enso/Soul_" +to_string(i+1)+ "P");
		m_lyt_soul_fire[i].LoadData("Layout/Enso/SoulFire_" + to_string(i + 1) + "P");
	}
	m_ct_fire_timer = { CTimeCounter(0,6,50) };
	m_ct_rainbow_timer = { CTimeCounter(0,8,RAINBOW_GAUGE_INTERVAL) };
	m_ct_rainbow_fade = { CTimeCounter(0,RAINBOW_GAUGE_INTERVAL,1) };
	m_ani_gauge_yellow.Start();

	m_mode = GAUGE_NORMAL;

	m_ani_soul_fire.LoadData("Animation/Enso/Gauge/Fire");
	m_ani_soul.LoadData("Animation/Enso/Gauge/SoulMax");

	m_first_action = false;
	m_ani_soul.Start();
	m_ani_soul_fire.Start();
}
//進行
void CObjNormaGauge::Action()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	if (m_first_action == false)
	{
		m_first_action = true;
		if (m_mode == GAUGE_HARD)
		{
			enso->m_enso->m_score_data.ct_gauge.NowValue = 100.0f;
		}
	}
	m_ani_soul.ActionLoop();
	m_ani_soul_fire.ActionLoop();

	m_ct_fire_timer.ActionLoop();
	m_ct_rainbow_timer.ActionLoop();
	m_ct_rainbow_fade.ActionLoop();
	m_ani_gauge_yellow.ActionLoop();
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_ani_gauge_update[i].Action();
		int gauge_memori = (int)enso->m_enso[i].m_score_data.ct_gauge.NowValue / 2;
		if (gauge_memori != m_gauge_update[i])
		{
			if (gauge_memori > m_gauge_update[i])
				m_ani_gauge_update[i].Start();

			m_gauge_update[i] = gauge_memori;

		}
	}

}
//描画
void CObjNormaGauge::Draw()
{


	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);


	if (((UserData*)Save::GetData())->m_now_select_diffculty[0] != DIFF_DAN)
	{
		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		{
			GaugeDraw((int)enso->m_enso[i].m_score_data.ct_gauge.NowValue,
				P1_GAUGE_POS[i].x, P1_GAUGE_POS[i].y, 1.0f, 1.0f, i, false);

		}
	}
	else
	{
	

		RECT_N rect_base = m_lyt_gauge_base[0].GetData().rectangle;
		RECT_N rect_line = m_lyt_gauge_line[0].GetData().rectangle;
		RECT_N rect_rainbow = m_lyt_gauge_rainbow[0].GetData().rectangle;

		int gauge_x = P1_GAUGE_POS[0].x;
		int gauge_y = P1_GAUGE_POS[0].y;
		MusicGame::g_tex_gauge_base_dan.Draw(gauge_x + m_lyt_gauge_base[0].GetData().pos.x, gauge_y + m_lyt_gauge_base[0].GetData().pos.y, rect_base);

		for (int j = 0; j < (int)enso->m_enso[0].m_score_data.ct_gauge.MaxValue / 2; j++)
		{
			

			int num = (j + 1) * 2;

			RECT_F rect_base = RECT_GAUGE_RED; 
			int tex = enso->m_enso[0].m_score_data.ct_gauge.NowValue < GetNorma(0) ? tex_GAUGE : tex_GAUGE_YELLOW;

			int gauge_offset_y = 0;

				gauge_offset_y = RECT_GAUGE_RED.m_y;

			if ((int)enso->m_enso[0].m_score_data.ct_gauge.NowValue >= num)
			{
				Draw::Draw(tex, gauge_x + j * RECT_GAUGE_RED.m_width, gauge_y + gauge_offset_y, rect_base);
			}
			//////黄色ゲージ
			//if (enso->m_enso[0].m_score_data.ct_gauge.NowValue >= GetNorma(i) && num < GetNorma(i))
			//{
			//	Draw::SetOpacity(tex_GAUGE_YELLOW, m_ani_gauge_yellow.GetValue().opacity);
			//	Draw::Draw(tex_GAUGE_YELLOW, P1_GAUGE_POS[i].x + j * RECT_GAUGE_RED.m_width, P1_GAUGE_POS[i].y + gauge_offset_y, RECT_GAUGE_RED);
			//}
		}



		//ニジイロゲージ
		if (enso->m_enso[0].m_score_data.ct_gauge.NowValue >= 100)
		{
			int fade_pattern = m_ct_rainbow_timer.NowValue + 1;
			if (fade_pattern >= m_ct_rainbow_timer.EndValue)
				fade_pattern = 0;

			rect_rainbow.m_y = rect_rainbow.m_height * m_ct_rainbow_timer.NowValue;
			MusicGame::g_tex_gauge_rainbow_dan.m_opacity = 1.0f;
			MusicGame::g_tex_gauge_rainbow_dan.Draw(gauge_x + m_lyt_gauge_rainbow[0].GetData().pos.x, gauge_y + m_lyt_gauge_rainbow[0].GetData().pos.y, rect_rainbow);

			rect_rainbow.m_y = rect_rainbow.m_height * fade_pattern;
			MusicGame::g_tex_gauge_rainbow_dan.m_opacity = (float)m_ct_rainbow_fade.NowValue / (float)m_ct_rainbow_fade.EndValue;
			MusicGame::g_tex_gauge_rainbow_dan.Draw(gauge_x + m_lyt_gauge_rainbow[0].GetData().pos.x, gauge_y +m_lyt_gauge_rainbow[0].GetData().pos.y, rect_rainbow);
		}

		//ゲージアップデートエフェクト

		RECT_F rect_effect = RECT_UPDATE;

		int gauge_offset_y = 0;

			gauge_offset_y = RECT_GAUGE_RED.m_y;


		Draw::SetBlend(tex_GAUGE_UPDATE, E_BLEND_MODE::ADDITIONALPHA);
		Draw::SetOpacity(tex_GAUGE_UPDATE, m_ani_gauge_update[0].GetValue().opacity);
		Draw::Draw(tex_GAUGE_UPDATE, gauge_x + (m_gauge_update[0] - 1) * RECT_GAUGE_RED.m_width + GAUGE_EFFECT_OFFSET.x, gauge_y + GAUGE_EFFECT_OFFSET.y, rect_effect);

		//線を描画
		MusicGame::g_tex_gauge_line_dan.m_opacity = 0.25f;
		MusicGame::g_tex_gauge_line_dan.Draw(gauge_x + m_lyt_gauge_line[0].GetData().pos.x, gauge_y + m_lyt_gauge_line[0].GetData().pos.y, rect_line);

		////魂　炎
		if (enso->m_enso[0].m_score_data.ct_gauge.NowValue >= 100)
		{
			RECT_N rect_fire = m_lyt_soul_fire[0].GetSource();
			rect_fire.m_x = (int)m_ani_soul_fire.GetValue(0).pattern * rect_fire.m_width;
			MusicGame::g_tex_soul_fire.Draw(gauge_x + m_lyt_soul_fire[0].GetPos().x, gauge_y + m_lyt_soul_fire[0].GetPos().y, rect_fire);
		}
		////魂　文字
		MusicGame::g_tex_soul.m_opacity = 1.0f;
		RECT_N rect_soul = m_lyt_soul[0].GetSource();

		if (enso->m_enso[0].m_score_data.ct_gauge.NowValue >= GetNorma(0))
			rect_soul.m_y = rect_soul.m_height;

		MusicGame::g_tex_soul.Draw(gauge_x + m_lyt_soul[0].GetPos().x, gauge_y + m_lyt_soul[0].GetPos().y, rect_soul);

		if (enso->m_enso[0].m_score_data.ct_gauge.NowValue >= 100)
		{
			rect_soul.m_y = 128.0f;
			MusicGame::g_tex_soul.m_opacity = m_ani_soul.GetValue(0).opacity;
			MusicGame::g_tex_soul.Draw(gauge_x + m_lyt_soul[0].GetPos().x, gauge_y + m_lyt_soul[0].GetPos().y, rect_soul);
		}

	}


}

void CObjNormaGauge::Add(E_JUDGE judge, int player)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjCharacter* chara = (CObjCharacter*)Objs::GetObj(OBJ_CHARACTER);

	if (m_mode == GAUGE_NORMAL)
	{
		//ゲージのレート値。1.0fからこれを割った値がゲージ増加量になる。
		//n%のノーツで良をだしたらゲージがMAXになるかの値。
		float gauge_rate = GetPlusRate(player);

		float gauge_plus = 100.0f / (float)(enso->m_enso[player].m_fumen.notes_count[BRANCH_NONE] + enso->m_enso[player].m_fumen.notes_count[BRANCH_TATSUJIN]) * (1.0f / gauge_rate);
		float damage = GetDamageRate(judge, player);
		float gauge_before = enso->m_enso[player].m_score_data.ct_gauge.NowValue;


		enso->m_enso[player].m_score_data.ct_gauge.Add(gauge_plus * damage);

		if (chara != nullptr)
		{
			if (gauge_before < 100.0f && enso->m_enso[player].m_score_data.ct_gauge.NowValue >= 100.0f)
			{
				chara->ActSoulIn(player);
			}
			if (gauge_before < GetNorma(player) && enso->m_enso[player].m_score_data.ct_gauge.NowValue >= GetNorma(player))
			{
				chara->ActClearIn(player);
			}
		}
	}

	//ハードモード
	else
	{
		float gauge_rate = GetPlusRate(player);

		float gauge_plus = 100.0f / (float)(enso->m_enso[player].m_fumen.notes_count[BRANCH_NONE] + enso->m_enso[player].m_fumen.notes_count[BRANCH_TATSUJIN]) * (1.0f / gauge_rate);
		float damage = judge == JUST ? 1.0f : judge == HIT ? -0.0f : -60.0f;
		

		float gauge_before = enso->m_enso[player].m_score_data.ct_gauge.NowValue;


		enso->m_enso[player].m_score_data.ct_gauge.Add(gauge_plus * damage);

		if (chara != nullptr)
		{
			if (gauge_before < 100.0f && enso->m_enso[player].m_score_data.ct_gauge.NowValue >= 100.0f)
			{
				chara->ActSoulIn(player);
			}
			if (gauge_before < GetNorma(player) && enso->m_enso[player].m_score_data.ct_gauge.NowValue >= GetNorma(player))
			{
				chara->ActClearIn(player);
			}
		}
	}
}

int CObjNormaGauge::GetNorma(int player)
{
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);

	switch (((UserData*)Save::GetData())->m_now_select_diffculty[player])
	{
	case DIFF_EASY:
		return 60;
		break;
	case DIFF_NORMAL:
	case DIFF_HARD:
		return 70;
		break;
	case DIFF_ONI:
	case DIFF_EDIT:
		return 80;
		break;
	case DIFF_DAN:
		return dan->GetGaugeNorma();
		break;
	default:
		return 80;
		break;
	}
}

//難易度やレベルによってダメージレートを計算する。
float CObjNormaGauge::GetDamageRate(E_JUDGE judge,int player)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	int diffculty = ((UserData*)Save::GetData())->m_now_select_diffculty[player];
	int level = enso->m_enso[player].m_fumen.level[diffculty];
	float rate = 1.0f;
	
	if (judge == E_JUDGE::HIT)
	{
		switch (diffculty)
		{
		case DIFF_EASY:
		case DIFF_NORMAL:
		case DIFF_HARD:
			rate = 0.75f;
			break;
		case DIFF_ONI:
		case DIFF_EDIT:
				rate = 0.5f;
			break;
		default:
			rate = 0.5f;
			break;
		}
	}
	else if (judge == E_JUDGE::MISS)
	{
		switch (diffculty)
		{
		case DIFF_EASY:
			rate = -0.5f;
			break;
		case DIFF_NORMAL:
			if (level <= 3)
				rate = -0.5f;
			else if (level <= 4)
				rate = -0.75f;
			else
				rate = -1.0f;
			break;
		case DIFF_HARD:
			if (level <= 2)
				rate = -0.75f;
			else if (level <= 3)
				rate = -1.0f;
			else if (level <= 4)
				rate = -1.1667f;
			else
				rate = -1.25f;
			break;
		case DIFF_ONI:
		case DIFF_EDIT:
			if (level <= 7)
				rate = -1.6f;
			else
				rate = -2.0f;
			break;
		default:
			rate = -2.0f;
			break;
		}
	}

	return rate;
}

//難易度によってレートを計算する。
//レベル8まではwiki参考.
//あとは自分なりに
float CObjNormaGauge::GetPlusRate(int player)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	int diffculty = ((UserData*)Save::GetData())->m_now_select_diffculty[player];
	int level = enso->m_enso[player].m_fumen.level[diffculty];
	float rate = 1.0f;

	rate = 0.82f;

	rate += (float)level * 0.01f;

	if (diffculty == DIFF_HARD)
		rate -= 0.03f;
	else if(diffculty == DIFF_NORMAL)
			rate -= 0.06f;
	else if (diffculty == DIFF_EASY)
		rate -= 0.09f;


	return rate;
}

void CObjNormaGauge::GaugeDraw(int param,int x, int y, float scale_x, float scale_y, int player, bool filp)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	RECT_N rect_base = m_lyt_gauge_base[player].GetData().rectangle;
	RECT_N rect_line = m_lyt_gauge_line[player].GetData().rectangle;
	RECT_N rect_rainbow = m_lyt_gauge_rainbow[player].GetData().rectangle;
	int pattern = 0;
	int norma = GetNorma(player);

	switch (((UserData*)Save::GetData())->m_now_select_diffculty[player])
	{
	case DIFF_EASY:
		pattern = 2;
		break;

	case DIFF_NORMAL:
	case DIFF_HARD:
		pattern = 1;
		break;

	case DIFF_ONI:
	case DIFF_EDIT:
	default:
		pattern = 0;
		break;

	}


	rect_base.m_y = pattern * rect_base.m_height;
	rect_line.m_y = pattern * rect_line.m_height;
	rect_rainbow.m_x = pattern * rect_rainbow.m_width;

	//2P対応
	rect_base.m_x = player * rect_base.m_width;

	int base_x = x + m_lyt_gauge_base[player].GetData().pos.x * scale_x;
	int base_y = y + m_lyt_gauge_base[player].GetData().pos.y * scale_y;

	MusicGame::g_tex_gauge_base.m_flip_y = player;
	MusicGame::g_tex_gauge_base.m_scale_x = scale_x;
	MusicGame::g_tex_gauge_base.m_scale_y = scale_y;
	MusicGame::g_tex_gauge_base.Draw(base_x, base_y, rect_base);

	Draw::SetScaleX(tex_GAUGE_YELLOW, scale_x);
	Draw::SetScaleY(tex_GAUGE_YELLOW, scale_y);
	Draw::SetScaleX(tex_GAUGE, scale_x);
	Draw::SetScaleY(tex_GAUGE, scale_y);

	for (int j = 0; j < (int)enso->m_enso[player].m_score_data.ct_gauge.MaxValue / 2; j++)
	{
		int num = (j + 1) * 2;

		RECT_F rect_base = player == 0 ? RECT_GAUGE_RED : RECT_GAUGE_BLUE;

		if (num == norma)
		{
			rect_base = player == 0 ? RECT_GAUGE_NORMA : RECT_GAUGE_NORMA2;
		}
		else if (num >= (int)enso->m_enso[player].m_score_data.ct_gauge.MaxValue)
		{
			rect_base = RECT_GAUGE_LAST;
		}
		else if (num > norma)
		{
			rect_base = RECT_GAUGE_YELLOW;
		}

		int gauge_offset_y = 0;

		if (player == 0 && USER_DATA->m_player_amount <= 2 && num < norma)
			gauge_offset_y = RECT_GAUGE_RED.m_y * scale_y;

		if (param >= num)
		{
			Draw::Draw(tex_GAUGE, x + j * RECT_GAUGE_RED.m_width * scale_x, y + gauge_offset_y, rect_base);
		}
		////黄色ゲージ
		if (param >= norma && num < norma)
		{
			Draw::SetOpacity(tex_GAUGE_YELLOW, m_ani_gauge_yellow.GetValue().opacity);
			Draw::Draw(tex_GAUGE_YELLOW, x + j * RECT_GAUGE_RED.m_width * scale_x,y + gauge_offset_y, RECT_GAUGE_RED);
		}
	}

	//ゲージアップデートエフェクト

	RECT_F rect_effect = player == 0 ? RECT_UPDATE : RECT_UPDATE2;

	if (m_gauge_update[player] * 2 == norma)
	{
		rect_effect = RECT_UPDATE_NORMA;
	}
	else if (m_gauge_update[player] * 2 > norma)
	{
		rect_effect = RECT_UPDATE_CLEAR;
	}
	int gauge_offset_y = 0;

	if (player == 0 && USER_DATA->m_player_amount <= 2 && m_gauge_update[player] * 2 < norma)
		gauge_offset_y = RECT_GAUGE_RED.m_y;


	Draw::SetBlend(tex_GAUGE_UPDATE, E_BLEND_MODE::ADDITIONALPHA);
	Draw::SetOpacity(tex_GAUGE_UPDATE, m_ani_gauge_update[player].GetValue().opacity);
	Draw::Draw(tex_GAUGE_UPDATE, P1_GAUGE_POS[player].x + (m_gauge_update[player] - 1) * RECT_GAUGE_RED.m_width + GAUGE_EFFECT_OFFSET.x, P1_GAUGE_POS[player].y + GAUGE_EFFECT_OFFSET.y, rect_effect, false, player);


	//ニジイロゲージ
	if (param >= 100)
	{
		int fade_pattern = m_ct_rainbow_timer.NowValue + 1;
		if (fade_pattern > m_ct_rainbow_timer.EndValue)
			fade_pattern = 0;

		int rainbow_x = x + m_lyt_gauge_rainbow[player].GetData().pos.x * scale_x;
		int rainbow_y = y + m_lyt_gauge_rainbow[player].GetData().pos.y * scale_y;

		MusicGame::g_tex_gauge_rainbow.m_scale_x = scale_x;
		MusicGame::g_tex_gauge_rainbow.m_scale_y = scale_y;

		MusicGame::g_tex_gauge_rainbow.m_flip_y = player;

		rect_rainbow.m_y = rect_rainbow.m_height * m_ct_rainbow_timer.NowValue;
		MusicGame::g_tex_gauge_rainbow.m_opacity = 1.0f;
		MusicGame::g_tex_gauge_rainbow.Draw(rainbow_x, rainbow_y, rect_rainbow);

		rect_rainbow.m_y = rect_rainbow.m_height * fade_pattern;
		MusicGame::g_tex_gauge_rainbow.m_opacity = (float)m_ct_rainbow_fade.NowValue / (float)m_ct_rainbow_fade.EndValue;
		MusicGame::g_tex_gauge_rainbow.Draw(rainbow_x, rainbow_y, rect_rainbow);
	}

	int line_x = x + m_lyt_gauge_line[player].GetData().pos.x * scale_x;
	int line_y = y + m_lyt_gauge_line[player].GetData().pos.y * scale_y;
	
	//線を描画
	MusicGame::g_tex_gauge_line.m_flip_y = player;
	MusicGame::g_tex_gauge_line.m_opacity = 0.25f;

	MusicGame::g_tex_gauge_line.m_scale_x = scale_x;
	MusicGame::g_tex_gauge_line.m_scale_y = scale_y;
	MusicGame::g_tex_gauge_line.Draw(line_x, line_y, rect_line);
	//クリア　文字

	Draw::Draw(tex_GAUGE, x + (norma / 2 - 1) * RECT_GAUGE_RED.m_width * scale_x, P1_GAUGE_TEXT_POS[player].y, param < norma ? RECT_GAUGE_NOT_CLEAR : RECT_GAUGE_CLEAR);


	MusicGame::g_tex_soul_fire.m_scale_x = scale_x;
	MusicGame::g_tex_soul_fire.m_scale_y = scale_y;
	MusicGame::g_tex_soul.m_scale_x = scale_x;
	MusicGame::g_tex_soul.m_scale_y = scale_y;
	////魂　炎
	if (param >= 100)
	{
		RECT_N rect_fire = m_lyt_soul_fire[player].GetSource();
		rect_fire.m_x = (int)m_ani_soul_fire.GetValue(0).pattern * rect_fire.m_width;
		int fire_x = x + m_lyt_soul_fire[player].GetPos().x * scale_x;
		int fire_y = y + m_lyt_soul_fire[player].GetPos().y * scale_y;
		MusicGame::g_tex_soul_fire.Draw(fire_x, fire_y, rect_fire);
	}
	////魂　文字
	MusicGame::g_tex_soul.m_opacity = 1.0f;
	int soul_x = x + m_lyt_soul[player].GetPos().x * scale_x;
	int soul_y = y + m_lyt_soul[player].GetPos().y * scale_y;
	RECT_N rect_soul = m_lyt_soul[player].GetSource();

	if (param >= norma)
		rect_soul.m_y = rect_soul.m_height;

	MusicGame::g_tex_soul.Draw(soul_x, soul_y, rect_soul);

	if (param >= 100)
	{
		rect_soul.m_y = 128.0f;
		MusicGame::g_tex_soul.m_opacity = m_ani_soul.GetValue(0).opacity;
		MusicGame::g_tex_soul.Draw(soul_x, soul_y, rect_soul);
	}

}