#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjRoll : public CObj
{
public:
	CObjRoll() {}
	~CObjRoll() {}
	void Init();
	void Action();
	void Draw();
	void Add(int player);
	void End(int player);
	void BalloonExtension(int player);
private:

	const Point ROLL_BALLOON_POS[2] = { {  301,23 } ,{  301,562 } };
	const Point ROLL_NUM_OFFSET = { 53,13 };
	const Point ROLL_TEXT_OFFSET = { 82,90 };
	const float ROLL_NUM_PADDING = 53.0f;
	CAnime m_ani_number_scale = { "Animation/RollNumScale" };
	CAnime2 m_ani_roll_ballon_in[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_roll_ballon_out[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_roll_ballon_wait[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_roll_ballon_num_in[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_roll_ballon_num_out[MusicGame::MAX_PLAYER_AMOUNT];
	CNumTexSource m_num_roll;
	const RECT_F RECT_ROLL = { 0.0f,0.0f,256.0f,144.0f };
	const RECT_F RECT_ROLL_NUMBER = { 0.0f,0.0f,63.0f,75.0f };
	const RECT_F RECT_ROLL_TEXT = { 0.0f, 75.0f, 57.0f, 23.0f };
	bool m_reset_flag[MusicGame::MAX_PLAYER_AMOUNT];
	bool m_show_flag;

	int m_roll_num[MusicGame::MAX_PLAYER_AMOUNT];
	//íËêî

};
