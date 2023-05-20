#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjStatusPanel : public CObj
{
public:
	CObjStatusPanel() {}
	~CObjStatusPanel() {}
	void Init();
	void Action();
	void Draw();
	void Draw(Point pos, E_DIFFCULTY diff);//ç∂è„äÓèÄï`âÊ
private:

	const RECT_F RECT_PLAYER_STATUS = { 0.0f,0.0f,224.0f,128.0f };
	const RECT_F RECT_NUM = { 0.0f,640.0f,12.0f,16.0f };
	const Point CROWN_NUMBER_OFFSET[(int)E_CROWN::CROWN_Count] =
	{
		{56,95},
		{117,95},
		{182,95},
	};
	const Point RANK_NUMBER_OFFSET[(int)E_SCORE_RANK::RANK_Count] =
	{
		{56,66},
		{117,66},
		{182,66},
		{56,41},
		{117,41},
		{182,41},
		{182,15},
	};
	const float NUMBER_PADDING = 9.0f;
	CNumTexSource m_num_count;
};