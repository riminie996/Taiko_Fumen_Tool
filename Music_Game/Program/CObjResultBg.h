#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjResultBg : public CObj
{
public:
	CObjResultBg() {}
	~CObjResultBg() {}
	void Init();
	void Action();
	void Draw();
	void FadeStart();
private:
	//íËêî
	CAnime2 m_ani_background_fade = { "Animation/Result/BackgroundFade" };
	CAnime2 m_ani_background_mountain = { "Animation/Result/BackgroundMountain" };
};
