#include "CObjLane.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//初期化
void CObjLane::Init()
{
	m_ct_fire_rect = { CTimeCounter(0,7,30) };
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_ani_hit_opacity[i].LoadData("Animation/Enso/HitEffectOpacity");
		m_ani_lane_flush[i].LoadData("Animation/Enso/LaneFlush");
		m_ani_lane_flush_yellow[i].LoadData("Animation/Enso/LaneFlush");

		m_ani_lane_gogo[i].LoadData("Animation/Enso/LaneGogo");
		m_ani_fire_scale[i].LoadData("Animation/Enso/Effect/GogoFireAppear");

		m_ani_branch_text_before[i].LoadData("Animation/Enso/BranchTextUpBefore");
		m_ani_branch_text_after[i].LoadData("Animation/Enso/BranchTextUpAfter");
		m_ani_branch_lane_after[i].LoadData("Animation/Enso/BranchUpAfterLane");
		m_branch[i] = BRANCH_NORMAL;
		m_branch_before[i] = BRANCH_NORMAL;
		m_ani_lane_flush[i].Start();
		m_ani_lane_flush_yellow[i].Start();

		m_branch_anime_dir[i] = 0;

		if (MusicGame::g_mode == E_GAME_MODE::ENSO)
		{
			m_lyt_lane[i].LoadData("Layout/Enso/Lane_" + to_string(i + 1) + "P");
			m_lyt_judge_pos[i].LoadData("Layout/Enso/JudgePos_" + to_string(i + 1) + "P");
		}
		else if(MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
		{
			m_lyt_lane[i].LoadData("Layout/Battle/Lane_" + to_string(i + 1) + "P");
			m_lyt_judge_pos[i].LoadData("Layout/Battle/JudgePos_" + to_string(i + 1) + "P");
		}
	}
	m_lyt_fire.LoadData("Layout/Enso/Effect/Fire");
	g_tex_gogo_fire.LoadTexture("Graphics/3_Enso/10_Effects/Fire.png");
}
//進行
void CObjLane::Action()
{
	m_ct_fire_rect.ActionLoop();
	
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_ani_hit_opacity[i].Action();
		m_ani_lane_flush[i].Action();
		m_ani_lane_flush_yellow[i].Action();
		m_ani_lane_gogo[i].Action();
		m_ani_fire_scale[i].Action();
		m_ani_branch_text_before[i].Action();
		m_ani_branch_text_after[i].Action();
		m_ani_branch_lane_after[i].Action();

		if (m_ani_branch_text_before[i].GetEnd())
		{
			m_branch_before[i] = m_branch[i];
		}
	}
}
//描画
void CObjLane::Draw()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	if (((UserData*)Save::GetData())->m_player_amount <= 2)
	{
		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		{
			//レーンを描画。
			int lane_x = m_lyt_lane[i].GetData().pos.x;
			int lane_y = m_lyt_lane[i].GetData().pos.y;
			int judge_pos_x = m_lyt_judge_pos[i].GetData().pos.x;
			int judge_pos_y = m_lyt_judge_pos[i].GetData().pos.y;

			while (lane_x < WINDOW_SIZE_W)
			{
				MusicGame::g_tex_lane.Draw(lane_x, lane_y);
				lane_x += m_lyt_lane[i].GetData().rectangle.m_width;
			}
			lane_x = m_lyt_lane[i].GetData().pos.x;
			if (enso->m_enso[i].m_fumen.is_branch[((UserData*)Save::GetData())->m_now_select_diffculty[i]] == true)
			{
				RECT_F rect_lane = RECT_LANE_NORMAL;

				switch (m_branch_before[i])
				{
				case BRANCH_KUROTO:
					rect_lane = RECT_LANE_KUROTO;
					break;
				case BRANCH_TATSUJIN:
					rect_lane = RECT_LANE_TATSUJIN;
					break;
				default:
					rect_lane = RECT_LANE_NORMAL;
					break;
				}

				Draw::SetOpacity(tex_BRANCH_LANE, 1.0f);
				Draw::SetOpacity(tex_BRANCH_TEXT, m_ani_branch_text_before[i].GetValue().opacity);
				Draw::Draw(tex_BRANCH_LANE, lane_x, lane_y + LANE_FLUSH_OFFSET, rect_lane);
				Draw::Draw(tex_BRANCH_TEXT, lane_x, lane_y + LANE_FLUSH_OFFSET + m_ani_branch_text_before[i].GetValue().y * m_branch_anime_dir[i] + LANE_FLUSH_OFFSET, rect_lane);



				switch (m_branch[i])
				{
				case BRANCH_KUROTO:
					rect_lane = RECT_LANE_KUROTO;
					break;
				case BRANCH_TATSUJIN:
					rect_lane = RECT_LANE_TATSUJIN;
					break;
				default:
					rect_lane = RECT_LANE_NORMAL;
					break;
				}


				Draw::SetOpacity(tex_BRANCH_LANE, m_ani_branch_lane_after[i].GetValue().opacity);
				Draw::SetOpacity(tex_BRANCH_TEXT, m_ani_branch_text_after[i].GetValue().opacity);
				Draw::Draw(tex_BRANCH_LANE, lane_x, lane_y + LANE_FLUSH_OFFSET, rect_lane);
				Draw::Draw(tex_BRANCH_TEXT, lane_x, lane_y + LANE_FLUSH_OFFSET + m_ani_branch_text_after[i].GetValue().y * m_branch_anime_dir[i], rect_lane);
			}

			//ゴーゴーレーンを描画
			if (enso->GetGOGO())
			{
				float y_scale = m_ani_lane_gogo[i].GetValue().scale_y;
				float y_move = (130.0f * y_scale) / 2.0f;
				Draw::SetOpacity(tex_LANE_GOGO, m_ani_lane_gogo[i].GetValue().opacity);
				Draw::SetScaleY(tex_LANE_GOGO, y_scale);
				Draw::Draw(tex_LANE_GOGO, 0.0f, lane_y + LANE_FLUSH_OFFSET + 65.0f - y_move);
			}

			//レーンフラッシュを描画]

			Draw::SetOpacity(tex_LANE_FLUSH, m_ani_lane_flush[i].GetValue().opacity);
			if (m_lane_color[i] == Red)
			{
				Draw::Draw(tex_LANE_FLUSH, 0.0f, lane_y + LANE_FLUSH_OFFSET, RECT_LANE_FLUSH[Red]);
			}
			else
			{
				Draw::Draw(tex_LANE_FLUSH, 0.0f, lane_y + LANE_FLUSH_OFFSET, RECT_LANE_FLUSH[Blue]);
			}

			Draw::SetOpacity(tex_LANE_FLUSH, m_ani_lane_flush_yellow[i].GetValue().opacity);
			Draw::Draw(tex_LANE_FLUSH, 0.0f, lane_y + LANE_FLUSH_OFFSET, RECT_LANE_FLUSH[Yellow]);

			//判定枠を描画。
			Draw::SetBlend(tex_NOTES, E_BLEND_MODE::ADDITIONALPHA);
			Draw::Draw(tex_NOTES, judge_pos_x, judge_pos_y, RECT_NOTES_JUDGE_LINE);

			//炎を描画。
			if (enso->GetGOGO())
			{
				RECT_N rect_fire =  m_lyt_fire.GetData().rectangle;
				rect_fire.m_x = rect_fire.m_width * m_ct_fire_rect.NowValue;

				float scale = m_ani_fire_scale[i].GetValue().scale_x;
				g_tex_gogo_fire.m_scale_x = scale;
				g_tex_gogo_fire.m_scale_y = scale;
				g_tex_gogo_fire.m_opacity = m_ani_fire_scale[i].GetValue().opacity;
				g_tex_gogo_fire.m_blend = E_BLEND_MODE::ADDITIONALPHA;
				g_tex_gogo_fire.m_rotation_z = -15.0f;

				g_tex_gogo_fire.Draw(judge_pos_x + m_lyt_fire.GetData().pos.x, judge_pos_y + +m_lyt_fire.GetData().pos.y, rect_fire,m_lyt_fire.GetData().reference_x, m_lyt_fire.GetData().reference_y);

			}
			//ヒットエフェクトを描画。
			Draw::SetOpacity(tex_HIT_EFFECT, m_ani_hit_opacity[i].GetValue().opacity);
			RECT_F rect_hit = { 0.0f,RECT_HIT_EFFECT.m_width * m_hit_effect_type[i],RECT_HIT_EFFECT.m_width,RECT_HIT_EFFECT.m_height };
			Draw::Draw(tex_HIT_EFFECT, MusicGame::NOTES_JUDGE_LINE[i].x, lane_y + LANE_FLUSH_OFFSET, rect_hit);
		}
	}
}

void CObjLane::HitEffectStart(E_JUDGE judge,bool big, int player)
{
	m_ani_hit_opacity[player].Start();

	switch (judge)
	{
	case JUST:
		m_hit_effect_type[player] = big == true ? 0 : 2;
		break;
	case HIT:
		m_hit_effect_type[player] = big == true ? 1 : 3;
		break;
	}
	
}

void CObjLane::LaneFlushStart(E_LANE_FLUSH_COLOR color, int player)
{
	switch (color)
	{
	case Red:
		m_ani_lane_flush[player].Start();
		m_lane_color[player] = Red;
		break;
	case Blue:
		m_ani_lane_flush[player].Start();
		m_lane_color[player] = Blue;
		break;
	case Yellow:
		m_ani_lane_flush_yellow[player].Start();
		break;
	}
}

void CObjLane::GogoStart(int player)
{
	m_ani_lane_gogo[player].Start();
	m_ani_fire_scale[player].Start();
}

void CObjLane::BranchChange(E_BRANCH branch, int player)
{
	//同じ場合何もしない
	if (m_branch[player] == branch)return;

	//上がるか下がるかによって方向を指定する
	if (m_branch[player] < branch)
		m_branch_anime_dir[player] = 1;
	else
		m_branch_anime_dir[player] = -1;

	m_branch[player] = branch;
	m_ani_branch_text_before[player].Start();
	m_ani_branch_text_after[player].Start();
	m_ani_branch_lane_after[player].Start();
}