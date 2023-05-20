#pragma once
//RECT_F構造体
//描画関数
#include "GameL\DrawTexture.h"
using namespace GameL;
//CCounter
#include "CCounter.h"

class CFIFO
{
public:
	enum FADE_TYPE
	{
		FadeIn,
		FadeOut,
	};

	CFIFO();
	~CFIFO() {}
	
	COLOR m_color;
	FADE_TYPE m_fade_type;

	void Start();
	void Start(int frame);
	void ActionDraw();
	bool GetEnd() { return m_ct_fade.GetMaxReached(); }
private:
	float m_opacity;			//透明度
	RECT_F m_rect_white_tile;	//白画像切り取り位置
	CCounter m_ct_fade;			//透明度管理
	bool m_start_flag;

	void DrawFill();			//全体に描画
};