#include "CObjMTaiko.h"
#include "GameHead.h"
#include "GameL/WinInputs.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
//èâä˙âª
void CObjMTaiko::Init()
{
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	for (int i = 0; i < MusicGame::MAX_PLAYER_AMOUNT; i++)
	{
		for (int j = 0; j < TAIKO_FLUSH_Count; j++)
		{
			m_ani_flush[i][j].LoadData("Animation/Enso/TaikoFlush");
			m_ani_flush[i][j].Start();
			m_key_flag[i] = false;
		}
		m_ct_auto_roll[i] = { CCounter(0.0f,0.0f,(float)((float)FRAME_FPS / (float)USER_DATA->m_auto_play_roll),FREE) };
		m_ct_auto_balloon[i] = { CCounter(0.0f,0.0f,(float)FRAME_FPS / (float)AUTOPLAY_BALLOON_INTERVAL,FREE) };
		m_auto_left[i] = false;
	}
	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		if (MusicGame::g_mode == E_GAME_MODE::ENSO)
		{
			m_lyt_taiko[i].LoadData("Layout/Enso/Taiko_" + to_string(i + 1) + "P");
			m_lyt_bg[i].LoadData("Layout/Enso/Lane_Left_" + to_string(i + 1) + "P");
		}
		else if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
		{
			m_lyt_taiko[i].LoadData("Layout/Battle/Taiko_" + to_string(i + 1) + "P");
			m_lyt_bg[i].LoadData("Layout/Battle/Lane_Left_" + to_string(i + 1) + "P");
		}
	}
}
//êiçs
void CObjMTaiko::Action()
{
	CObjNotes* notes = (CObjNotes*)Objs::GetObj(OBJ_NOTES);
	CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		for (int j = 0; j < TAIKO_FLUSH_Count; j++)
			m_ani_flush[i][j].Action();

		if (system->GetInput(LEFT_DON, i))
			Input(LEFT_DON,i);

		if (system->GetInput(RIGHT_DON, i))
			Input(RIGHT_DON,i);

		if (system->GetInput(LEFT_KA, i))
			Input(LEFT_KA,i);

		if (system->GetInput(RIGHT_KA, i))
			Input(RIGHT_KA,i);
	}
}
//ï`âÊ
void CObjMTaiko::Draw()
{
	//îwåiÇï`âÊÅB
	if (((UserData*)Save::GetData())->m_player_amount <= 2)
	{
		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		{
			if (USER_DATA->m_now_select_diffculty[0] != DIFF_DAN)
			{
				MusicGame::g_tex_lane_left.Draw(m_lyt_bg[i].GetData().pos.x, m_lyt_bg[i].GetData().pos.y, m_lyt_bg[i].GetData().rectangle);
			}
			else
			{
				MusicGame::g_tex_lane_left.Draw(m_lyt_bg[i].GetData().pos.x, m_lyt_bg[i].GetData().pos.y, RECT_LANE_LEFT_DAN);

			}

			MusicGame::g_tex_taiko.m_opacity = 1.0f;
			MusicGame::g_tex_taiko.Draw(m_lyt_taiko[i].GetData().pos.x, m_lyt_taiko[i].GetData().pos.y, m_lyt_taiko[i].GetData().rectangle);

			for (int j = 0; j < E_TAIKO_FLUSH::TAIKO_FLUSH_Count; j++)
			{
				RECT_N rect_effect = m_lyt_taiko[i].GetData().rectangle;
				rect_effect.m_y = (j + 1) * rect_effect.m_height;
				MusicGame::g_tex_taiko.m_opacity = m_ani_flush[i][j].GetValue().opacity;
				MusicGame::g_tex_taiko.Draw(m_lyt_taiko[i].GetData().pos.x, m_lyt_taiko[i].GetData().pos.y, rect_effect);
			}

			RECT_F rect_diffculty = RECT_DIFFCULTY;
			rect_diffculty.m_x = ((UserData*)Save::GetData())->m_now_select_diffculty[i] * RECT_DIFFCULTY.m_width;
			Draw::Draw(tex_DIFFCULTY, DIFFCULTY_POS.x, DIFFCULTY_POS.y + i * MusicGame::P2_HEIGHT, rect_diffculty);
		}
	}
}

void CObjMTaiko::Input(E_TAIKO_FLUSH input, int player)
{
	bool sound_play = true;

	if (((UserData*)Save::GetData())->m_auto_play[player] == true &&
		AUTO_AI == true)
		sound_play = false;


	CObjNotes* notes = (CObjNotes*)Objs::GetObj(OBJ_NOTES);
	CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);

	m_ani_flush[player][input].Start();
	switch (input)
	{
	case LEFT_DON:
	case RIGHT_DON:
		if (sound_play == true)
		{

			if (((UserData*)Save::GetData())->m_player_amount > 1)
			{
				if(player == 0)Audio::Start(se_DON_1P);
				if(player == 1)Audio::Start(se_DON_2P);
			}
			else
			{

				Audio::Start(se_DON);
			}
		}
		notes->InputJudge(DON, player);
		lane->LaneFlushStart(Red, player);
		break;
	case LEFT_KA:
	case RIGHT_KA:
		if (sound_play == true)
		{

			if (((UserData*)Save::GetData())->m_player_amount > 1)
			{
				if (player == 0)Audio::Start(se_KA_1P);
				if (player == 1)Audio::Start(se_KA_2P);
			}
			else
			{

				Audio::Start(se_KA);
			}
		}
		notes->InputJudge(KA, player);
		lane->LaneFlushStart(Blue, player);
		break;
	}
}

void CObjMTaiko::AutoPlayInput(E_NOTES_TYPE notes, int player)
{
	switch (notes)
	{
	case NOTES_DON:
		m_auto_left[player] = m_auto_left[player] == true ? false : true;//ì¸óÕÇì¸ÇÍë÷Ç¶ÇÈ
		Input(m_auto_left[player] == true ? LEFT_DON : RIGHT_DON,player);
		break;
	case NOTES_KA:
		m_auto_left[player] = m_auto_left[player] == true ? false : true;//ì¸óÕÇì¸ÇÍë÷Ç¶ÇÈ
		Input(m_auto_left[player] == true ? LEFT_KA : RIGHT_KA, player);
		break;
	case NOTES_BIG_DON:
		Input(m_auto_left[player] == true ? LEFT_DON : RIGHT_DON, player);
		m_ani_flush[player][m_auto_left[player] == false ? LEFT_DON : RIGHT_DON].Start();
		break;
	case NOTES_BIG_KA:
		Input(m_auto_left[player] == true ? LEFT_KA : RIGHT_KA, player);
		m_ani_flush[player][m_auto_left[player] == false ? LEFT_KA : RIGHT_KA].Start();
		break;
	case NOTES_ROLL:
	case NOTES_BIG_ROLL:

		m_ct_auto_roll[player].Add(1);

		if (m_ct_auto_roll[player].GetMaxReached())
		{
			m_ct_auto_roll[player].Sub(m_ct_auto_roll[player].MaxValue);
			m_auto_left[player] = m_auto_left[player] == true ? false : true;//ì¸óÕÇì¸ÇÍë÷Ç¶ÇÈ
			Input(m_auto_left[player] == true ? LEFT_DON : RIGHT_DON,player);
		}
		
		break;
	case NOTES_BALLOON:
	case NOTES_KUSUDAMA:
		m_ct_auto_balloon[player].Add(1);
		if (m_ct_auto_balloon[player].GetMaxReached())
		{
			m_ct_auto_balloon[player].Sub(m_ct_auto_balloon[player].MaxValue);
			m_auto_left[player] = m_auto_left[player] == true ? false : true;//ì¸óÕÇì¸ÇÍë÷Ç¶ÇÈ
			Input(m_auto_left[player] == true ? LEFT_DON : RIGHT_DON,player);
		}
		break;
	}
}