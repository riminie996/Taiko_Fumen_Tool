#include "CObjControllGuide.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

//初期化
void CObjControllGuide::Init()
{
	m_ani_taiko_effect.LoadData("Animation/Common/ControllGuide/TaikoEffect");
	m_ani_effect_loop.LoadData("Animation/Common/ControllGuide/EffectLoop");
	m_ani_taiko_effect.Start();
	m_ani_effect_loop.Start();
}
//進行
void CObjControllGuide::Action()
{
	m_ani_taiko_effect.ActionLoop();
	m_ani_effect_loop.ActionLoop();
}
//描画
void CObjControllGuide::Draw()
{
	float effect_opacity = m_ani_effect_loop.GetValue(0).opacity;

	//111,108
	MusicGame::g_tex_controll_guide.m_opacity = 1.0f;
	MusicGame::g_tex_controll_guide.Draw(GUIDE_POS.x, GUIDE_POS.y, RECT_BACKGROUND,ref_Center, ref_Center);
	MusicGame::g_tex_controll_guide.Draw(GUIDE_POS.x, GUIDE_POS.y, RECT_TAIKO,ref_Center, ref_Center);

	//左縁エフェクト
	MusicGame::g_tex_controll_guide.m_opacity = m_ani_taiko_effect.GetValue("LeftKA1").opacity * effect_opacity;
	MusicGame::g_tex_controll_guide.Draw(GUIDE_POS.x, GUIDE_POS.y, RECT_KA, ref_Right, ref_Center);
	MusicGame::g_tex_controll_guide.Draw(GUIDE_POS.x, GUIDE_POS.y, RECT_KA2, ref_Right, ref_Center);

	//右縁エフェクト
	MusicGame::g_tex_controll_guide.m_opacity = m_ani_taiko_effect.GetValue("RightKA1").opacity * effect_opacity;
	MusicGame::g_tex_controll_guide.m_flip_x = true;
	MusicGame::g_tex_controll_guide.Draw(GUIDE_POS.x, GUIDE_POS.y, RECT_KA, ref_Left, ref_Center);
	MusicGame::g_tex_controll_guide.Draw(GUIDE_POS.x, GUIDE_POS.y, RECT_KA2, ref_Left, ref_Center);


	//面エフェクト
	MusicGame::g_tex_controll_guide.m_opacity = m_ani_taiko_effect.GetValue("DON1").opacity * effect_opacity;
	MusicGame::g_tex_controll_guide.m_flip_x = false;
	MusicGame::g_tex_controll_guide.m_scale_x = m_ani_taiko_effect.GetValue("DON1").scale_x;
	MusicGame::g_tex_controll_guide.m_scale_y = m_ani_taiko_effect.GetValue("DON1").scale_x;
	MusicGame::g_tex_controll_guide.Draw(GUIDE_POS.x, GUIDE_POS.y, RECT_DON, ref_Center, ref_Center);

	MusicGame::g_tex_controll_guide.m_scale_x = 1.0f;
	MusicGame::g_tex_controll_guide.m_scale_y = 1.0f;


	//左矢印エフェクト
	MusicGame::g_tex_controll_guide.m_opacity = m_ani_taiko_effect.GetValue("ArrowLeft").opacity;
	MusicGame::g_tex_controll_guide.Draw(GUIDE_POS.x + m_ani_taiko_effect.GetValue("ArrowLeft").x, GUIDE_POS.y + m_ani_taiko_effect.GetValue("ArrowLeft").y, RECT_ARROW, ref_Center, ref_Center);

	//右矢印エフェクト
	MusicGame::g_tex_controll_guide.m_opacity = m_ani_taiko_effect.GetValue("ArrowRight").opacity;
	MusicGame::g_tex_controll_guide.m_flip_x = true;
	MusicGame::g_tex_controll_guide.m_flip_y = true;
	MusicGame::g_tex_controll_guide.Draw(GUIDE_POS.x + m_ani_taiko_effect.GetValue("ArrowRight").x, GUIDE_POS.y + m_ani_taiko_effect.GetValue("ArrowRight").y, RECT_ARROW, ref_Center, ref_Center);


	MusicGame::g_tex_controll_guide.m_flip_x = false;
	MusicGame::g_tex_controll_guide.m_flip_y = false;

	MusicGame::g_tex_controll_guide.m_scale_x =  m_ani_taiko_effect.GetValue("Decide").scale_x;
	MusicGame::g_tex_controll_guide.m_scale_y = m_ani_taiko_effect.GetValue("Decide").scale_x;

	MusicGame::g_tex_controll_guide.m_opacity = m_ani_taiko_effect.GetValue("DecideEffect").opacity * effect_opacity;
	MusicGame::g_tex_controll_guide.Draw(DECIDE_POS.x , DECIDE_POS.y, RECT_DECIDE_EFFECT, ref_Center, ref_Center);
	MusicGame::g_tex_controll_guide.m_opacity = m_ani_taiko_effect.GetValue("Decide").opacity;
	MusicGame::g_tex_controll_guide.Draw(DECIDE_POS.x , DECIDE_POS.y, RECT_DECIDE, ref_Center, ref_Center);


	MusicGame::g_tex_controll_guide.m_scale_x = 1.0f;
	MusicGame::g_tex_controll_guide.m_scale_y = 1.0f;

}
