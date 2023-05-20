#include "CObjEnso.h"
#include "GameHead.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"
#include <random>



CObjEnso::CObjEnso(string file_name, ST_ENSO_OPTION option)
{

	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_enso[i].LoadFumenData(file_name,i);
		m_enso[i].m_option = option;
	}

	//�X�L���l�[�������肷��
	string skin_str = "Common";

	if (m_enso[0].m_fumen.title.find("�����~�N") != -1 ||
		m_enso[0].m_fumen.sub_title.find("�����~�N") != -1)
	{
		skin_str = "Miku";
	}


		//	if (((UserData*)Save::GetData())->m_better_performance[MusicGame::E_BETTER_PERFORMANCE::bp_BG] == true)
	{
		CObjBg* bg = new CObjBg(skin_str);
		Objs::InsertObj(bg, OBJ_BG, PRIO_ENSO_BG);
	}
	if (USER_DATA->m_player_amount == 1 && USER_DATA->m_now_select_diffculty[0] != DIFF_DAN)
	{

		CObjDancer* dancer = new CObjDancer(skin_str);
		Objs::InsertObj(dancer, OBJ_DANCER, PRIO_ENSO_DANCER);

		CObjFooter* footer = new CObjFooter(skin_str);
		Objs::InsertObj(footer, OBJ_FOOTER, PRIO_ENSO_FOOTER);

	}
}

//������
void CObjEnso::Init()
{
	m_judge_num.SetTex(tex_JUDGE_PANEL_NUMBER, RECT_JUDGE_NUMBER.m_width, RECT_JUDGE_NUMBER.m_height);

	m_beat = 0.0f;
	m_key_flag = false;
	//�����t�@�C���̓ǂݍ��݂ɗ\�z�ȏ�Ɏ��Ԃ��������Ă��܂����Ƃ��l�����āA
	//�����t�@�C�����ǂݍ��ݏI����Ă���^�C�}�[���X�^�[�g������
	Audio::LoadAudio2(bgm_MUSIC, m_enso[0].m_fumen.wave_file.c_str(), SOUND_TYPE::EFFECT);

	//	vector<ST_NOTES_SECTION>section_measure_count;

	SetSENotes();
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		int notes_amount = 0;
		int notes_count = 0;

		bool abekobe = m_enso[i].m_option.abekobe;
		int random = m_enso[i].m_option.random;

		std::random_device rnd;

		//���ׂ��ׁE�����_���I�v�V��������
		for (auto itr = m_enso[i].m_fumen.list_notes.begin(); itr != m_enso[i].m_fumen.list_notes.end(); itr++)
		{
			int percent = rnd() % 100;

			switch (itr->notes_type)
			{
			case NOTES_DON://�ʏ�̃m�[�c
			case NOTES_KA:
				if ((m_enso[i].m_option.random == ST_ENSO_OPTION::RANDOM_KIMAGURE && percent < 25) ||
					(m_enso[i].m_option.random == ST_ENSO_OPTION::RANDOM_DETARAME && percent < 50))
				{
					//��������ւ�
					if (itr->notes_type == NOTES_DON)
					{
						itr->notes_type = NOTES_KA;
						itr->moji = itr->moji == MOJI_�h�� ? MOJI_�J�b : MOJI_�J;
					}
					else
					{
						itr->notes_type = NOTES_DON;
						itr->moji = itr->moji == MOJI_�J�b ? MOJI_�h�� : MOJI_�h;
					}
				}
				if (m_enso[i].m_option.abekobe == true)
				{
					//��������ւ�
					if (itr->notes_type == NOTES_DON)
					{
						itr->notes_type = NOTES_KA;
						itr->moji = itr->moji == MOJI_�h�� ? MOJI_�J�b : MOJI_�J;
					}
					else
					{
						itr->notes_type = NOTES_DON;
						itr->moji = itr->moji == MOJI_�J�b ? MOJI_�h�� : MOJI_�h;
					}
				}
				break;
			case NOTES_BIG_DON:
			case NOTES_BIG_KA:
				if ((m_enso[i].m_option.random == ST_ENSO_OPTION::RANDOM_KIMAGURE && percent < 25) ||
					(m_enso[i].m_option.random == ST_ENSO_OPTION::RANDOM_DETARAME && percent < 50))

				{
					itr->notes_type = itr->notes_type == NOTES_BIG_DON ? NOTES_BIG_KA : NOTES_BIG_DON;
					itr->moji = itr->notes_type == NOTES_BIG_DON ? MOJI_�h���� : MOJI_�J�b��;
				}
				if (m_enso[i].m_option.abekobe == true)
				{
					itr->notes_type = itr->notes_type == NOTES_BIG_DON ? NOTES_BIG_KA : NOTES_BIG_DON;
					itr->moji = itr->notes_type == NOTES_BIG_DON ? MOJI_�h���� : MOJI_�J�b��;
				}
				break;
			case NOTES_ROLL:
			case NOTES_BIG_ROLL:
			case NOTES_BALLOON:
			case NOTES_ROLLEND:
			case NOTES_KUSUDAMA:
				break;
			}
		}

		//�X�R�A�����N�m���}��ݒ�
		for (int j = 0; j < (int)E_SCORE_RANK::RANK_Count; j++)
		{
			//�ɃX�R�A��ݒ�
			int max_score = m_enso[i].m_score_add * (m_enso[i].m_fumen.notes_count[BRANCH_NONE] + m_enso[i].m_fumen.notes_count[BRANCH_TATSUJIN]) +
				(m_enso[i].m_roll_time * 16.0f) * 100 +
				m_enso[i].m_balloon_count * 100;

			m_enso[i].m_score_data.score_rank_norma[j] = max_score * MusicGame::SCORE_RANK_NORMA_PERCENTAGE[j];
		}
		m_enso[i].m_now_bpm = m_enso[i].m_fumen.bpm;
		m_roll_remain = m_enso[i].m_fumen.roll_remain;
		m_branch[i] = BRANCH_NONE;
		m_enso[i].m_measure_count = 0;
		m_branch_hold[i] = false;
		BranchInfoReset(i);
	}
	//--------------------------------------
	MusicGame::ScoreDataImport(m_enso[0].m_best_score_data, m_enso[0].m_fumen.fumen_path + SCOREFILE_STR);

	CObjNotes* notes = new CObjNotes(/*section_measure_count*/);
	Objs::InsertObj(notes, OBJ_NOTES, PRIO_ENSO_NOTES);

	m_play_start = false;
	m_play_end = false;
	m_to_result = true;

	m_fade_out.m_color = Color::Black;



	CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);

	//�W���������w�肳��Ă��Ȃ��ꍇ
	if (m_enso[0].m_fumen.genre == GENRE_NONE && select != nullptr)
	{
		m_enso[0].m_fumen.genre = select->GetNowSelectSong().genre;
	}

	m_first_action = true;
	//�J�n = 0, �ŏ� = 0, �ő� = ���v���t���ԁB
	//�J�n�̃I�t�Z�b�g�͂��łɊ܂܂�Ă��邽�ߐV���ɉ��Z���Ȃ��B
	m_enso[0].m_ct_now_time.Start(0, m_enso[0].m_fumen.end_time * 1000 + MusicGame::TIME_END_DELAY, 1);
}
//�i�s
void CObjEnso::Action()
{
	if (m_first_action == true)
	{
		m_first_action = false;

		CObjTitlePanel* title = (CObjTitlePanel*)Objs::GetObj(OBJ_TITLEPANEL);
		title->SetTitleString(m_enso[0].m_fumen.title, m_enso[0].m_fumen.genre);
	}

	CObjNotes* notes = (CObjNotes*)Objs::GetObj(OBJ_NOTES);

	//�b�����t���[����
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	m_enso[0].m_ct_now_time.Action();
	
	m_beat = m_enso[0].GetNowTime() * (m_enso[0].m_fumen.bpm / 60.0f);
	m_ct_fade_delay.Action();

	if (m_enso[0].m_ct_now_time.NowValue >= MusicGame::TIME_START_DELAY  && m_play_start == false &&
		((UserData*)Save::GetData())->m_now_select_diffculty[0] != DIFF_DAN)
	{
		m_play_start = true;
		Audio::Start(bgm_MUSIC);
		m_enso[0].SetTime(MusicGame::TIME_START_DELAY/1000.0f);
	}

	if (Input::GetVKey('S') && !m_enso[0].m_ct_now_time.GetStoped())
	{
		EnsoStop();
		Audio::Stop(bgm_MUSIC);
	}

	if (m_play_end == false && m_enso[0].m_ct_now_time.GetEndValueReached())
	{
		m_play_end = true;
		EnsoStop();
	}

	if (m_fade_out.GetEnd() && m_to_result == true)
	{
		m_to_result = false;

		if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
		{
		}
		else if (((UserData*)Save::GetData())->m_now_select_diffculty[0] != DIFF_DAN)
		{
			system->EnsoEnd();
			system->ResultStart(m_enso[0].m_score_data);
			//system->SongSelectStart();
		}
		else
		{
			system->EnsoEnd();
			system->DanResultStart(m_enso[0].m_score_data);
		}
	}
}
//�`��
void CObjEnso::Draw()
{
	if (((UserData*)Save::GetData())->m_judge_showing == true)
	{
		Draw::Draw(tex_JUDGE_PANEL, JUDGE_PANEL_POS.x, JUDGE_PANEL_POS.y);

		for (int i = 0; i < JUDGE_COUNT; i++)
		{
			int x = JUDGE_PANEL_POS.x + JUDGE_NUMBER_OFFSET.x + (numOfDigit(m_enso[0].m_score_data.judge[i]) - 1) * JUDGE_NUMBER_PADDING * 0.5f;
			int y = JUDGE_PANEL_POS.y + JUDGE_NUMBER_OFFSET.y + i * JUDGE_NUMBER_HEIGHT;
			m_judge_num.Draw(m_enso[0].m_score_data.judge[i], x, y, JUDGE_NUMBER_PADDING);
		}
	}

	if (m_ct_fade_delay.GetEndValueReached())
		m_fade_out.ActionDraw();
	//CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
	//CObjNotes* notes = (CObjNotes*)Objs::GetObj(OBJ_NOTES);
	//CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);
	//CObjCombo* combo = (CObjCombo*)Objs::GetObj(OBJ_COMBO);
	//CObjNormaGauge* gauge = (CObjNormaGauge*)Objs::GetObj(OBJ_GAUGE);
	//CObjJudgeMoji* judge = (CObjJudgeMoji*)Objs::GetObj(OBJ_JUDGE);
	//CObjMTaiko* taiko = (CObjMTaiko*)Objs::GetObj(OBJ_TAIKO);
	//CObjScore* score = (CObjScore*)Objs::GetObj(OBJ_SCORE);
	//CObjBalloon* balloon = (CObjBalloon*)Objs::GetObj(OBJ_BALLOON);
	//CObjRoll* roll = (CObjRoll*)Objs::GetObj(OBJ_ROLL);

	//CObjFlyingNotes* flying = (CObjFlyingNotes*)Objs::GetObj(OBJ_FLYINGNOTES);

	//CObjBg* bg = (CObjBg*)Objs::GetObj(OBJ_BG);

	//CObjComboBalloon* cballoon = (CObjComboBalloon*)Objs::GetObj(OBJ_COMBOBALLOON);
	//CObjTitlePanel* title = (CObjTitlePanel*)Objs::GetObj(OBJ_TITLEPANEL);
	//CObjKusudama* kusudama = (CObjKusudama*)Objs::GetObj(OBJ_KUSUDAMA);
	//int h = 32;
	//m_judge_num.Draw(notes->m_act_time,		NUM_POS.x,			NUM_POS.y,		NUM_WIDTH);
	//m_judge_num.Draw(notes->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y,	NUM_WIDTH);
	//m_judge_num.Draw(this->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 32,		NUM_WIDTH);
	//m_judge_num.Draw(this->m_draw_time,		NUM_POS.x + 64,		NUM_POS.y + 32, NUM_WIDTH);
	//m_judge_num.Draw(lane->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 64,		NUM_WIDTH);
	//m_judge_num.Draw(lane->m_draw_time,		NUM_POS.x + 64,		NUM_POS.y + 64, NUM_WIDTH);
	//m_judge_num.Draw(combo->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 96,		NUM_WIDTH);
	//m_judge_num.Draw(combo->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 96, NUM_WIDTH);
	//m_judge_num.Draw(gauge->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 128,		NUM_WIDTH);
	//m_judge_num.Draw(gauge->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 128, NUM_WIDTH);
	//m_judge_num.Draw(judge->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 160,		NUM_WIDTH);
	//m_judge_num.Draw(judge->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 160, NUM_WIDTH);
	//m_judge_num.Draw(taiko->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 192,		NUM_WIDTH);
	//m_judge_num.Draw(taiko->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 192, NUM_WIDTH);
	//m_judge_num.Draw(score->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 224,		NUM_WIDTH);
	//m_judge_num.Draw(score->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 224, NUM_WIDTH);
	//m_judge_num.Draw(balloon->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 256,		NUM_WIDTH);
	//m_judge_num.Draw(balloon->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 256, NUM_WIDTH);
	//m_judge_num.Draw(roll->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 288,		NUM_WIDTH);
	//m_judge_num.Draw(roll->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 288, NUM_WIDTH);
	//m_judge_num.Draw(bg->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 320,		NUM_WIDTH);
	//m_judge_num.Draw(bg->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 320, NUM_WIDTH);
	//m_judge_num.Draw(cballoon->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 352,		NUM_WIDTH);
	//m_judge_num.Draw(cballoon->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 352, NUM_WIDTH);
	//m_judge_num.Draw(title->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 384,		NUM_WIDTH);
	//m_judge_num.Draw(title->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 384, NUM_WIDTH);
	//m_judge_num.Draw(kusudama->m_act_time,		NUM_POS.x + 0,		NUM_POS.y + 416,		NUM_WIDTH);
	//m_judge_num.Draw(kusudama->m_draw_time,	NUM_POS.x + 64,		NUM_POS.y + 416, NUM_WIDTH);
}


void CObjEnso::EnsoStop()
{

	m_enso[0].m_ct_now_time.Stop();

	if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
	{
		CObjEnsoBattle* battle = (CObjEnsoBattle*)Objs::GetObj(OBJ_BATTLE);
		battle->BattleEnd();

		CObjBattleEndEffect* end = new CObjBattleEndEffect((E_BATTLE_RESULT)battle->GetResult());
		Objs::InsertObj(end, OBJ_END, PRIO_ENSO_END);
	}
	else
	{
		CObjEnsoEndEffect* end = new CObjEnsoEndEffect();
		Objs::InsertObj(end, OBJ_END, PRIO_ENSO_END);
	}

	m_ct_fade_delay.Start(0, FADEOUT_DELAY, 1);
	m_fade_out.Start();
	
}
void CObjEnso::BranchInfoReset(int player)
{
	m_branch_judge[player][JUST] = 0;
	m_branch_judge[player][HIT] = 0;
	m_branch_judge[player][MISS] = 0;
	m_branch_judge[player][ROLL] = 0;
	m_branch_score[player] = 0;

}

void CObjEnso::AddMeasureCount(int player)
{
	m_enso[player].m_measure_count++;
	//���򕈖ʂ�����
	if (m_enso[player].m_fumen.list_branch.size() > 0)
	{
		E_BRANCH branch;
		//��ԑO�̏��ߐ����1���ߕ����Ȃ��Ȃ�����
		auto itr = m_enso[player].m_fumen.list_branch.begin();
		if (m_enso[player].m_measure_count >= itr->measure - 1)
		{
			float value = 0;

			switch (itr->type)
			{
			case E_BRANCH_TYPE::BRANCH_PERFECT:
				if (m_branch_judge[player][JUST] + m_branch_judge[player][HIT] + m_branch_judge[player][MISS] > 0)
				{
					value = (float)(m_branch_judge[player][JUST]) / (float)(m_branch_judge[player][JUST] + m_branch_judge[player][HIT] + m_branch_judge[player][MISS]) * 100.0f;
				}
				break;
			case E_BRANCH_TYPE::BRANCH_ROLL:
				value = m_branch_judge[player][ROLL];
				break;
			case E_BRANCH_TYPE::BRANCH_SCORE:
				value = m_branch_score[player];
				break;
			}

			if (value >= itr->norma[1])
				branch = BRANCH_TATSUJIN;
			else if (value >= itr->norma[0])
				branch = BRANCH_KUROTO;
			else
				branch = BRANCH_NORMAL;

			if (m_branch_hold[player] == false)
				m_branch[player] = branch;



			CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);
			lane->BranchChange(m_branch[player], player);
			CObjNotes* notes = (CObjNotes*)Objs::GetObj(OBJ_NOTES);

			int start = itr->measure;
			//���̏��ߐ��A�܂��͍Ō�̏��ߐ�
			itr++;


			int end = itr == m_enso[player].m_fumen.list_branch.end() ? m_enso[player].m_fumen.measure_count : itr->measure;

			//���̕���܂ł̏��ߐ��̃m�[�c�����ׂč폜����B
			notes->BranchStart(m_branch[player], start, end, player);


			m_enso[player].m_fumen.list_branch.pop_front();
		}

	}

}
void CObjEnso::SubRollRemain(float time)
{
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);

	m_roll_remain--;

	if (dan != nullptr)
		dan->SubRollTime(time);
}

void CObjEnso::SetSENotes()
{


	int doco_source[] =
	{
		MOJI_�h��,
		MOJI_�h,
		MOJI_�R,
		MOJI_�J�b,
		MOJI_�J,
	};
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{

		//�����x�N�^�[
		string doko_notes;
		float bpm = m_enso[0].m_fumen.bpm;
		float time_temp = 0.0f;
		float time_temp2 = 0.0f;

		//�����Z�b�g����
		bool red_only = false;
		int doko_count = 0;
		string str_temp;

		//�ŏ��̃m�[�c�̎��Ԃ�����
		for (auto itr = m_enso[i].m_fumen.list_notes.begin(); itr != m_enso[i].m_fumen.list_notes.end(); itr++)
		{
			switch (itr->notes_type)
			{
			case NOTES_DON://�ʏ�̃m�[�c
			case NOTES_KA:
			case NOTES_BOMB_DON:
			case NOTES_BOMB_KA:
				time_temp = itr->judge_time;
				time_temp2 = time_temp;
				break;
			}
			if (time_temp != 0.0f)break;
		}


		for (auto itr = m_enso[i].m_fumen.list_notes.begin(); itr != m_enso[i].m_fumen.list_notes.end(); itr++)
		{
			//4������
			float time4 = 60.0f / bpm;
			float time8 = time4 / 2.0f;
			float time12 = time4 / 3.0f;

			//�W���Ԋu��藣��Ă���
			if (itr->judge_time - time_temp > time8)
			{
				if (str_temp == "11111")
				{
					doko_notes += to_string(MOJI_�h);
					doko_notes += to_string(MOJI_�R);
					doko_notes += to_string(MOJI_�h);
					doko_notes += to_string(MOJI_�R);
					doko_notes += to_string(MOJI_�h��);

					//���łɒǉ����Ă��邽�ߏ������Z�b�g����
					str_temp = "";
				}
				else if (str_temp == "111")
				{
					doko_notes += to_string(MOJI_�h);
					doko_notes += to_string(MOJI_�R);
					doko_notes += to_string(MOJI_�h��);
					//���łɒǉ����Ă��邽�ߏ������Z�b�g����
					str_temp = "";
				}
				else
				{
					for (int j = 0; j < str_temp.size(); j++)
					{
						if (str_temp[j] == '1' && i == str_temp.size() - 1)
						{
							doko_notes += to_string(MOJI_�h��);
						}
						else if (str_temp[j] == '2' && i == str_temp.size() - 1)
						{
							doko_notes += to_string(MOJI_�J�b);
						}
						else if (str_temp[j] == '1')
						{
							doko_notes += to_string(MOJI_�h);
						}
						else if (str_temp[j] == '2')
						{
							doko_notes += to_string(MOJI_�J);
						}
					}
					//���łɒǉ����Ă��邽�ߏ������Z�b�g����
					str_temp = "";
				}
				doko_notes += str_temp;
				str_temp = "";
				red_only = true;
			}
			//1�O�̃m�[�c�ƍ��̃m�[�c�̎��ԍ���8����蒷���A2�O��1�O�̃m�[�c�̎��ԍ���8�����Z���Ƃ�
			else if (itr->judge_time - time_temp >= time8 && time_temp - time_temp2 < time8)
			{
				if (str_temp == "11111")
				{
					doko_notes += to_string(MOJI_�h);
					doko_notes += to_string(MOJI_�R);
					doko_notes += to_string(MOJI_�h);
					doko_notes += to_string(MOJI_�R);
					doko_notes += to_string(MOJI_�h��);

					//���łɒǉ����Ă��邽�ߏ������Z�b�g����
					str_temp = "";
				}
				else if (str_temp == "111")
				{
					doko_notes += to_string(MOJI_�h);
					doko_notes += to_string(MOJI_�R);
					doko_notes += to_string(MOJI_�h��);
					//���łɒǉ����Ă��邽�ߏ������Z�b�g����
					str_temp = "";
				}
				else
				{
					for (int j = 0; j < str_temp.size(); j++)
					{
						if (str_temp[j] == '1' && i == str_temp.size() - 1)
						{
							doko_notes += to_string(MOJI_�h��);
						}
						else if (str_temp[j] == '2' && i == str_temp.size() - 1)
						{
							doko_notes += to_string(MOJI_�J�b);
						}
						else if (str_temp[j] == '1')
						{
							doko_notes += to_string(MOJI_�h);
						}
						else if (str_temp[j] == '2')
						{
							doko_notes += to_string(MOJI_�J);
						}
					}
					//���łɒǉ����Ă��邽�ߏ������Z�b�g����
					str_temp = "";
				}


				doko_notes += str_temp;
				str_temp = "";
				red_only = true;
			}

			switch (itr->notes_type)
			{
			case NOTES_DON://�ʏ�̃m�[�c
			case NOTES_BOMB_DON://���e
				str_temp += "1";
				time_temp2 = time_temp;
				time_temp = itr->judge_time;
				break;
			case NOTES_KA:
			case NOTES_BOMB_KA:
				red_only = false;
				str_temp += "2";
				time_temp2 = time_temp;
				time_temp = itr->judge_time;
				break;
			case NOTES_BIG_DON:
			case NOTES_BIG_KA:
			case NOTES_ROLL:
			case NOTES_BIG_ROLL:
			case NOTES_BALLOON:
			case NOTES_KUSUDAMA:
				//�^�C�������Z�b�g
				str_temp += "0";
				time_temp2 = time_temp;
				time_temp = itr->judge_time;
				break;
			case ORDER_BPM_CHANGE:
				bpm = itr->roll_time;
				break;
			default:
				break;
			}
		}

		int count = 0;
		for (auto itr = m_enso[i].m_fumen.list_notes.begin(); itr != m_enso[i].m_fumen.list_notes.end(); itr++)
		{
			if (count == doko_notes.size())break;
			string num = doko_notes.substr(count, 1);

			switch (itr->notes_type)
			{
			case NOTES_DON://�ʏ�̃m�[�c
			case NOTES_BOMB_DON://�ʏ�̃m�[�c
				itr->moji = (E_SE_NOTES)atoi(num.c_str());
				count++;
				break;
			case NOTES_KA:
			case NOTES_BOMB_KA:
				itr->moji = (E_SE_NOTES)atoi(num.c_str());
				count++;
				break;
			case NOTES_BIG_DON:
				itr->moji = MOJI_�h����;
				break;
			case NOTES_BIG_KA:
				itr->moji = MOJI_�J�b��;
				break;
			case NOTES_ROLL:
				itr->moji = MOJI_�A��;
				break;
			case NOTES_BIG_ROLL:
				itr->moji = MOJI_�A�ő�;
				break;
			case NOTES_BALLOON:
				itr->moji = MOJI_�ӂ�����;
				break;
			case NOTES_ROLLEND:

				break;
			case NOTES_KUSUDAMA:
				itr->moji = MOJI_��������;
				break;
			default:
				break;
			}
		}

	}
}