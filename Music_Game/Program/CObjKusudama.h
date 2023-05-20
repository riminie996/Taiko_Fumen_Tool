#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjKusudama : public CObj
{
public:
	CObjKusudama() {}
	~CObjKusudama() {}
	void Init();
	void Action();
	void Draw();
	void Start(int max);
	bool Sub();
	void End();
private:

	const Point KUSUDAMA_POS = { 640,230 };
	const Point RENDA_TEXT_POS = { 640,94 };
	const Point KUSUDAMA_NUM_POS = { 559,153 };
	const float KUSUDAMA_NUM_PADDING = 158.0f;
	CAnime m_ani_number_scale = { "Animation/BallonNumScale" };
	CNumTexSource m_num_roll;
	const RECT_F RECT_NUMBER = { 0.0f,0.0f,162.0f,196.0f };
	const RECT_N RECT_KUSUDAMA = { 0,0,1343,1245 };
	const RECT_N RECT_RENDA = { 0,0,242,106 };
	const RECT_N RECT_CONCENTRATION = { 0,0,640,720 };
	const RECT_N RECT_KUSUDAMA_BREAK[4] = 
	{
		{ 0,1248,1343,1245 } ,
		{ 0,2496,1343,1245 } ,
		{ 0,3744,1343,1245 } ,
		{ 0,4992,1343,1245 } ,
	};

	CTimeCounter m_ct_time_remain;
	CCounter m_ct_break_opacity;
	bool m_reset_flag;
	bool m_show_flag;
	int m_roll_remain;
	int m_max_val;
	//íËêî

	
	
	
	CAnime3 m_ani_kusudama_appear;
	CAnime3 m_ani_kusudama_wait;
	CAnime3 m_ani_kusudama_break;
	CAnime3 m_ani_text_appear;
	CAnime3 m_ani_text_wait;
	CAnime3 m_ani_concentration_line;
	
	void Break();
	void ConcentrationLineDraw();

};
