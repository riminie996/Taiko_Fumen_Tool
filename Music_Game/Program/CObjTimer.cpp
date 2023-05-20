#include "CObjTimer.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

CObjTimer::CObjTimer(Point pos, int count,bool start)
{
	m_pos = pos;
	//1000ms = 1•b
	m_ct_time = { CTimeCounter(0,count,1000) };
	if (start == false)
		m_progress = false;
	else
		m_progress = true;
	m_num_time.SetTex(tex_TIMER, RECT_NUM.m_width, RECT_NUM.m_height, RECT_NUM.m_x, RECT_NUM.m_y);
}
//‰Šú‰»
void CObjTimer::Init()
{
	
}
//is
void CObjTimer::Action()
{
	if (m_progress == true)
		m_ct_time.Action();
}
//•`‰æ
void CObjTimer::Draw()
{
	COLOR gray = { 0.5f,0.5f,0.5f };
	COLOR col = m_progress == true ? Color::White : gray;
	Draw::SetColor(tex_TIMER, col);
	Draw::SetScaleX(tex_TIMER, 1.0f);
	Draw::CenterDraw(tex_TIMER, m_pos.x, m_pos.y, RECT_BASE);
	COLOR col_num = { 0.25f,0.25f,0.25f };


	int val = m_ct_time.EndValue - m_ct_time.NowValue;
	float scale_x = numOfDigit(val) >= 3 ? 2.0f / (float)numOfDigit(val) : 1.0f;

	Draw::SetColor(tex_TIMER, col_num);
	Draw::SetScaleX(tex_TIMER, scale_x);
	float padding = NUM_PADDING * scale_x;
	m_num_time.CenterDraw(val, m_pos.x + (numOfDigit(val) - 1) * padding * 0.5f, m_pos.y, padding);
}

void CObjTimer::SetCount(int count)
{
	m_ct_time = { CTimeCounter(0,count,1000) };
}
void CObjTimer::Stop()
{
	m_ct_time.Stop();
}
void CObjTimer::Start()
{
	m_ct_time.Start(0,m_ct_time.EndValue,1000);
	m_progress = true;
}
