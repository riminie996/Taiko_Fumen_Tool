#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

namespace MusicGame
{

	namespace DanSelect
	{
		const RECT_F RECT_CURSOR = { 0.0f,0.0f,226.0f,96.0f };
		const RECT_F RECT_CURSOR_EFFECT = { 0.0f,96.0f,226.0f,96.0f };
		const RECT_F RECT_CURSOR_WHITE = { 0.0f,192.0f,226.0f,96.0f };
		const RECT_F RECT_CURSOR_WHITE_EFFECT = { 0.0f,288.0f,226.0f,96.0f };
		const RECT_F RECT_CURSOR_OPTION = { 226.0f,0.0f,94.0f,96.0f };
		const RECT_F RECT_CURSOR_EFFECT_OPTION = { 226.0f,96.0f,94.0f,96.0f };
		const RECT_F RECT_CURSOR_WHITE_OPTION = { 226.0f,192.0f,94.0f,96.0f };
		const RECT_F RECT_CURSOR_WHITE_EFFECT_OPTION = { 226.0f,288.0f,94.0f,96.0f };

		const int CONFIRM_ICON_AMOUNT = 3;
		const Point CONFIRM_POS[CONFIRM_ICON_AMOUNT] =
		{
			{409,387},
			{570,387},
			{795,387},
		};

		enum E_CONFIRM_ICON
		{
			ICON_OPTION,
			ICON_DECIDE,
			ICON_CANCEL,
		};

		const int FADE_DELAY = 3050;
		const int FADE_FRAME =30;
	}

}

class CObjDanSelectConfirm : public CObj
{
public:

	CObjDanSelectConfirm();
	~CObjDanSelectConfirm() {}
	void Init();
	void Action();
	void Draw();
private:
	int m_now_select;
	bool m_cancel;
	bool m_decide;

	CAnime2 m_ani_back_fadein;
	CAnime2 m_ani_window_fadein;
	CAnime2 m_ani_icon_fadein;
	CAnime2 m_ani_back_fadeout;
	CAnime2 m_ani_window_fadeout;
	CAnime2 m_ani_effect_loop;
	CAnime2 m_ani_decide_white;

	CFIFO m_fade_out;
	CTimeCounter m_ct_fade_delay;

	void SelectLeft();
	void SelectRight();
	void Decide();
};