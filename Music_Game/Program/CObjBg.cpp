#include "CObjBg.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//èâä˙âª
void CObjBg::Init()
{
//	m_ct_offset_x = { CCounter(0.0f,0.0f,RECT_TEX_SIZE_0_1.m_width,LOOP) };
	if (MusicGame::g_mode == E_GAME_MODE::ENSO)
	{

		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		{
			m_ct_clear_opacity[i] = { CCounter(0.0f,0.0f,1.0f,STOP) };
		}
		m_ani_bg_0_0.Start();
		m_ani_bg_0_1.Start();

		int skin_num = 0;
		string str_skin = m_skin_name;

		if (USER_DATA->m_now_select_diffculty[0] == DIFF_DAN)
		{
			str_skin = "Dan";
			skin_num = 0;
		}

		string dir = "Graphics/3_Enso/18_Skin/" + str_skin + "/Top/" + to_string(skin_num) + "/";
		if (USER_DATA->m_player_amount <= 2)
		{

			m_vec_bg_top_1p.resize(USER_DATA->m_player_amount);
			for (int i = 0; i < USER_DATA->m_player_amount; i++)
			{
				int count = MusicGame::TextureAmountCount(dir + to_string(i + 1) + "p/", ".rmlyt");

				m_vec_bg_top_1p[i].resize(count);
				for (int j = 0; j < count; j++)
				{
					m_vec_bg_top_1p[i][j].lyt.LoadData(dir + to_string(i + 1) + "p/" + to_string(j));
					m_vec_bg_top_1p[i][j].ani_appear.LoadData(dir + to_string(i + 1) + "p/appear_" + to_string(j));
					m_vec_bg_top_1p[i][j].ani_loop.LoadData(dir + to_string(i + 1) + "p/wait_" + to_string(j));
					m_vec_bg_top_1p[i][j].tex.LoadTexture(dir + to_string(i + 1) + "p/top_" + to_string(j) + ".png");
				}




			}
			int count = MusicGame::TextureAmountCount(dir + "clear/", ".rmlyt");
			m_vec_tex_top_clear.resize(count);
			for (int i = 0; i < count; i++)
			{
				m_vec_tex_top_clear[i].lyt.LoadData(dir + "clear/" + to_string(i));
				m_vec_tex_top_clear[i].ani_appear.LoadData(dir + "clear/appear_" + to_string(i));
				m_vec_tex_top_clear[i].ani_loop.LoadData(dir + "clear/wait_" + to_string(i));
				m_vec_tex_top_clear[i].tex.LoadTexture(dir + "clear/top_" + to_string(i) + ".png");
			}
		}
		if (USER_DATA->m_player_amount == 1 && USER_DATA->m_now_select_diffculty[0] != DIFF_DAN)
		{
			dir = "Graphics/3_Enso/18_Skin/" + str_skin + "/Bottom/Normal/0/";
			int count = MusicGame::TextureAmountCount(dir, ".rmlyt");
			m_vec_tex_bottom.resize(count);
			for (int i = 0; i < count; i++)
			{
				m_vec_tex_bottom[i].lyt.LoadData(dir + to_string(i));
				m_vec_tex_bottom[i].ani_appear.LoadData(dir + "Appear/" + to_string(i));
				m_vec_tex_bottom[i].ani_loop.LoadData(dir + "Loop/" + to_string(i));
				m_vec_tex_bottom[i].tex.LoadTexture(dir + to_string(i) + ".png");
			}

			dir = "Graphics/3_Enso/18_Skin/" + str_skin + "/Bottom/Clear/0/";
			count = MusicGame::TextureAmountCount(dir, ".rmlyt");
			m_vec_tex_bottom_clear.resize(count);
			for (int i = 0; i < count; i++)
			{
				m_vec_tex_bottom_clear[i].lyt.LoadData(dir + to_string(i));
				m_vec_tex_bottom_clear[i].ani_appear.LoadData(dir + "Appear/" + to_string(i));
				m_vec_tex_bottom_clear[i].ani_loop.LoadData(dir + "Loop/" + to_string(i));
				m_vec_tex_bottom_clear[i].tex.LoadTexture(dir + to_string(i) + ".png");
			}
		}

		for (int i = 0; i < m_vec_bg_top_1p.size(); i++)
		{
			for (int j = 0; j < m_vec_bg_top_1p[i].size(); j++)
			{
				m_vec_bg_top_1p[i][j].ani_appear.Start();
			}
		}
		for (int i = 0; i < m_vec_tex_top_clear.size(); i++)
		{
			m_vec_tex_top_clear[i].ani_appear.Start();
		}
		for (int i = 0; i < m_vec_tex_bottom.size(); i++)
		{
			m_vec_tex_bottom[i].ani_appear.Start();
		}

	}
	else if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
	{
		m_vec_tex_bottom.resize(1);
			
		m_vec_tex_bottom[0].lyt.LoadData("Layout/Battle/Background");
		m_vec_tex_bottom[0].tex.LoadTexture("Fumen_Battle/hikarinokanatahe-ura/Effect/Background/0.png");
	
	}
}
//êiçs
void CObjBg::Action()
{
	if (MusicGame::g_mode == E_GAME_MODE::ENSO)
	{
		for (int i = 0; i < m_vec_bg_top_1p.size(); i++)
		{
			for (int j = 0; j < m_vec_bg_top_1p[i].size(); j++)
			{
				m_vec_bg_top_1p[i][j].ani_appear.Action();
				m_vec_bg_top_1p[i][j].ani_loop.ActionLoop();

				if (m_vec_bg_top_1p[i][j].ani_appear.GetEnd() &&
					!m_vec_bg_top_1p[i][j].ani_loop.GetStart())
				{
					m_vec_bg_top_1p[i][j].ani_loop.Start();
				}
			}
		}
		for (int i = 0; i < m_vec_tex_top_clear.size(); i++)
		{
			m_vec_tex_top_clear[i].ani_appear.Action();
			m_vec_tex_top_clear[i].ani_loop.ActionLoop();

			if (m_vec_tex_top_clear[i].ani_appear.GetEnd() &&
				!m_vec_tex_top_clear[i].ani_loop.GetStart())
			{
				m_vec_tex_top_clear[i].ani_loop.Start();
			}
		}
		for (int i = 0; i < m_vec_tex_bottom.size(); i++)
		{
			m_vec_tex_bottom[i].ani_appear.Action();
			m_vec_tex_bottom[i].ani_loop.ActionLoop();

			if (m_vec_tex_bottom[i].ani_appear.GetEnd() &&
				!m_vec_tex_bottom[i].ani_loop.GetStart())
			{
				m_vec_tex_bottom[i].ani_loop.Start();
			}
		}
		CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
		CObjNormaGauge* norma = (CObjNormaGauge*)Objs::GetObj(OBJ_GAUGE);
		if (enso->m_enso[0].m_score_data.ct_gauge.NowValue >= norma->GetNorma(0))
		{
			for (int i = 0; i < m_vec_tex_bottom_clear.size(); i++)
			{

				m_vec_tex_bottom_clear[i].ani_appear.Action();
				m_vec_tex_bottom_clear[i].ani_loop.ActionLoop();

				if (!m_vec_tex_bottom_clear[i].ani_appear.GetStart())
				{
					m_vec_tex_bottom_clear[i].ani_appear.Start();
				}

				if (m_vec_tex_bottom_clear[i].ani_appear.GetEnd() &&
					!m_vec_tex_bottom_clear[i].ani_loop.GetStart())
				{
					m_vec_tex_bottom_clear[i].ani_loop.Start();
				}


			}
		}
		else
		{
			for (int i = 0; i < m_vec_tex_bottom_clear.size(); i++)
			{
				m_vec_tex_bottom_clear[i].ani_appear.End();
				m_vec_tex_bottom_clear[i].ani_loop.End();
			}
		}
		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		{
			if (enso->m_enso[i].m_score_data.ct_gauge.NowValue >= norma->GetNorma(i))
			{
				m_ct_clear_opacity[i].Add(1.0f / CLEAR_FADE_FRAME);

				for (int i = 0; i < BOTTOM_CLEAR_AMOUNT; i++)
				{
					if (!m_ani_bg_bottom_clear_appear[i].GetStart())
						m_ani_bg_bottom_clear_appear[i].Start();

					if (m_ani_bg_bottom_clear_appear[i].GetEnd() &&
						!m_ani_bg_bottom_clear_loop[i].GetStart())
					{
						m_ani_bg_bottom_clear_loop[i].Start();
					}


				}
			}
			else
			{
				m_ct_clear_opacity[i].Sub(1.0f / CLEAR_FADE_FRAME);

				for (int i = 0; i < BOTTOM_CLEAR_AMOUNT; i++)
				{
					m_ani_bg_bottom_clear_appear[i].End();
					m_ani_bg_bottom_clear_loop[i].End();
				}
			}
		}
	}
	else if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
	{
	}
}
//ï`âÊ
void CObjBg::Draw()
{
	//â∫îwåiÇÃï`âÊ
	if (MusicGame::g_mode == E_GAME_MODE::ENSO)
	{
		for (int i = 0; i < m_vec_tex_bottom.size(); i++)
		{
			m_vec_tex_bottom[i].BackGroundDraw(0);
		}
		CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
		CObjNormaGauge* norma = (CObjNormaGauge*)Objs::GetObj(OBJ_GAUGE);

		if (enso->m_enso[0].m_score_data.ct_gauge.NowValue >= norma->GetNorma(0))
		{
			for (int i = 0; i < m_vec_tex_bottom_clear.size(); i++)
			{
				m_vec_tex_bottom_clear[i].BackGroundDraw(0);
			}
		}
		//è„îwåiÇÃï`âÊ
		//1P
		for (int i = 0; i < m_vec_bg_top_1p.size(); i++)
		{
			for (int j = 0; j < m_vec_bg_top_1p[i].size(); j++)
			{
				m_vec_bg_top_1p[i][j].BackGroundDraw(i);
			}
		}

		//ÉNÉäÉA
		for (int j = 0; j < USER_DATA->m_player_amount; j++)
		{
			for (int i = 0; i < m_vec_tex_top_clear.size(); i++)
			{
				int x = m_vec_tex_top_clear[i].lyt.GetData().pos.x + m_vec_tex_top_clear[i].ani_loop.GetValue().x;
				int y = m_vec_tex_top_clear[i].lyt.GetData().pos.y + m_vec_tex_top_clear[i].ani_loop.GetValue().y;
				RECT_N rect = m_vec_tex_top_clear[i].lyt.GetData().rectangle;
				m_vec_tex_top_clear[i].tex.m_opacity = m_ct_clear_opacity[j].NowValue;
				rect.m_y = (int)m_vec_tex_top_clear[i].ani_loop.GetValue().pattern * rect.m_height;
				//ÉãÅ[Év
				do
				{
					do
					{


						m_vec_tex_top_clear[i].tex.Draw(x, y + j * BG_P2_TOP_POS, rect);
						x += rect.m_width;

					} while (x < WINDOW_SIZE_W && m_vec_tex_top_clear[i].lyt.GetData().loop_x == true);

					y += rect.m_height;

				} while (y < WINDOW_SIZE_H && m_vec_tex_top_clear[i].lyt.GetData().loop_y == true);

			}
		}
	}
	else if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
	{
		for (int i = 0; i < m_vec_tex_bottom.size(); i++)
		{
			m_vec_tex_bottom[i].BackGroundDraw(0);
		}
	}
}
