#include "CObjDanSelectConfirm.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"
#include <filesystem>

//初期化
CObjDanSelectConfirm::CObjDanSelectConfirm()
{

}

void CObjDanSelectConfirm::Init()
{
	m_ani_back_fadein.LoadData("Animation/DanSelect/Confirm/BackFadeIn");
	m_ani_window_fadein.LoadData("Animation/DanSelect/Confirm/WindowFadeIn");
	m_ani_icon_fadein.LoadData("Animation/DanSelect/Confirm/IconFadeIn");
	m_ani_back_fadeout.LoadData("Animation/DanSelect/Confirm/BackFadeOut");
	m_ani_window_fadeout.LoadData("Animation/DanSelect/Confirm/WindowFadeOut");
	m_ani_effect_loop.LoadData("Animation/DanSelect/Confirm/CursorEffectLoop");
	m_ani_decide_white.LoadData("Animation/DanSelect/Confirm/DecideEffectWhite");

	m_ani_back_fadein.Start();
	m_ani_window_fadein.Start();
	m_ani_icon_fadein.Start();
	m_ani_effect_loop.Start();

	m_cancel = false;
	m_decide = false;

	m_now_select = MusicGame::DanSelect::ICON_CANCEL;

	m_fade_out.m_color = Color::Black;
}
//進行
void CObjDanSelectConfirm::Action()
{
	m_ani_back_fadein.Action();
	m_ani_window_fadein.Action();
	m_ani_icon_fadein.Action();
	m_ani_back_fadeout.Action();
	m_ani_window_fadeout.Action();
	m_ani_effect_loop.ActionLoop();
	m_ani_decide_white.Action();
	m_ct_fade_delay.Action();

	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	if (m_cancel == true && m_ani_back_fadeout.GetEnd())
	{
		this->SetStatus(false);
	}

	if (m_ct_fade_delay.GetProgress() && m_ct_fade_delay.GetEndValueReached())
	{
		m_fade_out.Start(MusicGame::DanSelect::FADE_FRAME);
	}
	if (m_fade_out.GetEnd())
	{
		CObjDanSelect* select = (CObjDanSelect*)Objs::GetObj(OBJ_DANSELECT);
		select->ChallengeStart();
	}


	CObjEnsoOption* option = (CObjEnsoOption*)Objs::GetObj(OBJ_OPTION_SELECT);

	//キー入力
	if (m_decide == true || m_cancel == true || option != nullptr)return;

	if (system->GetInput(LEFT_KA,0))
	{
		Audio::Start(se_KA);
		SelectLeft();
	}
	if (system->GetInput(RIGHT_KA,0))
	{
		Audio::Start(se_KA);
		SelectRight();
	}
	if (system->GetInput(LEFT_DON,0) ||
		system->GetInput(RIGHT_DON,0))
	{
		Decide();
		m_ani_decide_white.Start();
	}
}
//描画
void CObjDanSelectConfirm::Draw()
{
	float cursor_effect_opacity = 1.0f;
	float cursor_white_opacity = 1.0f;

	if (m_cancel == false)
	{
		Draw::SetOpacity(tex_TILE, m_ani_back_fadein.GetValue().opacity);
		Draw::SetOpacity(tex_DANSELECT_CONFIRM_WINDOW, m_ani_window_fadein.GetValue().opacity);
		Draw::SetOpacity(tex_DANSELECT_CONFIRM_ICON, m_ani_icon_fadein.GetValue().opacity);

		Draw::SetOpacity(tex_DANSELECT_CONFIRM_CURSOR, m_ani_icon_fadein.GetValue().opacity);
		cursor_effect_opacity = m_ani_icon_fadein.GetValue().opacity;
	}
	else
	{
		Draw::SetOpacity(tex_TILE, m_ani_back_fadeout.GetValue().opacity);
		Draw::SetOpacity(tex_DANSELECT_CONFIRM_WINDOW, m_ani_window_fadeout.GetValue().opacity);
		Draw::SetOpacity(tex_DANSELECT_CONFIRM_ICON, m_ani_window_fadeout.GetValue().opacity);

		Draw::SetOpacity(tex_DANSELECT_CONFIRM_CURSOR, m_ani_window_fadeout.GetValue().opacity);
		cursor_effect_opacity = m_ani_window_fadeout.GetValue().opacity;
	}

	DrawFill(tex_TILE, MusicGame::RECT_TILE_BLACK);
	Draw::Draw(tex_DANSELECT_CONFIRM_WINDOW, 0, 0);

	float cursor_x = MusicGame::DanSelect::CONFIRM_POS[m_now_select].x;
	float cursor_y = MusicGame::DanSelect::CONFIRM_POS[m_now_select].y;
	RECT_F rect_cursor;
	RECT_F rect_effect;
	RECT_F rect_white;
	RECT_F rect_white_effect;

	switch (m_now_select)
	{
	case MusicGame::DanSelect::ICON_OPTION:
		rect_cursor = MusicGame::DanSelect::RECT_CURSOR_OPTION;
		rect_effect = MusicGame::DanSelect::RECT_CURSOR_EFFECT_OPTION;
		rect_white = MusicGame::DanSelect::RECT_CURSOR_WHITE_OPTION;
		rect_white_effect = MusicGame::DanSelect::RECT_CURSOR_WHITE_EFFECT_OPTION;
		break;
	case MusicGame::DanSelect::ICON_DECIDE:
	case MusicGame::DanSelect::ICON_CANCEL:
		rect_cursor = MusicGame::DanSelect::RECT_CURSOR;
		rect_effect = MusicGame::DanSelect::RECT_CURSOR_EFFECT;
		rect_white = MusicGame::DanSelect::RECT_CURSOR_WHITE;
		rect_white_effect = MusicGame::DanSelect::RECT_CURSOR_WHITE_EFFECT;
		break;
	}

	//カーソルの描画
	Draw::CenterDraw(tex_DANSELECT_CONFIRM_CURSOR, MusicGame::DanSelect::CONFIRM_POS[m_now_select].x, MusicGame::DanSelect::CONFIRM_POS[m_now_select].y, rect_cursor);

	cursor_effect_opacity *= m_ani_effect_loop.GetValue().opacity;
	Draw::SetOpacity(tex_DANSELECT_CONFIRM_CURSOR, cursor_effect_opacity);
	Draw::CenterDraw(tex_DANSELECT_CONFIRM_CURSOR, MusicGame::DanSelect::CONFIRM_POS[m_now_select].x, MusicGame::DanSelect::CONFIRM_POS[m_now_select].y, rect_effect);


	Draw::Draw(tex_DANSELECT_CONFIRM_ICON, 0, 0);

	//決定時エフェクトの描画
	if (m_ani_decide_white.GetStart() &&  !m_ani_decide_white.GetEnd())
	{
		Draw::SetOpacity(tex_DANSELECT_CONFIRM_CURSOR, m_ani_decide_white.GetValue().opacity);
		Draw::CenterDraw(tex_DANSELECT_CONFIRM_CURSOR, MusicGame::DanSelect::CONFIRM_POS[m_now_select].x, MusicGame::DanSelect::CONFIRM_POS[m_now_select].y, rect_white);
		Draw::SetOpacity(tex_DANSELECT_CONFIRM_CURSOR, 1.0f - m_ani_decide_white.GetValue().opacity);
		Draw::CenterDraw(tex_DANSELECT_CONFIRM_CURSOR, MusicGame::DanSelect::CONFIRM_POS[m_now_select].x, MusicGame::DanSelect::CONFIRM_POS[m_now_select].y, rect_white_effect);
	}

	m_fade_out.ActionDraw();
}

void CObjDanSelectConfirm::SelectLeft()
{
	m_now_select--;

	if (m_now_select < 0)
		m_now_select = 0;
}

void CObjDanSelectConfirm::SelectRight()
{
	m_now_select++;

	if (m_now_select > MusicGame::DanSelect::ICON_CANCEL)
		m_now_select = MusicGame::DanSelect::ICON_CANCEL;
}

void CObjDanSelectConfirm::Decide()
{
	CObjDanSelect* select = (CObjDanSelect*)Objs::GetObj(OBJ_DANSELECT);

	switch (m_now_select)
	{
	case MusicGame::DanSelect::ICON_OPTION:
	{
		Audio::Start(se_DON);
		CObjEnsoOption* option = new CObjEnsoOption(&select->m_enso_option,0);
		Objs::InsertObj(option, OBJ_OPTION_SELECT, PRIO_SONGSELECT_OPTION);
		break;
	}
	case MusicGame::DanSelect::ICON_DECIDE:
		Audio::Start(se_DANSELECT_DECIDE);
		m_decide = true;
		m_ct_fade_delay.Start(0, MusicGame::DanSelect::FADE_DELAY, 1);
		break;
	case MusicGame::DanSelect::ICON_CANCEL:
		Audio::Start(se_CANCEL);
		m_cancel = true;
		m_ani_back_fadeout.Start();
		m_ani_window_fadeout.Start();
		break;
	}
}