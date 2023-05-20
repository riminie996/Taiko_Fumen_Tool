#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
#include "CObjDanResult.h"
using namespace GameL;

namespace MusicGame
{
	namespace Dan
	{
		enum E_DAN_GAUGE_COLOR
		{
			GAUGE_LOW,
			GAUGE_NORMAL,
			GAUGE_REACH,
			GAUGE_CLEAR,
			GAUGE_RAINBOW,
			GAUGE_Count,
		};

		const RECT_F RECT_GAUGE[GAUGE_Count] =
		{
			{ 0.0f,0.0f,644.0f,54.0f },
			{ 0.0f,54.0f,644.0f,54.0f },
			{ 0.0f,108.0f,644.0f,54.0f },
			{ 0.0f,162.0f,644.0f,54.0f },
			{ 0.0f,216.0f,644.0f,54.0f },
		};

		const RECT_F RECT_NUMBER = { 0.0f,0.0f,48.0f,58.0f };
		const RECT_F RECT_RAINBOW_NUMBER = { 0.0f,58.0f,48.0f,58.0f };
		const int NUMBER_PADDING = 38;

		const RECT_F RECT_EXAM_TYPE = { 0.0f,0.0f,247.0f,28.0f };
		const RECT_F RECT_EXAM_RANGE_MORE = { 0.0f,0.0f,54.0f,30.0f };
		const RECT_F RECT_EXAM_RANGE_LESS = { 0.0f,30.0f,54.0f,30.0f };
		const RECT_F RECT_EXAM_NUMBER = { 0.0f,0.0f,24.0f,29.0f };
		const int EXAM_NUMBER_PADDING = 16;

		const int RAINBOW_PATTERN = 16;
		const int RAINBOW_TIMER = 1350;
	}
}

class CObjDanC : public CObj
{
public:

	struct ST_DAN_SONG_SCORE
	{
		//段位道場用　1曲ごとの情報
		int judge[E_JUDGE::JUDGE_COUNT];//判定記録情報 + 連打数
		int score;				//現在のスコア
		int combo;				//現在のコンボ
		int max_combo;			//最大のコンボ
	};
	enum E_DAN_GAUGE_COLOR
	{
		GAUGE_LOW,
		GAUGE_NORMAL,
		GAUGE_REACH,
		GAUGE_CLEAR,
		GAUGE_RAINBOW,
		GAUGE_Count,
	};

	CObjDanC(vector<ST_DAN_SONG> song, vector<MusicGame::DanC> dan,int gauge_norma,int gauge_gold);
	~CObjDanC() {}
	void Init();
	void Action();
	void Draw();
	void NextSong();
	void Update();
	float GetRollTime() { return m_vec_song[m_song_number].roll_time; }
	void SubRollTime(float time);

	void AddSongJudge(E_JUDGE judge);
	void AddSongCombo();
	void AddSongScore(int add);
	void ResetSongCombo() { m_vec_score[m_song_number].combo = 0; }
	ST_DAN_SONG GetNowSong();
	int GetSongJudge(E_JUDGE judge);
	int GetSongJudge(E_JUDGE judge,int song);
	int GetGaugeNorma() { return m_norma_gauge[0]; }
	int GetSongNumber() { return m_song_number < 0 ? 0 : m_song_number; }
	bool GetFailure();
	bool GetGoldReached();
	E_DANRESULT_STATUS GetResult();
	vector<MusicGame::DanC> m_vec_dan;
private:
	


	struct ST_DAN_ANIME
	{
		CAnime2 ani_number_scale;
		CAnime2 ani_gauge_change_effect;
		E_DAN_GAUGE_COLOR before_gauge;
		CAnime2 ani_gauge_effect;
		CAnime2 ani_gauge_effect_fast;
	};


	vector<ST_DAN_SONG> m_vec_song;
	vector<ST_DAN_ANIME> m_vec_anime;
	vector<ST_DAN_SONG_SCORE> m_vec_score;

	int m_song_number;
	int m_norma_gauge[2];
	int m_triple_show_number;

	CNumTexSource m_num_value;
	CNumTexSource m_num_value_rainbow;
	CNumTexSource m_num_exam_num;
	CNumTexSource m_num_mini_value;
	CNumTexSource m_num_mini_value_rainbow;

	CTimeCounter m_ct_music_delay;
	CTimeCounter m_ct_triple_change_delay;
	bool m_music_play;

	CAnime2 m_ani_nextsong_screen = { "Animation/DanEnso/NextSongScreen" };
	CAnime2 m_ani_exam_number_fade = { "Animation/DanEnso/ExamValueFade" };
	CAnime2 m_ani_exam_gauge_fade = { "Animation/DanEnso/ExamGaugeFade" };

	CTimeCounter m_ct_rainbow;

	bool m_first_action;


	const RECT_F RECT_NUMBER = { 0.0f,0.0f,48.0f,58.0f };
	const RECT_F RECT_RAINBOW_NUMBER = { 0.0f,58.0f,48.0f,58.0f };
	const RECT_F RECT_MINI_NUMBER = { 0.0f,0.0f,23.0f,28.0f };
	const RECT_F RECT_GAUGE_BASE = { 0.0f,0.0f,1006.0f,97.0f };
	const RECT_F RECT_GAUGE_BASE_TRIPLE = { 0.0f,97.0f,1006.0f,97.0f };
	const RECT_F RECT_GAUGE[GAUGE_Count] =
	{
		{ 0.0f,0.0f,644.0f,54.0f },
		{ 0.0f,54.0f,644.0f,54.0f },
		{ 0.0f,108.0f,644.0f,54.0f },
		{ 0.0f,162.0f,644.0f,54.0f },
		{ 0.0f,216.0f,644.0f,54.0f },
	};
	const RECT_F RECT_GAUGE_EFFECT =	{ 0.0f,270.0f,644.0f,54.0f };
	const RECT_F RECT_GAUGE_FLUSH =		{ 0.0f,324.0f,644.0f,54.0f };
	const RECT_F RECT_GAUGE_MINI[GAUGE_Count] =
	{
		{ 0.0f,0.0f,0.0f,0.0f },
		{ 0.0f,0.0f,0.0f,0.0f },
		{ 0.0f,0.0f,0.0f,0.0f },
		{ 0.0f,0.0f,155.0f,21.0f },
		{ 0.0f,21.0f,155.0f,21.0f },
	};
	const RECT_F RECT_EXAM_TYPE = { 0.0f,0.0f,247.0f,28.0f };
	const RECT_F RECT_EXAM_RANGE_MORE = { 0.0f,0.0f,54.0f,30.0f };
	const RECT_F RECT_EXAM_RANGE_LESS = { 0.0f,30.0f,54.0f,30.0f };
	const RECT_F RECT_FAILED = { 0.0f,0.0f,644.0f,54.0f };
	const RECT_F RECT_EXAM_NUMBER = { 0.0f,0.0f,24.0f,29.0f };
	const RECT_F RECT_SCREEN_LEFT = { 0.0f,0.0f,474.0f,130.0f };
	const RECT_F RECT_SCREEN_RIGHT = { 474.0f,0.0f,474.0f,130.0f };
	const RECT_F RECT_MINI_SONG_NUM = { 0.0f,0.0f,0.0f,0.0f };
	const RECT_F RECT_EXAMSYMBOL = { 0.0f,0.0f,197.0f,41.0f };
	const RECT_F RECT_EXAMSYMBOL_MINI = { 0.0f,0.0f,28.0f,28.0f };
	const float GAUGE_TRIPLE_WIDTH = 428.0f;

	const Point GAUGE_BASE_POS = { 82,385 };
	const int GAUGE_BASE_HEIGHT = 106;
	const Point GAUGE_OFFSET = { 259,22 };
	const Point NUMBER_OFFSET = { 229,13 };
	const Point EXAM_TYPE_OFFSET = { 0,1 };
	const Point EXAM_RANGE_OFFSET = { 184,43 };
	const Point EXAM_NUMBER_OFFSET = { 159,43 };
	const Point GAUGE_ASSIGNMENT_POS = { 124,116 };
	const Point GAUGE_ASSIGNMENT_NUMBER_POS = { 380,125 };
	const Point DAN_SCREEN_OFFSET = { 332,193 };
	const int GAUGE_BASE_MINI_HEIGHT = 33;
	const Point MINI_NUMBER_OFFSET = { 731,15 };
	const Point MINI_GAUGE_BASE_OFFSET = { 746,21 };
	const Point MINI_GAUGE_OFFSET = { 748,22 };
	const Point MINI_EXAMSYMBOL_OFFSET = { 716,18 };
	const Point DAN_PLATE_POS = { 1117,536 };
	const int GAUGE_MEMORI_WIDTH = 14;
	const int NUMBER_PADDING = 38;
	const int NUMBER_MINI_PADDING = 14;
	const int GAUGE_RAINBOW_LOOP = 1350;//何秒でゲージがループするか[ms]
	const int GAUGE_TRIPLE_RAINBOW_LOOP = 675;//何秒でゲージがループするか[ms]
	const int EXAM_NUMBER_PADDING = 16;

	const int NEXTSONG_SHOW_CHANGE_TIME = 1700;//#NEXTSONGから表示中の条件を切り替えるまでの時間[ms]
};
