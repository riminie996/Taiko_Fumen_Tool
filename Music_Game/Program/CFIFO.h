#pragma once
//RECT_F�\����
//�`��֐�
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
	float m_opacity;			//�����x
	RECT_F m_rect_white_tile;	//���摜�؂���ʒu
	CCounter m_ct_fade;			//�����x�Ǘ�
	bool m_start_flag;

	void DrawFill();			//�S�̂ɕ`��
};