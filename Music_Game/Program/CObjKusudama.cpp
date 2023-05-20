#include "CObjKusudama.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//初期化
void CObjKusudama::Init()
{
	m_reset_flag = true;
	m_show_flag = false;
	m_roll_remain = 0;
	
	m_num_roll.SetTex(tex_KUSUDAMA_NUMBER, RECT_NUMBER.m_width, RECT_NUMBER.m_height);
	m_ct_break_opacity = { CCounter(1.0f,0.0f,1.0f,STOP) };

	m_max_val = 0;



	m_ani_kusudama_appear.LoadData("Animation/Enso/Kusudama/KusudamaAppear");
	m_ani_kusudama_wait.LoadData("Animation/Enso/Kusudama/KusudamaWait");
	m_ani_kusudama_break.LoadData("Animation/Enso/Kusudama/KusudamaBreak");
	m_ani_text_appear.LoadData("Animation/Enso/Kusudama/TextAppear");
	m_ani_text_wait.LoadData("Animation/Enso/Kusudama/TextWait");
	m_ani_concentration_line.LoadData("Animation/Enso/Kusudama/ConcentrationLineWait");

	m_ani_kusudama_wait.Start();
	m_ani_concentration_line.Start();
}
//進行
void CObjKusudama::Action()
{
	m_ani_kusudama_appear.Action();
	m_ani_kusudama_wait.ActionLoop();
	m_ani_text_appear.Action();
	m_ani_text_wait.ActionLoop();
	m_ani_concentration_line.ActionLoop();
	m_ani_kusudama_break.Action();

	if (m_ani_kusudama_appear.GetEnd() && !m_ani_text_appear.GetStart())
		m_ani_text_appear.Start();

	if (m_ani_text_appear.GetEnd() && !m_ani_text_wait.GetStart())
		m_ani_text_wait.Start();
}
//描画
void CObjKusudama::Draw()
{
	if (m_show_flag == true)
	{
		if (!m_ani_kusudama_appear.GetEnd())
		{
			MusicGame::g_tex_concentration_line.m_opacity = m_ani_kusudama_appear.GetValue("ConcentrationLine").opacity;
			MusicGame::g_tex_concentration_line.m_blend = E_BLEND_MODE::NORMAL;
			ConcentrationLineDraw();

			MusicGame::g_tex_kusudama.m_opacity = 1.0f;
			MusicGame::g_tex_kusudama.Draw(KUSUDAMA_POS.x, KUSUDAMA_POS.y + m_ani_kusudama_appear.GetValue("Kusudama").y, RECT_KUSUDAMA, ref_Center, ref_Center);
		}
		else
		{
			//ふくらみレベルを決定
			float percent = 0.0f;
			int level = 0;
			
			if (m_roll_remain > 0)
				percent = (float)m_roll_remain / (float)m_max_val;

			if (percent > 1.0f / 6.0f * 5.0f)
				level = 0;//514
			else if (percent > 1.0f / 6.0f * 4.0f)
				level = 1;//518,524
			else if (percent > 1.0f / 6.0f * 3.0f)
				level = 2;//526,534
			else if (percent > 1.0f / 6.0f * 2.0f)
				level = 3;//528,538
			else if (percent > 1.0f / 6.0f * 1.0f)
				level = 4;//538,552
			else
				level = 5;//544,570

			//集中線の描画
			MusicGame::g_tex_concentration_line.m_opacity = (1.0f - percent) * 0.5f;
			MusicGame::g_tex_concentration_line.m_blend = E_BLEND_MODE::ADDITIONALPHA;
			ConcentrationLineDraw();
			//くすだまの描画
			MusicGame::g_tex_kusudama.m_scale_x = m_ani_kusudama_wait.GetValue(level).scale_x;
			MusicGame::g_tex_kusudama.m_scale_y = m_ani_kusudama_wait.GetValue(level).scale_x;

			MusicGame::g_tex_kusudama.Draw(KUSUDAMA_POS.x, KUSUDAMA_POS.y, RECT_KUSUDAMA, ref_Center, ref_Center);

			int text_y = RENDA_TEXT_POS.y + m_ani_text_appear.GetValue("Text").y + m_ani_text_wait.GetValue("Text").y;
			MusicGame::g_tex_kusudama_renda.m_opacity = m_ani_text_appear.GetValue("Text").opacity;
			MusicGame::g_tex_kusudama_renda.Draw(RENDA_TEXT_POS.x, text_y, RECT_RENDA, ref_Center, ref_Center);

			m_num_roll.Draw(m_roll_remain, KUSUDAMA_NUM_POS.x + (numOfDigit(m_roll_remain) - 1) * KUSUDAMA_NUM_PADDING / 2.0f, KUSUDAMA_NUM_POS.y/* - y_move*/, KUSUDAMA_NUM_PADDING);
		}
		
	}
	else
	{
		if (m_ani_kusudama_break.GetStart())
		{
			MusicGame::g_tex_concentration_line.m_opacity = m_ani_kusudama_break.GetValue("ConcentrationLine").opacity;
			ConcentrationLineDraw();

			MusicGame::g_tex_kusudama.m_scale_x = 1.0f;
			MusicGame::g_tex_kusudama.m_scale_y = 1.0f;

			MusicGame::g_tex_kusudama.m_opacity = m_ani_kusudama_break.GetValue("Kusudama").opacity;
			MusicGame::g_tex_kusudama.Draw(KUSUDAMA_POS.x, KUSUDAMA_POS.y, RECT_KUSUDAMA_BREAK[(int)m_ani_kusudama_break.GetValue("Kusudama").pattern], ref_Center, ref_Center);
		}
	}

}
void CObjKusudama::Start(int max)
{
	if (m_show_flag == false)
	{
		m_ani_kusudama_appear.Start();
		m_ani_kusudama_break.Start();
		m_ani_kusudama_break.End();
	}

	m_roll_remain += max;
	m_max_val += max;
	m_show_flag = true;
}
/// <summary>
/// 残り値を1減らす。
/// </summary>
/// <returns>割れたかどうか</returns>
bool CObjKusudama::Sub()
{
	m_roll_remain--;
	m_ani_number_scale.Start();

	if (m_roll_remain <= 0)
	{
		Break();
		return true;
	}

	return false;
}
void CObjKusudama::Break()
{
	m_show_flag = false;
	m_ct_break_opacity.Reset();
	m_max_val = 0;
	m_roll_remain = 0;
	m_ani_kusudama_break.Start();
}
void CObjKusudama::End()
{
	m_show_flag = false;
	m_max_val = 0;
	m_roll_remain = 0;
}

void CObjKusudama::ConcentrationLineDraw()
{
	RECT_N rect_cl = RECT_CONCENTRATION;
	rect_cl.m_y = RECT_CONCENTRATION.m_height * (int)m_ani_concentration_line.GetValue(0).pattern;


	MusicGame::g_tex_concentration_line.m_flip_x = false;
	MusicGame::g_tex_concentration_line.Draw(0, 0, rect_cl);
	MusicGame::g_tex_concentration_line.m_flip_x = true;
	MusicGame::g_tex_concentration_line.Draw(RECT_CONCENTRATION.m_width, 0, rect_cl);
}