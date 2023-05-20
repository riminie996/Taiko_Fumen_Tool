#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjLoading : public CObj
{
public:
	CObjLoading() {}
	~CObjLoading() {}
	void Init();
	void Action();
	void Draw();

private:
	CAnime2 m_ani_fade_L = { "Animation/Loading/LoadingFadeL" };
	CAnime2 m_ani_fade_R = { "Animation/Loading/LoadingFadeR" };
	CAnime2 m_ani_fadeout_L = { "Animation/Loading/LoadingFadeOutL" };
	CAnime2 m_ani_fadeout_R = { "Animation/Loading/LoadingFadeOutR" };
	CAnime2 m_ani_chara = { "Animation/Loading/CharacterMove" }; 
	CAnime2 m_ani_chara_out = { "Animation/Loading/CharacterMoveOut" }; 
	CAnime2 m_ani_wait_in = { "Animation/Loading/LoadingWaitIn" };
	CAnime2 m_ani_wait_out = { "Animation/Loading/LoadingWaitOut" };

	const RECT_F RECT_FADE_L = { 0.0f,0.0f,640.0f,720.0f };
	const RECT_F RECT_FADE_R = { 640.0f,0.0f,640.0f,720.0f };
	const Point TITLE_POS = { 640,258 };
	const float TITLE_FONT_SIZE = 45.0f;

	bool m_loading_start;
};
