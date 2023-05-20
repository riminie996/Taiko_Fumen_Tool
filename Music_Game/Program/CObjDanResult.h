#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

namespace MusicGame
{
	namespace DanResult
	{
		const int RESULT_IN_VOICE_DELAY = 358;
		const Point DAN_PLATE_POS = { 138,224 };
		const Point NORMAGAUGE_BASE_POS = { 376,264 };
	
		const Point SOUL_POS = { 1075,251 };
		const Point GAUGE_BASE_OFFSET = { 266,19 };
		const Point GAUGE_BASE_TRIPLE_OFFSET = { 81,47 };
		const Point GAUGE_OFFSET = { 271,23 };
		const Point GAUGE_TRIPLE_OFFSET = { 85,50 };
		const int DANPLATE_ANIME_START_DELAY = 460;
		const int GAUGE_BASE_HEIGHT = 103;
		const int GAUGE_BASE_TRIPLE_WIDTH = 310;

		const RECT_F RECT_DANRESULT_NUMBER = { 0.0f,0.0f,21.0f,28.0f };
		const RECT_F RECT_GAUGE_BG = { 0.0f,0.0f,944.0f,105.0f };
		const RECT_F RECT_GAUGE_BG_TRIPLE = { 0.0f,105.0f,944.0f,105.0f };

		const RECT_F RECT_GAUGE_TRIPLE[5] =
		{
			{ 0.0f,0.0f,214.0f,27.0f },
			{ 0.0f,27.0f,214.0f,27.0f },
			{ 0.0f,54.0f,214.0f,27.0f },
			{ 0.0f,81.0f,214.0f,27.0f },
			{ 0.0f,108.0f,214.0f,27.0f },
		};

		const int NORMAGAUGE_START_DELAY = 3160;
		const int DANRESULT_STATEPANEL_ACT_TIME = 31840;
		const int BGM_LOOP_START_DELAY = 2989;

		const float FAILURE_TEXT_WIDTH = 132;
		const float FAILURE_TEXT_HEIGHT = 180;
		const int FAILURE_TEXT_DELAY = 167;
		const float FAILURE_TEXT_OFFSET_X = 72;
		const Point FAILURE_TEXT_POS = { 11,318 };
		const int FAILURE_TEXT_PATTERN_X = 3;
		const int FAILURE_TEXT_PATTERN_Y = 4;
		const Point CLEAR_POS = { 130,372 };

		const RECT_F RECT_CLEARED = { 0.0f,0.0f,257.0f,226.0f };
		const RECT_F RECT_GOLDCLEARED = { 257.0f,0.0f,257.0f,226.0f };
		const RECT_F RECT_BACK_SILVER = { 0.0f,226.0f,257.0f,226.0f };
		const RECT_F RECT_BACK_GOLD = { 257.0f,226.0f,257.0f,226.0f };
		const RECT_F RECT_BACK_RAINBOW = { 514.0f,226.0f,257.0f,226.0f };


	}
}



class CObjDanResult : public CObj
{
public:
	CObjDanResult(ST_SCORE_DATA score) { m_score = score; }
	~CObjDanResult() {}
	void Init();
	void Action();
	void Draw();
	ST_SCORE_DATA GetScore() { return m_score; }
	void AnimeStart();
private:


	E_DANRESULT_STATUS m_result_status;

	const int DANRESULT_SONGPANEL_SLIDE_START_TIME = 1060;
	const int DANRESULT_SONGPANEL_WAIT_TIME = 28940;

	CTimeCounter m_ct_result_dan;
	CTimeCounter m_ct_result_dan2;
	CTimeCounter m_ct_bgm_loop_delay;
	bool m_bgm_flag;
	bool m_result_voice_flag;
	CAnime2 m_ani_danplate = { "Animation/DanResult/DanPlateSlide" };
	ST_SCORE_DATA m_score;

	//ÉAÉjÉÅóp
	CTimeCounter m_ct_anime_delay;
	CAnime2 m_ani_failure[MusicGame::DanResult::FAILURE_TEXT_PATTERN_X];
	CAnime2 m_ani_clear;
	bool m_anime_start_flag;
};
