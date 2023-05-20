#include "CObjResult.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

//èâä˙âª
void CObjResultBg::Init()
{

}
//êiçs
void CObjResultBg::Action()
{
	m_ani_background_fade.Action();
	m_ani_background_mountain.Action();

}
//ï`âÊ
void CObjResultBg::Draw()
{
	Draw::SetOpacity(tex_RESULT_CLEAR, m_ani_background_fade.GetValue().opacity);
	Draw::SetOpacity(tex_RESULT_CLEAR_YAMA, m_ani_background_fade.GetValue().opacity);

	//îwåiÇÃï`âÊ
	Draw::Draw(tex_RESULT_BG, 0, 0);
	Draw::Draw(tex_RESULT_CLEAR, 0, 0);


	float mountain_scale = m_ani_background_mountain.GetValue().scale_y;
	float mountain_y = 720.0f * mountain_scale - 720.0f;

	Draw::SetScaleY(tex_RESULT_YAMA, mountain_scale);
	Draw::SetScaleY(tex_RESULT_CLEAR_YAMA, mountain_scale);
	Draw::Draw(tex_RESULT_YAMA, 0, -mountain_y);
	Draw::Draw(tex_RESULT_CLEAR_YAMA, 0, -mountain_y);


	Draw::Draw(tex_RESULT_HEADER, 0, 0);

}

void CObjResultBg::FadeStart()
{
	m_ani_background_fade.Start();
	m_ani_background_mountain.Start();
}