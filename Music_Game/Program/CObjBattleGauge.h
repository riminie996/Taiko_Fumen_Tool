#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjBattleGauge : public CObj
{
public:
	CObjBattleGauge() {}
	~CObjBattleGauge() {}
	void Init();
	void Action();
	void Draw();
	void Update();
	float GetGaugePercent();
private:

	//íËêî
	const RECT_F RECT_SOUL = { 0.0f,0.0f,64.0f,64.0f };
	const RECT_F RECT_SOUL_FIRE = { 0.0f,0.0f,230.0f,230.0f };
	const RECT_F RECT_GAUGE_RED = { 0.0f,22.0f,12.0f,22.0f };
	const RECT_F RECT_GAUGE_BLUE = { 42.0f,22.0f,12.0f,22.0f };
	const RECT_F RECT_GAUGE_NORMA = { 14.0f,0.0f,14.0f,44.0f };
	const RECT_F RECT_GAUGE_NORMA2 = { 56.0f,0.0f,14.0f,44.0f };
	const RECT_F RECT_GAUGE_YELLOW = { 28.0f,0.0f,14.0f,44.0f };
	const RECT_F RECT_GAUGE_LAST = { 28.0f,0.0f,10.0f,44.0f };
	const RECT_F RECT_UPDATE = { 0.0f,0.0f,32.0f,64.0f };
	const RECT_F RECT_UPDATE2 = { 96.0f,0.0f,32.0f,64.0f };
	const Point P1_SOUL_POS[2] = { { 1194,132 } ,{ 1194,523 } };
	const Point P1_SOUL_FIRE_POS[2] = { { 1129,52 },{ 1129,440 } };
	const Point GAUGE_EFFECT_OFFSET = { -9,-29 };

	int m_gauge_update[2];
	CTimeCounter m_ct_fire_timer;
	CAnime2 m_ani_gauge_yellow = { "Animation/Enso/GaugeYellowOpacity" };
	CAnime2 m_ani_gauge_update[MusicGame::MAX_PLAYER_AMOUNT];
	bool m_first_action;

	float GetPlusRate(int player);
	float GetDamageRate(E_JUDGE judge, int player);

	CLayout m_lyt_gauge_base;
	CLayout m_lyt_gauge_line;
	CLayout m_lyt_gauge[2];
	CLayout m_lyt_soul;
	CLayout m_lyt_soul_fire;
	CAnime3 m_ani_soul_fire;
	CAnime3 m_ani_soul;
	CTexture m_tex_gauge_base;
	CTexture m_tex_gauge_line;


};
