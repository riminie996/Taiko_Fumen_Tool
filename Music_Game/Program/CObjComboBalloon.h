#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjComboBalloon : public CObj
{
public:
	CObjComboBalloon() {}
	~CObjComboBalloon() {}
	void Init();
	void Action();
	void Draw();
	void AnimeStart(int val,int player);
private:
	const RECT_F RECT_NUM = { 0.0f,0.0f,53.0f,62.0f };
	const RECT_F RECT_TEXT = { 0.0f,124.0f,76.0f,30.0f };
	const RECT_F RECT_BALLOON = { 0.0f,0.0f,360.0f,192.0f };
	const Point COMBO_BALLOON_POS[2] = { { 295,-13 } ,{ 295,546 } };
	const Point COMBO_BALLOON_NUMBER_OFFSET = { 134,60 };
	const Point COMBO_BALLOON_NUMBER_1000COMBO_OFFSET = { 147,60 };
	const Point COMBO_BALLOON_TEXT_OFFSET = { 185,95 };
	const Point COMBO_BALLOON_TEXT_1000COMBO_OFFSET = { 185,95 };
	const float COMBO_NUM_SCALE_1000COMBO = { 0.85f };
	const float NUM_PADDING[2] = { 42,36 };

	CNumTexSource m_num_combo[MusicGame::MAX_PLAYER_AMOUNT];
	int m_combo_value[MusicGame::MAX_PLAYER_AMOUNT];

	CAnime2 m_ani_combo_balloon[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_combo_balloon_number[MusicGame::MAX_PLAYER_AMOUNT];
};
