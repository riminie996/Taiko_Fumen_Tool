#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

namespace MusicGame
{
	namespace DanResult
	{
		const Point STATE_JUDGE_POS[JUDGE_COUNT] = 
		{
			{ 825,104 },
			{ 825,145 },
			{ 825,186 },
			{ 1127,104 },
		};
		const Point STATE_COMBO_POS = { 1127,145 };
		const Point STATE_HIT_POS = { 1127,186 };
		const Point STATE_SCORE_POS = { 530,122 };
		const int JUDGE_NUMBER_PADDING = 20;
		const int SCORE_NUMBER_PADDING = 30;
		const RECT_F RECT_GAUGE = { 0.0f,0.0f,14.0f,44.0f };

		const int DANRESULT_ACT_TIME = 35000;
		const int DANRESULT_ANIME_TIME = 3370;
		const int DANRESULT_GAUGE_INTERVAL = 17;
		const int DANRESULT_NUMBER_DELAY = 670;
		const int DANRESULT_EXAM_DELAY = 2230;
		const int DANRESULT_EXAM_GAUGE_DELAY = 500;
		const int DANRESULT_ANIME_END_DELAY =1100;

		const Point GAUGE_BASE_POS = { 265,232 };
		const Point DANRESULT_VALUE_NUMBER_OFFSET = { 237,16 };
		const Point DANRESULT_TRIPLE_VALUE_NUMBER_OFFSET = { 70,45 };
		const float DANRESULT_TRIPLE_VALUE_SCALE = 0.5f;
		const float DANRESULT_TRIPLE_VALUE_PADDING = 18;

		const RECT_F RECT_PERCENT_NORMAL = { 0.0f,0.0f,40.0f,40.0f };
		const RECT_F RECT_PERCENT_GOLD = { 40.0f,0.0f,40.0f,40.0f };
		const Point DANRESULT_PERCENT_NUMBER_POS = { 559,239 };
		const Point DANRESULT_PERCENT_POS = { 585,237 };
		const int DANRESULT_PERCENT_NUMBER_PADDING = 22;
		const float DANRESULT_PERCENT_NUMBER_SCALE = 0.6667f;

		const RECT_F RECT_TRIPLE_EXAMNUMBER = { 0.0f,0.0f,16.0f,16.0f };
		const int TRIPLE_EXAMNUMBER_PADDING = 10;
		const RECT_F RECT_TRIPLE_EXAMRANGE_MORE = { 0.0f,0.0f,32.0f,18.0f };
		const RECT_F RECT_TRIPLE_EXAMRANGE_LESS = { 0.0f,18.0f,32.0f,18.0f };

		const Point EXAM_NUMBER_OFFSET = { 169,47 };
		const Point EXAM_RANGE_OFFSET = { 193,47 };
		const Point EXAM_TYPE_OFFSET = { 3,1 };
		const Point EXAM_NUMBER_TRIPLE_OFFSET = { 252,73 };
		const Point EXAM_RANGE_TRIPLE_OFFSET = { 267,73 };
		const int EXAM_NUMBER_TRIPLE_PADDING = 10;
	}
}

class CObjDanResultPanel : public CObj
{
public:
	CObjDanResultPanel() {}
	~CObjDanResultPanel() {}
	void Init();
	void Action();
	void Draw();
	void AnimeStart();
private:
	struct ST_DANRESULT_ANIME
	{
		CTimeCounter ct_act;
		CTimeCounter ct_gauge[MusicGame::DAN_MAX_SONG];
		CAnime2 ani_number_appear[MusicGame::DAN_MAX_SONG];
		CAnime2 ani_fade;
	};

	CAnime2 m_ani_statepanel_slide = { "Animation/DanResult/StatePanelSlide" };
	CAnime2 m_ani_statepanel_fade = { "Animation/DanResult/StatePanelFade" };
	CAnime2 m_ani_gauge_number;
	CNumTexSource m_num_score;
	CNumTexSource m_num_song_judge;
	CNumTexSource m_num_dan;
	CNumTexSource m_num_dan_rainbow;
	CNumTexSource m_num_exam;
	CNumTexSource m_num_exam_triple;
	CTimeCounter m_ct_result_gauge;
	CTimeCounter m_ct_act;
	vector<ST_DANRESULT_ANIME> m_vec_anime;

	int DrawExam(int num);

	void AnimeSkip();
};
