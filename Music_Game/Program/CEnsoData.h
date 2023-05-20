#pragma once 
#include "MusicGame.h"

#define SAVE_SCORE (false)
#define AUTO_AI (false)
//‰‰‘tî•ñ
class CEnsoData
{
public:
	CEnsoData();
	~CEnsoData() {}

	void JudgeAdd(E_JUDGE judge);
	void LoadFumenData(string file_name,int player);
	float GetNowTime();
	void SetTime(float time);
	//private:

	ST_ENSO_OPTION m_option;
	
	ST_SCORE_DATA m_score_data;
	ST_SCORE_DATA m_best_score_data[DIFF_Count];
	float m_now_bpm;			//Œ»İ‚ÌBPM
	CTimeCounter m_ct_now_time;	//Œ»İ‚ÌŒo‰ßŠÔ
	int m_now_signature[2];		//Œ»İ‚Ì”q ( [0] / [1] )
	int m_measure_count;			//Œ»İ‚Ì¬ß”
	float m_judge_offset;
	bool m_gogo;
	float m_roll_time;
	int m_balloon_count;
	int m_score_add;

	MusicGame::ST_FUMEN_DATA m_fumen;

	void FumenDataLoad(list<string>& command_param,int player);
};
