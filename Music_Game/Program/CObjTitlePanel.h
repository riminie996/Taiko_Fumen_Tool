#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

namespace MusicGame
{
	namespace Enso
	{
		const float TITLE_PANEL_FONT_SIZE = 35.0f;
		const float TITLE_PANEL_RIGHT_X = 1237.0f;
		const float TITLE_PANEL_Y = 23.0f;

		const Point GENRE_POS = { 1029,69 };
		const Point NOW_SONG_OFFSET = { 63,3 };
		const Point MAX_SONG_OFFSET = { 162,3 };
		const int SONG_NUMBER_PADDING = 13;

		const RECT_F RECT_GENRE = { 0.0f,0.0f,256.0f,23.0f };
		const RECT_F RECT_SONGNUMBER = { 0.0f,0.0f,15.0f,16.0f };
		const RECT_F RECT_SONG_BACK = { 0.0f,207.0f,256.0f,23.0f };
		const RECT_F RECT_INFINITY = { 0.0f,16.0f,16.0f,16.0f };
	}
}
class CObjTitlePanel : public CObj
{
public:
	CObjTitlePanel() {}
	~CObjTitlePanel() {}
	void Init();
	void Action();
	void Draw();
	void SetTitleString(string title, int genre);
	void DisableShowing() { m_show_flag = false; }
private:
	CAnime2 m_ani_genre_fade = { "Animation/Enso/TitlePanelOpacity" };
	string m_str_title;
	int m_music_count;
	int m_genre;
	CNumTexSource m_num_song;
	bool m_show_flag;
};
