#include "CObjStatusPanel.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

//èâä˙âª
void CObjStatusPanel::Init()
{
	m_num_count.SetTex(tex_STATUSPANEL, RECT_NUM.m_width, RECT_NUM.m_height, RECT_NUM.m_x, RECT_NUM.m_y);
}
//êiçs
void CObjStatusPanel::Action()
{
}
//ï`âÊ
void CObjStatusPanel::Draw()
{
}

void CObjStatusPanel::Draw(Point pos, E_DIFFCULTY diff)
{
	//11,209
	RECT_F rect_panel = RECT_PLAYER_STATUS;
	rect_panel.m_y = (int)diff * rect_panel.m_height;
	Draw::Draw(tex_STATUSPANEL, pos.x, pos.y, rect_panel);

	for (int i = 0; i < (int)E_CROWN::CROWN_Count; i++)
	{
		int val = MusicGame::g_player_status.crown_count[(int)diff][i];

		if (diff == E_DIFFCULTY::DIFF_EDIT)
			val += MusicGame::g_player_status.crown_count[(int)E_DIFFCULTY::DIFF_ONI][i];

		m_num_count.Draw(val, pos.x + CROWN_NUMBER_OFFSET[i].x + (numOfDigit(val) - 1) * NUMBER_PADDING * 0.5f, pos.y + CROWN_NUMBER_OFFSET[i].y, NUMBER_PADDING);
	}
	for (int i = 0; i < (int)E_SCORE_RANK::RANK_Count; i++)
	{
		int val = MusicGame::g_player_status.rank_count[(int)diff][i];
		if (diff == E_DIFFCULTY::DIFF_EDIT)
			val += MusicGame::g_player_status.rank_count[(int)E_DIFFCULTY::DIFF_ONI][i];
		m_num_count.Draw(val, pos.x + RANK_NUMBER_OFFSET[i].x + (numOfDigit(val) - 1) * NUMBER_PADDING * 0.5f, pos.y + RANK_NUMBER_OFFSET[i].y, NUMBER_PADDING);
	}

}
