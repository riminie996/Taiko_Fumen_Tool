#include "CObjHeya.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL/WinInputs.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/Userdata.h"


#define SONG_BAR(num) MusicGame::SongSelect::g_vec_all_fumen_bar[m_vec_songselect_fumen[num]]

//������
void CObjHeya::Init()
{

	//�t���O��true�ɂ��Ƃ�
	m_ani_bar_pos_x.Start();
	m_ani_bar_pos_y.Start();

	//�o�[�ʒu���A�j���[�V�����t�@�C������ݒ�
	for (int i = 0; i < BAR_AMOUNT; i++)
	{
		m_bar_pos[i].x = m_ani_bar_pos_x.GetValue();
		m_bar_pos[i].y = m_ani_bar_pos_y.GetValue();
		m_ani_bar_pos_x.Action();
		m_ani_bar_pos_y.Action();
	}

	m_ani_selected_bar.LoadData("Animation/SongSelect/SelectedBar");
	m_ani_not_selected_bar.LoadData("Animation/SongSelect/SelectedBar");

	m_vec_heya_item.resize((int)E_HEYA_ITEM::ITEM_Count);

	m_ct_bar_move = { CCounter(0.0f,0.0f,1.0f,STOP) };


	m_move_direction = 0;

	m_fade_in.m_color = Color::Black;
	m_fade_in.m_fade_type = CFIFO::FadeIn;
	m_fade_in.Start();


	//	m_before_background_color = m_vec_songselect_fumen[m_now_select].genre;

	m_ani_cursor_effect_loop.Start();


	m_now_select = 0;

	m_first_action = false;
	Audio::Start(bgm_HEYA);
	m_phase = E_HEYA_PHASE::SELECT;

	MusicGame::SongSelect::g_tex_box_overlay.m_opacity = 0.5f;
}
//�i�s
void CObjHeya::Action()
{

	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	if (m_first_action == false)
	{
		m_first_action = true;

	}


	m_ani_cursor_decide_yellow.Action();
	m_ani_cursor_decide_white.Action();
	m_ani_cursor_effect_loop.ActionLoop();

	CObjEnsoOption* option = (CObjEnsoOption*)Objs::GetObj(OBJ_OPTION_SELECT);

	//���͂��󂯕t���Ȃ�
	if (m_phase == E_HEYA_PHASE::EXIT)return;

	//�o�[���ړ���
	if (m_move_direction != 0)
	{
		//�l�����炷
		m_ct_bar_move.Add((1.0f / BAR_MOVE_TIME) * (1.0f / FRAME_FPS));
		m_ani_selected_bar.Add(-SELECTED_BAR_ANIME_SPEED);

		//�ړ���ɒl��0�ɂȂ�����B�B
		if (m_ct_bar_move.GetMaxReached())
		{
			if (m_move_direction == -1)
			{
				PreviousSong();
			}
			else if (m_move_direction == 1)
			{
				NextSong();
			}
			m_move_direction = 0;
			m_ct_bar_move.Reset();

		}
	}

	//�o�[���ړ����ĂȂ����̂�
	if (m_move_direction == 0)
	{
		m_ani_selected_bar.Add(SELECTED_BAR_ANIME_SPEED);

	}
	else if (m_move_direction != 0)
	{

	}


	//���͂�����
	if (m_move_direction != 0 ||
		option != nullptr)return;

	//�h����
	if (m_ani_selected_bar.GetMaxReached())
	{
		if (system->GetInput(LEFT_DON, 0) || system->GetInput(RIGHT_DON, 0))
		{
			Decide();
		}
	}
	//�J�b��
	if (system->GetInput(LEFT_KA, 0))
	{
		SelectLeft();
		Audio::Start(se_KA);
	}
	//�J�b�E
	if (system->GetInput(RIGHT_KA, 0))
	{
		SelectRight();
		Audio::Start(se_KA);
	}

}


//�`��
void CObjHeya::Draw()
{
	Draw::Draw(tex_HEYA_BG, 0, 0);

	for (int i = 0; i < BAR_AMOUNT; i++)
	{
		float x = m_bar_pos[i].x;
		float y = m_bar_pos[i].y;

		float x_anime = 0.0f;
		float y_anime = 0.0f;

		//�o�[�̈ړ����������Z
		if (i >= 1 && i < MusicGame::SONGSELECT_BAR_AMOUNT - 1)
		{
			//
			x_anime = (m_bar_pos[i - m_move_direction].x - x) * m_ct_bar_move.NowValue;
			y_anime = (m_bar_pos[i - m_move_direction].y - y) * m_ct_bar_move.NowValue;
		}
		x += x_anime;
		y += y_anime;

		int num = m_now_select - BAR_SHOW_AMOUNT + i;

		if (num >= (int)m_vec_heya_item.size())
		{
			num -= m_vec_heya_item.size();
		}
		if (num < 0)
		{
			num += m_vec_heya_item.size();
		}

		wstring str = L"";//MusicGame::StringToWString(SONG_BAR(num).title);
		wstring substr = L"";//MusicGame::StringToWString(SONG_BAR(num).title);

		switch ((E_HEYA_ITEM)num)
		{
			//�V�X�e��
		case E_HEYA_ITEM::MAX_SONG:
			str = L"�����ׂ�Ȑ�";
			break;
		case E_HEYA_ITEM::AUTOPLAY_ROLLSPEED:
			str = L"�I�[�g�v���C���̘A�ő��x";
			break;
		case E_HEYA_ITEM::PLAYER_AMOUNT:
			str = L"�����Ԑl��";
			break;
		case E_HEYA_ITEM::SCORE_SAVE:
			str = L"�X�R�A�f�[�^�ۑ�";
			break;
		case E_HEYA_ITEM::SCORE_DELETE:
			str = L"�X�R�A�f�[�^�폜";
			break;
		case E_HEYA_ITEM::DEMO_PLAY:
			str = L"�y�Ȃ̃v���r���[���Đ�";
			break;
			//�f�[�^
		case E_HEYA_ITEM::PANEL_SHOW:
			str = L"�������уp�l����\��";
			break;
		case E_HEYA_ITEM::AUTOPLAY_1P:
			str = L"�I�[�g�v���C(1P)";
			break;
		case E_HEYA_ITEM::AUTOPLAY_2P:
			str = L"�I�[�g�v���C(2P)";
			break;
		case E_HEYA_ITEM::DEFAULT_DIFFCULTY:
			str = L"�f�t�H���g�̂ނ�������";
			break;
		case E_HEYA_ITEM::DEFAULT_OPTION:
			str = L"�f�t�H���g�̉��t�I�v�V����";
			break;
		case E_HEYA_ITEM::JUDGEPANEL_SHOWING:
			str = L"���萔�p�l����\��";
			break;
		case E_HEYA_ITEM::JUDGESEC_SHOWING:
			str = L"���莞�ɕb����\��";
			break;
			//���ǂ�
		case E_HEYA_ITEM::EXIT:
			str = L"���ǂ�";
			break;
		}
		//�^�񒆂̃o�[
		if (i == BAR_SHOW_AMOUNT)
		{
			CursorDraw(x, y);
			//�^�񒆂̃o�[
			SelectBarDraw(num, x, y);

			Font::StrCenterDraw(str.c_str(), x, y + m_ani_selected_bar.GetValue("TitleMove").y, TITLE_FONT_SIZE, ColorA::White);

			switch ((E_HEYA_ITEM)num)
			{
				//�V�X�e��
			case E_HEYA_ITEM::MAX_SONG:
				substr = to_wstring(USER_DATA->m_max_song);
				break;
			case E_HEYA_ITEM::AUTOPLAY_ROLLSPEED:
				substr = to_wstring(USER_DATA->m_auto_play_roll);
				break;
			case E_HEYA_ITEM::PLAYER_AMOUNT:
				substr = to_wstring(USER_DATA->m_player_amount);
				break;
			case E_HEYA_ITEM::SCORE_SAVE:
				substr = USER_DATA->m_save_score == true ? L"����" : L"���Ȃ�";
				break;
			case E_HEYA_ITEM::SCORE_DELETE:
			//	substr = L"�X�R�A�f�[�^�폜";
				break;
			case E_HEYA_ITEM::DEMO_PLAY:
				substr = USER_DATA->m_bgm_demo_play == true ? L"����" : L"���Ȃ�";
				break;
				//�f�[�^
			case E_HEYA_ITEM::PANEL_SHOW:
				substr = USER_DATA->m_panel_showing == true ? L"����" : L"���Ȃ�";
				break;
			case E_HEYA_ITEM::AUTOPLAY_1P:
				substr = USER_DATA->m_auto_play[0] == true ? L"����" : L"���Ȃ�";
				break;
			case E_HEYA_ITEM::AUTOPLAY_2P:
				substr = USER_DATA->m_auto_play[1] == true ? L"����" : L"���Ȃ�";
				break;
			case E_HEYA_ITEM::DEFAULT_DIFFCULTY:
				switch (USER_DATA->m_default_diffculty)
				{
				case DIFF_EASY:
					substr = L"���񂽂�";
					break;
				case DIFF_NORMAL:
					substr = L"�ӂ�";
					break;
				case DIFF_HARD:
					substr = L"�ނ�������";
					break;
				case DIFF_ONI:
					substr = L"����";
					break;
				case DIFF_EDIT:
					substr = L"����+���ɗ�";
					break;

				}
				break;
			case E_HEYA_ITEM::DEFAULT_OPTION:
				substr = L"�ݒ肷��";
				break;
			case E_HEYA_ITEM::JUDGEPANEL_SHOWING:
				substr = USER_DATA->m_judge_showing == true ? L"����" : L"���Ȃ�";
				break;
			case E_HEYA_ITEM::JUDGESEC_SHOWING:
				substr = USER_DATA->m_judge_sec_showimg == true ? L"����" : L"���Ȃ�";
				break;
				//���ǂ�
			case E_HEYA_ITEM::EXIT:
				substr = L"�G���g���[��ʂɖ߂�܂�";
				break;
			}

			Font::StrCenterDraw(substr.c_str(), x, y+ 45, TITLE_FONT_SIZE, ColorA::White);
		}
		//�㉺�ɕ`�悳���o�[
		else
		{
			//�^�񒆂̃o�[
			NotSelectFolderDraw(num, x, y);
			Font::StrCenterDraw(str.c_str(), x, y + m_ani_not_selected_bar.GetValue("TitleMove").y, TITLE_FONT_SIZE, ColorA::White);
		}

	
	//	swprintf_s(wcr, L"%s", str.c_str());
		

	}

	m_fade_in.ActionDraw();
}

void CObjHeya::Decide()
{
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
			Audio::Start(se_DON);
	
	switch (m_phase)
	{
	case E_HEYA_PHASE::SELECT:
		switch ((E_HEYA_ITEM)m_now_select)
		{
		case E_HEYA_ITEM::EXIT:
			Save::Seve();
			m_phase = E_HEYA_PHASE::EXIT;
			system->HeyaEnd();
			system->EntryStart();
			break;
		case E_HEYA_ITEM::MAX_SONG:
			m_phase = E_HEYA_PHASE::MAX_SONG;
			break;
		case E_HEYA_ITEM::AUTOPLAY_ROLLSPEED:
			m_phase = E_HEYA_PHASE::AUTOPLAY_ROLLSPEED;
			break;
		case E_HEYA_ITEM::PLAYER_AMOUNT:
			m_phase = E_HEYA_PHASE::PLAYER_AMOUNT;
			break;
		case E_HEYA_ITEM::SCORE_SAVE:
			USER_DATA->m_save_score = USER_DATA->m_save_score == true ? false : true;
			break;
		case E_HEYA_ITEM::SCORE_DELETE:
			break;
		case E_HEYA_ITEM::PANEL_SHOW:
			USER_DATA->m_panel_showing = USER_DATA->m_panel_showing == true ? false : true;
			break;
		case E_HEYA_ITEM::AUTOPLAY_1P:
			USER_DATA->m_auto_play[0] = USER_DATA->m_auto_play[0] == true ? false : true;
			break;
		case E_HEYA_ITEM::AUTOPLAY_2P:
			USER_DATA->m_auto_play[1] = USER_DATA->m_auto_play[1] == true ? false : true;
			break;
		case E_HEYA_ITEM::DEFAULT_DIFFCULTY:
			m_phase = E_HEYA_PHASE::DEFAULT_DIFFCULTY;
			break;
		case E_HEYA_ITEM::DEFAULT_OPTION:
		{
			CObjEnsoOption* option = new CObjEnsoOption(&USER_DATA->m_default_option, 0);
			Objs::InsertObj(option, OBJ_OPTION_SELECT, PRIO_SONGSELECT_OPTION);
		}
			break;
		case E_HEYA_ITEM::JUDGEPANEL_SHOWING:
			USER_DATA->m_judge_showing = USER_DATA->m_judge_showing == true ? false : true;
			break;
		case E_HEYA_ITEM::JUDGESEC_SHOWING:
			USER_DATA->m_judge_sec_showimg = USER_DATA->m_judge_sec_showimg == true ? false : true;
			break;
		case E_HEYA_ITEM::DEMO_PLAY:
			USER_DATA->m_bgm_demo_play = USER_DATA->m_bgm_demo_play == true ? false : true;
			break;
		}
		break;
	case E_HEYA_PHASE::MAX_SONG:
	case E_HEYA_PHASE::AUTOPLAY_ROLLSPEED:
	case E_HEYA_PHASE::PLAYER_AMOUNT:
	case E_HEYA_PHASE::SCORE_DELETE:
	case E_HEYA_PHASE::DEFAULT_DIFFCULTY:
	case E_HEYA_PHASE::DEFAULT_OPTION:
		m_phase = E_HEYA_PHASE::SELECT;
		break;
	default:
		break;
	}
}

void CObjHeya::SelectLeft()
{
	switch (m_phase)
	{
	case E_HEYA_PHASE::SELECT:
		m_move_direction = -1;
		break;
	case E_HEYA_PHASE::MAX_SONG:
		USER_DATA->m_max_song--;
		break;
	case E_HEYA_PHASE::AUTOPLAY_ROLLSPEED:
		USER_DATA->m_auto_play_roll--;
		break;
	case E_HEYA_PHASE::PLAYER_AMOUNT:
		USER_DATA->m_player_amount--;
		break;
	case E_HEYA_PHASE::SCORE_DELETE:

		break;
	case E_HEYA_PHASE::DEFAULT_DIFFCULTY:
		USER_DATA->m_default_diffculty--;
		break;
	case E_HEYA_PHASE::DEFAULT_OPTION:
		break;
	default:
		break;
	}
}

void CObjHeya::SelectRight()
{
	switch (m_phase)
	{
	case E_HEYA_PHASE::SELECT:
		m_move_direction = +1;
		break;
	case E_HEYA_PHASE::MAX_SONG:
		USER_DATA->m_max_song++;
		break;
	case E_HEYA_PHASE::AUTOPLAY_ROLLSPEED:
		USER_DATA->m_auto_play_roll++;
		break;
	case E_HEYA_PHASE::PLAYER_AMOUNT:
		USER_DATA->m_player_amount++;
		break;
	case E_HEYA_PHASE::SCORE_DELETE:

		break;
	case E_HEYA_PHASE::DEFAULT_DIFFCULTY:
		USER_DATA->m_default_diffculty++;
		break;
	case E_HEYA_PHASE::DEFAULT_OPTION:
		break;
	default:
		break;
	}
}

void CObjHeya::NotSelectFolderDraw(int bar_num, int x, int y)
{
	//�o�[�����k����X�P�[��(CAnime3�ɒ�`����Ă���)
	float center_scale_y = m_ani_not_selected_bar.GetValue("BarCenterScale").scale_y;
	float center_overlay_scale_y = m_ani_not_selected_bar.GetValue("BarOverlayScale").scale_y;
	int yOffset = (RECT_BAR_CENTER.m_height * center_scale_y) / 2.0f + (RECT_BAR_TOP.m_height / 2.0f);
	int color = bar_num == (int)E_HEYA_ITEM::EXIT ? tex_BOX_CLOSE : tex_BOX_NONE + GENRE_GAMEMUSIC;
	int overlay_offset = (float)RECT_OVERLAY_CENTER.m_height * center_overlay_scale_y;

	//�^�񒆂̊g�嗦��ύX
	Draw::SetScaleY(color, center_scale_y);
	Draw::CenterDraw(color, x, y, RECT_BAR_CENTER);
	MusicGame::SongSelect::g_tex_box_overlay.m_scale_y = center_overlay_scale_y;
	MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y, RECT_OVERLAY_CENTER, ref_Center, ref_Bottom);
	MusicGame::SongSelect::g_tex_box_overlay.m_scale_y = center_overlay_scale_y;
	MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y, RECT_OVERLAY_CENTER, ref_Center, ref_Top);

	//�g�嗦�����Ƃɖ߂��āA�㉺��`�悷��
	Draw::SetScaleY(color, 1.0f);
	Draw::CenterDraw( color, x, y - yOffset, RECT_BAR_TOP);
	Draw::CenterDraw(color, x, y + yOffset, RECT_BAR_BOTTOM);
	MusicGame::SongSelect::g_tex_box_overlay.m_scale_y = 1.0f;
	MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y - overlay_offset, RECT_OVERLAY_CENTER, ref_Center, ref_Bottom);
	MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y + overlay_offset, RECT_OVERLAY_CENTER, ref_Center, ref_Top);

}
void CObjHeya::SelectBarDraw(int bar_num, int x, int y)
{

	float center_overlay_up_scale_y = m_ani_selected_bar.GetValue("BarOverlayScale").scale_y;
	float center_overlay_down_scale_y = m_ani_selected_bar.GetValue("BarOverlayScale").scale_y;
	float center_scale_y = m_ani_selected_bar.GetValue("BarCenterScale").scale_y;
	int yOffset = (RECT_BAR_CENTER.m_height * center_scale_y) / 2.0f + (RECT_BAR_TOP.m_height / 2.0f);
	int overlay_c_up_height = (float)RECT_OVERLAY_CENTER.m_height * center_overlay_up_scale_y;
	int overlay_c_down_height = (float)RECT_OVERLAY_CENTER.m_height * center_overlay_down_scale_y;

	int tex_id = tex_BOX_NONE;
	int color = bar_num == (int)E_HEYA_ITEM::EXIT ? tex_BOX_CLOSE : tex_BOX_NONE + GENRE_GAMEMUSIC;


	//�^�񒆂̊g�嗦��ύX
	Draw::SetScaleY(color, center_scale_y);
	Draw::CenterDraw(color, x, y, RECT_BAR_CENTER);
	MusicGame::SongSelect::g_tex_box_overlay.m_scale_y = center_overlay_up_scale_y;
	MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y, RECT_OVERLAY_CENTER, ref_Center, ref_Bottom);
	MusicGame::SongSelect::g_tex_box_overlay.m_scale_y = center_overlay_down_scale_y;
	MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y, RECT_OVERLAY_CENTER, ref_Center, ref_Top);

	//�g�嗦�����Ƃɖ߂��āA�㉺��`�悷��
	Draw::SetScaleY(color, 1.0f);
	Draw::CenterDraw(color, x, y - yOffset, RECT_BAR_TOP);
	Draw::CenterDraw(color, x, y + yOffset, RECT_BAR_BOTTOM);
	MusicGame::SongSelect::g_tex_box_overlay.m_scale_y = 1.0f;
	MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y + overlay_c_up_height, RECT_OVERLAY_CENTER, ref_Center, ref_Bottom);
	MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y + overlay_c_down_height, RECT_OVERLAY_CENTER, ref_Center, ref_Top);




}

void CObjHeya::PreviousSong()
{
	m_now_select--;

	if (m_now_select < 0)
		m_now_select = m_vec_heya_item.size() - 1;
}

void CObjHeya::NextSong()
{
	m_now_select++;

	if (m_now_select >= m_vec_heya_item.size())
		m_now_select = 0;
}
void CObjHeya::CursorDraw(int x, int y)
{

	float center_scale_y = m_ani_selected_bar.GetValue("Cursor").scale_y;
	int yOffset = (RECT_CURSOR_CENTER.m_height * center_scale_y) / 2.0f + (RECT_CURSOR_TOP.m_height / 2.0f);
	float opacity = m_ani_selected_bar.GetValue("Cursor").opacity;

	if (m_ani_cursor_decide_yellow.GetStart())
	{
		opacity *= m_ani_cursor_decide_yellow.GetValue().opacity;
	}
	float effect_opacity = opacity * m_ani_cursor_effect_loop.GetValue().opacity;

	//���F���J�[�\����`��
	Draw::SetOpacity(tex_SONGSELECT_CURSOR, opacity);

	//�^�񒆂̊g�嗦��ύX
	Draw::SetScaleY(tex_SONGSELECT_CURSOR, center_scale_y);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y, RECT_CURSOR_CENTER);

	//�G�t�F�N�g�`��
	RECT_F rect_center = RECT_CURSOR_CENTER;
	rect_center.m_y += RECT_CURSOR_YELLOW.m_height;
	Draw::SetOpacity(tex_SONGSELECT_CURSOR, effect_opacity);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y, rect_center);

	RECT_F rect_top = RECT_CURSOR_TOP;
	RECT_F rect_bottom = RECT_CURSOR_BOTTOM;
	Draw::SetOpacity(tex_SONGSELECT_CURSOR, opacity);

	//�g�嗦�����Ƃɖ߂��āA�㉺��`�悷��
	Draw::SetScaleY(tex_SONGSELECT_CURSOR, 1.0f);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y - yOffset, rect_top);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y + yOffset, rect_bottom);

	//�G�t�F�N�g�`��
	Draw::SetOpacity(tex_SONGSELECT_CURSOR, effect_opacity);

	rect_top.m_y += RECT_CURSOR_YELLOW.m_height;
	rect_bottom.m_y += RECT_CURSOR_YELLOW.m_height;
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y - yOffset, rect_top);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y + yOffset, rect_bottom);

	//�����J�[�\����`��
	Draw::SetOpacity(tex_SONGSELECT_CURSOR, m_ani_cursor_decide_white.GetValue().opacity);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y, RECT_CURSOR_WHITE);

}

