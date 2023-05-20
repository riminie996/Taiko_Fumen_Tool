#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjScorePanel : public CObj
{
public:
	CObjScorePanel() {}
	~CObjScorePanel() {}
	void Init();
	void Action();
	void Draw();
	void Draw(E_DIFFCULTY diff, int score);
private:
	const RECT_F RECT_SCORE_PANEL = { 0.0f,0.0f,224.0f,60.0f };
	const RECT_F RECT_DIFFCULTY = { 0.0f,60.0f,36.0f,26.0f };
	const RECT_F RECT_SCORE_NUM = { 0.0f,86.0f,16.0f,20.0f };
	const Point PANEL_POS = { 17,386 };
	const Point DIFFCULTY_OFFSET = { 19,22 };
	const Point NUMBER_OFFSET = { 162,26 };
	const float NUMBER_PADDING = 13.5f;
	CNumTexSource m_num_score;
};