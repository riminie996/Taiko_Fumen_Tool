#include "CObjBattleEndEffect.h"
#include "GameHead.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"
//èâä˙âª
void CObjBattleEndEffect::Init()
{
	if (m_result == E_BATTLE_RESULT::VICTORY)
	{
		m_tex_result.LoadTexture("Graphics/10_Battle/Victory.png");
		Audio::LoadAudio2(se_BATTLE_RESULT, "Sound/10_Battle/Victory.ogg", EFFECT);
	
	}
	else
	{
		m_tex_result.LoadTexture("Graphics/10_Battle/Lose.png");
		Audio::LoadAudio2(se_BATTLE_RESULT, "Sound/10_Battle/Lose.ogg", EFFECT);
	}
	m_ani_result.LoadData("Animation/Battle/Result");
	
	m_ani_result.Start();
	Audio::Start(se_BATTLE_RESULT);
}
//êiçs
void CObjBattleEndEffect::Action()
{
	m_ani_result.Action();
}
//ï`âÊ
void CObjBattleEndEffect::Draw()
{
	RECT_N rect_uchiwa = { 0,(int)m_ani_result.GetValue("Uchiwa").pattern*256,512,256 };
	m_tex_result.m_scale_x = m_ani_result.GetValue("Uchiwa").scale_x;
	m_tex_result.m_scale_y = m_ani_result.GetValue("Uchiwa").scale_y;
	m_tex_result.m_opacity = 1.0f;
	m_tex_result.Draw(640, 360, rect_uchiwa, ref_Center, ref_Center);

	RECT_N rect_text = { 0,768,512,256 };
	m_tex_result.m_scale_x = m_ani_result.GetValue("Text").scale_x;
	m_tex_result.m_scale_y = m_ani_result.GetValue("Text").scale_y;
	m_tex_result.m_opacity = m_ani_result.GetValue("Text").opacity;
	m_tex_result.Draw(640, 360, rect_text, ref_Center, ref_Center);
}
