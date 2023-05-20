#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

enum E_GAUGE_MODE
{
	GAUGE_NORMAL,
	GAUGE_HARD,
};

namespace MusicGame
{
	namespace Enso
	{
		const RECT_F RECT_GAUGE_BASE = { 0.0f,0.0f,720.0f,44.0f };
		const RECT_F RECT_SOUL = { 0.0f,0.0f,64.0f,64.0f };
		const RECT_F RECT_SOUL_NOT = { 0.0f,64.0f,64.0f,64.0f };
	}
}

class CObjNormaGauge : public CObj
{
public:
	CObjNormaGauge() {}
	~CObjNormaGauge() {}
	void Init();
	void Action();
	void Draw();
	void Add(E_JUDGE judge,int player);
	int GetNorma(int player);
	void GaugeDraw(int param,int x, int y,float scale_x,float scale_y,int player, bool filp);
private:

	//íËêî
	const RECT_F RECT_SOUL = { 0.0f,0.0f,64.0f,64.0f };
	const RECT_F RECT_SOUL_NOT = { 0.0f,64.0f,64.0f,64.0f };
	const RECT_F RECT_SOUL_FIRE = { 0.0f,0.0f,230.0f,230.0f };
	const RECT_F RECT_GAUGE_NOT_CLEAR = { 58.0f,44.0f,58.0f,24.0f };
	const RECT_F RECT_GAUGE_CLEAR = { 0.0f,44.0f,58.0f,24.0f };
	const RECT_F RECT_GAUGE_BASE = { 0.0f,0.0f,796.0f,56.0f };
	const RECT_F RECT_GAUGE_LINE = { 0.0f,0.0f,714.0f,44.0f };
	const RECT_F RECT_GAUGE_BASE_NORMAL = { 0.0f,56.0f,796.0f,56.0f };
	const RECT_F RECT_GAUGE_LINE_NORMAL = { 0.0f,44.0f,714.0f,44.0f };
	const RECT_F RECT_GAUGE_BASE_EASY = { 0.0f,112.0f,796.0f,56.0f };
	const RECT_F RECT_GAUGE_LINE_EASY = { 0.0f,88.0f,714.0f,44.0f };
	const RECT_F RECT_GAUGE = { 0.0f,0.0f,14.0f,44.0f };
	const RECT_F RECT_GAUGE_RAINBOW = { 0.0f,0.0f,704.0f,51.0f };
	const RECT_F RECT_GAUGE_RAINBOW_NORMAL = { 704.0f,0.0f,704.0f,51.0f };
	const RECT_F RECT_GAUGE_RAINBOW_EASY = { 1408.0f,0.0f,704.0f,51.0f };
	const RECT_F RECT_GAUGE_RAINBOW_DAN = { 0.0f,0.0f,697.0f,22.0f };
	const RECT_F RECT_GAUGE_RED = { 0.0f,22.0f,14.0f,22.0f };
	const RECT_F RECT_GAUGE_BLUE = { 42.0f,22.0f,14.0f,22.0f };
	const RECT_F RECT_GAUGE_NORMA = { 14.0f,0.0f,14.0f,44.0f };
	const RECT_F RECT_GAUGE_NORMA2 = { 56.0f,0.0f,14.0f,44.0f };
	const RECT_F RECT_GAUGE_YELLOW = { 28.0f,0.0f,14.0f,44.0f };
	const RECT_F RECT_GAUGE_LAST = { 28.0f,0.0f,10.0f,44.0f };
	const RECT_F RECT_UPDATE = { 0.0f,0.0f,32.0f,58.0f };
	const RECT_F RECT_UPDATE2 = { 96.0f,0.0f,32.0f,58.0f };
	const RECT_F RECT_UPDATE_NORMA = { 32.0f,0.0f,32.0f,58.0f };
	const RECT_F RECT_UPDATE_CLEAR = { 64.0f,0.0f,32.0f,58.0f };
	const Point P1_GAUGE_POS[2] = { { 495,144 }, { 495,532 } };
	const Point P1_GAUGE_TEXT_POS[2] = { { 1039,144 }, { 1039,532 } };
	const Point P1_DAN_RAINBOW_OFFSET = { 0,22 };
	const Point GAUGE_EFFECT_OFFSET = { -9,-7 };
	const static int RAINBOW_GAUGE_INTERVAL = 84;

	float m_norma_gauge[MusicGame::MAX_PLAYER_AMOUNT];
	int m_gauge_update[MusicGame::MAX_PLAYER_AMOUNT];
	CTimeCounter m_ct_fire_timer;
	CTimeCounter m_ct_rainbow_timer;
	CTimeCounter m_ct_rainbow_fade;
	CAnime2 m_ani_gauge_yellow = { "Animation/Enso/GaugeYellowOpacity" };
	CAnime2 m_ani_gauge_update[MusicGame::MAX_PLAYER_AMOUNT];
	const float HARD_GAUGE_DAMAGE_RATE = 5.0f;
	bool m_first_action;

	E_GAUGE_MODE m_mode;
	float GetPlusRate(int player);
	float GetDamageRate(E_JUDGE judge,int player);

	CLayout m_lyt_gauge_base[MusicGame::MAX_PLAYER_AMOUNT];
	CLayout m_lyt_gauge_line[MusicGame::MAX_PLAYER_AMOUNT];
	CLayout m_lyt_gauge_rainbow[MusicGame::MAX_PLAYER_AMOUNT];

	CLayout m_lyt_soul[MusicGame::MAX_PLAYER_AMOUNT];
	CLayout m_lyt_soul_fire[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime3 m_ani_soul_fire;
	CAnime3 m_ani_soul;

};
