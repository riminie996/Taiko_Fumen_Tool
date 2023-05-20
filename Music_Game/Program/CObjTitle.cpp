#include "CObjTitle.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

//‰Šú‰»
void CObjTitle::Init()
{
	Audio::LoadAudio2(bgm_MUSIC, "Sound/0_Title/BGM.ogg", EFFECT);
	Audio::LoadAudio2(bgm_IN, "Sound/0_Title/voice.ogg", EFFECT);
	m_fadein.m_color = Color::Black;
	m_fadeout.m_color = Color::Black;
	m_fadein.m_fade_type = CFIFO::FadeIn;
	m_fadeout.m_fade_type = CFIFO::FadeOut;
	m_ani_appear.LoadData("Animation/Title/Appear");
	m_ani_logo_effect.LoadData("Animation/Title/LogoEffect");
	m_fadein.Start();
	Audio::Start(bgm_MUSIC);
	Audio::Start(bgm_IN);
	m_ani_appear.Start();
	m_ani_logo_effect.Start();

}
//is
void CObjTitle::Action()
{
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
	m_ani_appear.Action();
	m_ani_logo_effect.Action();

	if (system->GetInput(LEFT_DON, 0) || system->GetInput(RIGHT_DON, 0))
	{
		m_fadeout.Start();
	}
	if (m_fadeout.GetEnd())
	{
		system->TitleEnd();
		system->EntryStart();
	}
}
//•`‰æ
void CObjTitle::Draw()
{
	int anime_x = 0;
	int anime_y = 0;
	MusicGame::g_tex_title.m_scale_x = 1.0f;
	MusicGame::g_tex_title.m_scale_y = 1.0f;
	MusicGame::g_tex_title.m_opacity = 1.0f;	
	MusicGame::g_tex_title.m_blend = E_BLEND_MODE::NORMAL;

	MusicGame::g_tex_title.Draw(BACKGROUND_POS.x + anime_x, BACKGROUND_POS.y + anime_y, RECT_BACKGROUND);

	anime_x = m_ani_appear.GetValue("Hiyoko1").x;
	anime_y = m_ani_appear.GetValue("Hiyoko1").y;
	MusicGame::g_tex_title.Draw(HIYOKO1_POS.x + anime_x, HIYOKO1_POS.y + anime_y, RECT_HIYOKO1);
	anime_x = m_ani_appear.GetValue("Hiyoko2").x;
	anime_y = m_ani_appear.GetValue("Hiyoko2").y;
	MusicGame::g_tex_title.Draw(HIYOKO2_POS.x + anime_x, HIYOKO2_POS.y + anime_y, RECT_HIYOKO2);
	anime_x = m_ani_appear.GetValue("Daruma").x;
	anime_y = m_ani_appear.GetValue("Daruma").y;
	MusicGame::g_tex_title.Draw(DARUMA_POS.x + anime_x, DARUMA_POS.y + anime_y, RECT_DARUMA);
	anime_x = m_ani_appear.GetValue("Suzu").x;
	anime_y = m_ani_appear.GetValue("Suzu").y;
	MusicGame::g_tex_title.Draw(SUZU_POS.x + anime_x, SUZU_POS.y + anime_y, RECT_SUZU);
	anime_x = m_ani_appear.GetValue("Bachio").x;
	anime_y = m_ani_appear.GetValue("Bachio").y;
	MusicGame::g_tex_title.Draw(BACHIO_POS.x + anime_x, BACHIO_POS.y + anime_y, RECT_BACHIO);
	anime_x = m_ani_appear.GetValue("Tetsuo").x;
	anime_y = m_ani_appear.GetValue("Tetsuo").y;
	MusicGame::g_tex_title.Draw(TETSUO_POS.x + anime_x, TETSUO_POS.y + anime_y, RECT_TETSUO);
	anime_x = m_ani_appear.GetValue("Hanako").x;
	anime_y = m_ani_appear.GetValue("Hanako").y;
	MusicGame::g_tex_title.Draw(HANAKO_POS.x + anime_x, HANAKO_POS.y + anime_y, RECT_HANAKO);
	anime_x = m_ani_appear.GetValue("Donko").x;
	anime_y = m_ani_appear.GetValue("Donko").y;
	MusicGame::g_tex_title.Draw(DONKO_POS.x + anime_x, DONKO_POS.y + anime_y, RECT_DONKO);
	anime_x = m_ani_appear.GetValue("Kamen").x;
	anime_y = m_ani_appear.GetValue("Kamen").y;
	MusicGame::g_tex_title.Draw(KAMEN_POS.x + anime_x, KAMEN_POS.y + anime_y, RECT_KAMEN);
	anime_x = m_ani_appear.GetValue("Donchan").x;
	anime_y = m_ani_appear.GetValue("Donchan").y;
	MusicGame::g_tex_title.Draw(DONCHAN_POS.x + anime_x, DONCHAN_POS.y + anime_y, RECT_DONCHAN);
	anime_x = m_ani_appear.GetValue("Kacchan").x;
	anime_y = m_ani_appear.GetValue("Kacchan").y;
	MusicGame::g_tex_title.Draw(KACCHAN_POS.x + anime_x, KACCHAN_POS.y + anime_y, RECT_KACCHAN);
	anime_x = 0;
	anime_y = 0;
	float scale = m_ani_appear.GetValue("Taiko").scale_x;
	MusicGame::g_tex_title.m_scale_x = scale;
	MusicGame::g_tex_title.m_scale_y = scale;
	MusicGame::g_tex_title.Draw(TAIKO_POS.x + anime_x, TAIKO_POS.y + anime_y, RECT_TAIKO, ref_Center, ref_Center);

	scale = m_ani_appear.GetValue("Logo").scale_x;
	MusicGame::g_tex_title.m_scale_x = scale;
	MusicGame::g_tex_title.m_scale_y = scale;
	MusicGame::g_tex_title.m_opacity = m_ani_appear.GetValue("Logo").opacity;
	MusicGame::g_tex_title.Draw(LOGO_POS.x + anime_x, LOGO_POS.y + anime_y, RECT_LOGO, ref_Center, ref_Center);

	scale = m_ani_logo_effect.GetValue(0).scale_x;
	MusicGame::g_tex_title.m_scale_x = scale;
	MusicGame::g_tex_title.m_scale_y = scale;
	MusicGame::g_tex_title.m_opacity = m_ani_logo_effect.GetValue(0).opacity;
	MusicGame::g_tex_title.m_blend = E_BLEND_MODE::ADDITIONALPHA;
	MusicGame::g_tex_title.Draw(LOGO_POS.x + anime_x, LOGO_POS.y + anime_y, RECT_LOGO, ref_Center, ref_Center);
	m_fadein.ActionDraw();			   
	m_fadeout.ActionDraw();
}
