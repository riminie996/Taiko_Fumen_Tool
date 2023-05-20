#include "CObjScore.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//初期化
void CObjScore::Init()
{
	m_num_score.SetTex(tex_SCORE, RECT_SCORE_NUM.m_width, RECT_SCORE_NUM.m_height);
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
	if (((UserData*)Save::GetData())->m_player_amount <= 2)
	{
		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		{
			for (int j = 0; j < (int)E_SCORE_RANK::RANK_Count; j++)
			{
				m_ani_score_rank_appear[i][j].LoadData("Animation/Enso/ScoreRankAppear");
			}

			m_add.ani_add_score_in.LoadData("Animation/Enso/Add1PScoreIn");

			m_add.vec_ani_add_score_out.resize(6);
			for (int j = 0; j < m_add.vec_ani_add_score_out.size(); j++)
			{
				m_add.vec_ani_add_score_out[j].LoadData("Animation/Enso/Add1PScoreOut");
			}
			m_lyt_score_bg[i].LoadData("Layout/Enso/Score_BG_" + to_string(i + 1) + "P");
		}
	}
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_ani_score_scale[i].LoadData("Animation/Enso/Score/ScoreScale");
	}
	m_ani_scorenum_effect.LoadData("Animation/Enso/ScoreNumEffect");
	m_ani_score_effect_appear.LoadData("Animation/Enso/ScoreEffectAppear");
	m_ani_score_effect_wait.LoadData("Animation/Enso/ScoreEffectWait");

	m_ani_bestscore_back.LoadData("Animation/Enso/Score/BestScoreBack");
	m_ani_bestscore_effect.LoadData("Animation/Enso/Score/BestScoreEffect");
	m_ani_bestscore_light.LoadData("Animation/Enso/Score/BestScoreLight");
	m_ani_bestscore_text.LoadData("Animation/Enso/Score/BestScoreText");
	m_ani_scorenum_effect.Start();
	m_ani_score_effect_wait.Start();
}
//進行
void CObjScore::Action()
{
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_ani_score_scale[i].Action();
	}
	m_ani_scorenum_effect.ActionLoop();
	m_ani_score_effect_appear.Action();
	m_ani_score_effect_wait.ActionLoop();

	m_ani_bestscore_back.Action();
	m_ani_bestscore_effect.Action();
	m_ani_bestscore_light.Action();
	m_ani_bestscore_text.Action();

	if (((UserData*)Save::GetData())->m_player_amount <= 2)
	{
		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		{
			for (int j = 0; j < (int)E_SCORE_RANK::RANK_Count; j++)
				m_ani_score_rank_appear[i][j].Action();

			for (auto itr = m_list_add[i].begin(); itr != m_list_add[i].end();)
			{
				itr->ani_add_score_in.Action();
				for (int j = 0; j < itr->vec_ani_add_score_out.size(); j++)
					itr->vec_ani_add_score_out[j].Action();

				if (itr->vec_ani_add_score_out[itr->vec_ani_add_score_out.size() - 1].GetEnd())
				{
					itr = m_list_add[i].erase(itr);
				}
				else
				{
					itr++;
				}
			}


		}
	}

	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		if (enso->m_enso[i].m_best_score_data[((UserData*)Save::GetData())->m_now_select_diffculty[i]].score > 0 &&
			enso->m_enso[i].m_best_score_data[((UserData*)Save::GetData())->m_now_select_diffculty[i]].score < enso->m_enso[i].m_score_data.score)
		{
			if (!m_ani_score_effect_appear.GetStart())
			{
				m_ani_score_effect_appear.Start();
				m_ani_bestscore_back.Start();
				m_ani_bestscore_effect.Start();
				m_ani_bestscore_light.Start();
				m_ani_bestscore_text.Start();
			}
		}
	}
}
//描画
void CObjScore::Draw()
{
	if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)return;

	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	Draw::SetBlend(tex_SCORE_EFFECT, ADDITIONALPHA);

	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{

		MusicGame::g_tex_score_bg.m_flip_y = i % 2 == 0 ? false : true;
		MusicGame::g_tex_score_bg.Draw(m_lyt_score_bg[i].GetData().pos.x, m_lyt_score_bg[i].GetData().pos.y, m_lyt_score_bg[i].GetData().rectangle);

		Draw::SetScaleY(tex_SCORE, m_ani_score_scale[i].GetValue(0).scale_y);
		int val = enso->m_enso[i].m_score_data.score;

		if (enso->m_enso[i].m_best_score_data[((UserData*)Save::GetData())->m_now_select_diffculty[i]].score > 0 &&
			enso->m_enso[i].m_best_score_data[((UserData*)Save::GetData())->m_now_select_diffculty[i]].score < val)
		{
			float effect_x = P1_SCORE_POS[i].x + SCORE_EFFECT_OFFSET.x;
			float effect_y = P1_SCORE_POS[i].y + SCORE_EFFECT_OFFSET.y;

			if (m_ani_score_effect_appear.GetEnd())
			{
				Draw::SetScaleX(tex_SCORE_EFFECT, 1.0f);

				Draw::SetOpacity(tex_SCORE_EFFECT, m_ani_score_effect_wait.GetValue().opacity);
				Draw::CenterDraw(tex_SCORE_EFFECT, effect_x, effect_y, RECT_EFFECT);

				Draw::SetOpacity(tex_SCORE_EFFECT, 0.75f - m_ani_score_effect_wait.GetValue().opacity);
				Draw::CenterDraw(tex_SCORE_EFFECT, effect_x, effect_y, RECT_EFFECT, false, true);
			}
			else
			{
				Draw::SetScaleX(tex_SCORE_EFFECT, m_ani_score_effect_appear.GetValue().scale_x);
				Draw::SetOpacity(tex_SCORE_EFFECT, m_ani_score_effect_appear.GetValue().opacity);
				Draw::CenterDraw(tex_SCORE_EFFECT, effect_x, effect_y, RECT_EFFECT);
			}
		}
		float y_move = m_ani_score_scale[i].GetValue(0).scale_y * RECT_SCORE_NUM.m_height - RECT_SCORE_NUM.m_height;
		Draw::SetColor(tex_SCORE, Color::White);
		Draw::SetOpacity(tex_SCORE, 1.0f);
		m_num_score.Draw(val, P1_SCORE_POS[i].x, P1_SCORE_POS[i].y - y_move, SCORE_PADDING);

		if (enso->m_enso[i].m_best_score_data[((UserData*)Save::GetData())->m_now_select_diffculty[i]].score > 0 &&
			enso->m_enso[i].m_best_score_data[((UserData*)Save::GetData())->m_now_select_diffculty[i]].score * 0.97f <= val)
		{
			float effect_x = P1_SCORE_POS[i].x + SCORENUM_EFFECT_OFFSET.x;
			Draw::SetOpacity(tex_SCORE_EFFECT, m_ani_scorenum_effect.GetValue().opacity);
			for (int j = 0; j < numOfDigit(val); j++)
			{
				Draw::CenterDraw(tex_SCORE_EFFECT, effect_x - j * SCORE_PADDING, P1_SCORE_POS[i].y + SCORENUM_EFFECT_OFFSET.y, RECT_NUMEFFECT);
			}
		}
		

		//同じテクスチャを使いまわしてるので、拡大率をもとに戻す
		Draw::SetScaleY(tex_SCORE, 1.0f);
		for (auto itr = m_list_add[i].rbegin(); itr != m_list_add[i].rend(); itr++)
		{
			Draw::SetColor(tex_SCORE, P1_SCORE_COLOR[i]);
			float x = 0.0f;
			float y = 0.0f;
			float opacity = itr->ani_add_score_in.GetValue().opacity;

			x = P1_SCORE_POS[i].x + itr->ani_add_score_in.GetValue().x;
			for (int j = 0; j < itr->vec_ani_add_score_out.size(); j++)
			{
				y = P1_SCORE_POS[i].y;
				y += i == 0 ? itr->vec_ani_add_score_out[j].GetValue().y : -itr->vec_ani_add_score_out[j].GetValue().y;
				opacity *= itr->vec_ani_add_score_out[j].GetValue().opacity;
			}


			Draw::SetOpacity(tex_SCORE, opacity);
			m_num_score.Draw(itr->add, x, y, SCORE_PADDING);
		}

		for (int j = 0; j < (int)E_SCORE_RANK::RANK_Count; j++)
		{
			RECT_F rect_rank = RECT_RANK;
			rect_rank.m_y = RECT_RANK.m_height * j;

			Draw::SetOpacity(tex_SCORE_RANK, m_ani_score_rank_appear[i][j].GetValue().opacity);
			Draw::SetScaleX(tex_SCORE_RANK, m_ani_score_rank_appear[i][j].GetValue().scale_x);
			Draw::SetScaleY(tex_SCORE_RANK, m_ani_score_rank_appear[i][j].GetValue().scale_x);
			float y_move = i == 0 ? m_ani_score_rank_appear[i][j].GetValue().y : -m_ani_score_rank_appear[i][j].GetValue().y;
			Draw::CenterDraw(tex_SCORE_RANK, RANK_POS[i].x + m_ani_score_rank_appear[i][j].GetValue().x, RANK_POS[i].y + y_move, rect_rank);
		}
	}
	Draw::SetScaleX(tex_ENSO_BESTSCORE, m_ani_bestscore_back.GetValue().scale_x);
	Draw::SetScaleY(tex_ENSO_BESTSCORE, m_ani_bestscore_back.GetValue().scale_y);
	Draw::SetOpacity(tex_ENSO_BESTSCORE, m_ani_bestscore_back.GetValue().opacity);
	Draw::SetBlend(tex_ENSO_BESTSCORE, NORMAL);
	Draw::CenterDraw(tex_ENSO_BESTSCORE, BESTSCORE_POS.x, BESTSCORE_POS.y, RECT_BEST_BACK);

	Draw::SetScaleX(tex_ENSO_BESTSCORE, 1.0f);
	Draw::SetScaleY(tex_ENSO_BESTSCORE, 1.0f);
	Draw::SetOpacity(tex_ENSO_BESTSCORE, m_ani_bestscore_light.GetValue().opacity);
	Draw::CenterDraw(tex_ENSO_BESTSCORE, BESTSCORE_POS.x, BESTSCORE_POS.y, RECT_BEST_LIGHT[(int)m_ani_bestscore_light.GetValue().pattern]);

	Draw::SetOpacity(tex_ENSO_BESTSCORE, m_ani_bestscore_text.GetValue().opacity);
	Draw::CenterDraw(tex_ENSO_BESTSCORE, BESTSCORE_POS.x, BESTSCORE_POS.y, RECT_BEST_TEXT);

	Draw::SetScaleX(tex_ENSO_BESTSCORE, m_ani_bestscore_effect.GetValue().scale_x);
	Draw::SetScaleY(tex_ENSO_BESTSCORE, m_ani_bestscore_effect.GetValue().scale_y);
	Draw::SetOpacity(tex_ENSO_BESTSCORE, m_ani_bestscore_effect.GetValue().opacity);
	Draw::SetBlend(tex_ENSO_BESTSCORE, ADDITIONALPHA);
	Draw::CenterDraw(tex_ENSO_BESTSCORE, BESTSCORE_POS.x, BESTSCORE_POS.y, RECT_BEST_EFFECT);
	
}

void CObjScore::AddScore(int add,int player)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);

	add = add / 10 * 10;

	//10点未満は切り捨て
	enso->m_enso[player].m_score_data.score += add;
	m_ani_score_scale[player].Start();


	stAddScore add_score = m_add;
	add_score.add = add;
	add_score.ani_add_score_in.Start();

	for (int i = 0; i < add_score.vec_ani_add_score_out.size(); i++)
	{
		add_score.vec_ani_add_score_out[i].Start();
	}

	m_list_add[player].push_back(add_score);

	if (((UserData*)Save::GetData())->m_now_select_diffculty[0] != DIFF_DAN)
	{

		for (int i = 0; i < (int)E_SCORE_RANK::RANK_Count; i++)
		{
			if (enso->m_enso[player].m_score_data.score >= enso->m_enso[player].m_score_data.score_rank_norma[i] &&
				!m_ani_score_rank_appear[player][i].GetStart())
			{
				m_ani_score_rank_appear[player][i].Start();
				enso->m_enso[player].m_score_data.score_rank = (E_SCORE_RANK)i;
			}
		}
	}
	if (dan != nullptr)
		dan->AddSongScore(add);
}