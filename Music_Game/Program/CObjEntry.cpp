#include "CObjEntry.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL/WinInputs.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/Userdata.h"
//‰Šú‰»
void CObjEntry::Init()
{
	Audio::LoadAudio2(bgm_IN, "Sound/1_Entry/bgm_in.ogg", EFFECT);
	Audio::LoadAudio2(bgm_MUSIC, "Sound/1_Entry/bgm_loop.ogg", BACK_MUSIC);

	m_ani_entry_fadein.Start();
	m_fade_in.m_fade_type = m_fade_in.FadeIn;
	m_fade_in.m_color = Color::Black;
	m_fade_in.Start();

	Audio::Start(bgm_IN);
	m_ct_bgm_loop_start.Start(0, BGM_LOOP_START_DELAY, 1);
	m_bgm_play_flag = true;
}
//is
void CObjEntry::Action()
{
	m_ani_entry_fadein.Action();
	m_ani_entry_fadeout.Action();
	m_ani_entry_decide_effect.Action();

	m_ct_modeselect_delay.Action();
	m_ct_bgm_loop_start.Action();

	if (m_ct_bgm_loop_start.GetEndValueReached() && m_bgm_play_flag == true)
	{
		m_bgm_play_flag = false;
		Audio::Start(bgm_MUSIC);
	}

	CObjModeSelect* select = (CObjModeSelect*)Objs::GetObj(OBJ_MODESELECT);
	if (m_ct_modeselect_delay.GetProgress() && m_ct_modeselect_delay.GetEndValueReached() &&
		select == nullptr)
	{
		CObjModeSelect* mode = new CObjModeSelect();
		Objs::InsertObj(mode, OBJ_MODESELECT, PRIO_ENTRY_MODESELECT);
	}


	if (m_ani_entry_decide_effect.GetStart())return;

	//‘€ì‰Â”\
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	if (system->GetInput(LEFT_KA,0))
	{

	}
	if (system->GetInput(RIGHT_KA,0))
	{

	}
	if (system->GetInput(LEFT_DON,0) ||
		system->GetInput(RIGHT_DON,0))
	{
		m_ani_entry_decide_effect.Start();
		m_ani_entry_fadeout.Start();
		Audio::Start(se_DON);
		m_ct_modeselect_delay.Start(0, MusicGame::Entry::MODESELECT_DELAY, 1);
	}
}


//•`‰æ
void CObjEntry::Draw()
{
	if (!m_ani_entry_decide_effect.GetStart())
	{
		Draw::SetOpacity(tex_ENTRY_ENTRY, m_ani_entry_fadein.GetValue().opacity);
	}
	else
	{
		Draw::SetOpacity(tex_ENTRY_ENTRY, m_ani_entry_fadeout.GetValue().opacity);
	}
	for (int i = 0 ; i < MusicGame::Entry::ENTRY_BAR_AMOUNT; i++)
	{
		Draw::CenterDraw(tex_ENTRY_ENTRY, MusicGame::Entry::ENTRY_BAR_POS.x, MusicGame::Entry::ENTRY_BAR_POS.y, MusicGame::Entry::RECT_ENTRY_BAR);
	}

	Draw::SetOpacity(tex_ENTRY_ENTRY, m_ani_entry_decide_effect.GetValue().opacity);
	Draw::CenterDraw(tex_ENTRY_ENTRY, MusicGame::Entry::ENTRY_BAR_POS.x, MusicGame::Entry::ENTRY_BAR_POS.y, MusicGame::Entry::RECT_ENTRY_BAR_EFFECT);

	m_fade_in.ActionDraw();
}
