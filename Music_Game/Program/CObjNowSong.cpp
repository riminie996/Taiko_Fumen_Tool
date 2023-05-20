#include "CObjNowSong.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

//‰Šú‰»
void CObjNowSong::Init()
{
	m_num_song.SetTex(tex_NOW_SONG_NUMBER, MusicGame::RECT_NOWSONG_NUMBER.m_width, MusicGame::RECT_NOWSONG_NUMBER.m_height);
}
//is
void CObjNowSong::Action()
{

}
//•`‰æ
void CObjNowSong::Draw()
{
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	int now = system->GetNowSongNumber();
	int max = ((UserData*)Save::GetData())->m_max_song;

	Draw::Draw(tex_NOW_SONG, m_pos.x, m_pos.y);

	Draw::SetScaleX(tex_NOW_SONG_NUMBER, 1.0f);
	Draw::SetScaleY(tex_NOW_SONG_NUMBER, 1.0f);
	m_num_song.Draw(now, m_pos.x + NOW_NUMBER_OFFSET.x, m_pos.y + NOW_NUMBER_OFFSET.y, NOW_NUMBER_PADDING);

	Draw::SetScaleX(tex_NOW_SONG_NUMBER, MAX_NUMBER_SCALE);
	Draw::SetScaleY(tex_NOW_SONG_NUMBER, MAX_NUMBER_SCALE);

	if (max > 0)
		m_num_song.Draw(max, m_pos.x + MAX_NUMBER_OFFSET.x, m_pos.y + MAX_NUMBER_OFFSET.y, NOW_NUMBER_PADDING * MAX_NUMBER_SCALE);
	else
		Draw::Draw(tex_NOW_SONG_NUMBER, m_pos.x + MAX_NUMBER_OFFSET.x, m_pos.y + MAX_NUMBER_OFFSET.y, RECT_INFINITY);
}
