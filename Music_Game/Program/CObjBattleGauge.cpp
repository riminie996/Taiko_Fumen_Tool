#include "CObjBattleGauge.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//初期化
void CObjBattleGauge::Init()
{
	for (int i = 0; i < 2; i++)
	{
		m_ani_gauge_update[i].LoadData("Animation/Enso/GaugeUpdateEffect");
		m_lyt_gauge[i].LoadData("Layout/Battle/Gauge_" + to_string(i + 1) + "P");

		m_gauge_update[i] = 50;
	}
		m_lyt_gauge_base.LoadData("Layout/Battle/GaugeBase_1P");
		m_lyt_gauge_line.LoadData("Layout/Battle/GaugeLine_1P");
		m_lyt_soul.LoadData("Layout/Battle/Soul_1P");
		m_lyt_soul_fire.LoadData("Layout/Battle/SoulFire_1P");
		m_ani_soul_fire.LoadData("Animation/Enso/Gauge/Fire");
		m_ani_soul.LoadData("Animation/Enso/Gauge/SoulMax");
	m_ct_fire_timer = { CTimeCounter(0,6,50) };
	m_ani_gauge_yellow.Start();
	m_first_action = false;

	m_tex_gauge_base.LoadTexture("Graphics/10_Battle/Gauge_Base.png");
	m_tex_gauge_line.LoadTexture("Graphics/10_Battle/Gauge_line.png");

	m_ani_soul.Start();
	m_ani_soul_fire.Start();
}
//進行
void CObjBattleGauge::Action()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjEnsoBattle* battle = (CObjEnsoBattle*)Objs::GetObj(OBJ_BATTLE);
	if (m_first_action == false)
	{
		m_first_action = true;

	}
	m_ani_gauge_update[0].Action();
	m_ani_gauge_update[1].Action();
	m_ani_soul.ActionLoop();
	m_ani_soul_fire.ActionLoop();

	m_ct_fire_timer.ActionLoop();
	m_ani_gauge_yellow.ActionLoop();

	int gauge_memori = (int)battle->GetLife();
	if (gauge_memori != m_gauge_update[0])
	{
		if (gauge_memori < m_gauge_update[0])
			m_ani_gauge_update[0].Start();

		m_gauge_update[0] = gauge_memori;

	}
	gauge_memori = (1.0f - GetGaugePercent()) * 50.0f;
	if (gauge_memori != m_gauge_update[1])
	{
		if (gauge_memori < m_gauge_update[1])
			m_ani_gauge_update[1].Start();

		m_gauge_update[1] = gauge_memori;

	}
}
//描画
void CObjBattleGauge::Draw()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjEnsoBattle* battle = (CObjEnsoBattle*)Objs::GetObj(OBJ_BATTLE);

	RECT_N rect_base = m_lyt_gauge_base.GetData().rectangle;
	RECT_N rect_line = m_lyt_gauge_line.GetData().rectangle;

	m_tex_gauge_base.Draw(m_lyt_gauge_base.GetPos().x, m_lyt_gauge_base.GetPos().y, rect_base);

	int x = m_lyt_gauge[0].GetPos().x;
	int y = m_lyt_gauge[0].GetPos().y;
	for (int i = 0; i < (int)battle->GetLife(); i++)
	{
		Draw::Draw(tex_GAUGE, m_lyt_gauge[0].GetPos().x - i * RECT_GAUGE_RED.m_width, m_lyt_gauge[0].GetPos().y, RECT_GAUGE_RED);
	}
	for (int i = 0; i < (1.0f - ((float)enso->m_enso[0].m_score_data.score / (float)enso->m_enso[0].m_score_data.score_rank_norma[(int)E_SCORE_RANK::RANK_KIWAMI])) * 50.0f; i++)
	{
		Draw::Draw(tex_GAUGE, m_lyt_gauge[1].GetPos().x + i * RECT_GAUGE_BLUE.m_width, m_lyt_gauge[1].GetPos().y, RECT_GAUGE_BLUE);
	}


	//ゲージアップデートエフェクト
	for (int i = 0; i < 2; i++)
	{
		RECT_F rect_effect = i == 0 ? RECT_UPDATE : RECT_UPDATE2;


		Draw::SetBlend(tex_GAUGE_UPDATE, E_BLEND_MODE::ADDITIONALPHA);
		Draw::SetOpacity(tex_GAUGE_UPDATE, m_ani_gauge_update[i].GetValue().opacity);
		Draw::Draw(tex_GAUGE_UPDATE, m_lyt_gauge[i].GetPos().x + (m_gauge_update[i]) * RECT_GAUGE_RED.m_width + GAUGE_EFFECT_OFFSET.x, m_lyt_gauge[i].GetPos().y + GAUGE_EFFECT_OFFSET.y, rect_effect, false, false);
	}
	//線を描画
	m_tex_gauge_line.m_opacity = 0.25f;
	m_tex_gauge_line.Draw(m_lyt_gauge_line.GetPos().x, m_lyt_gauge_line.GetPos().y, rect_line);


	////魂　炎
	RECT_N rect_fire = m_lyt_soul_fire.GetSource();
	rect_fire.m_x = (int)m_ani_soul_fire.GetValue(0).pattern * rect_fire.m_width;
	MusicGame::g_tex_soul_fire.Draw(m_lyt_soul_fire.GetPos().x, m_lyt_soul_fire.GetPos().y,rect_fire);

	////魂　文字
	MusicGame::g_tex_soul.m_opacity = 1.0f;
	RECT_N rect_soul = m_lyt_soul.GetSource();
	MusicGame::g_tex_soul.Draw(m_lyt_soul.GetPos().x, m_lyt_soul.GetPos().y, rect_soul);
	rect_soul.m_y = 128.0f;
	MusicGame::g_tex_soul.m_opacity = m_ani_soul.GetValue(0).opacity;
	MusicGame::g_tex_soul.Draw(m_lyt_soul.GetPos().x, m_lyt_soul.GetPos().y, rect_soul);
}

float CObjBattleGauge::GetGaugePercent()
{

	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	return (float)enso->m_enso[0].m_score_data.score / (float)enso->m_enso[0].m_score_data.score_rank_norma[(int)E_SCORE_RANK::RANK_KIWAMI];
}