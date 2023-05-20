#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
#include "CObjDanResult.h"
using namespace GameL;

namespace MusicGame
{

	namespace DanSelect
	{
		const int TEXT_COUNT = 4;

		const int FADE_START_DELAY[TEXT_COUNT] = { 180,610,1050,1500 };
		const int IN_ANIME_TIME = 5500;
		const int FADE_OUT_DELAY = 2150;

		const RECT_F RECT_FUSUMA_LEFT = { 0.0f,0.0f,640.0f,720.0f };
		const RECT_F RECT_FUSUMA_RIGHT = { 640.0f,0.0f,640.0f,720.0f };
		const RECT_F RECT_TEXT[TEXT_COUNT] =
		{
			{0.0f,0.0f,228.0f,228.0f},
			{228.0f,0.0f,228.0f,228.0f},
			{0.0f,228.0f,228.0f,228.0f},
			{228.0f,228.0f,228.0f,228.0f},
		};
		const Point TEXT_POS[TEXT_COUNT] =
		{
			{305,184},
			{949,184},
			{306,525},
			{947,525},
		};

		const int BAR_START_DELAY = 3030;
		const int BAR_MAX_AMOUNT = 20;
		const float BAR_APPEAR_INTERVAL = 32.5f;

		const Point BAR_POS = { 123,18 };
		const int BAR_WIDTH = 45;

		enum E_DAN_BAR_COLOR
		{
			DAN_BAR_KYU,
			DAN_BAR_BLUE,
			DAN_BAR_RED,
			DAN_BAR_SILVER,
			DAN_BAR_GOLD,
			DAN_BAR_GREEN,
			DAN_BAR_Count,
		};

		const RECT_F RECT_DANBAR[DAN_BAR_Count] =
		{
			{0.0f,0.0f,53.0f,113.0f},//KYU,
			{106.0f,0.0f,53.0f,113.0f},//BLUE,
			{53.0f,0.0f,53.0f,113.0f},//RED,
			{159.0f,0.0f,53.0f,113.0f},//SILVER,
			{212.0f,0.0f,53.0f,113.0f},//GOLD,
			{265.0f,0.0f,53.0f,113.0f},//GREEN,
		};
		const RECT_F RECT_DANBAR_CURSOR = { 318.0f,0.0f,53.0f,113.0f };
		const RECT_F RECT_DAN_INFO[DAN_BAR_Count] =
		{
			{0.0f,0.0f,1280.0f,720.0f},//KYU,
			{1440.0f,0.0f,1280.0f,720.0f},//BLUE,
			{720.0f,0.0f,1280.0f,720.0f},//RED,
			{2160.0f,0.0f,1280.0f,720.0f},//SILVER,
			{2880.0f,0.0f,1280.0f,720.0f},//GOLD,
			{3600.0f,0.0f,1280.0f,720.0f},//GREEN,
		};
		const int INFO_SLIDE_DELAY = 5150;

		const Point GAUGE_POS = { 292,413 };
		const Point GAUGE_NUMBER_POS = { 391,452 };
		const Point PERCENT_POS = { 414,449 };
		const Point GAUGE_RANGE_POS = { 437,449 };
		const Point INFO_POS = { 514,406 };
		const Point EXAM_NUMBER_OFFSET = { 146,39 };
		const Point EXAM_RANGE_OFFSET = { 167,39 };
		const Point EXAM_TYPE_OFFSET = { 1,10 };
		const int INFO_HEIGHT = 88;
		const int INFO_WIDTH = 218;
		const int GAUGE_NUMBER_PADDING = 16;
		const int EXAM_NUMBER_PADDING = 14;

		const RECT_F RECT_EXAM_NUMBER = { 0.0f,0.0f,18.0f,22.0f };
		const RECT_F RECT_GAUGE_NUMBER = { 0.0f,0.0f,22.0f,27.0f };
		const RECT_F RECT_GAUGE_MORE = { 0.0f,0.0f,56.0f,32.0f };
		const RECT_F RECT_EXAM_MORE = { 0.0f,0.0f,45.0f,25.0f };
		const RECT_F RECT_EXAM_LESS = { 0.0f,25.0f,45.0f,25.0f };
		const RECT_F RECT_EXAM_TYPE = { 0.0f,0.0f,202.0f,22.875f };

		const RECT_F RECT_INFO_BASE = { 0.0f,0.0f,666.0f,100.0f };
		const RECT_F RECT_INFO_SINGLE = { 0.0f,100.0f,666.0f,100.0f };
		const RECT_F RECT_INFO_TRIPLE = { 0.0f,200.0f,666.0f,100.0f };

		const Point TITLE_POS = { 422,177 };
		const float SONG_HEIGHT = 73.5f;
		const float SONG_FONT_SIZE = 27.0f;
		const int PANEL_X[3] = { -1500,0,1500 };

		const int PANEL_DISPLAY_AMOUNT = 3;
		const Point DAN_PLATE_POS = { 79,118 };

		const int BGM_LOOP_START_DELAY = 7141;
	}

}

class CObjDanSelect : public CObj
{
public:

	CObjDanSelect();
	~CObjDanSelect() {}
	void Init();
	void Action();
	void Draw();
	void ChallengeStart();

	ST_ENSO_OPTION m_enso_option;
private:

	struct ST_DAN_FUMEN
	{
		vector<MusicGame::DanC> vec_info;
		vector<ST_DAN_SONG> vec_song;
		MusicGame::ST_FUMEN_DATA fumen;
		int gauge_norma[2] = { 90,100 };
		void DanFumenDataLoad(list<string>& command_param);
	};

	struct ST_DAN_BAR
	{
		CAnime2 ani_bar_appear = { "Animation/DanSelect/BarAppear" };
		MusicGame::DanSelect::E_DAN_BAR_COLOR color = MusicGame::DanSelect::DAN_BAR_GREEN;
		ST_DAN_FUMEN data;
	};
	CAnime2 m_ani_text_fade_in[MusicGame::DanSelect::TEXT_COUNT];
	CAnime2 m_ani_text_fade_out;
	CAnime2 m_ani_text_dan;
	CAnime2 m_ani_text_i;
	CAnime2 m_ani_text_do;
	CAnime2 m_ani_text_jo;
	CAnime2 m_ani_fusuma;
	CAnime2 m_ani_fusuma_open;
	CAnime2 m_ani_fade;
	CAnime2 m_ani_bg_scale;
	CTimeCounter m_ct_in_anime;
	CTimeCounter m_ct_bar_delay;
	ST_DAN_BAR m_st_dan_bar[MusicGame::DanSelect::BAR_MAX_AMOUNT];
	CAnime2 m_ani_info_slide;
	CNumTexSource m_num_exam;
	CNumTexSource m_num_gauge;
	CTimeCounter m_ct_bgm_delay;
	bool m_bgm_flag;

	vector<string> m_vec_fumen_path;
	vector<ST_DAN_BAR> m_vec_dan_bar;
	void LoadDirectory(string path);
	void FumenListCreate();

	int m_now_select;
	int m_direction;

	void PreviousSong();
	void NextSong();
	void Decide();
};