#include "CObjComboBalloon.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//èâä˙âª
void CObjComboBalloon::Init()
{

	for(int i = 0;i<((UserData*)Save::GetData())->m_player_amount;i++)
	{
		m_ani_combo_balloon[i].LoadData("Animation/Enso/ComboBalloon");
		m_ani_combo_balloon_number[i].LoadData("Animation/Enso/ComboBalloonNumber");
		m_num_combo[i].SetTex(tex_COMBOBALLOON_NUMBER, RECT_NUM.m_width, RECT_NUM.m_height,0.0f, i * RECT_NUM.m_height);
	}
}
//êiçs
void CObjComboBalloon::Action()
{

	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_ani_combo_balloon[i].Action();
		m_ani_combo_balloon_number[i].Action();
	}
}
//ï`âÊ
void CObjComboBalloon::Draw()
{
	if (((UserData*)Save::GetData())->m_player_amount <= 2)
	{
		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		{
			bool is1000combo = m_combo_value[i] >= 1000;
			Draw::SetOpacity(tex_COMBOBALLOON, m_ani_combo_balloon[i].GetValue().opacity);
			Draw::SetOpacity(tex_COMBOBALLOON_NUMBER, m_ani_combo_balloon_number[i].GetValue().opacity);

			RECT_F rect_balloon = RECT_BALLOON;
			rect_balloon.m_x = (int)m_ani_combo_balloon[i].GetValue().pattern * RECT_BALLOON.m_width;
			rect_balloon.m_y = i * RECT_BALLOON.m_height;
			Draw::Draw(tex_COMBOBALLOON, COMBO_BALLOON_POS[i].x, COMBO_BALLOON_POS[i].y, rect_balloon);

			int padding = is1000combo ? NUM_PADDING[1] : NUM_PADDING[0];
			float scale_x = is1000combo ? COMBO_NUM_SCALE_1000COMBO : 1.0f;

			Draw::SetScaleX(tex_COMBOBALLOON_NUMBER, scale_x);
			m_num_combo[i].Draw(m_combo_value[i], is1000combo ? COMBO_BALLOON_POS[i].x + COMBO_BALLOON_NUMBER_1000COMBO_OFFSET.x : COMBO_BALLOON_POS[i].x + COMBO_BALLOON_NUMBER_OFFSET.x, COMBO_BALLOON_POS[i].y + COMBO_BALLOON_NUMBER_OFFSET.y, padding);

			Draw::SetScaleX(tex_COMBOBALLOON_NUMBER, 1.0f);
			Draw::Draw(tex_COMBOBALLOON_NUMBER,  is1000combo ? COMBO_BALLOON_POS[i].x + COMBO_BALLOON_TEXT_1000COMBO_OFFSET.x : COMBO_BALLOON_POS[i].x + COMBO_BALLOON_TEXT_OFFSET.x, COMBO_BALLOON_POS[i].y + COMBO_BALLOON_TEXT_OFFSET.y, RECT_TEXT);
		}
	}
}

void CObjComboBalloon::AnimeStart(int val,int player)
{
	m_combo_value[player] = val;
	m_ani_combo_balloon[player].Start();
	m_ani_combo_balloon_number[player].Start();
}