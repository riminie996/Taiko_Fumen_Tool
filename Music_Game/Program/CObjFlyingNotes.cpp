#include "CObjFlyingNotes.h"
#include "GameL\UserData.h"

//初期化
void CObjFlyingNotes::Init()
{
	//デフォルトアニメ構造体を定義
	if (MusicGame::g_mode == E_GAME_MODE::ENSO)
	{
		if (((UserData*)Save::GetData())->m_player_amount <= 2)
		{
			for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
			{
				m_st_flying[i].ani_flying.LoadData("Animation/Enso/Notes/FlyingNotes_" + to_string(i + 1) + "P");
				m_st_flying[i].ani_notes_effect.LoadData("Animation/Enso/NotesEffect");
				m_st_flying[i].ani_flying_effect.LoadData("Animation/Enso/FlyingNotesEffectP" + to_string(i + 1));
			}
		}
	}
	else if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
	{
		m_st_flying[0].ani_flying.LoadData("Animation/Battle/FlyingNotes");
		m_st_flying[0].ani_notes_effect.LoadData("Animation/Battle/NotesEffect");
		m_st_flying[0].ani_flying_effect.LoadData("Animation/Battle/FlyingNotesEffectP1");
	}
}
//進行
void CObjFlyingNotes::Action()
{
	if (((UserData*)Save::GetData())->m_player_amount <= 2)
	{
		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		{
			for (auto itr = m_list_flying[i].begin(); itr != m_list_flying[i].end(); )
			{
				itr->ani_flying.Add(1);
				itr->ani_flying_effect.Action();
				itr->ani_notes_effect.Action();

				//エフェクトアニメ開始
				if (itr->ani_flying.GetMaxReached())
				{
					if (!itr->ani_flying_effect.GetStart())
					{
						itr->ani_flying_effect.Start();
						itr->ani_notes_effect.Start();
					}
				}

				//大音符エフェクトの追加
				if (itr->type == NOTES_BIG_DON || itr->type == NOTES_BIG_KA)
				{
					itr->ct_firework_interval.Add(1);

					if (itr->ct_firework_interval.GetMaxReached() && !itr->ani_flying.GetMaxReached())
					{
						ST_BIG_EFFECT effect;
						effect.ct_pattern = { CCounter(0.0f,0.0f,FIREWORK_PATTERN,STOP) };
						effect.pos.x = itr->ani_flying.GetValue(0).x;
						effect.pos.y = itr->ani_flying.GetValue(0).y;
						m_list_effect[i].push_back(effect);

						itr->ct_firework_interval.Reset();
					}
				}


				if (itr->ani_flying_effect.GetEnd() && itr->ani_notes_effect.GetEnd())
				{
					itr = m_list_flying[i].erase(itr);
				}
				else
				{
					itr++;
				}
			}
			for (auto itr = m_list_effect[i].begin(); itr != m_list_effect[i].end(); )
			{
				itr->ct_pattern.Add(1);
				if (itr->ct_pattern.GetMaxReached())
				{
					itr = m_list_effect[i].erase(itr);
				}
				else
				{
					itr++;
				}
			}
		}
	}
}
//描画
void CObjFlyingNotes::Draw()
{
	Draw::SetBlend(tex_NOTES_FIREWORK, E_BLEND_MODE::ADDITION);
	CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);

	if (((UserData*)Save::GetData())->m_player_amount <= 2)
	{
		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		{
			float judge_x = lane->GetJudgePosX(i);
			float judge_y = lane->GetJudgePosY(i);

			for (auto itr = m_list_effect[i].begin(); itr != m_list_effect[i].end(); itr++)
			{

				RECT_F rect_effect = { itr->ct_pattern.NowValue * RECT_FIREWORK.m_width,0.0f, RECT_FIREWORK.m_width, RECT_FIREWORK.m_height };
				float x = judge_x + itr->pos.x - (RECT_FIREWORK.m_width - 128.0f) * 0.5f;
				float y = judge_y + itr->pos.y - (RECT_FIREWORK.m_height - 128.0f) * 0.5f;

				Draw::Draw(tex_NOTES_FIREWORK, x, y, rect_effect);
			}
			//エフェクトを後面に描画
			for (auto itr = m_list_flying[i].begin(); itr != m_list_flying[i].end(); itr++)
			{
				if (itr->ani_flying_effect.GetStart())
				{
					RECT_F rect_effect = RECT_EFFECT;
					rect_effect.m_x = (int)itr->ani_flying_effect.GetValue().pattern * RECT_EFFECT.m_width;
					COLOR col = { itr->ani_flying_effect.GetValue().r, itr->ani_flying_effect.GetValue().g, itr->ani_flying_effect.GetValue().b };
					Draw::SetColor(tex_GAUGE_EXPLOSION, col);
					Draw::SetOpacity(tex_GAUGE_EXPLOSION, itr->ani_flying_effect.GetValue().opacity);
					Draw::SetRotationZ(tex_GAUGE_EXPLOSION, itr->ani_flying_effect.GetValue().rotate_z);
					Draw::SetScaleX(tex_GAUGE_EXPLOSION, itr->ani_flying_effect.GetValue().scale_x);
					Draw::SetScaleY(tex_GAUGE_EXPLOSION, itr->ani_flying_effect.GetValue().scale_x);

					Draw::CenterDraw(tex_GAUGE_EXPLOSION, EFFECT_POS[i].x, EFFECT_POS[i].y, rect_effect);
				}
			}
			for (auto itr = m_list_flying[i].begin(); itr != m_list_flying[i].end(); itr++)
			{

				RECT_F rect_notes = { itr->type * 128.0f,0.0f,128.0f,128.0f };

				float y =  judge_y + itr->ani_flying.GetValue(0).y;
				if (itr->ani_notes_effect.GetNowFrame() <= 0.175f)
					Draw::Draw(tex_NOTES, judge_x + itr->ani_flying.GetValue(0).x, y, rect_notes);

				Draw::SetOpacity(tex_NOTES_EFFECT, itr->ani_notes_effect.GetValue().opacity);
				COLOR col = { 1.0f,1.0f,itr->ani_notes_effect.GetValue().b };
				Draw::SetColor(tex_NOTES_EFFECT, col);

				Draw::Draw(tex_NOTES_EFFECT, judge_x + itr->ani_flying.GetValue(0).x, y, rect_notes);
			}
		}
	}
}

void CObjFlyingNotes::Add(E_NOTES_TYPE notes,bool rainbow,int player)
{

	ST_FLYING_NOTES flying = m_st_flying[player];	
//	flying.ani_flying_effect.LoadData("Animation/Enso/FlyingNotesEffectP" + to_string(player + 1));
	flying.ani_flying.Start();
	flying.rainbow = rainbow;
	flying.type = notes;
	flying.ct_firework_interval = { CCounter(0.0f,0.0f,FIREWORK_INTERVAL_FRAME,STOP) };
	m_list_flying[player].push_back(flying);

	while (m_list_flying[player].size() >= FLYING_MAX_COUNT)
	{
		m_list_flying[player].erase(m_list_flying[player].begin());
	}
}
