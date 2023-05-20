#include "CObjRoll.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//初期化
void CObjRoll::Init()
{
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_roll_num[i] = 0;
		m_reset_flag[i] = true;

		m_ani_roll_ballon_in[i].LoadData("Animation/Enso/RollBalloon_In");
		m_ani_roll_ballon_out[i].LoadData("Animation/Enso/RollBalloon_Out");
		m_ani_roll_ballon_wait[i].LoadData("Animation/Enso/RollBalloon_Wait");
		m_ani_roll_ballon_num_in[i].LoadData("Animation/Enso/Roll_Number_In");
		m_ani_roll_ballon_num_out[i].LoadData("Animation/Enso/Roll_Number_Out");
	}
		m_show_flag = false;
	m_num_roll.SetTex(tex_ROLL_NUMBER, RECT_ROLL_NUMBER.m_width, RECT_ROLL_NUMBER.m_height);
}
//進行
void CObjRoll::Action()
{
	m_ani_number_scale.Action();

	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{

		if (m_ani_roll_ballon_wait[i].GetEnd())
		{
			//Outを進行させる
			if (m_reset_flag[i] == true)
			{
				if (!m_ani_roll_ballon_out[i].GetStart())
				{
					m_ani_roll_ballon_out[i].Start();
					m_ani_roll_ballon_num_out[i].Start();
				}

				m_ani_roll_ballon_out[i].Action();
				m_ani_roll_ballon_num_out[i].Action();
			}
		}
		else if (m_ani_roll_ballon_in[i].GetEnd())
		{
			if (!m_ani_roll_ballon_wait[i].GetStart())
				m_ani_roll_ballon_wait[i].Start();

			//Waitを進行させる
			m_ani_roll_ballon_wait[i].Action();
		}
		else if (!m_ani_roll_ballon_in[i].GetEnd())
		{


			//Inを進行させる
			m_ani_roll_ballon_in[i].Action();
			m_ani_roll_ballon_num_in[i].Action();
		}
	}
}
//描画
void CObjRoll::Draw()
{
	int roll_type = 0;

	float roll_opacity = 1.0f;
	float num_opacity = 1.0f;
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		if (m_ani_roll_ballon_wait[i].GetEnd())
		{
			//Outを進行させる
			roll_type = (int)m_ani_roll_ballon_out[i].GetValue().pattern;
			roll_opacity = m_ani_roll_ballon_out[i].GetValue().opacity;
			num_opacity = m_ani_roll_ballon_num_out[i].GetValue().opacity;
		}
		else if (m_ani_roll_ballon_in[i].GetEnd())
		{
			//Waitを進行させる
			roll_type = (int)m_ani_roll_ballon_wait[i].GetValue().pattern;
			roll_opacity = 1.0f;
			num_opacity = 1.0f;
		}
		else if (!m_ani_roll_ballon_in[i].GetEnd())
		{
			//Waitを進行させる
			roll_type = (int)m_ani_roll_ballon_in[i].GetValue().pattern;
			roll_opacity = m_ani_roll_ballon_in[i].GetValue().opacity;
			num_opacity = m_ani_roll_ballon_num_in[i].GetValue().opacity;
		}

		Draw::SetOpacity(tex_ROLL, roll_opacity);
		Draw::SetOpacity(tex_ROLL_NUMBER, num_opacity);

		RECT_F rect_roll = { 0.0f,RECT_ROLL.m_height * roll_type,RECT_ROLL.m_width,RECT_ROLL.m_height };
		Draw::Draw(tex_ROLL, ROLL_BALLOON_POS[i].x, ROLL_BALLOON_POS[i].y, rect_roll);

		Draw::SetScaleY(tex_ROLL_NUMBER, m_ani_number_scale.GetValue());
		float y_move = m_ani_number_scale.GetValue() * RECT_ROLL_NUMBER.m_height - RECT_ROLL_NUMBER.m_height;
		m_num_roll.Draw(m_roll_num[i], ROLL_BALLOON_POS[i].x + ROLL_NUM_OFFSET.x + (numOfDigit(m_roll_num[i]) * ROLL_NUM_PADDING / 2.0f), ROLL_BALLOON_POS[i].y + ROLL_NUM_OFFSET.y - y_move, ROLL_NUM_PADDING);
		Draw::SetScaleY(tex_ROLL_NUMBER, 1.0f);
		Draw::Draw(tex_ROLL_NUMBER, ROLL_BALLOON_POS[i].x + ROLL_TEXT_OFFSET.x, ROLL_BALLOON_POS[i].y + ROLL_TEXT_OFFSET.y, RECT_ROLL_TEXT);
	}
}

void CObjRoll::Add(int player)
{
	if (m_reset_flag[player] == true)
	{
		//アニメーション最初から
		m_ani_roll_ballon_in[player].Start();
		m_ani_roll_ballon_num_in[player].Start();
		//スタートフラグを初期化
		m_ani_roll_ballon_out[player].Start();
		m_ani_roll_ballon_out[player].End();
		m_ani_roll_ballon_num_out[player].Start();
		m_ani_roll_ballon_num_out[player].End();

		m_reset_flag[player] = false;
		m_roll_num[player] = 0;
	}

	m_roll_num[player]++;
	m_show_flag = true;
	m_ani_number_scale.Start();

	BalloonExtension(player);
}

void CObjRoll::End(int player)
{
	m_reset_flag[player] = true;
}

void CObjRoll::BalloonExtension(int player)
{
	m_ani_roll_ballon_wait[player].Start();
}