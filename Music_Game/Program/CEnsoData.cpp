#include "CEnsoData.h"
#include "GameL/UserData.h"
#include <fstream>
#include <sstream>
#include "GameHead.h"//CObjSongSelect

#define BPM_BEAT_TIME(bpm) (60.0f / bpm)

//�R���X�g���N�^
CEnsoData::CEnsoData()
{

	for (int i = 0; i < E_JUDGE::JUDGE_COUNT; i++)
	{
		m_score_data.judge[i] = 0;
	}
	m_score_data.score = 0;
	m_score_data.combo = 0;
	m_score_data.max_combo = 0;
	m_score_data.score_rank = E_SCORE_RANK::RANK_NONE;
	m_score_data.crown = E_CROWN::CROWN_NONE;
	m_now_bpm = 120.0f;
	m_now_signature[0] = MusicGame::MEASURE_LENGTH;
	m_now_signature[1] = MusicGame::MEASURE_LENGTH;
	m_measure_count = 0;//���ʃf�[�^�ǂݍ��ݗp���ߐ��J�E���^�[
	m_judge_offset = MusicGame::JUDGE_OFFSET;
	m_gogo = false;
	m_score_data.ct_gauge = { CCounter(0.0f,0.0f,100.0f,STOP) };
	m_roll_time = 0.0f;
	m_balloon_count = 0;

}

void CEnsoData::JudgeAdd(E_JUDGE judge)
{
	m_score_data.judge[judge]++;
}

/// <summary>
/// ���t�J�n����̌��݂̌o�ߎ��Ԃ��擾����B
/// </summary>
/// <returns>���݂̌o�ߎ��ԁB</returns>
float CEnsoData::GetNowTime()
{
	return m_ct_now_time.NowValue / 1000.0f;
}
void CEnsoData::SetTime(float time)
{
	m_ct_now_time.Start(time * 1000.0f,m_ct_now_time.EndValue,1);
}

void CEnsoData::LoadFumenData(string file_name,int player)
{
	string str_fumen_command;
	list<string> str_split_fumen_command;

	//�t�@�C�����J��
	ifstream ifs(file_name);
	if (!ifs)
	{
		MessageBox(NULL, TEXT("���Ȃ����Ă�������"),
			TEXT("���ʃt�@�C���ǂݍ��ݎ��s"), MB_OK);
		ifs.close();
	}

	m_fumen.fumen_path = file_name;

	while (getline(ifs,str_fumen_command))
	{
		str_split_fumen_command.push_back(str_fumen_command);
	}

	//�w�b�_�̓ǂݍ��݁B
	for (auto itr = str_split_fumen_command.begin(); itr != str_split_fumen_command.end(); itr++)
	{
		m_fumen.FumenHeaderLoad(*itr);
	}

	
	FumenDataLoad(str_split_fumen_command,player);
	
	if (m_fumen.score_add == 0 && (m_fumen.notes_count[BRANCH_NONE] + m_fumen.notes_count[BRANCH_TATSUJIN]) > 0)
	{
		m_score_add = (1000000/  (m_fumen.notes_count[BRANCH_NONE] + m_fumen.notes_count[BRANCH_TATSUJIN])) / 10 * 10;
	}
	//1�̈ʂ��[���̏ꍇ�؂�グ
//	m_fumen.score_add += m_fumen.score_add % 10 > 0 ? 10 : 0;


}

#include "GameHead.h"
/// <summary>
/// ���ʃf�[�^��ǂݍ��ށB�I�ȉ�ʂɎg�p������ȂǁB
/// </summary>
/// <param name="command_param"></param>
void CEnsoData::FumenDataLoad(list<string>& command_param,int player)
{

	m_now_bpm = m_fumen.bpm;



	bool load_notes = false;

	bool attack_notes = false;

	//�m�[�c�f�[�^�̓ǂݍ��݁B

	float start_time = MusicGame::TIME_START_DELAY / 1000.0f - m_fumen.offset;
	float time = start_time;

	//�X�N���[���X�s�[�h�̏�����
	float scroll_speed = 1.0f;

	int now_diffculty=DIFF_ONI;
	int now_roll_type = 0;

	//BARLINEON�̎���
	bool barline = true;


	auto roll_itr = m_fumen.list_balloon.begin();


	//���򕈖ʊJ�n�ʒu�L���p
	int branch_start_measure = 0;
	float branch_start_time = 0.0f;
	E_BRANCH branch_course = BRANCH_NONE;
	bool branch_hold = false;
	float branch_start_bpm = 0.0f;

	//�i�ʓ���p
	vector<ST_DAN_SONG> vec_dan_song;
	vector<MusicGame::DanC> vec_dan;
	ST_DAN_SONG dan_song;
	bool load_dansong = false;
	int dan_gauge_norma[2] = { 90,100 };

	//�A�Œ��͘A�ŉ�����}�����Ȃ�
	bool roll_now = false;

	bool kusudama_to_balloon = false;

	if (USER_DATA->m_now_select_diffculty[0] == E_DIFFCULTY::DIFF_DAN ||
		MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE ||
		(USER_DATA->m_player_amount == 2 && (USER_DATA->m_now_select_diffculty[0] != USER_DATA->m_now_select_diffculty[1])))
		kusudama_to_balloon = true;

	for (auto itr = command_param.begin(); itr != command_param.end(); itr++)
	{
		if (*itr == "")continue;

		if (itr->find("COURSE:") != -1)
		{
			string str = itr->substr(7);
			now_diffculty = MusicGame::StrToDiffculty(str);
		}
		else if (itr->find("LEVEL:") != -1)
		{
			string str = itr->substr(6);
			m_fumen.level[now_diffculty] = atoi(str.c_str());
		}
		else if (itr->find("BALLOON:") != -1)
		{
			if (now_diffculty == ((UserData*)Save::GetData())->m_now_select_diffculty[player])
			{
				string str = itr->substr(8);
				
				int num = 0;
				for (int i = 0; i < str.size(); i++)
				{
					if (str[i] == ',')
					{
						m_fumen.list_balloon.push_back(num);
						num = 0;
					}
					else
					{
						num *= 10;
						string strnum = str.substr(i,1);
						num += atoi(strnum.c_str());
						
					}
				}
				//�Ō�̐��������X�g�ɓ����
				m_fumen.list_balloon.push_back(num);
			}
		}
		else if (itr->find("SCOREINIT:") != -1)
		{
			string str = itr->substr(10);
			vector<string> split_str = split(str, ',');

			if (split_str.size() > 0)
			{
				m_fumen.score_add = atoi(split_str.back().c_str());
				m_score_add = m_fumen.score_add;
			}
		}
		else if (itr->find("DEMOSTART:") != -1)
		{
			string str = itr->substr(10);
			m_fumen.demo_start = atoi(str.c_str());
		}
		else if (itr->find("EXAM1:") != -1 ||
			itr->find("EXAM2:") != -1 ||
			itr->find("EXAM3:") != -1 ||
			itr->find("EXAM4:") != -1)
		{
			string command = itr->substr(6);
			vector<string> command_strsplit;
			string str;
			MusicGame::DanC dan;

			int count = 0;
			for (int i = 0; i < command.size(); i++)
			{
				if (command[i] == ',')
				{
					command_strsplit.push_back(str);
					str = "";
				}
				else
				{
					str += command[i];

				}
			}
			command_strsplit.push_back(str);

			E_DAN_TYPE type;
			MusicGame::DanC::E_DAN_RANGE range;

			for (int i = 0; i < command_strsplit.size(); i++)
			{
				switch (i)
				{
				case 0:
					if (command_strsplit[i] == "g")dan.m_type = E_DAN_TYPE::TYPE_GAUGE;
					else if (command_strsplit[i] == "jp")dan.m_type = E_DAN_TYPE::TYPE_GREAT;
					else if (command_strsplit[i] == "jg")dan.m_type = E_DAN_TYPE::TYPE_GOOD;
					else if (command_strsplit[i] == "jb")dan.m_type = E_DAN_TYPE::TYPE_MISS;
					else if (command_strsplit[i] == "s")dan.m_type = E_DAN_TYPE::TYPE_SCORE;
					else if (command_strsplit[i] == "r")dan.m_type = E_DAN_TYPE::TYPE_ROLL;
					else if (command_strsplit[i] == "h")dan.m_type = E_DAN_TYPE::TYPE_HIT;
					else if (command_strsplit[i] == "c")dan.m_type = E_DAN_TYPE::TYPE_COMBO;
					else dan.m_type = E_DAN_TYPE::TYPE_GAUGE;
					break;
				case 1:
					dan.m_norma[0][0] = atoi(command_strsplit[i].c_str());
					break;
				case 2:
					dan.m_norma[0][1] = atoi(command_strsplit[i].c_str());
					break;
				case 3:
					if (command_strsplit[i] == "m")dan.m_range = MusicGame::DanC::RANGE_MORE;
					else if (command_strsplit[i] == "l")dan.m_range = MusicGame::DanC::RANGE_LESS;
					else range = MusicGame::DanC::RANGE_MORE;
					break;
				case 4:
					dan.m_norma[1][0] = atoi(command_strsplit[i].c_str());
					dan.m_common = false;
					break;
				case 5:
					dan.m_norma[1][1] = atoi(command_strsplit[i].c_str());
					break;
				case 6:
					dan.m_norma[2][0] = atoi(command_strsplit[i].c_str());
					break;
				case 7:
					dan.m_norma[2][1] = atoi(command_strsplit[i].c_str());
					break;
				}
			}

			//�Q�[�W�̏ꍇ�ǉ����Ȃ�
			if (dan.m_type == E_DAN_TYPE::TYPE_GAUGE)
			{
				dan_gauge_norma[0] = dan.m_norma[0][0];
				dan_gauge_norma[1] = dan.m_norma[0][1];
			}
			else
			{
				vec_dan.push_back(dan);
			}
		}
		else if (itr->find("NORMA:") != -1)
		{
		string command = itr->substr(6);
		vector<string> command_strsplit;
		string str;
		int count = 0;
		for (int i = 0; i < command.size(); i++)
		{
			if (command[i] == ',')
			{
				command_strsplit.push_back(str);
				str = "";
			}
			else
			{
				str += command[i];

			}
		}
		command_strsplit.push_back(str);

		dan_gauge_norma[0] = atoi(command_strsplit[0].c_str());
		dan_gauge_norma[1] = atoi(command_strsplit[1].c_str());
		}

		//�J�n����I���܂�
		if (itr->find("#START") != -1 &&
			load_notes == false &&
			now_diffculty == ((UserData*)Save::GetData())->m_now_select_diffculty[player])
		{
			load_notes = true;

			ST_NOTES notes_test;
		
			roll_itr = m_fumen.list_balloon.begin();
		}


		//���ʃf�[�^�ǂݍ��ݒ�
		if (load_notes == true)
		{
			//���߂̍��Ԃ�BPM�ω���}���ł���悤�ɕύX
			list<string> measure_notes;
			int measure_count = 0;

			for (;itr != command_param.end(); itr++)
			{
				//�J���}��������܂ł��
				if (itr->find("//") != -1)
				{
					//�R�����g���܂܂�Ă���ꍇ�؂���
					*itr = itr->substr(0, itr->find("//"));
				}

				if (itr->find("#") != -1)
				{
					measure_notes.push_back(*itr);
				}
				else
				{

					for (int i = 0; i < itr->size(); i++)
					{
						string c = itr->substr(i, 1);

						if (c == ",")
						{
							measure_notes.push_back(c);
							break;
						}
						//����������ꍇ�A�m�[�c�J�E���g�𑝂₷
						if (atoi(c.c_str()) >= 0 && atoi(c.c_str()) < NOTES_Count)
						{
							measure_count++;
							measure_notes.push_back(c);
						}
					}

					//�R���}������
					if (itr->find(",") != -1)
					{
						break;
					}
				}


			}


			float measure_start_time = time;
			bool bar_line_insert = true;
			bool bar_yellow = false;


			for (auto itrs = measure_notes.begin(); itrs != measure_notes.end(); itrs++)
			{

				if (itrs->find("#") != -1)
				{
					ST_NOTES order;
					if (itrs->find("#SCROLL") != -1)
					{
						string command = itrs->substr(8);//�󔒂��܂߂� (#SCROLL 1.0)
						scroll_speed = atof(command.c_str());

					}
					else if (itrs->find("#BPMCHANGE") != -1)
					{
						string command = itrs->substr(11);//�󔒂��܂߂� (#SCROLL 1.0)
						m_now_bpm = atof(command.c_str());

						//BPMCHANGE ���߂�}���B
						order.notes_type = ORDER_BPM_CHANGE;
						//	order.lane = 0;
						order.judge = true;

						order.measure = m_fumen.measure_count;
						order.judge_time = time;
						//���[���^�C�������Ɏg�p.
						order.roll_time = m_now_bpm;

						m_fumen.list_notes.push_back(order);
					}
					else if (itrs->find("#MEASURE") != -1)
					{
						string command = itrs->substr(9);//�󔒂��܂߂� (#SCROLL 1.0)
						m_now_signature[0] = atoi(command.c_str());

						command = itrs->substr(10 + numOfDigit(m_now_signature[0]));
						m_now_signature[1] = atoi(command.c_str());
					}
					else if (itrs->find("#GOGOSTART") != -1)
					{
						order.notes_type = ORDER_GOGOSTART;
						//	order.lane = 0;
						order.judge = true;

						order.measure = m_fumen.measure_count;
						order.judge_time = time;
						order.roll_time = 0.0f;
						order.branch = branch_course;

						m_fumen.list_notes.push_back(order);
					}
					else if (itrs->find("#GOGOEND") != -1)
					{
						//�I��
						order.notes_type = ORDER_GOGOEND;
						//	order.lane = 0;
						order.judge = true;

						order.measure = m_fumen.measure_count;
						order.judge_time = time;
						order.roll_time = 0.0f;
						order.branch = branch_course;

						m_fumen.list_notes.push_back(order);
					}
					else if (itrs->find("#BARLINEON") != -1)
					{
						barline = true;
					}
					else if (itrs->find("#BARLINEOFF") != -1)
					{
						barline = false;
					}
					else if (itrs->find("#END") != -1)
					{
						//�I��
						order.notes_type = ORDER_END;
					//	order.lane = 0;
						order.judge = false;

						order.measure = m_fumen.measure_count;
						order.judge_time = time;
						order.roll_time = 0.0f;

						m_fumen.list_notes.push_back(order);

						load_notes = false;
						m_fumen.end_time = time;
						break;
					}
					else if (itrs->find("#BRANCHSTART") != -1)
					{
						ST_NOTES_BRANCH branch;
						branch.judge = true;
						branch.judge_time = measure_start_time;
						branch.measure = m_fumen.measure_count;

						//�J�n�ʒu���L��
						branch_start_measure = m_fumen.measure_count;
						branch_start_time = measure_start_time;
						branch_start_bpm = m_now_bpm;

						string command = itrs->substr(13);
						if (command[0] == 'p')//���x
						{
							branch.type = BRANCH_PERFECT;
						}
						else if (command[0] == 'r')//�A�Ő�
						{
							branch.type = BRANCH_ROLL;
						}
						else if (command[0] == 's')//�X�R�A
						{
							branch.type = BRANCH_SCORE;
						}
						command = command.substr(2);
						vector<string> str_split = split(command, ',');

						//int num = 0;
						//int count = 0;
						//for (int i = 0; i < command.size() && count < 2; i++)
						//{
						//	if (command[i] == ',')
						//	{
						//		branch.norma[count] = num;
						//		num = 0;
						//		count++;
						//	}
						//	else
						//	{
						//		num *= 10;
						//		string strnum = command.substr(i, 1);
						//		num += atof(strnum.c_str());

						//	}
						//}

						branch.norma[0] = stof(str_split[0]);
						branch.norma[1] = stof(str_split[1]);
						m_fumen.list_branch.push_back(branch);

					}
					else if (itrs->find("#NEXTSONG") != -1)
					{
						if (load_dansong == true)
						{
							vec_dan_song.push_back(dan_song);
							dan_song = ST_DAN_SONG();
						}
						else
						{
							load_dansong = true;
						}

						//�I�[�_�[��ǉ�
						order.notes_type = ORDER_NEXTSONG;
						order.judge = true;

						order.measure = m_fumen.measure_count;
						order.judge_time = time;
						order.roll_time = 0.0f;
						order.branch = branch_course;

						m_fumen.list_notes.push_back(order);


						time += MusicGame::DAN_NEXTSONG_TIME / 1000.0f;
						measure_start_time += MusicGame::DAN_NEXTSONG_TIME / 1000.0f;

						dan_song.music_start_time = time;

						string command = itrs->substr(10);
						vector<string> command_strsplit;
						string str;

						int count = 0;
						for (int i = 0; i < command.size(); i++)
						{
							if (command[i] == ',')
							{
								command_strsplit.push_back(str);
								str = "";
							}
							else
							{
								str += command[i];

							}
						}
						command_strsplit.push_back(str);

						//�ȏ���ǉ�
						for (int i = 0; i < command_strsplit.size(); i++)
						{
							switch (i)
							{
							case 0:
								dan_song.title = command_strsplit[i];
								break;
							case 1:
								dan_song.sub_title = command_strsplit[i];
								break;
							case 2:
								dan_song.genre = MusicGame::StrToGenre(command_strsplit[i]);
								break;
							case 3:
								dan_song.wave_file = m_fumen.fumen_path + "/../" + command_strsplit[i];
								break;
							case 4:
								dan_song.score_add = atoi(command_strsplit[i].c_str());
								break;
							default:
								break;
							}
						}


					}
					else if (itrs->find("#DELAY") != -1)
					{
						string command = itrs->substr(7);//�󔒂��܂߂�
						time += atof(command.c_str());
						measure_start_time += atof(command.c_str());
					}
					else if (itrs->find("#BRANCHEND") != -1)
					{
						branch_course = BRANCH_NONE;
					}
					else if (itrs->find("#SECTION") != -1)
					{
						//����������Z�b�g
						order.notes_type = ORDER_SECTION;
						order.judge = true;

						order.measure = m_fumen.measure_count;
						order.judge_time = time;
						order.roll_time = 0.0f;
						order.branch = BRANCH_NONE;

						m_fumen.list_notes.push_back(order);

						bar_yellow = true;
					}
					else if (itrs->find("#LEVELHOLD") != -1)
					{
						order.notes_type = ORDER_LEVELHOLD;
						order.judge = true;

						order.measure = m_fumen.measure_count;
						order.judge_time = time;
						order.roll_time = 0.0f;
						order.branch = BRANCH_NONE;

						m_fumen.list_notes.push_back(order);
					}
					else if (itrs->find("#EFFECT1") != -1)
					{
						order.notes_type = ORDER_EFFECT1;
						//	order.lane = 0;
						order.judge = true;

						order.measure = m_fumen.measure_count;
						order.judge_time = time;
						order.roll_time = 0.0f;
						order.branch = branch_course;

						m_fumen.list_notes.push_back(order);
					}
					else if (itrs->find("#EFFECTEND") != -1)
					{
						order.notes_type = ORDER_EFFECTEND;
						//	order.lane = 0;
						order.judge = true;

						order.measure = m_fumen.measure_count;
						order.judge_time = time;
						order.roll_time = 0.0f;
						order.branch = branch_course;

						m_fumen.list_notes.push_back(order);
					}
					else if (itrs->find("#N") != -1)
					{
						//�ǂݍ��݃X�^�[�g�I
						time = branch_start_time;
						m_fumen.measure_count = branch_start_measure;
						branch_course = BRANCH_NORMAL;
						m_now_bpm = branch_start_bpm;
						measure_start_time = branch_start_time;
					}
					else if (itrs->find("#E") != -1)
					{
						time = branch_start_time;
						m_fumen.measure_count = branch_start_measure;
						branch_course = BRANCH_KUROTO;
						m_now_bpm = branch_start_bpm;
						measure_start_time = branch_start_time;
					}
					else if (itrs->find("#M") != -1)
					{
						time = branch_start_time;
						m_fumen.measure_count = branch_start_measure;
						branch_course = BRANCH_TATSUJIN;
						m_now_bpm = branch_start_bpm;
						measure_start_time = branch_start_time;
					}
					
				}
				else if (*itrs == ",")
				{
					if (bar_line_insert == true)
					{
						bar_line_insert = false;

						if (barline == true)
						{
							ST_NOTES notes_test;
							//���ߐ��}���e�X�g�B
							notes_test.notes_type = NOTES_BAR_LINE;
							//	notes_test.lane = 0;
							notes_test.judge = true;
							notes_test.measure = m_fumen.measure_count;
							notes_test.judge_time = measure_start_time;
							notes_test.scroll_speed = scroll_speed * m_now_bpm;
							notes_test.branch = branch_course;
							m_fumen.list_notes.push_back(notes_test);
						}
						//���̏��߂ɂ����鎞�Ԃ�BPM�Ɣ�������v�Z����
						float measure_time = BPM_BEAT_TIME(m_now_bpm) * ((float)m_now_signature[0] / (float)m_now_signature[1] * MusicGame::MEASURE_LENGTH);//1���߂ɂ����鎞��
						//��������Ƃ̎��Ԃ�ǉ�����
						time += measure_time;
					}

				}
				else //�m�[�c
				{
					//�ŏ��̃m�[�c�Əd�˂�悤�ɏ��ߐ���}������B
					if (bar_line_insert == true)
					{
						bar_line_insert = false;

						if (barline == true)
						{
							ST_NOTES notes_test;
							//���ߐ��}���e�X�g�B
							notes_test.notes_type = NOTES_BAR_LINE;
							//	notes_test.lane = 0;
							notes_test.judge = true;
							notes_test.measure = m_fumen.measure_count;
							notes_test.judge_time = measure_start_time;
							notes_test.scroll_speed = scroll_speed * m_now_bpm;
							notes_test.branch = branch_course;
							m_fumen.list_notes.push_back(notes_test);
						}
					}

					ST_NOTES notes;
					notes.measure = m_fumen.measure_count;
				//	notes.lane = 0;
					notes.judge = true;
					notes.scroll_speed = scroll_speed * m_now_bpm;
					notes.roll_time = 0.0f;
					notes.roll_info = 0;
					notes.branch = branch_course;

					E_NOTES_TYPE num = NOTES_BAR_LINE;
					try
					{
						num = (E_NOTES_TYPE)stoi(*itrs);
					}
					catch (const std::invalid_argument)
					{
						if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
						{
							if (*itrs == "a" || *itrs == "A")
							{
								num = NOTES_BOMB_DON;
							}
							else if (*itrs == "b" || *itrs == "B")
							{
								num = NOTES_BOMB_KA;
							}
						}
					}

					switch (num)
					{
					case NOTES_BAR_LINE://���ߐ�
						break;
					case NOTES_DON://�ʏ�̃m�[�c
					case NOTES_KA:
					case NOTES_BIG_DON:
					case NOTES_BIG_KA:

						notes.notes_type = num;
						notes.judge_time = time;
						m_fumen.list_notes.push_back(notes);
						m_fumen.notes_count[branch_course]++;

						if (load_dansong == true)
						{
							dan_song.notes_count[branch_course]++;
						}

						break;

					case NOTES_BOMB_DON:
					case NOTES_BOMB_KA:
						notes.notes_type = num;
						notes.judge_time = time;
						m_fumen.list_notes.push_back(notes);

						break;
					case NOTES_ROLL:
					case NOTES_BIG_ROLL:
					case NOTES_BALLOON:
					case NOTES_KUSUDAMA:

						if (roll_now == true)break;

						roll_now = true;
						notes.notes_type = num;
						notes.judge_time = time;
						now_roll_type = num;
						notes.judge = true;

						//���D�����ɒu��������B
						if (num == NOTES_KUSUDAMA &&
							kusudama_to_balloon == true)
							notes.notes_type = NOTES_BALLOON;

						if (num == NOTES_BALLOON || num == NOTES_KUSUDAMA)
						{
							if (roll_itr != m_fumen.list_balloon.end())
							{
								notes.roll_info = *roll_itr;
								roll_itr++;
							}
							else
							{
								notes.roll_info = 5;
							}


						}
						m_fumen.list_notes.push_back(notes);
						m_fumen.roll_remain++;
						if (load_dansong == true)
						{
							dan_song.roll_remain++;
						}

						break;


						//�V���A��
					case NOTES_ROLLEND:

						roll_now = false;

						//�m�[�c���X�g�������̂ڂ�A��ԍŌ�ɂ���m�[�c�̏��𔻒f���ĘA�ł�}������B
						for (auto itre = m_fumen.list_notes.rbegin(); itre != m_fumen.list_notes.rend(); itre++)
						{
							//���߂͖�������
							if (itre->notes_type >= NOTES_Count)
							{
								continue;
							}

							bool is_roll = false;

							switch (itre->notes_type)
							{
							case NOTES_ROLL:
							case NOTES_BIG_ROLL:
								//�A�ŊJ�n���ƘA�ŏI�����̎��Ԃ̍��𒲂ׂĘA�Ŏ��Ԃ̏���ς���
								itre->roll_time = time - itre->judge_time;
								is_roll = true;

								//���v�A�Ŏ��Ԃɉ��Z
								m_roll_time += time - itre->judge_time;
								if (load_dansong == true)
								{
									dan_song.roll_time += time - itre->judge_time;
								}
								break;
							case NOTES_BALLOON:
							case NOTES_KUSUDAMA:
							{
								//�A�ŊJ�n���ƘA�ŏI�����̎��Ԃ̍��𒲂ׂĘA�Ŏ��Ԃ̏���ς���
								itre->roll_time = time - itre->judge_time;
								is_roll = true;

								//�A�Ő��~�t���[���� > �b���̏ꍇ�A�ʏ�A�łƂ��ăJ�E���g����
								if (itre->roll_info * (1.0f / FRAME_FPS) > time - itre->judge_time)
									m_roll_time += time - itre->judge_time;
								else
									m_balloon_count += itre->roll_info;

								if (load_dansong == true)
								{
									dan_song.roll_time += time - itre->judge_time;
								}
							}
							break;
							}

							if (is_roll == true)break;
						}

						break;
					}
					


					//���̏��߂ɂ����鎞�Ԃ�BPM�Ɣ�������v�Z����
					float measure_time = BPM_BEAT_TIME(m_now_bpm) * ((float)m_now_signature[0] / (float)m_now_signature[1] * MusicGame::MEASURE_LENGTH);//1���߂ɂ����鎞��
					//��������Ƃ̎��Ԃ�ǉ�����
					time += measure_time * (1.0f / (float)measure_count);

				}

			}

			//�Ō�ɏ��ߐ��𑝂₷�B
			m_fumen.measure_count++;

			if (load_notes == false)break;
		}

	}
	if (load_dansong == true)
	{
		vec_dan_song.push_back(dan_song);

		CObjDanC* dan = new CObjDanC(vec_dan_song,vec_dan,dan_gauge_norma[0], dan_gauge_norma[1]);
		Objs::InsertObj(dan, OBJ_DANC, PRIO_ENSO_DANC);
	}
}