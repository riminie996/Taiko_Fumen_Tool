#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjFlyingNotes : public CObj
{
public:
	CObjFlyingNotes() {}
	~CObjFlyingNotes() {}
	void Init();
	void Action();
	void Draw();
	void Add(E_NOTES_TYPE notes, bool rainbow,int player);
private:
	struct ST_FLYING_NOTES
	{
		E_NOTES_TYPE type;
		CAnime3 ani_flying;
		CAnime2 ani_flying_effect;
		CAnime2 ani_notes_effect;
		bool rainbow;
		CCounter ct_firework_interval;


	};
	struct ST_BIG_EFFECT
	{
		Point pos;
		CCounter ct_pattern;
	};
	ST_FLYING_NOTES m_st_flying[2];


	const RECT_F RECT_EFFECT = { 0.0f,0.0f,180.0f,180.0f };
	const RECT_F RECT_FIREWORK = { 0.0f,0.0f,171.0f,171.0f };
	const static int FIREWORK_INTERVAL_FRAME = 3;
	const static int FIREWORK_PATTERN = 13;
	const static int FLYING_MAX_COUNT = 16;

	const Point EFFECT_POS[2] = 
	{
		{ 1225, 160}, 
		{ 1225, 551} 
	};

	const Point FLYING_START_POS[2] =
	{
		{ MusicGame::NOTES_JUDGE_LINE[0].x , MusicGame::NOTES_JUDGE_LINE[0].y },
		{ MusicGame::NOTES_JUDGE_LINE[1].x , MusicGame::NOTES_JUDGE_LINE[1].y }
	};
	list<ST_FLYING_NOTES> m_list_flying[2];
	list<ST_BIG_EFFECT> m_list_effect[2];
};
