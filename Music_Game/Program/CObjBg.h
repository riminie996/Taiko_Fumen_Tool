#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjBg : public CObj
{
public:
	CObjBg() { m_skin_name = "Common"; }
	CObjBg(string name) { m_skin_name = name; }
	~CObjBg() {}
	void Init();
	void Action();
	void Draw();
private:
	struct ST_BG
	{
		CTexture tex;
		CLayout lyt;
		CAnime2 ani_appear;
		CAnime2 ani_loop;

		void BackGroundDraw(int player)
		{
			int x = 0; 
			int y = 0; ;
			//Yの切り取り開始位置をパターンで変更する
			RECT_N rect = lyt.GetSource();

			if (!ani_appear.GetEnd())
			{
				x = lyt.GetPos().x + ani_appear.GetValue().x;
				y = lyt.GetPos().y + ani_appear.GetValue().y + player * BG_P2_TOP_POS;
				tex.m_opacity = ani_appear.GetValue().opacity;
				tex.m_scale_x = ani_appear.GetValue().scale_x;
				tex.m_scale_y = ani_appear.GetValue().scale_y;
				rect.m_y = (int)ani_appear.GetValue().pattern * rect.m_height;
			}
			else
			{
				x = lyt.GetPos().x + ani_loop.GetValue().x;
				y = lyt.GetPos().y + ani_loop.GetValue().y + player * BG_P2_TOP_POS;
				tex.m_opacity = ani_loop.GetValue().opacity;
				tex.m_scale_x = ani_loop.GetValue().scale_x;
				tex.m_scale_y = ani_loop.GetValue().scale_y;
				rect.m_y = (int)ani_loop.GetValue().pattern * rect.m_height;
			}


			tex.m_blend =lyt.GetBlend();
			

			//ループ
			do
			{
				do
				{
					tex.Draw(x, y, rect, lyt.GetRefX(), lyt.GetRefY());
					x += rect.m_width;

				} while (x < WINDOW_SIZE_W && lyt.GetLoopX() == true);

				y += rect.m_height;

			} while (y < WINDOW_SIZE_H && lyt.GetLoopY() == true);
		}
	};


	const RECT_N RECT_TEX_SIZE_0_0 = { 0,0,328,192 };
	const RECT_N RECT_TEX_SIZE_0_1 = { 0,0,1312,267 };
	const int CLEAR_FADE_FRAME = 15;//クリア背景のフェードにかけるフレーム数
	const Point BG_BOTTOM_POS = { 0,360 };
	const Point BG_FOOTER_POS = { 0,676 };
	const static int BOTTOM_CLEAR_AMOUNT = 6;
	const static int BG_P2_TOP_POS = 536;


	CCounter m_ct_offset_x;
	CCounter m_ct_clear_opacity[2];//2player

	CAnime2 m_ani_bg_0_0 = { "Animation/Enso/bg/top0/0" };
	CAnime2 m_ani_bg_0_1 = { "Animation/Enso/bg/top0/1" };
	CAnime2 m_ani_bg_bottom_loop_0_1 = { "Graphics/3_Enso/5_Background/Bottom/0/Loop/1" };
	CAnime2 m_ani_bg_bottom_clear_appear[BOTTOM_CLEAR_AMOUNT];
	CAnime2 m_ani_bg_bottom_clear_loop[BOTTOM_CLEAR_AMOUNT];


	CAnime2 m_ani_bg_dan_0 = { "Animation/Enso/bg/Dan/0" };
	CAnime2 m_ani_bg_dan_2 = { "Animation/Enso/bg/Dan/2" };
	CAnime2 m_ani_bg_dan_3 = { "Animation/Enso/bg/Dan/3" };
	CAnime2 m_ani_bg_dan_4 = { "Animation/Enso/bg/Dan/4" };
	CAnime2 m_ani_bg_dan_5 = { "Animation/Enso/bg/Dan/5" };


	vector<vector<ST_BG>> m_vec_bg_top_1p;
	//2Pとクリアのものは1Pのやつを流用してみる
	vector<ST_BG> m_vec_bg_top_2p;
	vector<ST_BG> m_vec_tex_top_clear;
	vector<ST_BG> m_vec_tex_bottom;
	vector<ST_BG> m_vec_tex_bottom_clear;
	string m_skin_name;
};
