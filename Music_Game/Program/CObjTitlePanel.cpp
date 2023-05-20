#include "CObjTitlePanel.h"
#include "GameHead.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
//‰Šú‰»
void CObjTitlePanel::Init()
{
	m_show_flag = false;
	m_num_song.SetTex(tex_SONG_NUMBER, MusicGame::Enso::RECT_SONGNUMBER.m_width, MusicGame::Enso::RECT_SONGNUMBER.m_height);

}
//is
void CObjTitlePanel::Action()
{
	m_ani_genre_fade.ActionLoop();
}
//•`‰æ
void CObjTitlePanel::Draw()
{
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	wchar_t wcr[64];
	wstring str = MusicGame::StringToWString(m_str_title);
	swprintf_s(wcr, L"%s", str.c_str());

	if (m_show_flag == true)
	{
		Font::StrRightDraw(wcr, MusicGame::Enso::TITLE_PANEL_RIGHT_X, MusicGame::Enso::TITLE_PANEL_Y, MusicGame::Enso::TITLE_PANEL_FONT_SIZE, ColorA::White);


		float x = MusicGame::Enso::GENRE_POS.x;
		float y = MusicGame::Enso::GENRE_POS.y;

		RECT_F rect_genre = MusicGame::Enso::RECT_GENRE;
		rect_genre.m_y = m_genre * rect_genre.m_height;

		Draw::SetOpacity(tex_GENRE, m_ani_genre_fade.GetValue().opacity);
		Draw::Draw(tex_GENRE, x, y, rect_genre);

		Draw::SetOpacity(tex_GENRE, 1.0f - m_ani_genre_fade.GetValue().opacity);
		Draw::SetOpacity(tex_SONG_NUMBER, 1.0f - m_ani_genre_fade.GetValue().opacity);
		Draw::Draw(tex_GENRE, x, y, MusicGame::Enso::RECT_SONG_BACK);

		int now = system->GetNowSongNumber();
		int max = ((UserData*)Save::GetData())->m_max_song;
		m_num_song.Draw(now, x + MusicGame::Enso::NOW_SONG_OFFSET.x, y + MusicGame::Enso::NOW_SONG_OFFSET.y, MusicGame::Enso::SONG_NUMBER_PADDING);

		if (max == 0)
		{
			Draw::Draw(tex_SONG_NUMBER, x + MusicGame::Enso::MAX_SONG_OFFSET.x, y + MusicGame::Enso::MAX_SONG_OFFSET.y,MusicGame::Enso::RECT_INFINITY);
		}
		else
		{
			m_num_song.Draw(max, x + MusicGame::Enso::MAX_SONG_OFFSET.x, y + MusicGame::Enso::MAX_SONG_OFFSET.y, MusicGame::Enso::SONG_NUMBER_PADDING);
		}
	}
}

void CObjTitlePanel::SetTitleString(string title, int genre)
{
	m_str_title = title;
	m_genre = genre;
	m_show_flag = true;
	m_ani_genre_fade.Start();
}