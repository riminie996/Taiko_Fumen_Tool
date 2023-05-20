#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjControllGuide : public CObj
{
public:
	CObjControllGuide() {}
	~CObjControllGuide() {}
	void Init();
	void Action();
	void Draw();
private:
	const RECT_N RECT_BACKGROUND = { 0,0,222,164 };
	const RECT_N RECT_TAIKO = { 0,164,222,164 };
	const RECT_N RECT_DON = { 0,328,222,164 };
	const RECT_N RECT_KA = { 0,492,111,164 };
	const RECT_N RECT_KA2 = { 0,656,111,164 };
	const RECT_N RECT_KA3 = { 0,820,111,164 };
	const RECT_N RECT_DECIDE = { 112,738,134,43 };
	const RECT_N RECT_DECIDE_EFFECT = { 112,781,134,45 };
	const RECT_N RECT_ARROW = { 112,492,76,91 };
	const RECT_N RECT_BACHI_KA[3] = 
	{ 
		{ 188,492,30,91 },
		{ 218,492,30,91 },
		{ 112,583,29,83 }, 
	};
	const RECT_N RECT_BACHI_DON[3] = 
	{ 
		{ 141,583,57,83 },
		{ 198,583,58,72 },
		{ 112,666,58,72 }, 
	};
	const Point GUIDE_POS = { 111,108 };
	const Point DECIDE_POS = { 112,167 };

	CAnime3 m_ani_taiko_effect;
	CAnime3 m_ani_effect_loop;
};