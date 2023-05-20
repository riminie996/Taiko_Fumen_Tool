#include "CObjBalloon.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//èâä˙âª
void CObjBalloon::Init()
{
	m_reset_flag = true;
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_show_flag[i] = false;
		m_roll_remain[i] = 0;

		if (MusicGame::g_mode == E_GAME_MODE::ENSO)
		{
			m_lyt_balloon[i].LoadData("Layout/Enso/Balloon/Balloon_" + to_string(i + 1) + "P");
			m_lyt_fukidashi[i].LoadData("Layout/Enso/Balloon/Fukidashi_" + to_string(i + 1) + "P");
			m_lyt_number[i].LoadData("Layout/Enso/Balloon/BalloonNumber_" + to_string(i + 1) + "P");
		}
		else if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
		{
			m_lyt_balloon[i].LoadData("Layout/Battle/Balloon/Balloon_" + to_string(i + 1) + "P");
			m_lyt_fukidashi[i].LoadData("Layout/Battle/Balloon/Fukidashi_" + to_string(i + 1) + "P");
			m_lyt_number[i].LoadData("Layout/Battle/Balloon/BalloonNumber_" + to_string(i + 1) + "P");
		}

		m_ani_balloon_fadeout[i].LoadData("Animation/Enso/Balloon/Balloon_Break");
	}
	m_num_roll.SetTex(tex_BALLOON_NUMBER, RECT_ROLL_NUMBER.m_width, RECT_ROLL_NUMBER.m_height);
	m_ct_break_opacity = { CCounter(1.0f,0.0f,1.0f,STOP) };
}
//êiçs
void CObjBalloon::Action()
{
	m_ani_number_scale.Action();
	m_ct_break_opacity.Sub(OPACITY_SPEED);
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_ani_balloon_fadeout[i].Action();
	}
}
//ï`âÊ
void CObjBalloon::Draw()
{
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		if (m_show_flag[i] == true)
		{
			float rect_y = (float)(m_max_val[i] - m_roll_remain[i]) / (float)m_max_val[i] * (7);
			RECT_N rect_balloon = m_lyt_balloon[i].GetSource();
			rect_balloon.m_y = (int)rect_y * rect_balloon.m_height;
			MusicGame::g_tex_balloon.m_opacity = 1.0f;
			MusicGame::g_tex_balloon.Draw(m_lyt_balloon[i].GetPos().x, m_lyt_balloon[i].GetPos().y, rect_balloon);

			MusicGame::g_tex_balloon_fukidashi.Draw(m_lyt_fukidashi[i].GetPos().x, m_lyt_fukidashi[i].GetPos().y);

			float y_scale = m_ani_number_scale.GetValue() * BALLOON_NUM_SCALE;
			Draw::SetScaleX(tex_BALLOON_NUMBER, BALLOON_NUM_SCALE);
			Draw::SetScaleY(tex_BALLOON_NUMBER, y_scale);
			float y_move = y_scale * RECT_ROLL_NUMBER.m_height - BALLOON_NUM_SCALE *RECT_ROLL_NUMBER.m_height;
			m_num_roll.Draw(m_roll_remain[i], m_lyt_number[i].GetPos().x + ((numOfDigit(m_roll_remain[i]) - 1) * BALLOON_NUM_PADDING / 2.0f), m_lyt_number[i].GetPos().y - y_move, BALLOON_NUM_PADDING);
		}
		else
		{
			if (m_ani_balloon_fadeout[i].GetStart())
			{
				RECT_N rect_balloon = m_lyt_balloon[i].GetSource();
				rect_balloon.m_y = MusicGame::g_tex_balloon.GetTexSizeH() - rect_balloon.m_height;
				MusicGame::g_tex_balloon.m_opacity = m_ani_balloon_fadeout[i].GetValue(0).opacity;
				MusicGame::g_tex_balloon.Draw(m_lyt_balloon[i].GetPos().x, m_lyt_balloon[i].GetPos().y, rect_balloon);
			}
		}
	}
}
void CObjBalloon::Start(int max, int player)
{
	if (m_show_flag[player] == true)return;

	m_max_val[player] = max;
	m_show_flag[player] = true;
}
void CObjBalloon::Set(int val, int player)
{
	m_roll_remain[player] = val;
	m_ani_number_scale.Start();
}
void CObjBalloon::Break(int player)
{
	m_show_flag[player] = false;
	m_ct_break_opacity.Reset();
	m_ani_balloon_fadeout[player].Start();
}
void CObjBalloon::End(int player)
{
	m_show_flag[player] = false;
}