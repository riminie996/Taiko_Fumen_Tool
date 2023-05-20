#include "CObjEntryBG.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL/WinInputs.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/Userdata.h"
//‰Šú‰»
void CObjEntryBG::Init()
{

	m_ani_background_fadeout.Start();
	m_ani_light.Start();
}
//is
void CObjEntryBG::Action()
{
	m_ani_background_fadeout.Action();
	m_ani_light.ActionLoop();
}


//•`‰æ
void CObjEntryBG::Draw()
{
	//‚Ú‚¯”wŒi‚Ì•`‰æ
	Draw::Draw(tex_ENTRY_BG_BOKE_B, 0, 0);
	Draw::Draw(tex_ENTRY_BG_BOKE, 0, 0);

	Draw::SetOpacity(tex_ENTRY_LIGHT, m_ani_light.GetValue().opacity);
	Draw::SetBlend(tex_ENTRY_LIGHT, E_BLEND_MODE::ADDITIONALPHA);
	//–¾‚©‚è‚Ì•`‰æ
	for (int i = 0; i < MusicGame::Entry::LIGHT_AMOUNT; i++)
	{
		Draw::CenterDraw(tex_ENTRY_LIGHT, MusicGame::Entry::LIGHT_POS[i].x, MusicGame::Entry::LIGHT_POS[i].y);
	}

	Draw::SetOpacity(tex_ENTRY_BACKGROUND, m_ani_background_fadeout.GetValue().opacity);
	Draw::Draw(tex_ENTRY_BACKGROUND, 0, 0);
}
