#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjJudgeMoji : public CObj
{
public:
	CObjJudgeMoji() {}
	~CObjJudgeMoji() {}
	void Init();
	void Action();
	void Draw();
	void Add(E_JUDGE judge,bool big,int player,float time = 0.0f);
private:
	enum class E_EXPLOSION_TYPE
	{
		GREAT,
		GOOD,
		GREAT_BIG,
		GOOD_BIG,
	};
	struct JudgeMoji
	{
		E_JUDGE judge;
		CAnime2 ani;
		float time;
	};
	struct stExplosion
	{
		JudgeMoji moji;
		E_EXPLOSION_TYPE effect_type;
		CAnime3 ani;
		void ExplosionDraw()
		{

		}
	};

	JudgeMoji m_ani_moji;
	stExplosion m_ani_exp;
	stExplosion m_ani_exp_big;

	//íËêî
	const RECT_F RECT_JUDGE[JUDGE_COUNT]
	{ 
		{ 0.0f,0.0f,128.0f,64.0f },
		{ 0.0f,64.0f,128.0f,64.0f },
		{ 0.0f,128.0f,128.0f,64.0f },
		{ 0.0f,0.0f,0.0f,0.0f },
	};
	const RECT_F RECT_EXPLOSION = { 0.0f,0.0f,256.0f,256.0f };
	const Point EXPLOSION_POS = { 64,64 };
	const Point JUDGE_OFFSET = { 0,-53 };
	const float APPEAR_SPEED = 0.1f;
	const float FADE_SPEED = 0.06f;
	const float Y_MOVE_DISTANCE = -32.0f;

//	list<JudgeMoji> m_list_judge[MusicGame::MAX_PLAYER_AMOUNT];
	list<stExplosion> m_list_ani_explosion[MusicGame::MAX_PLAYER_AMOUNT];

//	CAnime m_ani_explosion = { "Animation/HitExplosion" };
	CNumTexSource m_num_judge[3];
	const RECT_F RECT_NUMBER[JUDGE_COUNT]
	{
		{ 0.0f,	0.0f,	19.0f,64.0f },
		{ 0.0f,	64.0f,19.0f,64.0f },
		{ 0.0f,	128.0f,19.0f,64.0f },
		{ 0.0f,0.0f,0.0f,0.0f },
	};
	const RECT_F RECT_COMMA[JUDGE_COUNT]
	{
		{ 242.0f,	0.0f,	14.0f,64.0f },
		{ 242.0f,	64.0f,14.0f,64.0f },
		{ 242.0f,	128.0f,14.0f,64.0f },
		{ 0.0f,0.0f,0.0f,0.0f },
	};
	const RECT_F RECT_PLUS = { 190.0f,	0.0f,	17.0f,64.0f };
	const RECT_F RECT_MINUS = { 207.0f,	0.0f,	14.0f,64.0f };
	const RECT_F RECT_PLUS_MINUS = { 221.0f,	0.0f,	21.0f,64.0f };
	const float NUMBER_PADDING = 19.0f;
};
