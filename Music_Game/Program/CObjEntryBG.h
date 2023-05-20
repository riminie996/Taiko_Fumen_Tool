#pragma once
#include "MusicGame.h"
#include "GameHead.h"
#include "GameL\SceneObjManager.h"
using namespace GameL;

namespace MusicGame
{
	namespace Entry
	{
		const int LIGHT_AMOUNT = 4;
		const Point LIGHT_POS[LIGHT_AMOUNT] =
		{
			{16,227},
			{966,292},
			{1100,276},
			{1240,260},
		};
	}
}

class CObjEntryBG : public CObj
{
public:

	CObjEntryBG() {}
	~CObjEntryBG() {}
	void Init();
	void Action();
	void Draw();

private:

	CAnime2 m_ani_background_fadeout = { "Animation/Entry/BackGroundFadeOut" };
	CAnime2 m_ani_light = { "Animation/Entry/LightOpacity" };
};
