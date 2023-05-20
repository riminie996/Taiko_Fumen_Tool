#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;


enum TAIKO_INPUT
{
	DON,
	KA,
};

class CObjNotes : public CObj
{
public:
	CObjNotes() {}
	//	CObjNotes(vector<ST_NOTES_SECTION> sec_mea) { m_vec_section_measure = sec_mea; }
	~CObjNotes() {}
	void Init();
	void Action();
	void Draw();
	void InputJudge(TAIKO_INPUT input, int player);
	//	void Section(int measure, E_JUDGE judge,bool b_return);
	//	int GetSecMaxNotes() { return m_vec_section_measure[m_section_count].max_notes_count; }
	void BranchStart(E_BRANCH branch, int start, int end, int player);


private:

	const RECT_F RECT_NOTES = { 0.0f,0.0f,128.0f,128.0f };
	const RECT_F RECT_ROLL_CENTER = { 1024.0f,0.0f,5.0f,128.0f };
	const RECT_F RECT_ROLL_CENTER_BIG = { 1152.0f,0.0f,5.0f,128.0f };
	const RECT_F RECT_ROLL_RIGHT =		{ 1024.0f,128.0f,128.0f,128.0f };
	const RECT_F RECT_ROLL_RIGHT_BIG =	{ 1152.0f,128.0f,128.0f,128.0f };

	const RECT_F RECT_BALLOON = { 1408.0f , 0.0f, 256.0f, 128.0f };
	const RECT_F RECT_BALLOON_RIGHT = { 1024.0f , 256.0f, 128.0f, 128.0f };
	const RECT_F RECT_KUSUDAMA = { 1152.0f , 256.0f, 128.0f, 128.0f };
	const RECT_F RECT_BOMB = { 0.0f , 128.0f, 128.0f, 128.0f };
	
	const float NOTES_BEAT_WIDTH = 4.0f;
	const float NOTES_RED_RETURN_POWER = 1.2F;
	const float BALLOON_RIGHT_OFFSET = 109.0f;


	bool m_first_flag;

	list<ST_NOTES> m_list_notes[MusicGame::MAX_PLAYER_AMOUNT];
	list<ST_NOTES> m_list_roll[MusicGame::MAX_PLAYER_AMOUNT];

	int m_section_count;
	bool m_roll_flag[MusicGame::MAX_PLAYER_AMOUNT];
	int m_notes_count;
	int m_roll_remain;

//	vector<ST_NOTES_SECTION> m_vec_section_measure;

	const RECT_F RECT_NUM = { 0.0f,0.0f,40.0f,49.0f };
	const RECT_F RECT_SE_NOTES = { 0.0f,0.0f,128.0f,32.0f };
	const float NUM_WIDTH = 40.0f;
	const Point NUM_POS = { 240,0 };
	const Point REMAIN_POS = { 17,508 };
	CNumTexSource m_notes_remain_num;
	CCounter m_ct_auto_roll;

	void JudgeProcess(E_JUDGE judge,bool moji,bool big,E_NOTES_TYPE type,int player,float time);

	float AINextJudgeTiming();

	CAnime3 m_ani_notes_face;
};
