#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

enum class E_COMBO_COLOR
{
	NOT = -1,
	NORMAL,
	SILVER,
	GOLD,
};


class CObjCombo : public CObj
{
public:
	CObjCombo() {}
	~CObjCombo() {}
	void Init();
	void Action();
	void Draw();

	void Add(int player);
	void Reset(int player);

	E_COMBO_COLOR GetComboColor(int player);

private:
	//íËêî
	const RECT_F RECT_COMBO_NUM =			{ 0.0f,0.0f,40.0f,49.0f };
	const RECT_F RECT_COMBO_SILVER_NUM =	{ 0.0f,49.0f,40.0f,49.0f };
	const RECT_F RECT_COMBO_GOLD_NUM =		{ 0.0f,98.0f,40.0f,49.0f };
	const float NUM_PADDING =  35.0f;
	const float NUM_PADDING_1000COMBO =  29.0f;
	const float NUM_SCALE_X_1000COMBO =  0.875f;
	CNumTexSource m_combo_num[3];
	const Point COMBO_TEXT_OFFSET = { 17,0 };
	CAnime3 m_ani_combo_scale[MusicGame::MAX_PLAYER_AMOUNT];

	const int COMBO_RAME_AMOUNT = 3;
	const Point COMBO_RAME_OFFSET[3] =
	{
		{19,9},
		{30,21},
		{14,16},
	};
	const int COMBO_RAME_LOOPTIME = 600;
	const int COMBO_RAME_DELAY[3] = { 0,110,300 };
	const RECT_F RECT_COMBO_RAME = { 0.0f,0.0f,25.0f,25.0f };
	CAnime2 m_ani_combo_rame[3];
	CTimeCounter m_ct_rame_delay;
	bool m_first_action;




	CLayout m_lyt_combo[MusicGame::MAX_PLAYER_AMOUNT];
	CLayout m_lyt_combo_text[MusicGame::MAX_PLAYER_AMOUNT];

	void ComboVoiceStart(int combo,int player);
};
