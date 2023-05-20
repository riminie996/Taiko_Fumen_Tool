#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

namespace MusicGame
{
	namespace Exit
	{
		enum class E_EXIT_TO
		{
			TITLE,
			ENTRY,
			GAMEEND,
		};
	}
}

class CObjExit : public CObj
{
public:
	CObjExit(MusicGame::Exit::E_EXIT_TO phase) { m_exit_phase = phase; }
	~CObjExit() {}
	void Init();
	void Action();
	void Draw();
private:

	CAnime2 m_ani_curtain = { "Animation/End/Curtain" };
	CAnime2 m_ani_text = { "Animation/End/Text" };

	//-92,406

	const RECT_F RECT_CHARA = { 0.0f,0.0f,214.0f,320.0f };
	const int CURTAIN_LEFT_WIDTH = 656;
	const int CURTAIN_WIDTH = 360;
	const Point CHARA_OFFSET = { -92,406 };
	const static int FADE_START_DELAY = 7000;
	const static int FADE_FRAME = 30;

	const static int CHARA_PATTERN = 10;
	const static int CHARA_PATTERN_INTERVAL = 80;
	CTimeCounter m_ct_chara_pattern;
	CTimeCounter m_ct_fade_delay;
	CFIFO m_fadeout;
	MusicGame::Exit::E_EXIT_TO m_exit_phase;
};
