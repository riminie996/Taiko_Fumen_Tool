#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjScore : public CObj
{
public:
	CObjScore() {}
	~CObjScore() {}
	void Init();
	void Action();
	void Draw();
	void AddScore(int add,int player);
private:

	//íËêî
	const RECT_F RECT_SCORE_NUM = { 0.0f,0.0f,25.0f,32.0f };
	const Point P1_SCORE_POS[2] = { { 155,194 },{ 155,498 } };
	const Point SCORE_EFFECT_OFFSET = { -47,15 };
	const Point BESTSCORE_POS = { 105,254 };
	const float SCORE_PADDING = 20;
	const COLOR P1_SCORE_COLOR[2] = { { 0.996f,0.392f,0.090f },{ 0.318f,0.769f,0.694f } };
	const Point SCORENUM_EFFECT_OFFSET = { 13,15 };
	const Point RANK_POS[2] = { { 98,98 },{ 98,633 } };
	const RECT_F RECT_RANK = { 0.0f,0.0f,140.0f,120.0f };
	const RECT_F RECT_NUMEFFECT = { 0.0f,26.0f,25.0f,25.0f };
	const RECT_F RECT_EFFECT = { 0.0f,0.0f,264.0f,26.0f };

	const RECT_F RECT_BEST_BACK = { 0.0f,0.0f,224.0f,64.0f };
	const RECT_F RECT_BEST_EFFECT = { 0.0f,64.0f,224.0f,64.0f };
	const RECT_F RECT_BEST_LIGHT[4] = 
	{
		{ 0.0f,128.0f,224.0f,64.0f },
		{ 0.0f,192.0f,224.0f,64.0f },
		{ 0.0f,256.0f,224.0f,64.0f },
		{ 0.0f,320.0f,224.0f,64.0f },
	};
	const RECT_F RECT_BEST_TEXT = { 0.0f,384.0f,224.0f,64.0f };

	CNumTexSource m_num_score;
	CAnime3 m_ani_score_scale[MusicGame::MAX_PLAYER_AMOUNT];

	struct stAddScore
	{
		int add = 0;

		CAnime2 ani_add_score_in;
		vector<CAnime2> vec_ani_add_score_out;
	};
	list<stAddScore> m_list_add[2];
	stAddScore m_add;

	CAnime2 m_ani_score_rank_appear[2][(int)E_SCORE_RANK::RANK_Count];
	CAnime2 m_ani_score_effect_appear;
	CAnime2 m_ani_score_effect_wait;
	CAnime2 m_ani_scorenum_effect;

	CAnime2 m_ani_bestscore_back;
	CAnime2 m_ani_bestscore_effect;
	CAnime2 m_ani_bestscore_light;
	CAnime2 m_ani_bestscore_text;

	CLayout m_lyt_score_bg[MusicGame::MAX_PLAYER_AMOUNT];
};
