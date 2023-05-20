#include "CFIFO.h"
#include "GameHead.h"


CFIFO::CFIFO()
{
	this->m_opacity = 0.0f;
	this->m_color = Color::White;
	this->m_ct_fade = { CCounter(0.0f,0.0f,FRAME_FPS,STOP) };
	this->m_fade_type = FadeOut;
	this->m_start_flag = false;

	//�����摜�؂���ʒu
	this->m_rect_white_tile = { 0.0f,0.0f,64.0f,64.0f };
}

//�J�n
void CFIFO::Start()
{
	m_start_flag = true;
}
void CFIFO::Start(int frame)
{
	if (m_start_flag == true)return;

	this->m_ct_fade = { CCounter(0.0f,0.0f,frame,STOP) };
	m_start_flag = true;
}

//�`��
void CFIFO::DrawFill()
{
	//�e�N�X�`���T�C�Y�̕��ړ�������B
	for (float y = 0.0f; y < WINDOW_SIZE_H; y += m_rect_white_tile.m_height)
	{
		for (float x = 0.0f; x < WINDOW_SIZE_W; x += m_rect_white_tile.m_width)
		{
			//�`��֐�
			Draw::Draw(tex_TILE, x, y, m_rect_white_tile);
		}
	}
}
//�i�s
void CFIFO::ActionDraw()
{
	//
	if (m_start_flag == false)return;

	//1�t���[��������
	m_ct_fade.Add(1.0f);

	m_opacity = m_fade_type == FadeOut ? 
		m_ct_fade.NowValue / m_ct_fade.MaxValue : 
		(m_ct_fade.MaxValue - m_ct_fade.NowValue) / m_ct_fade.MaxValue;

	Draw::SetColor(tex_TILE, m_color);
	Draw::SetOpacity(tex_TILE, m_opacity);
	DrawFill();

}