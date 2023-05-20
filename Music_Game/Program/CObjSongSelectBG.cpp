#include "CObjSongSelectBG.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL/WinInputs.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/Userdata.h"
#include <filesystem>



//初期化
void CObjSongSelectBG::Init()
{

	m_ani_background_scroll.Start();

	m_first_action = true;
	m_before_color = 0;
	m_now_color = 0;
}
//進行
void CObjSongSelectBG::Action()
{
	CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);
//	m_now_color = select->GetNowSelectSong().genre;
	
	if (m_first_action == true)
	{
		m_first_action = false;
		m_before_color = m_now_color;
	}

	m_ani_background_scroll.ActionLoop();
	m_ani_background_fade.Action();

}


//描画
void CObjSongSelectBG::Draw()
{
	float x = m_ani_background_scroll.GetValue().x;
	int color = m_now_color;
	while (x <= WINDOW_SIZE_W)
	{
		Draw::SetOpacity(tex_BACKGROUND_NONE + m_before_color, 1.0f);
		Draw::Draw(tex_BACKGROUND_NONE + m_before_color, x, 0.0f);


		Draw::SetOpacity(tex_BACKGROUND_NONE + color, m_ani_background_fade.GetValue().opacity);
		Draw::Draw(tex_BACKGROUND_NONE + color, x, 0.0f);

		//テクスチャサイズぶん加算する
		x += Draw::GetTexSizeW(tex_BACKGROUND_NONE + color);
	}
}

void CObjSongSelectBG::GenreChange(int genre)
{
	CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);
	m_ani_background_fade.Start();
	m_before_color = m_now_color;
	m_now_color = genre;
}

