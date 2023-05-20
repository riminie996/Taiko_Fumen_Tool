#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjCharacter : public CObj
{
public:
	CObjCharacter() {}
	~CObjCharacter() {}
	void Init();
	void Action();
	void Draw();
	void Act10Combo(int player);
	void Act10ComboMax(int player);
	void ActGogoStart(int player);
	void ActClearIn(int player);
	void ActSoulIn(int player);
	void ActBalloonStart(int player);
	void ActBalloonBroke(int player);
	void ActBalloonMiss(int player);
	void ActBalloonBreak(int player);
	void ActEnd(int player);
private:
	//tex_DONCHAN_NORMAL_119,
	//	tex_DONCHAN_10COMBO_44 =
	//	tex_DONCHAN_10COMBO_MAX_63 =
	//	tex_DONCHAN_CLEAR_59 =
	//	tex_DONCHAN_CLEAR_MAX_59 =
	//	tex_DONCHAN_CLEAR_IN_44 =
	//	tex_DONCHAN_GOGOSTART_53 =
	//	tex_DONCHAN_GOGOSTART_MAX_53 =
	struct ST_CHARA_MOTION
	{
		CCounter ct_normal;
		CCounter ct_10combo;
		CCounter ct_10combo_max;
		CCounter ct_clear;
		CCounter ct_clear_in;
		CCounter ct_gogostart;
		CCounter ct_gogo;
		CCounter ct_soulin;
		CCounter ct_balloon_broke;
		CCounter ct_balloon_miss;
		CCounter ct_balloon_break;

	float motion_bpm;
	

	bool action_now;
	bool balloon_now;
	};

	CAnime2 m_ani_effect = { "Animation/Enso/CharacterEffect" };
	vector<ST_CHARA_MOTION> m_chara_motion;


	//îºìßñæÇ≈ê≥ämÇ…îªífÇ≈Ç´Ç»Ç¢ÇΩÇﬂä®
	const Point GOLDEFFECT_POS = { 27,-7 };
	const RECT_F RECT_GOLDEFFECT = { 0.0f,0.0f,320.0f,224.0f };
	const float BALLOON_TIMER = 1.0f;
	const Point CHARA_BALLOON_POS = { 108,24 };

	CLayout m_lyt_normal[MusicGame::MAX_PLAYER_AMOUNT];
	CLayout m_lyt_balloon[MusicGame::MAX_PLAYER_AMOUNT];

	void MotionBpmSet(int player);
};
