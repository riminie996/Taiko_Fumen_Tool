#include "CObjCharacter.h"
#include "GameHead.h"
//初期化
void CObjCharacter::Init()
{
	m_chara_motion.resize(USER_DATA->m_player_amount);

	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		m_chara_motion[i].ct_normal = { CCounter(0,0,MusicGame::g_tex_normal.size(),LOOP) };
		m_chara_motion[i].ct_clear = { CCounter(0,0,MusicGame::g_tex_clear.size(),LOOP) };
		m_chara_motion[i].ct_gogo = { CCounter(0,0,MusicGame::g_tex_gogo.size(),LOOP) };
		m_chara_motion[i].ct_10combo = { CCounter(0,0,MusicGame::g_tex_10combo.size(),STOP) };
		m_chara_motion[i].ct_10combo_max = { CCounter(0,0,MusicGame::g_tex_10combo_max.size(),STOP) };
		m_chara_motion[i].ct_clear_in = { CCounter(0,0,MusicGame::g_tex_clear_in.size(),STOP) };
		m_chara_motion[i].ct_gogostart = { CCounter(0,0,MusicGame::g_tex_gogostart.size(),STOP) };
		m_chara_motion[i].ct_soulin = { CCounter(0,0,MusicGame::g_tex_soulin.size(),STOP) };
		m_chara_motion[i].ct_balloon_broke = { CCounter(0,0,MusicGame::g_tex_balloon_broke.size(),STOP) };
		m_chara_motion[i].ct_balloon_break = { CCounter(0,0,MusicGame::g_tex_balloon_break.size() - 1,STOP) };
		m_chara_motion[i].ct_balloon_miss = { CCounter(0,0,MusicGame::g_tex_balloon_miss.size(),STOP) };

		m_chara_motion[i].ct_10combo.NowValue = m_chara_motion[i].ct_10combo.MaxValue;
		m_chara_motion[i].ct_10combo_max.NowValue = m_chara_motion[i].ct_10combo_max.MaxValue;
		m_chara_motion[i].ct_clear_in.NowValue = m_chara_motion[i].ct_clear_in.MaxValue;
		m_chara_motion[i].ct_gogostart.NowValue = m_chara_motion[i].ct_gogostart.MaxValue;
		m_chara_motion[i].ct_soulin.NowValue = m_chara_motion[i].ct_soulin.MaxValue;

		m_chara_motion[i].action_now = false;
		m_chara_motion[i].balloon_now = false;
		m_chara_motion[i].motion_bpm = 0.0f;

		if (MusicGame::g_mode == E_GAME_MODE::ENSO)
		{
			m_lyt_normal[i].LoadData("Layout/Enso/Character/Chara_Normal_" + to_string(i + 1) + "P");
			m_lyt_balloon[i].LoadData("Layout/Enso/Character/Chara_Balloon_" + to_string(i + 1) + "P");
		}
		else if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
		{
			m_lyt_normal[i].LoadData("Layout/Battle/Character/Chara_Normal_" + to_string(i + 1) + "P");
			m_lyt_balloon[i].LoadData("Layout/Battle/Character/Chara_Balloon_" + to_string(i + 1) + "P");
		}
	}
		m_ani_effect.Start();
}									 
//進行
void CObjCharacter::Action()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		float unit = m_chara_motion[i].motion_bpm / 4.0f;

		m_chara_motion[i].ct_normal.Add(enso->m_enso[0].m_now_bpm / m_chara_motion[i].ct_normal.MaxValue);
		m_chara_motion[i].ct_clear.Add(enso->m_enso[0].m_now_bpm / m_chara_motion[i].ct_clear.MaxValue / 2.0f);
		//	if(m_chara_motion[i].ct_gogostart.GetMaxReached())
		m_chara_motion[i].ct_gogo.Add(enso->m_enso[0].m_now_bpm / m_chara_motion[i].ct_gogo.MaxValue);
		m_chara_motion[i].ct_10combo.Add(unit / m_chara_motion[i].ct_10combo.MaxValue);
		m_chara_motion[i].ct_10combo_max.Add(unit / m_chara_motion[i].ct_10combo_max.MaxValue * 2);
		m_chara_motion[i].ct_clear_in.Add(unit / m_chara_motion[i].ct_clear_in.MaxValue * 2);
		m_chara_motion[i].ct_gogostart.Add(unit / m_chara_motion[i].ct_gogostart.MaxValue * 2);
		m_chara_motion[i].ct_soulin.Add(unit / m_chara_motion[i].ct_soulin.MaxValue * 2);
		//風船
		m_chara_motion[i].ct_balloon_broke.Add(BALLOON_TIMER);
		m_chara_motion[i].ct_balloon_break.Add(BALLOON_TIMER);
		m_chara_motion[i].ct_balloon_miss.Add(BALLOON_TIMER);

		if (m_chara_motion[i].ct_10combo.GetMaxReached() &&
			m_chara_motion[i].ct_10combo_max.GetMaxReached() &&
			m_chara_motion[i].ct_clear_in.GetMaxReached() &&
			m_chara_motion[i].ct_gogostart.GetMaxReached() &&
			m_chara_motion[i].ct_soulin.GetMaxReached())
			m_chara_motion[i].action_now = false;
	}
	m_ani_effect.ActionLoop();
}
//描画
void CObjCharacter::Draw()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		int x = m_lyt_normal[i].GetPos().x;
		int y = m_lyt_normal[i].GetPos().y;
		float balloon_x = m_lyt_balloon[i].GetPos().x;
		float balloon_y = m_lyt_balloon[i].GetPos().y;
		if (m_chara_motion[i].balloon_now)
		{
			int val = (int)m_chara_motion[i].ct_balloon_break.NowValue;
			MusicGame::g_tex_balloon_break[val].Draw(balloon_x, balloon_y);
		}
		else if (!m_chara_motion[i].ct_balloon_miss.GetMaxReached())
		{
			int val = m_chara_motion[i].ct_balloon_miss.NowValue;
			MusicGame::g_tex_balloon_miss[val].Draw(balloon_x, balloon_y);
		}
		else if (!m_chara_motion[i].ct_balloon_broke.GetMaxReached())
		{
			int val = m_chara_motion[i].ct_balloon_broke.NowValue;
			MusicGame::g_tex_balloon_broke[val].Draw(balloon_x, balloon_y);
		}
		else if (m_chara_motion[i].action_now)
		{
			

			if (!m_chara_motion[i].ct_soulin.GetMaxReached())
			{
				int val = m_chara_motion[i].ct_soulin.NowValue;
				MusicGame::g_tex_soulin[val].Draw(x, y);
			}
			else if (!m_chara_motion[i].ct_clear_in.GetMaxReached())
			{
				int val = m_chara_motion[i].ct_clear_in.NowValue;
				MusicGame::g_tex_clear_in[val].Draw(x, y);
			}
			else if (!m_chara_motion[i].ct_gogostart.GetMaxReached())
			{
				int val = m_chara_motion[i].ct_gogostart.NowValue;
				MusicGame::g_tex_gogostart[val].Draw(x, y);
			}
			else if (!m_chara_motion[i].ct_10combo_max.GetMaxReached())
			{
				int val = m_chara_motion[i].ct_10combo_max.NowValue;
				MusicGame::g_tex_10combo_max[val].Draw(x, y);

			}
			else if (!m_chara_motion[i].ct_10combo.GetMaxReached())
			{

				int val = m_chara_motion[i].ct_10combo.NowValue;
				MusicGame::g_tex_10combo[val].Draw(x, y);
			}

		}
		else
		{
			if (enso->m_enso[0].m_gogo)
			{
				int val = m_chara_motion[i].ct_gogo.NowValue;
				MusicGame::g_tex_gogo[val].Draw(x, y);
			}
			else if (enso->m_enso[i].m_score_data.ct_gauge.NowValue >= 80)
			{
				int val = m_chara_motion[i].ct_clear.NowValue;
				MusicGame::g_tex_clear[val].Draw(x, y);
			}
			else
			{
				int val = m_chara_motion[i].ct_normal.NowValue;
				//Draw::Draw(tex_DONCHAN_NORMAL_119 + val, 0, 0);
				MusicGame::g_tex_normal[val].Draw(x, y);
			}

		}


		if (enso->m_enso[i].m_score_data.ct_gauge.NowValue >= 100)
		{
			Draw::SetBlend(tex_CHARACTER_EFFECT, E_BLEND_MODE::ADDITIONALPHA);
			Draw::SetOpacity(tex_CHARACTER_EFFECT, m_ani_effect.GetValue().opacity);
			Draw::Draw(tex_CHARACTER_EFFECT, GOLDEFFECT_POS.x, GOLDEFFECT_POS.y + y, RECT_GOLDEFFECT);
		}
}
	}

void CObjCharacter::Act10Combo(int player)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);

	//キャンセル
	if (enso->m_enso[0].m_gogo == true)return;

	if (enso->m_enso[player].m_score_data.ct_gauge.NowValue >= 100)
	{
		m_chara_motion[player].ct_10combo_max.Reset();
	}
	else
	{
		m_chara_motion[player].ct_10combo.Reset();
	}

	MotionBpmSet(player);
}
void CObjCharacter::Act10ComboMax(int player)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);


	m_chara_motion[player].ct_10combo_max.Reset();

	MotionBpmSet(player);
}
void CObjCharacter::ActGogoStart(int player)
{
	m_chara_motion[player].ct_gogostart.Reset();
	m_chara_motion[player].ct_gogo.Reset();
	MotionBpmSet(player);
}
void CObjCharacter::ActClearIn(int player)
{
	m_chara_motion[player].ct_clear_in.Reset();
	MotionBpmSet(player);
}
void CObjCharacter::ActSoulIn(int player)
{
	m_chara_motion[player].ct_soulin.Reset();
	MotionBpmSet(player);
}
void CObjCharacter::ActEnd(int player)
{
	m_chara_motion[player].ct_10combo_max.Reset();
	MotionBpmSet(player);
}
void CObjCharacter::ActBalloonStart(int player)
{
}
void CObjCharacter::ActBalloonBroke(int player)
{
	m_chara_motion[player].balloon_now = true;
	if (m_chara_motion[player].ct_balloon_break.GetMaxReached())
		m_chara_motion[player].ct_balloon_break.Reset();
}
void CObjCharacter::ActBalloonMiss(int player)
{
	m_chara_motion[player].balloon_now = false;
	m_chara_motion[player].ct_balloon_miss.Reset();
}
void CObjCharacter::ActBalloonBreak(int player)
{
	m_chara_motion[player].balloon_now = false;

	m_chara_motion[player].ct_balloon_broke.Reset();
}

void CObjCharacter::MotionBpmSet(int player)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	m_chara_motion[player].motion_bpm = enso->m_enso[0].m_now_bpm;
	m_chara_motion[player].action_now = true;
}