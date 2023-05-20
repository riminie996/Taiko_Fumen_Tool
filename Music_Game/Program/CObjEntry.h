#pragma once
#include "MusicGame.h"
#include "GameHead.h"
#include "GameL\SceneObjManager.h"
using namespace GameL;

namespace MusicGame
{
	namespace Entry
	{
		const int ENTRY_BAR_AMOUNT = 1;
		const Point ENTRY_BAR_POS = { 640,334 };
		const int ENTRY_BAR_HEIGHT = 118;

		const RECT_F RECT_ENTRY_BAR = { 0.0f,0.0f,774.0f,128.0f };
		const RECT_F RECT_ENTRY_BAR_EFFECT = { 0.0f,128.0f,774.0f,128.0f };

		const int MODESELECT_DELAY = 1300;


	}
}


class CObjEntry : public CObj
{
public:
	
	CObjEntry() {}
	~CObjEntry() {}
	void Init();
	void Action();
	void Draw();

private:

	CFIFO m_fade_in;
	CAnime2 m_ani_entry_fadein = { "Animation/Entry/EntryFadeIn" };
	CAnime2 m_ani_entry_fadeout = { "Animation/Entry/EntryFadeOut" };
	CAnime2 m_ani_entry_decide_effect = { "Animation/Entry/EntryEffect" };

	CTimeCounter m_ct_modeselect_delay;

	bool m_bgm_play_flag;

	const int BGM_LOOP_START_DELAY = 232;
	CTimeCounter m_ct_bgm_loop_start;
};
