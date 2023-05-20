#include "CObjSongSelectCharacter.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL/WinInputs.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/Userdata.h"
#include <filesystem>



//èâä˙âª
void CObjSongSelectCharacter::Init()
{
	m_ct_chara_loop = { CCounter(0.0f,0.0f,MusicGame::SongSelect::g_tex_chara_loop.size(), LOOP) };
	m_ct_chara_start = { CCounter(0.0f,0.0f,MusicGame::SongSelect::g_tex_chara_start.size() - 1, STOP) };
	m_ct_chara_select = { CCounter(0.0f,0.0f,MusicGame::SongSelect::g_tex_chara_select.size(), STOP) };

	m_ct_chara_select.NowValue = m_ct_chara_select.MaxValue;
	m_song_start = false;
}
//êiçs
void CObjSongSelectCharacter::Action()
{
	m_ct_chara_loop.Add(m_ct_chara_loop.MaxValue / CHARA_LOOP_FRAME);
	m_ct_chara_select.Add(m_ct_chara_select.MaxValue / CHARA_SELECT_FRAME);

	if (m_song_start == true)
		m_ct_chara_start.Add(m_ct_chara_start.MaxValue / CHARA_START_FRAME);
}


//ï`âÊ
void CObjSongSelectCharacter::Draw()
{
	if (m_song_start == true)
	{
		int val = m_ct_chara_start.NowValue;
		MusicGame::SongSelect::g_tex_chara_start[val].Draw(CHARACTER_POS.x, CHARACTER_POS.y);
	}
	else if (!m_ct_chara_select.GetMaxReached())
	{
		int val = m_ct_chara_select.NowValue;
		MusicGame::SongSelect::g_tex_chara_select[val].Draw(CHARACTER_POS.x, CHARACTER_POS.y);
	}
	else
	{
		int val = m_ct_chara_loop.NowValue;
		MusicGame::SongSelect::g_tex_chara_loop[val].Draw(CHARACTER_POS.x, CHARACTER_POS.y);
	}
}

void CObjSongSelectCharacter::Select()
{
	m_ct_chara_select.Reset();
}
void CObjSongSelectCharacter::SongStart()
{
	m_song_start = true;
}