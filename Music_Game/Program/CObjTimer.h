#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjTimer : public CObj
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="count"></param>
	/// <param name="start">ê∂ê¨Ç∆ìØéûÇ…äJénÇ∑ÇÈÇ©ÅB</param>
	CObjTimer(Point pos, int count,bool start);
	~CObjTimer() {}
	void Init();
	void Action();
	void Draw();
	void Start();
	void Stop();
	int GetCount();
	void SetCount(int count);
private:

	const RECT_F RECT_NUM = { 0.0f,152.0f,43.0f,69.0f };
	const RECT_F RECT_BASE = { 0.0f,0.0f,152.0f,152.0f };
	const RECT_F RECT_EFFECT = { 152.0f,0.0f,152.0f,152.0f };
	const float NUM_PADDING = 43.0f;

	CTimeCounter m_ct_time;
	Point m_pos;
	CNumTexSource m_num_time;
	bool m_progress;
};