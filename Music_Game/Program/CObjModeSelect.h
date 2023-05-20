#pragma once
#include "MusicGame.h"
#include "GameHead.h"
#include "GameL\SceneObjManager.h"
using namespace GameL;

namespace MusicGame
{
	namespace Entry
	{
		const int APPEAR_TIME = 1580;

		const int CHARA_APPEAR_DELAY = 180;
		const int CURSOR_APPEAR_DELAY = 550;

		const RECT_F RECT_BAR_TOP = { 0.0f,0.0f,672.0f,32.0f };
		const RECT_F RECT_BAR_CENTER = { 0.0f,32.0f,672.0f,192.0f };
		const RECT_F RECT_BAR_BOTTOM = { 0.0f,224.0f,672.0f,32.0f };
		const RECT_F RECT_CHARA_LEFT = { 0.0f,0.0f,256.0f,240.0f };
		const RECT_F RECT_CHARA_RIGHT = { 256.0f,0.0f,256.0f,240.0f };
		const RECT_F RECT_OVERLAY_TOP = { 0.0f,0.0f,576.0f,22.0f };
		const RECT_F RECT_OVERLAY_CENTER = { 0.0f,22.0f,576.0f,116.0f };
		const RECT_F RECT_OVERLAY_BOTTOM = { 0.0f,138.0f,576.0f,22.0f };

		const Point BAR_POS = { 640,360 };
		const Point CHARA_LEFT_POS = { 235,234 };
		const Point CHARA_RIGHT_POS = { 790,234 };

		const RECT_F RECT_CURSOR = { 0.0f,0.0f,704.0f,320.0f };
		const RECT_F RECT_CURSOR_EFFECT = { 0.0f,320.0f,704.0f,320.0f };
		const RECT_F RECT_CURSOR_WHITE = { 0.0f,640.0f,704.0f,320.0f };

		const Point OVERLAY_TOP_OFFSET = { 1,-42 };
		const float OVERLAY_CENTER_MIN_HEIGHT = 40;
		const float BAR_SCALE_SPEED = 0.08f / FRAME_FPS;
		const float TEXT_OFFSET_Y = -70;
		const float BAR_CENTER_SCALE_MIN = 0.203125f;
		const float OVERLAY_CENTER_SCALE_MIN = 0.3448275f;

		const int BAR_SCALE_DELAY = 80;

		enum E_MODE
		{
			MODE_ENSO,
			MODE_Count,
		};


		enum class E_TO_MODE
		{
			SONGSELECT,
			HEYA,
			DANSELECT,
			BATTLESELECT,
		};
	}
}

class CObjModeSelect : public CObj
{
public:

	CObjModeSelect() {}
	~CObjModeSelect() {}
	void Init();
	void Action();
	void Draw();

private:
	CAnime2 m_ani_bar_appear = { "Animation/Entry/ModeBarAppear" };
	CAnime2 m_ani_chara_appear = { "Animation/Entry/ModeBarCharaAppear" };
	CAnime2 m_ani_text_appear = { "Animation/Entry/ModeBarTextAppear" };
	CAnime2 m_ani_cursor_appear = { "Animation/Entry/ModeBarCursorAppear" };
	CAnime2 m_ani_mode_decide = { "Animation/Entry/DecideEffect" };
	CAnime2 m_ani_mode_fadeout = { "Animation/Entry/ModeBarFadeOut" };
	CTimeCounter m_ct_appear;

	CFIFO m_fade_out;
	MusicGame::Entry::E_TO_MODE m_to_mode;
};