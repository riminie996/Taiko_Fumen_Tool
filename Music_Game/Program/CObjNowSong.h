#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjNowSong : public CObj
{
public:
	CObjNowSong(Point pos) { m_pos = pos; }
	~CObjNowSong() {}
	void Init();
	void Action();
	void Draw();
private:

	const Point NOW_NUMBER_OFFSET = { 32, 18 };
	const Point MAX_NUMBER_OFFSET = { 127, 25 };
	const float MAX_NUMBER_SCALE = 0.75f;
	const float NOW_NUMBER_PADDING = 18.0f;
	const RECT_F RECT_INFINITY = { 270.0f,0.0f,27.0f,29.0f };


	Point m_pos;
	CNumTexSource m_num_song;
};