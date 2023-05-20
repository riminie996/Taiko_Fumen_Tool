#include "CObjExit.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

//‰Šú‰»
void CObjExit::Init()
{
	Audio::StopAudio();
	m_ani_curtain.Start();
	m_ani_text.Start();
	m_ct_chara_pattern.Start(0, CHARA_PATTERN - 1, CHARA_PATTERN_INTERVAL);

	Audio::LoadAudio2(se_END, "Sound/8_End/Game end.ogg", SOUND_TYPE::EFFECT);
	Audio::Start(se_END);

	m_fadeout.m_fade_type = CFIFO::FadeOut;
	m_fadeout.m_color = Color::Black;
	m_ct_fade_delay.Start(0, FADE_START_DELAY, 1);
}
//is
void CObjExit::Action()
{
	m_ani_curtain.Action();
	m_ani_text.Action();
	m_ct_chara_pattern.ActionLoop();
	m_ct_fade_delay.Action();

	if (m_ct_fade_delay.GetEndValueReached())
	{
		m_fadeout.Start(FADE_FRAME);
	}

	if (m_fadeout.GetEnd())
	{
		CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
		this->SetStatus(false);
		system->ResultEnd();
		system->DanResultEnd();

		if (m_exit_phase == MusicGame::Exit::E_EXIT_TO::ENTRY)
		{
			system->EntryStart();
		}
		return;
	}
}
//•`‰æ
void CObjExit::Draw()
{
	RECT_F rect_chara = RECT_CHARA;
	rect_chara.m_x = RECT_CHARA.m_width * m_ct_chara_pattern.NowValue;
	Draw::Draw(tex_EXIT_CHARA, m_ani_curtain.GetValue().x + CHARA_OFFSET.x, CHARA_OFFSET.y, rect_chara);

	Draw::Draw(tex_EXIT_CURTAIN_LEFT, m_ani_curtain.GetValue().x, 0);
	
	float x = m_ani_curtain.GetValue().x + CURTAIN_LEFT_WIDTH;
	while (x < WINDOW_SIZE_W)
	{
		Draw::Draw(tex_EXIT_CURTAIN, x, 0);
		x += CURTAIN_WIDTH;
	}

	Draw::Draw(tex_EXIT_TEXT, 0, m_ani_text.GetValue().y);

	m_fadeout.ActionDraw();
}
