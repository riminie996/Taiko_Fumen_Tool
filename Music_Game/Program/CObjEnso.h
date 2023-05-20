#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjEnso : public CObj
{
public:
	CObjEnso(string file_name,ST_ENSO_OPTION option);
	~CObjEnso() {}
	void Init();
	void Action();
	void Draw();
	CEnsoData m_enso[MusicGame::MAX_PLAYER_AMOUNT];
	float m_beat;
	void EnsoStop();
	bool GetGOGO() { return m_enso[0].m_gogo; }
	void SubRollRemain(float time);
	int GetRollRemain() { return m_roll_remain; }
	void BranchInfoReset(int player);
	void AddMeasureCount(int player);
	int GetMeasureCount();
	void AddBranchJudge(E_JUDGE judge,int player) { m_branch_judge[player][judge]++; }
	int GetBranchJudgePercent(int player) {return  (float)(m_branch_judge[player][JUST]) / (float)(m_branch_judge[player][JUST] + m_branch_judge[player][HIT] + m_branch_judge[player][MISS]) * 100.0f; }
	void SetBranchHold(int player) { m_branch_hold[player] = true; }
private:
	string GetTestFumenStr();
	void SetSENotes();

	bool m_key_flag;
	bool m_play_start;
	bool m_play_end;
	int m_roll_remain;
	float m_roll_time;
	E_BRANCH m_branch[MusicGame::MAX_PLAYER_AMOUNT];//ñ{óàÇÃï™äÚ
	E_BRANCH m_show_branch;//åªç›ï\é¶íÜÇÃï™äÚ
	//ïàñ ï™äÚópÇÃèÓïÒ
	int m_branch_judge[MusicGame::MAX_PLAYER_AMOUNT][JUDGE_COUNT];
	int m_branch_score[MusicGame::MAX_PLAYER_AMOUNT];
	bool m_branch_hold[MusicGame::MAX_PLAYER_AMOUNT];
	bool m_first_action;
	bool m_to_result;


	const int FADEOUT_DELAY = 6600;
	const Point JUDGE_PANEL_POS = { 6,31 };
	const Point JUDGE_NUMBER_OFFSET = { 107,13 };
	const int JUDGE_NUMBER_HEIGHT = 17;
	const int JUDGE_NUMBER_PADDING = 11;
	const RECT_F RECT_JUDGE_NUMBER = { 0.0f,0.0f,14.0f,16.0f };

	const Point NUM_POS = { 240,0 };
	const float NUM_WIDTH = 11.0f;
	CTimeCounter m_ct_fade_delay;
	CFIFO m_fade_out;
	CNumTexSource m_judge_num;
};
