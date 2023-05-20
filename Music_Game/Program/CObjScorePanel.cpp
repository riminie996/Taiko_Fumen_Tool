#include "CObjScorePanel.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

//初期化
void CObjScorePanel::Init()
{
	m_num_score.SetTex(tex_SCOREPANEL, RECT_SCORE_NUM.m_width, RECT_SCORE_NUM.m_height, RECT_SCORE_NUM.m_x, RECT_SCORE_NUM.m_y);

}
//進行
void CObjScorePanel::Action()
{
}
//描画
void CObjScorePanel::Draw()
{
	//描画処理は各オブジェクトから呼び出して行うこと。
}
void CObjScorePanel::Draw(E_DIFFCULTY diff, int score)
{



	Draw::Draw(tex_SCOREPANEL, PANEL_POS.x, PANEL_POS.y, RECT_SCORE_PANEL);

	RECT_F rect_diffculty = RECT_DIFFCULTY;
	rect_diffculty.m_x = (int)diff * rect_diffculty.m_width;

	Draw::Draw(tex_SCOREPANEL, PANEL_POS.x + DIFFCULTY_OFFSET.x, PANEL_POS.y + DIFFCULTY_OFFSET.y, rect_diffculty);

	m_num_score.Draw(score, PANEL_POS.x + NUMBER_OFFSET.x, PANEL_POS.y + NUMBER_OFFSET.y, NUMBER_PADDING);
}