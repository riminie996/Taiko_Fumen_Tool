#include "CObjDanResultSongPanel.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

//‰Šú‰»
void CObjDanResultSongPanel::Init()
{
	for (int i = 0; i < MusicGame::DAN_MAX_SONG; i++)
		m_ani_song_slide[i].LoadData("Animation/DanResult/SongPanelSlide");

	m_num_song_judge.SetTex(tex_DANRESULT_SONGPANEL_NUMBER, RECT_DANRESULT_NUMBER.m_width, RECT_DANRESULT_NUMBER.m_height);
}
//is
void CObjDanResultSongPanel::Action()
{
	m_ct_song_slide_delay.Action();
	for (int i = 0; i < MusicGame::DAN_MAX_SONG; i++)
	{
		m_ani_song_slide[i].Action();

		if (m_ct_song_slide_delay.GetProgress() && 
			m_ct_song_slide_delay.NowValue >= i * DANRESULT_SONGPANEL_SLIDE_DELAY)
		{
			if (!m_ani_song_slide[i].GetStart())
				m_ani_song_slide[i].Start();
		}
	}
}
//•`‰æ
void CObjDanResultSongPanel::Draw()
{
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);

	//”wŒi‚Ì•`‰æ
	Draw::Draw(tex_DANRESULT_BG, 0, 0);

	//‹Èƒpƒlƒ‹‚Ì”wŒi•`‰æ
	Draw::Draw(tex_DANRESULT_SONGPANEL_BG, 0, 0);

	for (int i = 0; i < MusicGame::DAN_MAX_SONG; i++)
	{
		float panel_x = DANSONG_POS.x + m_ani_song_slide[i].GetValue().x;
		float panel_y = DANSONG_POS.y + i * DANSONG_HEIGHT;

		RECT_F rect_panel = MusicGame::DanResult::RECT_SONG_PANEL;
		rect_panel.m_y = i * MusicGame::DanResult::RECT_SONG_PANEL.m_height;
		Draw::Draw(tex_DANRESULT_SONGPANEL, panel_x, panel_y ,rect_panel);


		for (int j = 0; j < JUDGE_COUNT; j++)
		{
			m_num_song_judge.Draw(dan->GetSongJudge((E_JUDGE)j, i),panel_x + DANSONG_NUMBER_OFFSET[j].x , panel_y + DANSONG_NUMBER_OFFSET[j].y, DANSONG_NUMBER_PADDING);
		}
		if (dan->GetSongNumber() < i)
		{
			Draw::Draw(tex_DANRESULT_NOTREACH, panel_x, panel_y, rect_panel);
		}
	}

}

void CObjDanResultSongPanel::AnimeStart()
{
	if (!m_ct_song_slide_delay.GetProgress())
		m_ct_song_slide_delay.Start(0, MusicGame::DAN_MAX_SONG * DANRESULT_SONGPANEL_SLIDE_DELAY, 1);
	
}