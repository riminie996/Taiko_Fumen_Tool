#pragma once
#include "MusicGame.h"
#include "GameHead.h"
#include "GameL\SceneObjManager.h"
using namespace GameL;


class CObjSongSelectBG : public CObj
{
public:
	CObjSongSelectBG() {}
	~CObjSongSelectBG() {}
	void Init();
	void Action();
	void Draw();
	void GenreChange(int genre);
	void GenreChange();
private:
	bool m_first_action;
	int m_before_color;
	int m_now_color;
	void BackgroundDraw();
	CAnime2 m_ani_background_scroll = { "Animation/SongSelect/BackGroundScroll" };
	CAnime2 m_ani_background_fade = { "Animation/SongSelect/BackGroundFade" };

};
