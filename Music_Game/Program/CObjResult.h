#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

namespace MusicGame
{
	namespace Result
	{
		const RECT_F RECT_SCORE_NUMBER = { 0.0f,0.0f,38.0f,54.0f };
		const int GAUGE_MEMORI_TIME = 57;

		enum E_SCORE_FILE
		{
			SCORE_SCORE,
			SCORE_CROWN,
			SCORE_RANK,
			SCORE_GREAT,
			SCORE_GOOD,
			SCORE_MISS,
			SCORE_ROLL,
			SCORE_MAXCOMBO,
			SCORE_PLAYCOUNT,
			SCORE_Count,
		};
	}
}

class CObjResult : public CObj
{
public:
	CObjResult(ST_SCORE_DATA score) { m_score = score; }
	~CObjResult() {}
	void Init();
	void Action();
	void Draw();
	void ScoreSave();
private:
	//定数
	const RECT_F RECT_NUM = { 0.0f,0.0f,24.0f,32.0f };
	const RECT_F RECT_SCORE_NUM = { 0.0f,0.0f,38.0f,54.0f };
	const float NUM_PADDING = 20.5f;
	const float SCORE_NUM_PADDING = 30.0f;
	const Point JUDGE_TEXT_OFFSET = { 240,300 };
	const Point PARAMATER_PANEL_POS = { 27,120 };
	const Point PARAMATER_GAUGE_POS = { 58,144 };
	const Point PARAMATER_RAINBOW_POS = { 58,144 };
	const Point PARAMATER_DIFFCULTY_OFFSET = { -7,-44 };
	const Point PARAM_JUDGE_NUM_POS[JUDGE_COUNT + 1/*+最大コンボ数*/] =
	{
		{559,193},//良
		{559,234},//可
		{559,276},//不可
		{559,317},//連打数
		{559,359},//最大コンボ数

	};
	const Point PARAM_SCORE_NUM_POS = { 259,216 };
	const Point PARAM_SCORE_RANK_POS = { 124,340 };
	const Point PARAM_CROWN_POS = { 262,338 };
	const Point PARAM_SOUL_OFFSET = { 524,0 };
	const Point PARAM_SOUL_FIRE_OFFSET = { 467,-45 };
	const RECT_F RECT_DIFFCULTY = { 0.0f,0.0f,167.0f,60.0f };
	const RECT_F RECT_GAUGE_MEMORI = { 2.0f,4.0f,9.78f,34.0f };
	const RECT_F RECT_RANK = { 0.0f,0.0f,229.0f,194.0f };
	const RECT_F RECT_CROWN = { 0.0f,0.0f,113.0f,112.0f };
	const RECT_F RECT_SOUL = { 0.0f,0.0f,37.0f,37.0f };
	const RECT_F RECT_FIRE = { 0.0f,0.0f,150.0f,131.0f };
	const RECT_F RECT_RAINBOW = { 0.0f,0.0f,487.0f,31.0f };
	const int FIRE_ANIME_TIME = 50;
	const int RAINBOW_ANIME_TIME = 16;
	const int GAUGE_START_DELAY = 2000;//ゲージ進行開始するまでの時間[ms]
	const int RESULT_END_DELAY = 4840;//ゲージ進行開始するまでの時間[ms]
	const int GAUGE_MEMORI_TIME = 57;
	const int NUMBER_START_DELAY = 880;//ゲージ終了してからナンバー開始するまでの時間[ms]
	const int NUMBER_INTERVAL = 440;//ゲージ終了してからナンバー開始するまでの時間[ms]
	const int SCORE_NUMBER_START_DELAY = 440;//ゲージ終了してからナンバー開始するまでの時間[ms]
	const int CROWN_START_DELAY = 1320;//スコア終わってから王冠開始するまでの時間[ms]
	const int RANK_START_DELAY = 1320;//王冠終わってからスコアランク開始するまでの時間[ms]

	const int RESULT_BGM_DELAY = 634;//リザルトイン音を再生してからBGMを流し始めるまでの時間[ms]
	const int RESULT_WAIT_TIME = 15000;//リザルトの演出終わってから選曲画面に移行するまでの待機時間[ms]

	CNumTexSource m_judge_num;
	CNumTexSource m_score_num;
	CTimeCounter m_ct_fire;
	CTimeCounter m_ct_rainbow;
	CTimeCounter m_ct_result;
	CTimeCounter m_ct_gauge;
	CTimeCounter m_ct_bgm_delay;
	CTimeCounter m_ct_wait;
	bool m_bgm_play;

	ST_SCORE_DATA m_score;
	ST_SCORE_DATA m_best_score[DIFF_Count];

	CFIFO m_fade_in;
	CFIFO m_fade_out;

	CAnime2 m_ani_judge_num[5];
	CAnime2 m_ani_score_num = { "Animation/Result/ScoreNumberScale" };
	CAnime2 m_ani_crown = { "Animation/Result/ScoreRankScale" };
	CAnime2 m_ani_score_rank = { "Animation/Result/ScoreRankScale" };


	bool m_key_flag[TAIKO_FLUSH_Count];
	void Decide();
	void ScoreDataImport();
	void ScoreDataExport(ST_SCORE_DATA score);
};
