#include "CObjFooter.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//������
void CObjFooter::Init()
{
	
		Draw::LoadImageW(L"Graphics/3_Enso/8_Footer/0.png", tex_FOOTER, TEX_SIZE_64);

}
//�i�s
void CObjFooter::Action()
{
	
}
//�`��
void CObjFooter::Draw()
{
	if(((UserData*)Save::GetData())->m_player_amount == 1)
	{
		Draw::Draw(tex_FOOTER, BG_FOOTER_POS.x, BG_FOOTER_POS.y);
	}
}

