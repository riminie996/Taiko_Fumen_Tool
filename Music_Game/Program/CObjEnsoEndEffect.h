#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjEnsoEndEffect : public CObj
{
public:
	CObjEnsoEndEffect() {}
	~CObjEnsoEndEffect() {}
	void Init();
	void Action();
	void Draw();

private:

	enum E_PHASE_ENSO_END
	{
		FAILED,
		CLEARED,
		FULLCOMBO,
		DONDAFULLCOMBO,
		//段位道場用演出
		DAN_FAILED,
		DAN_CLEARED,
		DAN_FULLCOMBO,
		DAN_DONDAFULLCOMBO,
		DAN_GOLD_CLEARED,
		DAN_GOLD_FULLCOMBO,
		DAN_GOLD_DONDAFULLCOMBO,
	};

	E_PHASE_ENSO_END m_phase[MusicGame::MAX_PLAYER_AMOUNT];
	bool m_sound_play;
	CCounter m_ct_sound_delay;
	const float VOICE_FAILED_DELAY = 12.0f;//失敗ボイスを再生するまでの遅延[frame]
	const float VOICE_CLEARED_DELAY = 3.0f;//成功ボイスを再生するまでの遅延[frame]
	const float VOICE_FULLCOMBO_DELAY = 3.0f;//フルコンボボイスを再生するまでの遅延[frame]
	const float VOICE_DONDAFULLCOMBO_DELAY = 3.0f;//ドンダフルコンボボイスを再生するまでの遅延[frame]

	const RECT_N RECT_CLEAR_TEXT = { 0,0,90,90 };
	const RECT_N RECT_CLEAR_TEXT_ALL = { 0,96,342,96 };
	const RECT_N RECT_CLEAR_TEXT_LIGHT = { 0,192,342,96 };
	const RECT_N RECT_FULLCOMBO_TEXT = { 0,0,640,128 };
	const RECT_N RECT_FULLCOMBO_TEXT_LIGHT = { 0,128,640,128 };
	const RECT_N RECT_FULLCOMBO_TEXT_EFFECT = { 0,256,640,128 };
	const float FULLCOMBO_TEXT_OFFSET = 107.0f;
	const RECT_F RECT_UCHIWA = { 0.0f,0.0f,220.0f,220.0f };
	const int CLEAR_TEXT_MOJI = 5;
	const Point CLEAR_TEXT_POS = { 633,211 };
	const Point FULLCOMBO_TEXT_POS = { 482,192 };
	const int CLEAR_MOJI_OFFSET[5] =
	{
		0,58,117,185,256
	};

	const Point FAILED_TEXT_POS = { 301,215 };
	const Point UCHIWA_LEFT_POS = { 382,153 };
	const Point UCHIWA_RIGHT_POS = { 1012,154 };
	const Point PAPER_LEFT_POS = { 492,153 };
	const Point PAPER_RIGHT_POS = { 908,154 };
	const Point BG_POS = { 332,193 };
	const Point BACHIO_LEFT_POS = { 521,348 };//左下基準,
	const Point BACHIO_RIGHT_POS = { 1087,348 };//右下基準
	
	//Paper
	const RECT_F RECT_PAPER = { 0.0f,0.0f,214.0f,175.0f };
	const static int PAPER_IN_PATTERN = 65;
	const static int PAPER_LOOP_PATTERN = 50;

	CCounter m_ct_paper_in;
	CCounter m_ct_paper_loop;

	CAnime2 m_ani_failed_text = { "Animation/Enso/End/StageFailedText" };
	CAnime2 m_ani_failed_bachio_L = { "Animation/Enso/End/StageFailedBachioL" };
	CAnime2 m_ani_failed_bachio_R = { "Animation/Enso/End/StageFailedBachioR" };

	CAnime2 m_ani_cleared_text[5];

	CAnime2 m_ani_fullcombo_uchiwa = { "Animation/Enso/End/StageFullcomboUchiwa" };
	CAnime2 m_ani_fullcombo_uchiwa_loop = { "Animation/Enso/End/StageFullcomboUchiwaLoop" };
	CAnime2 m_ani_fullcombo_text = { "Animation/Enso/End/StageFullcomboText" };
	CAnime2 m_ani_fullcombo_text_effect = { "Animation/Enso/End/StageFullcomboTextEffect" };
	CAnime2 m_ani_fullcombo_clear_text = { "Animation/Enso/End/StageFullcomboClearedText" };
	CAnime2 m_ani_fullcombo_clear_text_effect = { "Animation/Enso/End/StageFullcomboClearedTextEffect" };
	CAnime2 m_ani_fullcombo_bachio_L = { "Animation/Enso/End/StageFullcomboBachioL" };
	CAnime2 m_ani_fullcombo_bachio_R = { "Animation/Enso/End/StageFullcomboBachioR" };
	CAnime2 m_ani_dondafullcombo_bachio_L = { "Animation/Enso/End/StageDondaFullcomboBachioL" };
	CAnime2 m_ani_dondafullcombo_bachio_effect = { "Animation/Enso/End/StageDondaFullcomboBachioEffect" };
	CAnime2 m_ani_dondafullcombo_bg = { "Animation/Enso/End/StageDondaFullcomboBg" };
	CTimeCounter m_ct_uchiwa_loop;

	CAnime3 m_ani_cleared;
	CAnime3 m_ani_fullcombo;
	CAnime3 m_ani_dondafullcombo;
	CTexture m_tex_bachio_L[9];
	CTexture m_tex_bachio_effect_L[2];
	CTexture m_tex_bachio_R[9];
	CTexture m_tex_bachio_effect_R[2];
	CTexture m_tex_cleared;
	CTexture m_tex_fullcombo_text;
	CTexture m_tex_star;

	//星エフェクト用変数&構造体
	CAnime2 m_default_star;
	struct ST_STAR
	{
		CAnime2 ani;
		int delay_ms;
		Point pos;

		ST_STAR(int x, int y, int delay)
		{
			pos.x = x;
			pos.y = y;
			delay_ms = delay;
		}
	};
	CTimeCounter m_ct_star;
	vector<ST_STAR> m_vec_star;

	//パラメータ
	const int CLEARED_STAR[7][3] =
	{
		{804,208,360},
		{926,208,430},
		{684,208,530},
		{726,304,600},
		{962,290,700},
		{644,287,760},
		{874,304,760},
	};


	bool first_action;
};
