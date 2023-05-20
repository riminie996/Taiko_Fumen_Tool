#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;


class CObjMTaiko : public CObj
{
public:
	CObjMTaiko() {}
	~CObjMTaiko() {}
	void Init();
	void Action();
	void Draw();
	void AutoPlayInput(E_NOTES_TYPE notes,int player);
	void Input(E_TAIKO_FLUSH input,int player);
private:
	CCounter m_ct_flush_effect[MusicGame::MAX_PLAYER_AMOUNT][MusicGame::TAIKO_FLUSH_TYPE];
	CAnime2 m_ani_flush[MusicGame::MAX_PLAYER_AMOUNT][MusicGame::TAIKO_FLUSH_TYPE];
	bool m_key_flag[TAIKO_FLUSH_Count];

	//íËêî
	const Point DIFFCULTY_POS = { 19,233 };
	const RECT_F RECT_DIFFCULTY = { 0.0f,0.0f,89.0f,60.0f };
	const int AUTOPLAY_BALLOON_INTERVAL = 30;
	const Point OPTION_ICON_POS = { 112,233 };
	const float OPTION_ICON_PADDING = 29.0f;
	const RECT_N RECT_LANE_LEFT_DAN = { 0,352,332,176 };


	bool m_auto_left[MusicGame::MAX_PLAYER_AMOUNT];
	CCounter m_ct_auto_roll[MusicGame::MAX_PLAYER_AMOUNT];
	CCounter m_ct_auto_balloon[MusicGame::MAX_PLAYER_AMOUNT];

	CLayout m_lyt_taiko[MusicGame::MAX_PLAYER_AMOUNT];
	CLayout m_lyt_bg[MusicGame::MAX_PLAYER_AMOUNT];
};
