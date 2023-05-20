#include "CObjFooter.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//初期化
void CObjFooter::Init()
{
	
		Draw::LoadImageW(L"Graphics/3_Enso/8_Footer/0.png", tex_FOOTER, TEX_SIZE_64);

}
//進行
void CObjFooter::Action()
{
	
}
//描画
void CObjFooter::Draw()
{
	if(((UserData*)Save::GetData())->m_player_amount == 1)
	{
		Draw::Draw(tex_FOOTER, BG_FOOTER_POS.x, BG_FOOTER_POS.y);
	}
}

