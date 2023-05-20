#include "CObjNotes.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
//AI�̔���^�C�~���O���߂�悤
#include <random>

//�C�e���[�^(itr)�ƌ��݂̎���(enso->time)���g�p����B
#define NOTES_TIME_DIFF (itr->judge_time - enso->m_enso[0].GetNowTime())
#define NOTES_TIME_DIFF_NEW(time) (time - enso->m_enso[0].GetNowTime())

//������
void CObjNotes::Init()
{

	m_first_flag = true;

	m_section_count = 0;

	m_notes_remain_num.SetTex(tex_NUMBER, RECT_NUM.m_width, RECT_NUM.m_height);

	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		m_roll_flag[i] = false;
	}

	m_ct_auto_roll = { CCounter(0.0f,0.0f,4.0f,LOOP) };

	m_ani_notes_face.LoadData("Animation/Enso/Notes/Face");
}
//�i�s
void CObjNotes::Action()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjBalloon* balloon = (CObjBalloon*)Objs::GetObj(OBJ_BALLOON);
	CObjRoll* roll = (CObjRoll*)Objs::GetObj(OBJ_ROLL);
	CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);
	m_ani_notes_face.AddLoop(enso->m_enso[0].m_fumen.bpm / 60.0f / 60.0f);

	CObjEnsoBattle* battle = (CObjEnsoBattle*)Objs::GetObj(OBJ_BATTLE);
	
	if (m_first_flag)
	{
		for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
		m_list_notes[i] = enso->m_enso[i].m_fumen.list_notes;
		m_first_flag = false;
		//sort(m_list_notes.begin(), m_list_notes.end(),
		//	[](ST_NOTES notes1, ST_NOTES notes2)->float {
		//		return (notes1.judge_time < notes2.judge_time);
		//	});
	}

	for(int i=0;i<((UserData*)Save::GetData())->m_player_amount;i++)
	{ 
	
		for (auto itr = m_list_notes[i].begin(); itr != m_list_notes[i].end(); )
		{

			float time = NOTES_TIME_DIFF_NEW(itr->judge_time + (float)enso->m_enso[i].m_option.offset * MusicGame::JUDGE_OFFSET);

			if (time >= MusicGame::JUDGE_RANGE[MISS])
			{
				break;
			}
			//�߂��Ă��܂����m�[�c�̔�����폜���A�s����𑝂₷�B
			if (itr->judge == true)
			{
				if (itr->notes_type == NOTES_BAR_LINE && time < 0.0f)
				{
					itr->judge = false;
					enso->AddMeasureCount(i);
				}

				if (itr->judge_time < enso->m_enso[0].GetNowTime())
				{
					if (itr->notes_type == ORDER_GOGOSTART)
					{
						enso->m_enso[i].m_gogo = true;
						lane->GogoStart(i);
						CObjCharacter* chara = (CObjCharacter*)Objs::GetObj(OBJ_CHARACTER);
						if (chara != nullptr)
							chara->ActGogoStart(i);
						CObjSpark* spark = (CObjSpark*)Objs::GetObj(OBJ_SPARK);
						if (spark != nullptr)
							spark->SparkStart();
						itr = m_list_notes[i].erase(itr);
						continue;
					}
					else if (itr->notes_type == ORDER_GOGOEND)
					{
						enso->m_enso[0].m_gogo = false;
						itr = m_list_notes[i].erase(itr);
						continue;
					}
					else if (itr->notes_type == ORDER_BPM_CHANGE)
					{
						itr->judge = false;
						enso->m_enso[i].m_now_bpm = itr->roll_time;
						itr = m_list_notes[i].erase(itr);
						continue;
					}
					else if (itr->notes_type == ORDER_SECTION)
					{
						itr->judge = false;
						enso->BranchInfoReset(i);
						itr = m_list_notes[i].erase(itr);
						continue;
					}
					else if (itr->notes_type == ORDER_LEVELHOLD)
					{
						itr->judge = false;
						enso->SetBranchHold(i);
						continue;
					}
					else if (itr->notes_type == ORDER_NEXTSONG)
					{
						itr->judge = false;
						CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);
						dan->NextSong();
						itr = m_list_notes[i].erase(itr);
						continue;
					}
					else if (itr->notes_type == ORDER_EFFECT1)
					{
						battle->EffectStart(0);
						itr = m_list_notes[i].erase(itr);
						continue;
					}
					else if (itr->notes_type == ORDER_EFFECTEND)
					{
						battle->EffectEnd();	itr = m_list_notes[i].erase(itr);
						continue;
					}
					
					
				}

				//�X���[����
				if (time < -MusicGame::JUDGE_RANGE[HIT] &&
					(itr->notes_type == NOTES_DON || itr->notes_type == NOTES_KA ||
						itr->notes_type == NOTES_BIG_DON || itr->notes_type == NOTES_BIG_KA))
				{
					JudgeProcess(MISS, false, false, (E_NOTES_TYPE)itr->notes_type, i,0.0f);
					//	Section(itr->measure,MISS,false);
					itr->judge = false;
				}

				//�A�Œ�
				if (itr->notes_type == NOTES_ROLL ||
					itr->notes_type == NOTES_BIG_ROLL ||
					itr->notes_type == NOTES_BALLOON)
				{

					CObjCharacter* chara = (CObjCharacter*)Objs::GetObj(OBJ_CHARACTER);


					if (itr->roll_info > 0 && (itr->notes_type == NOTES_ROLL ||
						itr->notes_type == NOTES_BIG_ROLL))
						itr->roll_info -= 2;

					//�I��
					if (time + itr->roll_time < 0.0f)
					{
						itr->judge = false;
						m_roll_flag[i] = false;
						m_ct_auto_roll.Reset();
						roll->End(i);

						if ((itr->notes_type == NOTES_BALLOON))
						{
							balloon->End(i);
							if (chara != nullptr)
								chara->ActBalloonMiss(i);
						}
						enso->SubRollRemain(itr->roll_time);
					}
					else if (time < 0.0f && time + itr->roll_time >= 0.0f)
					{
						m_roll_flag[i] = true;

						if (((UserData*)Save::GetData())->m_auto_play[i] == true)
						{


							CObjMTaiko* taiko = (CObjMTaiko*)Objs::GetObj(OBJ_TAIKO);
							taiko->AutoPlayInput((E_NOTES_TYPE)itr->notes_type, i);
							break;
						}
					}

				}
				else if (itr->notes_type == NOTES_KUSUDAMA)
				{
					CObjKusudama* kusudama = (CObjKusudama*)Objs::GetObj(OBJ_KUSUDAMA);

					//�J�n
					if (time < 0.0f && itr->roll_info > 0)
					{
						kusudama->Start(itr->roll_info);
						itr->roll_info = 0;
					}

					//�I��
					if (time + itr->roll_time < 0.0f)
					{
						itr->judge = false;
						m_roll_flag[i] = false;

						kusudama->End();
						enso->SubRollRemain(itr->roll_time);
					}
					else if (time < 0.0f && time + itr->roll_time >= 0.0f)
					{
						m_roll_flag[i] = true;

						if (((UserData*)Save::GetData())->m_auto_play[i] == true)
						{


							CObjMTaiko* taiko = (CObjMTaiko*)Objs::GetObj(OBJ_TAIKO);
							taiko->AutoPlayInput((E_NOTES_TYPE)itr->notes_type, i);
							break;
						}
					}
				}



				if (((UserData*)Save::GetData())->m_auto_play[i] == true)
				{
					
					float ai_offset = 0.0f;
					if(AUTO_AI)
					ai_offset = AINextJudgeTiming();

					//�I�[�g�v���C���̂�1�t���[���Ԃ񑁂߂ɔ�����s��
					if (time - enso->m_enso[i].m_judge_offset + ai_offset < 0.0f &&
						(itr->notes_type == NOTES_DON ||
							itr->notes_type == NOTES_KA ||
							itr->notes_type == NOTES_BIG_DON ||
							itr->notes_type == NOTES_BIG_KA))
					{
						CObjMTaiko* taiko = (CObjMTaiko*)Objs::GetObj(OBJ_TAIKO);
						taiko->AutoPlayInput((E_NOTES_TYPE)itr->notes_type, i);
						break;
					}


				}
			}
			//�m�[�c�̈ʒu�����݂̎��ԂƔ���̎��Ԃ���v�Z����B
			float pos_x = NOTES_TIME_DIFF_NEW(itr->judge_time) * (NOTES_BEAT_WIDTH)*itr->scroll_speed;

			//�m�[�c����ʊO�ɍs���΍폜����B
			if (pos_x < -512.0f &&
				(itr->notes_type == NOTES_BAR_LINE ||
					itr->notes_type == NOTES_DON || itr->notes_type == NOTES_KA ||
					itr->notes_type == NOTES_BIG_DON || itr->notes_type == NOTES_BIG_KA))
			{
				itr = m_list_notes[i].erase(itr);

			}
			else if (NOTES_TIME_DIFF_NEW(itr->judge_time + itr->roll_time) * (enso->m_enso[0].m_now_bpm * NOTES_BEAT_WIDTH) < -256.0f &&
				(itr->notes_type == NOTES_ROLL || itr->notes_type == NOTES_BIG_ROLL ||
					itr->notes_type == NOTES_BALLOON || itr->notes_type == NOTES_KUSUDAMA))
			{
				itr = m_list_notes[i].erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}

}
//�`��
void CObjNotes::Draw()
{

	Draw::SetBlend(tex_NOTES, E_BLEND_MODE::NORMAL);
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);
	CObjCombo* combo = (CObjCombo*)Objs::GetObj(OBJ_COMBO);


	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		int judge_pos_x = lane->GetJudgePosX(i);
		int judge_pos_y = lane->GetJudgePosY(i);

		//���ߐ���`��B
		for (auto itr = m_list_notes[i].begin(); itr != m_list_notes[i].end(); itr++)
		{


			//���ߐ��͖������ŕ`��
			if (itr->notes_type == NOTES_BAR_LINE)
			{
				//�m�[�c�̈ʒu�����݂̎��ԂƔ���̎��Ԃ���v�Z����B
				float pos_x = NOTES_TIME_DIFF_NEW(itr->judge_time + (float)enso->m_enso[i].m_option.offset * MusicGame::JUDGE_OFFSET) * (NOTES_BEAT_WIDTH);
				//�X�N���[�����x��K��
				pos_x *= itr->scroll_speed;
				pos_x *= enso->m_enso[i].m_option.scroll_speed;

				//��ʊO�̏ꍇ�̓X�L�b�v
				if (judge_pos_x + pos_x > WINDOW_SIZE_W)
				{
					continue;
				}

				Draw::Draw(tex_LINE, judge_pos_x + pos_x, judge_pos_y);
			}
		}

		//������`��B
		//�t������`�悷��
		for (auto itr = m_list_notes[i].rbegin(); itr != m_list_notes[i].rend(); itr++)
		{

			//�m�[�c�̈ʒu�����݂̎��ԂƔ���̎��Ԃ���v�Z����B
			float pos_x = NOTES_TIME_DIFF_NEW(itr->judge_time + (float)enso->m_enso[i].m_option.offset * MusicGame::JUDGE_OFFSET) * (NOTES_BEAT_WIDTH);
			//�X�N���[�����x��K��
			pos_x *= itr->scroll_speed;
			pos_x *= enso->m_enso[i].m_option.scroll_speed;

			//�A�ŏI���ʒu
			float pos_x_e = NOTES_TIME_DIFF_NEW(itr->judge_time + itr->roll_time + (float)enso->m_enso[i].m_option.offset * MusicGame::JUDGE_OFFSET) * (NOTES_BEAT_WIDTH);
			pos_x_e *= itr->scroll_speed;
			pos_x_e *= enso->m_enso[i].m_option.scroll_speed;

			if (enso->m_enso[i].m_option.doron != true)
			{

				//��ʊO�̏ꍇ�̓X�L�b�v
				if ((judge_pos_x + pos_x_e < 0 ||
					judge_pos_x + pos_x > WINDOW_SIZE_W)
					&& itr->notes_type != NOTES_ROLLEND)
				{
					continue;
				}

				//�R���{�����擾���āA���Y���Ő؂���J�n�ʒu��ς���B
				float rect_notes_y = 0.0f;

				RECT_F rect_notes = { itr->notes_type * RECT_NOTES.m_width,0.0f,128.0f,128.0f };

				if (itr->notes_type == NOTES_ROLL ||
					itr->notes_type == NOTES_BIG_ROLL)
				{
					//�A�ł̒���


					//�ԐF�ɃZ�b�g
					COLOR red = { 1.0f,1.0f - ((float)itr->roll_info / 100.0f),1.0f - ((float)itr->roll_info / 100.0f) };
					Draw::SetColor(tex_NOTES, red);

					RECT_F rect_roll = itr->notes_type == NOTES_ROLL ? RECT_ROLL_CENTER : RECT_ROLL_CENTER_BIG;

					int pos_x_c = pos_x + RECT_NOTES.m_width * 0.5f;
					pos_x_e += RECT_NOTES.m_width * 0.5f;

					while (pos_x_c < pos_x_e && judge_pos_x + pos_x_c < WINDOW_SIZE_W)
					{
						if (judge_pos_x + pos_x_c < 0)
						{
							//��ʊO�Ȃ̂ŉ������Ȃ�
							pos_x_c += (rect_roll.m_width - 1);
							continue;
						}
						else if (pos_x_e - pos_x_c > rect_roll.m_width)
						{
							Draw::Draw(tex_NOTES, judge_pos_x + pos_x_c, judge_pos_y, rect_roll);
							pos_x_c += (rect_roll.m_width - 1);
						}
						else
						{
							rect_roll.m_width = pos_x_e - pos_x_c + 1;
							Draw::Draw(tex_NOTES, judge_pos_x + pos_x_c, judge_pos_y, rect_roll);
						
							rect_roll = itr->notes_type == NOTES_ROLL ? RECT_ROLL_RIGHT : RECT_ROLL_RIGHT_BIG;
							Draw::Draw(tex_NOTES, judge_pos_x + pos_x_e, judge_pos_y, rect_roll);

							break;
						}
					}
				}
				if (itr->notes_type == NOTES_BALLOON)
				{
					//�A�Œ��ŁA���A�ł��I����Ă��Ȃ�
					if (pos_x <= 0.0f && pos_x_e > 0.0f)
					{
						pos_x = 0.0f;
					}
					else if (pos_x_e < 0.0f)
					{
						pos_x += (pos_x_e - pos_x);
					}

					float scale_x = 1.0f;
					if (combo->GetComboColor(i) == E_COMBO_COLOR::NOT)
					{
						;
					}
					else if (combo->GetComboColor(i) == E_COMBO_COLOR::NORMAL)
					{
						scale_x = m_ani_notes_face.GetValue("BalloonScale").scale_x;
					}
					else 
					{
						scale_x = m_ani_notes_face.GetValue("BalloonScaleFast").scale_x;
					}
					Draw::SetScaleX(tex_NOTES, m_ani_notes_face.GetValue("BalloonScale").scale_x);
					Draw::Draw(tex_NOTES, judge_pos_x+ pos_x + BALLOON_RIGHT_OFFSET, judge_pos_y, RECT_BALLOON_RIGHT);
				}

				//�܂��́A��[�̕`��
				switch (itr->notes_type)
				{
				case NOTES_BAR_LINE:
					//�ړ]���܂����B
					continue;
				case NOTES_DON://�ʏ�̃m�[�c
				case NOTES_KA:
				case NOTES_BIG_DON:
				case NOTES_BIG_KA:
				case NOTES_ROLL:
				case NOTES_BIG_ROLL:
				case NOTES_BALLOON:
				{
					int pattern = 0;

					if (combo->GetComboColor(i) == E_COMBO_COLOR::NORMAL)
						pattern = m_ani_notes_face.GetValue("Face").pattern;

					else if (combo->GetComboColor(i) == E_COMBO_COLOR::SILVER)
						pattern = m_ani_notes_face.GetValue("FaceFast").pattern;

					else if (combo->GetComboColor(i) == E_COMBO_COLOR::GOLD)
						pattern = m_ani_notes_face.GetValue("FaceFast").pattern * 2;

					rect_notes.m_y = pattern * rect_notes.m_height;

					Draw::SetScaleX(tex_NOTES, 1.0f);
					Draw::SetColor(tex_NOTES, Color::White);
					Draw::Draw(tex_NOTES, (int)(judge_pos_x + pos_x), judge_pos_y, rect_notes);
					break;
				}
				
				case NOTES_KUSUDAMA:
				{
					RECT_F rect_balloon = itr->notes_type == NOTES_BALLOON ? RECT_BALLOON : RECT_KUSUDAMA;

					float x = pos_x;

					//�A�Œ��ŁA���A�ł��I����Ă��Ȃ�
					if (pos_x <= 0.0f && pos_x_e > 0.0f)
					{
						x = 0.0f;
					}
					else if (pos_x_e < 0.0f)
					{
						x += (pos_x_e - pos_x);
					}
					Draw::Draw(tex_NOTES, judge_pos_x + x, judge_pos_y, rect_balloon);
					break;
				}
				case NOTES_ROLLEND:
					break;
				case NOTES_BOMB_DON:
				case NOTES_BOMB_KA:
				{
					Draw::Draw(tex_NOTES, judge_pos_x + pos_x, judge_pos_y, RECT_BOMB);
					break;
				}
				default:
					continue;
				}
			}

			switch (itr->notes_type)
			{
			case NOTES_BAR_LINE:
				//�ړ]���܂����B
				continue;
			case NOTES_DON://�ʏ�̃m�[�c
			case NOTES_KA:
			case NOTES_BIG_DON:
			case NOTES_BIG_KA:
			case NOTES_BOMB_DON:
			case NOTES_BOMB_KA:
			{
				//�����̕`��
				RECT_F rect_moji = RECT_SE_NOTES;
				rect_moji.m_y = itr->moji * RECT_SE_NOTES.m_height;
				Draw::Draw(tex_SE_NOTES,(int)( judge_pos_x + pos_x), judge_pos_y + MusicGame::SE_NOTES_OFFSET_Y, rect_moji);
				break;
			}
			case NOTES_ROLL:
			case NOTES_BIG_ROLL:
			{
				////�A�ł̒���


				////�ԐF�ɃZ�b�g
				//COLOR red = { 1.0f,1.0f - ((float)itr->roll_info / 100.0f),1.0f - ((float)itr->roll_info / 100.0f) };
				//Draw::SetColor(tex_NOTES, red);

				////���̕`��
				//RECT_F rect_roll = { RECT_ROLL_X[itr->notes_type == NOTES_ROLL ? 2 : 5],rect_notes_y,128.0f,128.0f };
				//Draw::Draw(tex_NOTES, MusicGame::NOTES_JUDGE_LINE[0].x + pos_x_e, MusicGame::NOTES_JUDGE_LINE[0].y, rect_roll);

				//float pos_x_c = pos_x_e - pos_x - 64.0f;



				//while (pos_x_c > 0.0f)
				//{
				//	if (pos_x_c > 64.0f)
				//	{
				//		rect_roll = { RECT_ROLL_X[itr->notes_type == NOTES_ROLL ? 1 : 4],rect_notes_y,66.0f,128.0f };
				//		Draw::Draw(tex_NOTES, MusicGame::NOTES_JUDGE_LINE[0].x + pos_x_e - pos_x_c, MusicGame::NOTES_JUDGE_LINE[0].y, rect_roll);
				//		pos_x_c -= 64.0f;
				//	}
				//	else
				//	{
				//		rect_roll = { RECT_ROLL_X[itr->notes_type == NOTES_ROLL ? 1 : 4],rect_notes_y,pos_x_c,128.0f };
				//		Draw::Draw(tex_NOTES, MusicGame::NOTES_JUDGE_LINE[0].x + pos_x_e - pos_x_c, MusicGame::NOTES_JUDGE_LINE[0].y, rect_roll);
				//		pos_x_c = 0.0f;
				//		break;
				//	}
				//}
				//�����̕`��
				RECT_F rect_moji = RECT_SE_NOTES;
				rect_moji.m_y = itr->moji * RECT_SE_NOTES.m_height;
				Draw::Draw(tex_SE_NOTES, judge_pos_x + pos_x, judge_pos_y + MusicGame::SE_NOTES_OFFSET_Y, rect_moji);
				break;
			}
			case NOTES_BALLOON:
			case NOTES_KUSUDAMA:
			{

				float x = pos_x;

				//�A�Œ��ŁA���A�ł��I����Ă��Ȃ�
				if (pos_x <= 0.0f && pos_x_e > 0.0f)
				{
					x = 0.0f;
				}
				else if (pos_x_e < 0.0f)
				{
					x += (pos_x_e - pos_x);
				}
				//�����̕`��
				RECT_F rect_moji = RECT_SE_NOTES;
				rect_moji.m_y = itr->moji * RECT_SE_NOTES.m_height;
				Draw::Draw(tex_SE_NOTES, judge_pos_x + x, judge_pos_y + MusicGame::SE_NOTES_OFFSET_Y, rect_moji);
				break;
			}
			case NOTES_ROLLEND:
				break;
			default:
				continue;
			}



		}
	}
	Draw::SetScaleY(tex_NUMBER, 1.0f);

	//��O�ݒ�
	//if(m_section_count > 0)


	
	//Draw::Draw(tex_ATTACK_NOTES_TEXT, REMAIN_POS.x, REMAIN_POS.y);

	//int notes_count = enso->m_enso[0].m_fumen.notes_count[BRANCH_NONE] + enso->m_enso[0].m_fumen.notes_count[BRANCH_TATSUJIN];
	//notes_count *= 0.05f;
	//int judge_notes = enso->m_enso[0].m_score_data.judge[JUST] + enso->m_enso[0].m_score_data.judge[HIT] + enso->m_enso[0].m_score_data.judge[MISS];

	//for (int i = MISS; i >= JUST; i--)
	//{
	//	int percent = 0;
	//	int offset = 0;

	//	if (i == JUST || i == HIT)offset = notes_count * 0.5f;

	//	if (judge_notes > 0)
	//	{
	//		percent = (float)(enso->m_enso[0].m_score_data.judge[i] + offset) / (float)(judge_notes + notes_count) * 100.0f;
	//	}
	//	m_notes_remain_num.Draw(percent, NUM_POS.x, NUM_POS.y + i * 64, NUM_WIDTH);

	//}
}

//����̕��@�B
// ����ł���m�[�c�ň�ԋ߂��m�[�c�𔻒肷��
// 
//
void CObjNotes::InputJudge(TAIKO_INPUT input,int player)
{
	//�����擾
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjScore* score = (CObjScore*)Objs::GetObj(OBJ_SCORE);
	CObjBalloon* balloon = (CObjBalloon*)Objs::GetObj(OBJ_BALLOON);
	CObjKusudama* kusudama = (CObjKusudama*)Objs::GetObj(OBJ_KUSUDAMA);
	CObjRoll* roll = (CObjRoll*)Objs::GetObj(OBJ_ROLL);
	CObjCharacter* chara = (CObjCharacter*)Objs::GetObj(OBJ_CHARACTER);
	CObjFlyingNotes* flying = (CObjFlyingNotes*)Objs::GetObj(OBJ_FLYINGNOTES);
	float time = 0.0f;

	for (auto itr = m_list_notes[player].begin(); itr != m_list_notes[player].end(); itr++)
	{
		//�o�ߎ��Ԃƃm�[�c���莞�Ԃ̍��B
		time = NOTES_TIME_DIFF_NEW(itr->judge_time + (float)enso->m_enso[player].m_option.offset * MusicGame::JUDGE_OFFSET);

		//�e�X�g�p�@��딻��
		//time += 0.016f;

		//�A�Œ�
		if (m_roll_flag[player] == true)
		{
			if (itr->notes_type == NOTES_ROLL || itr->notes_type == NOTES_BIG_ROLL)
			{
				if (time < 0.0f && time + itr->roll_time >= 0.0f)
				{
					if (itr->roll_info < 100)
						itr->roll_info += 20;

					roll->Add(player);

					E_NOTES_TYPE type;

					if (itr->notes_type == NOTES_ROLL)
					{
						type = input == DON ? NOTES_DON : NOTES_KA;
					}
					else //if (itr->notes_type == NOTES_BIG_ROLL)
					{

						type = input == DON ? NOTES_BIG_DON : NOTES_BIG_KA;
					}

					JudgeProcess(ROLL, false, false, type, player,0.0f);
					return;
				}
			}
			else if ((itr->notes_type == NOTES_BALLOON || itr->notes_type == NOTES_KUSUDAMA) &&
				input == DON)
			{
				if (time < 0.0f && time + itr->roll_time >= 0.0f)
				{
						//�����ʂ̏ꍇ�̂݃X�R�A��100 / �v���C���[�ɂ���
						if (itr->notes_type == NOTES_KUSUDAMA)
							score->AddScore(100 / ((UserData*)Save::GetData())->m_player_amount, player);
						else
							score->AddScore(100, player);
					

					enso->AddBranchJudge(ROLL,player);
					enso->m_enso[player].m_score_data.judge[ROLL]++;
	

					CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);
					if (dan != nullptr)
					{
						dan->AddSongJudge(ROLL);
						dan->Update();
					}
			
					if (itr->notes_type == NOTES_BALLOON)
					{
						balloon->Start(itr->roll_info, player);
						itr->roll_info--;
						balloon->Set(itr->roll_info, player);
						if (chara != nullptr)
							chara->ActBalloonBroke(player);
						//���D����
						if (itr->roll_info <= 0)
						{
							balloon->Break(player);
							m_list_notes[player].erase(itr);
							Audio::Start(se_BALLOON);
							m_roll_flag[player] = false;
							if (flying != nullptr)
							flying->Add(NOTES_BIG_DON, true, player);

							if (chara != nullptr)
								chara->ActBalloonBreak(player);

							enso->SubRollRemain(itr->roll_time);
						}
					}
					if (itr->notes_type == NOTES_KUSUDAMA)
					{
						if (kusudama->Sub() == true)
						{
						//	m_list_notes[player].erase(itr);
							
							//�S�v���C���[�̈�ԍŏ��̂������܂��폜����
							for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
							{
								for (auto itr = m_list_notes[i].begin(); itr != m_list_notes[i].end(); itr++)
								{
									if (itr->notes_type == NOTES_KUSUDAMA)
									{
										m_list_notes[i].erase(itr);
										m_roll_flag[i] = false;
										break;
									}
								}
							}

							Audio::Start(se_KUSUDAMA);
							enso->SubRollRemain(itr->roll_time);
						}
						
					
						//chara->ActBalloonBreak();

					}

					return;
				}
			}
		}

		else if ((itr->notes_type == NOTES_DON || itr->notes_type == NOTES_BIG_DON) && input == DON ||
			(itr->notes_type == NOTES_KA || itr->notes_type == NOTES_BIG_KA) && input == KA || 
			(itr->notes_type == NOTES_BOMB_DON || itr->notes_type == NOTES_BOMB_KA))
		{

			//����̂���
			// �ǔ��肩�璲�ׂĂ����B
			// �ŏ����珇�Ԃɒ��ׂĂ����A���ʂɏ������Ԃ𑝂₳�Ȃ��悤��
			// ���莞�Ԃ̍������̂��΃��[�v���I�����A����Ɉڂ�B
			// 
			//�܂��m�[�c���ǔ���ɐG��Ă��邩��������B
			//�G��Ă��Ȃ���ΉɁA
			//����ł��G��Ă��Ȃ���Εs�͈͂ɓ����Ă��邩���ׂ�B

			bool big = false;
			if (itr->notes_type == NOTES_BIG_DON || itr->notes_type == NOTES_BIG_KA)
			{
				big = true;
			}

			//�͈͓�
			if (time >= -MusicGame::JUDGE_RANGE[HIT] && time <= MusicGame::JUDGE_RANGE[MISS])
			{
				if (abs(time) < MusicGame::JUDGE_RANGE[JUST])
					JudgeProcess(JUST,true,big,(E_NOTES_TYPE)itr->notes_type, player, time);
				else if (abs(time) < MusicGame::JUDGE_RANGE[HIT])
					JudgeProcess(HIT,true,big, (E_NOTES_TYPE)itr->notes_type, player, time);
				else if (abs(time) < MusicGame::JUDGE_RANGE[MISS])
					JudgeProcess(MISS,true,big, (E_NOTES_TYPE)itr->notes_type, player, time);

				//�v�f���폜
				itr = m_list_notes[player].erase(itr);

				return;
			}

			if (time > MusicGame::JUDGE_RANGE[MISS])
			{
				//�܂��͂��Ȃ��m�[�c�����͔��肵�Ȃ�
				break;
			}
		}
	}

}

//void CObjNotes::Section(int measure,E_JUDGE judge,bool b_return)
//{
//	if (m_section_count == 0)return;
//
//	//�m�[�c�̏��ߐ��Ƃ��̋�Ԃ̏��ߐ��𒲂ׂāA�����ɂȂ�΋�Ԃ��ړ�����B
//	if (measure >= m_vec_section_measure[m_section_count].measure_count)
//	{
//		m_section_count++;
//
//		if (judge == MISS)
//		{
//
//		}
//		else if(b_return == false)
//		{
//
//		}
//		else
//		{
//
//		}
//	}
//
//}

/// <summary>
/// ������s���Ƃ��ɂ��鏈�����A�����Ȃ��Ă����̂ł܂Ƃ߂��B
/// </summary>
/// <param name="judge"></param>
/// <param name="moji">�X���[����p�@�����o���Ȃ����߂ɒǉ��B</param>
/// <param name="big">�q�b�g�G�t�F�N�g�p�ɒǉ��B</param>
void CObjNotes::JudgeProcess(E_JUDGE judge, bool moji, bool big, E_NOTES_TYPE type, int player,float time)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjCombo* combo = (CObjCombo*)Objs::GetObj(OBJ_COMBO);
	CObjJudgeMoji* judgemoji = (CObjJudgeMoji*)Objs::GetObj(OBJ_JUDGE);
	CObjNormaGauge* gauge = (CObjNormaGauge*)Objs::GetObj(OBJ_GAUGE);
	CObjEnsoBattle* battle = (CObjEnsoBattle*)Objs::GetObj(OBJ_BATTLE);
	CObjScore* score = (CObjScore*)Objs::GetObj(OBJ_SCORE);
	CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);
	CObjFlyingNotes* flying = (CObjFlyingNotes*)Objs::GetObj(OBJ_FLYINGNOTES);
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);

	//���e���������������ꍇ
	if (MusicGame::g_mode == E_GAME_MODE::ENSO_BATTLE)
	{
		if (type == NOTES_BOMB_DON || type == NOTES_BOMB_KA)
		{
			combo->Reset(player);


			if (battle != nullptr)
			battle->SubLife(5);

			return;
		}
	}


	enso->m_enso[player].JudgeAdd(judge);
	
	enso->AddBranchJudge(judge,player);

	if (moji == true)
		judgemoji->Add(judge, big, player,time);

	switch (judge)
	{
	case JUST:
		combo->Add(player);
		if (score != nullptr)
		score->AddScore(enso->m_enso[player].m_score_add, player);
		lane->HitEffectStart(JUST, big,player);
		lane->LaneFlushStart(Yellow, player);
		if (flying != nullptr)
		flying->Add(type, false,player);
		if (gauge != nullptr)
		gauge->Add(judge,player);

		break;
	case HIT:
		combo->Add(player);
		if (score != nullptr)
		score->AddScore(enso->m_enso[player].m_score_add * 0.5f, player);
		lane->HitEffectStart(HIT, big, player);
		lane->LaneFlushStart(Yellow, player);
		if (flying != nullptr)
		flying->Add(type, false,player);
		if (gauge != nullptr)
		gauge->Add(judge,player);
		break;
	case MISS:
		combo->Reset(player);
		if (gauge != nullptr)
		gauge->Add(judge,player);

		if (battle != nullptr)
			battle->SubLife(1);
		break;
	case ROLL:
		if (score != nullptr)
		score->AddScore(100, player);
		lane->LaneFlushStart(Yellow, player);
		if (flying != nullptr)
		flying->Add(type, false,player);
		break;
	}

	if (dan != nullptr)
	{
		dan->AddSongJudge(judge);
		dan->Update();
	}
}

//�Ԃɂ���m�[�c�폜
void CObjNotes::BranchStart(E_BRANCH branch, int start, int end, int player)
{
	for (auto itr = m_list_notes[player].begin(); itr != m_list_notes[player].end(); itr++)
	{
		if (itr->measure >= start)
		{
			while (1)
			{
				if (itr->measure >= end || itr == m_list_notes[player].end())
				{
					return;
				}
				//����ȊO�̃u�����`�̃m�[�c���폜����
				if (itr->branch != BRANCH_NONE && itr->branch != branch)
					itr = m_list_notes[player].erase(itr);
				else
					itr++;
			}
		}
	}
}

//�Ȃ�ƂȂ����߂Ă݂�B
float CObjNotes::AINextJudgeTiming()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	int notes_count = enso->m_enso[0].m_fumen.notes_count[BRANCH_NONE] + enso->m_enso[0].m_fumen.notes_count[BRANCH_TATSUJIN];
	notes_count *= 0.1f;
	int judge_notes = enso->m_enso[0].m_score_data.judge[JUST] + enso->m_enso[0].m_score_data.judge[HIT] + enso->m_enso[0].m_score_data.judge[MISS];

	int i;
	std::random_device rnd;
	for (int i = MISS; i > JUST; i--)
	{
		int percent = 0;
		int offset = 0;

		if (i == JUST || i == HIT)offset = notes_count * 0.5f;

		if (judge_notes > 0)
		{
			percent = (float)(enso->m_enso[0].m_score_data.judge[i] + offset) / (float)(judge_notes + notes_count) * 100.0f;
		}
		m_notes_remain_num.Draw(percent, NUM_POS.x, NUM_POS.y + i * 64, NUM_WIDTH);
		int val = rnd() % 100;

		//n%�̊m���Ń��[�v�𔲂���
		if (val < percent)
		{
			return (rnd() % 2) == 0 ? -MusicGame::JUDGE_RANGE[i-1] : MusicGame::JUDGE_RANGE[i-1];
		}
	}
	return 0.0f;

}