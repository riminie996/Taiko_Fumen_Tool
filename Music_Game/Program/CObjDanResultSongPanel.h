#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

namespace MusicGame
{
	namespace DanResult
	{
		const RECT_F RECT_SONG_PANEL = { 0.0f,0.0f,960.0f,170.667f };
	};
}

class CObjDanResultSongPanel : public CObj
{
public:
	CObjDanResultSongPanel() {}
	~CObjDanResultSongPanel() {}
	void Init();
	void Action();
	void Draw();
	void AnimeStart();
private:
	CAnime2 m_ani_song_slide[MusicGame::DAN_MAX_SONG];
	CTimeCounter m_ct_song_slide_delay;
	CNumTexSource m_num_song_judge;

	const RECT_F RECT_DANRESULT_NUMBER = { 0.0f,0.0f,21.0f,28.0f };

	const int DANRESULT_SONGPANEL_SLIDE_DELAY = 400;
	const Point DANSONG_POS = { 253,99 };
	const float DANSONG_HEIGHT = 184;
	const Point DANSONG_NUMBER_OFFSET[JUDGE_COUNT] =
	{ 
		{ 276,109 },
		{ 487,109 },
		{ 698,109 },
		{ 909,109 },
	};
	const float DANSONG_NUMBER_PADDING = 20.0f;
};
