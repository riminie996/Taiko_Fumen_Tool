#include "CObjModeSelect.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL/WinInputs.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/Userdata.h"
//初期化
void CObjModeSelect::Init()
{
	m_ct_appear.Start(0, MusicGame::Entry::APPEAR_TIME, 1);
	m_ani_bar_appear.Start();
	m_fade_out.m_color = Color::Black;
	m_to_mode = MusicGame::Entry::E_TO_MODE::SONGSELECT;
}
//進行
void CObjModeSelect::Action()
{
	m_ct_appear.Action();

	m_ani_bar_appear.Action();
	m_ani_chara_appear.Action();
	m_ani_text_appear.Action();
	m_ani_cursor_appear.Action();
	m_ani_mode_decide.Action();
	m_ani_mode_fadeout.Action();

	if (m_ct_appear.NowValue >= MusicGame::Entry::CHARA_APPEAR_DELAY && !m_ani_chara_appear.GetStart())
	{
		m_ani_chara_appear.Start();
		m_ani_text_appear.Start();
	}
	if (m_ct_appear.NowValue >= MusicGame::Entry::CURSOR_APPEAR_DELAY && !m_ani_cursor_appear.GetStart())
	{
		m_ani_cursor_appear.Start();
	}
	if (m_ani_mode_fadeout.GetEnd())
	{
		m_fade_out.Start();
	}
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
	if (m_fade_out.GetEnd())
	{
		Audio::Stop(bgm_MUSIC);
		system->EntryEnd();

		if (m_to_mode == MusicGame::Entry::E_TO_MODE::SONGSELECT)
			system->SongSelectStart();
		else if (m_to_mode == MusicGame::Entry::E_TO_MODE::DANSELECT)
			system->DanSelectStart();
		else if (m_to_mode == MusicGame::Entry::E_TO_MODE::HEYA)
			system->HeyaStart();
	//	else if (m_to_mode == MusicGame::Entry::E_TO_MODE::BATTLESELECT)
	//		system->HeyaStart();
	}

	if (m_ani_mode_fadeout.GetStart())return;

	//操作可能

	if (system->GetInput(LEFT_KA,0))
	{

	}
	if (system->GetInput(RIGHT_KA,0))
	{

	}
	if (system->GetInput(LEFT_DON,0) ||
		system->GetInput(RIGHT_DON,0))
	{

		m_ani_mode_decide.Start();
		m_ani_mode_fadeout.Start();
		Audio::Start(se_DON);
	}

	if (Input::GetVKey(VK_F1))
	{
		m_to_mode = MusicGame::Entry::E_TO_MODE::DANSELECT;
		m_ani_mode_decide.Start();
		m_ani_mode_fadeout.Start();
		Audio::Start(se_DON);
	}

	if (Input::GetVKey(VK_F2))
	{
		m_to_mode = MusicGame::Entry::E_TO_MODE::HEYA;
		m_ani_mode_decide.Start();
		m_ani_mode_fadeout.Start();
		Audio::Start(se_DON);
	}
	if (Input::GetVKey(VK_F3))
	{
		m_to_mode = MusicGame::Entry::E_TO_MODE::BATTLESELECT;
		m_ani_mode_decide.Start();
		m_ani_mode_fadeout.Start();
		Audio::Start(se_DON);
	}
}


//描画
void CObjModeSelect::Draw()
{
	if (!m_ani_mode_fadeout.GetStart())
	{
		Draw::SetOpacity(tex_ENTRY_ENSO_BAR, m_ani_bar_appear.GetValue().opacity);
		Draw::SetOpacity(tex_ENTRY_ENSO_CURSOR, m_ani_cursor_appear.GetValue().opacity);
		Draw::SetOpacity(tex_ENTRY_ENSO_TEXT, m_ani_text_appear.GetValue().opacity);
		Draw::SetOpacity(tex_ENTRY_ENSO_CHARA, m_ani_chara_appear.GetValue().opacity);
		Draw::SetOpacity(tex_ENTRY_MODESELECT_OVERLAY, m_ani_text_appear.GetValue().opacity);
	}
	else
	{
		Draw::SetOpacity(tex_ENTRY_ENSO_BAR, m_ani_mode_fadeout.GetValue().opacity);
		Draw::SetOpacity(tex_ENTRY_ENSO_CURSOR, m_ani_mode_fadeout.GetValue().opacity);
		Draw::SetOpacity(tex_ENTRY_ENSO_TEXT, m_ani_mode_fadeout.GetValue().opacity);
		Draw::SetOpacity(tex_ENTRY_ENSO_CHARA, m_ani_mode_fadeout.GetValue().opacity);
		Draw::SetOpacity(tex_ENTRY_MODESELECT_OVERLAY, m_ani_mode_fadeout.GetValue().opacity);
	}

	float y_offset = MusicGame::Entry::RECT_BAR_CENTER.m_height * 0.5f * m_ani_bar_appear.GetValue().scale_y + MusicGame::Entry::RECT_BAR_TOP.m_height * 0.5f;

	//バーの描画
	Draw::SetScaleY(tex_ENTRY_ENSO_BAR, m_ani_bar_appear.GetValue().scale_y);
	Draw::CenterDraw(tex_ENTRY_ENSO_BAR, MusicGame::Entry::BAR_POS.x, MusicGame::Entry::BAR_POS.y,MusicGame::Entry::RECT_BAR_CENTER);

	Draw::SetScaleY(tex_ENTRY_ENSO_BAR, 1.0f);
	Draw::CenterDraw(tex_ENTRY_ENSO_BAR, MusicGame::Entry::BAR_POS.x, MusicGame::Entry::BAR_POS.y - y_offset, MusicGame::Entry::RECT_BAR_TOP);
	Draw::CenterDraw(tex_ENTRY_ENSO_BAR, MusicGame::Entry::BAR_POS.x, MusicGame::Entry::BAR_POS.y + y_offset, MusicGame::Entry::RECT_BAR_BOTTOM);

	//オーバーレイの描画
	float overlay_x = MusicGame::Entry::BAR_POS.x + MusicGame::Entry::OVERLAY_TOP_OFFSET.x;
	float overlay_y = MusicGame::Entry::BAR_POS.y + MusicGame::Entry::OVERLAY_TOP_OFFSET.y;
	Draw::TopCenterDraw(tex_ENTRY_MODESELECT_OVERLAY,overlay_x, overlay_y, MusicGame::Entry::RECT_OVERLAY_TOP);
	overlay_y += MusicGame::Entry::RECT_OVERLAY_TOP.m_height;
	Draw::TopCenterDraw(tex_ENTRY_MODESELECT_OVERLAY, overlay_x, overlay_y , MusicGame::Entry::RECT_OVERLAY_CENTER);
	overlay_y += MusicGame::Entry::RECT_OVERLAY_CENTER.m_height;// * scale_y
	Draw::TopCenterDraw(tex_ENTRY_MODESELECT_OVERLAY, overlay_x, overlay_y, MusicGame::Entry::RECT_OVERLAY_BOTTOM);

	//カーソルの描画
	Draw::CenterDraw(tex_ENTRY_ENSO_CURSOR, MusicGame::Entry::BAR_POS.x, MusicGame::Entry::BAR_POS.y, MusicGame::Entry::RECT_CURSOR);

	Draw::SetOpacity(tex_ENTRY_ENSO_CURSOR, m_ani_mode_decide.GetValue().opacity);
	Draw::CenterDraw(tex_ENTRY_ENSO_CURSOR, MusicGame::Entry::BAR_POS.x, MusicGame::Entry::BAR_POS.y, MusicGame::Entry::RECT_CURSOR_WHITE);

	//テキストの描画
	Draw::CenterDraw(tex_ENTRY_ENSO_TEXT, MusicGame::Entry::BAR_POS.x, MusicGame::Entry::BAR_POS.y + MusicGame::Entry::TEXT_OFFSET_Y);

	//キャラクターの描画
	Draw::Draw(tex_ENTRY_ENSO_CHARA, MusicGame::Entry::CHARA_LEFT_POS.x + m_ani_chara_appear.GetValue().x, MusicGame::Entry::CHARA_LEFT_POS.y, MusicGame::Entry::RECT_CHARA_LEFT);
	Draw::Draw(tex_ENTRY_ENSO_CHARA, MusicGame::Entry::CHARA_RIGHT_POS.x - m_ani_chara_appear.GetValue().x, MusicGame::Entry::CHARA_RIGHT_POS.y, MusicGame::Entry::RECT_CHARA_RIGHT);

	m_fade_out.ActionDraw();
}
