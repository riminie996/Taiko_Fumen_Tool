#include "CObjLoading.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"
//èâä˙âª
void CObjLoading::Init()
{
	m_ani_fade_L.Start();
	m_ani_fade_R.Start();
	m_loading_start = false;
	Audio::Stop(bgm_SONGSELECT);
}
//êiçs
void CObjLoading::Action()
{
	m_ani_fade_L.Action();
	m_ani_fade_R.Action();
	m_ani_chara.Action();


	m_ani_fadeout_L.Action();
	m_ani_fadeout_R.Action();
	m_ani_chara_out.Action();
	m_ani_wait_out.Action();

	if (m_ani_fade_L.GetEnd() && m_ani_fade_R.GetEnd())
	{
		if (!m_ani_chara.GetStart())
		{
			m_ani_chara.Start();
			m_ani_wait_in.Start();
			Audio::Stop(bgm_MUSIC);
		}
	}

	if (m_ani_chara.GetEnd() && m_ani_wait_in.GetEnd() && m_loading_start == false)
	{
		CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);
		CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

		system->SongSelectEnd();
		system->EnsoStart(select->GetNowSelectSong().folder_path,select->m_enso_option);
		
		m_loading_start = true;
		m_ani_chara_out.Start();
		m_ani_wait_out.Start();
	}

	if (m_ani_chara_out.GetEnd() && !m_ani_fadeout_L.GetStart())
	{
		m_ani_fadeout_L.Start();
		m_ani_fadeout_R.Start();
	}
	m_ani_wait_in.Action();
}
//ï`âÊ
void CObjLoading::Draw()
{


	if (!m_ani_fade_L.GetEnd())
	{
		Draw::SetScaleX(tex_LOADING_FADE, m_ani_fade_L.GetValue().scale_x);
		Draw::Draw(tex_LOADING_FADE, m_ani_fade_L.GetValue().x, 0.0f, RECT_FADE_L);
		Draw::Draw(tex_LOADING_FADE, m_ani_fade_R.GetValue().x, 0.0f, RECT_FADE_R);
	}
	else if (m_ani_fadeout_L.GetStart())
	{
		Draw::SetScaleX(tex_LOADING_FADE, m_ani_fadeout_L.GetValue().scale_x);
		Draw::Draw(tex_LOADING_FADE, m_ani_fadeout_L.GetValue().x, 0.0f, RECT_FADE_L);
		Draw::Draw(tex_LOADING_FADE, m_ani_fadeout_R.GetValue().x, 0.0f, RECT_FADE_R);
	}
	else
	{
		//îwåiÇÃï`âÊ
		Draw::Draw(tex_LOADING_BG, 0.0f, 0.0f);

		float opacity = m_ani_wait_in.GetValue().opacity * m_ani_wait_out.GetValue().opacity;

		Draw::SetOpacity(tex_LOADING_WAIT, opacity);
		Draw::SetOpacity(tex_LOADING_PLATE, opacity);
		Draw::SetScaleX(tex_LOADING_PLATE, m_ani_wait_in.GetValue().scale_x);
		Draw::Draw(tex_LOADING_WAIT, 0.0f, 0.0f);
		Draw::CenterDraw(tex_LOADING_PLATE, 640.0f, 360.0f);

		opacity = m_ani_chara.GetValue().opacity * m_ani_chara_out.GetValue().opacity;
		float y = m_ani_chara.GetValue().y + m_ani_chara_out.GetValue().y;

		//ÉLÉÉÉâÉNÉ^Å[ÇÃï`âÊ
		Draw::SetOpacity(tex_LOADING_CHARA, opacity);
		Draw::Draw(tex_LOADING_CHARA, -m_ani_chara.GetValue().x, y, RECT_FADE_L);
		Draw::Draw(tex_LOADING_CHARA, RECT_FADE_L.m_width + m_ani_chara.GetValue().x, y, RECT_FADE_R);

		CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);
		

		wchar_t title[64];
		COLOR_A col = {1.0f, 1.0f, 1.0f, 1.0f};
		wstring str = MusicGame::StringToWString(MusicGame::g_now_select_songtitle);
		swprintf_s(title, L"%s", str.c_str());

		if (m_ani_wait_in.GetEnd() && !m_ani_wait_out.GetStart())
		Font::StrCenterDraw(title, TITLE_POS.x, TITLE_POS.y, TITLE_FONT_SIZE, col);
	}
}
