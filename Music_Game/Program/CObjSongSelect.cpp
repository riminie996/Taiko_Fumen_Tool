#include "CObjSongSelect.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL/WinInputs.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/Userdata.h"
#include "GameL/MultiThread.h"

#define SONG_BAR(num) MusicGame::SongSelect::g_vec_all_fumen_bar[m_vec_songselect_fumen[num]]

CObjSongSelect::~CObjSongSelect()
{
//	GameLoop::DeleteThread(thr_load_music);

}
//初期化

void CObjSongSelect::Init()
{
	tex_songselect_crown.LoadTexture("Graphics/2_SongSelect/crown.png");
	tex_songselect_rank.LoadTexture("Graphics/2_SongSelect/rank.png");


	//フラグをtrueにしとく
	m_ani_bar_pos_x.Start();
	m_ani_bar_pos_y.Start();

	//バー位置をアニメーションファイルから設定
	for (int i = 0; i < BAR_AMOUNT; i++)
	{
		m_ani_open_bar_move_in[i].LoadData("Animation/SongSelect/FolderOpenBarMoveIn");
		m_ani_open_bar_move_out[i].LoadData("Animation/SongSelect/FolderOpenBarMoveOut");
		m_bar_pos[i].x = m_ani_bar_pos_x.GetValue();
		m_bar_pos[i].y = m_ani_bar_pos_y.GetValue();
		m_ani_bar_pos_x.Action();
		m_ani_bar_pos_y.Action();
	}

	m_ani_selected_bar.LoadData("Animation/SongSelect/SelectedBar");
	m_ani_not_selected_bar.LoadData("Animation/SongSelect/SelectedBar");


	for (auto itr = MusicGame::SongSelect::g_vec_folder_bar.begin(); itr != MusicGame::SongSelect::g_vec_folder_bar.end(); itr++)
	{
		m_vec_songselect_fumen.push_back(itr->id);
	}


	//キーフラグの初期化
	for (int i = 0; i < MusicGame::TAIKO_FLUSH_TYPE; i++)
		m_key_flag[i] = false;
	m_key_flag_skip[0] = false;
	m_key_flag_skip[1] = false;

	m_ct_bar_move = { CCounter(0.0f,0.0f,1.0f,STOP) };
	m_ct_bar_scale_y_delay = { CTimeCounter(0,BAR_MOVE_SCALE_DELAY,1) };

	
	m_move_direction = 0;
	m_ani_folder_open_in_scale_x.Start();

	m_fade_in.m_color = Color::Black;
	m_fade_in.m_fade_type = CFIFO::FadeIn;
	m_fade_in.Start();

	SongSelectBgmStart();
	m_bgm_play_flag = false;
	m_demo_play_flag = true;
	m_demo_load_success = false;

	m_ani_background_scroll.Start();

//	m_before_background_color = m_vec_songselect_fumen[m_now_select].genre;

	m_ani_edit_score_fade.Start();
	m_ani_cursor_effect_loop.Start();

	m_ct_open_bar_move_delay = { CTimeCounter(0,MusicGame::SongSelect::BAR_OPEN_IN_DELAY + MusicGame::SongSelect::BAR_OPEN_INTERVAL * BAR_SHOW_AMOUNT,1) };

	m_enso_option = USER_DATA->m_default_option;


	m_now_select = 0;
	m_open_folder = -1;

	m_phase = PHASE_SONG_SELECT;

	m_first_action = false;


	m_ani_ura.LoadData("Animation/SongSelect/ScorePanelUra");
	m_ani_ura.Start();

	m_fadeout_to_entry.m_fade_type = CFIFO::FadeOut;
	m_fadeout_to_entry.m_color = Color::Black;

	thr_load_music = new thread(&CObjSongSelect::SubThrActionDraw, this);
///GameLoop::AddThread(thr_load_music);
}

void CObjSongSelect::Delete()
{
	thr_load_music->join();
	delete thr_load_music;
}
//進行
void CObjSongSelect::Action()
{
	m_ani_ura.ActionLoop();
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	if (m_first_action == false)
	{
		m_first_action = true;
		FavoliteFolderSet();
	}

	m_ct_bgm_loop_start.Action();
	m_ani_open_title_opacity.Action();
	m_ani_background_scroll.ActionLoop();
	m_ani_background_fade.Action();
	m_ani_edit_score_fade.ActionLoop();
	m_ani_cursor_decide_yellow.Action();
	m_ani_cursor_decide_white.Action();
	m_ani_cursor_effect_loop.ActionLoop();
	m_ct_open_bar_move_delay.Action();

	for (int i = 0; i < BAR_AMOUNT; i++)
	{
		m_ani_open_bar_move_out[i].Action();
		m_ani_open_bar_move_in[i].Action();
	}
	if (m_ct_open_bar_move_delay.GetProgress())
	{
		for (int i = 0; i < BAR_SHOW_AMOUNT; i++)
		{
			int up = i;
			int down = BAR_AMOUNT - 1 - i;

			if (!m_ani_open_bar_move_out[up].GetStart() && m_ct_open_bar_move_delay.NowValue >= MusicGame::SongSelect::BAR_OPEN_OUT_DELAY + i * MusicGame::SongSelect::BAR_OPEN_INTERVAL)
				m_ani_open_bar_move_out[up].Start();

			if (!m_ani_open_bar_move_out[down].GetStart() && m_ct_open_bar_move_delay.NowValue >= MusicGame::SongSelect::BAR_OPEN_OUT_DELAY + i * MusicGame::SongSelect::BAR_OPEN_INTERVAL)
				m_ani_open_bar_move_out[down].Start();

			up = BAR_SHOW_AMOUNT - 1 - i;
			down = BAR_SHOW_AMOUNT + i;

			if (!m_ani_open_bar_move_in[up].GetStart() && m_ct_open_bar_move_delay.NowValue >= MusicGame::SongSelect::BAR_OPEN_IN_DELAY + i * MusicGame::SongSelect::BAR_OPEN_INTERVAL)
				m_ani_open_bar_move_in[up].Start();

			if (!m_ani_open_bar_move_in[down].GetStart() && m_ct_open_bar_move_delay.NowValue >= MusicGame::SongSelect::BAR_OPEN_IN_DELAY + i * MusicGame::SongSelect::BAR_OPEN_INTERVAL)
				m_ani_open_bar_move_in[down].Start();
		}
	}

	if (m_ct_bgm_loop_start.GetEndValueReached() && m_bgm_loop_flag == true)
	{
		m_bgm_loop_flag = false;
		Audio::Start(bgm_SONGSELECT);
	}

	if (m_phase == PHASE_DECIDE)return;
	m_ani_songselect_fadeout.Action();

	//バーが移動中
	if (m_move_direction != 0)
	{
		//値を減らす
		m_ct_bar_move.Add((1.0f / BAR_MOVE_TIME) * (1.0f / FRAME_FPS));
		m_ani_selected_bar.Add(-SELECTED_BAR_ANIME_SPEED);

		//移動後に値が0になったら。。
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
			m_ct_bar_scale_y_delay.Start(0, BAR_MOVE_SCALE_DELAY, 1);


		}
	}

	//バーが移動してない時のみ
	if (m_move_direction == 0)
	{
		m_ct_bar_scale_y_delay.Action();
		if (m_ct_bar_scale_y_delay.GetEndValueReached())
		{
			m_ani_selected_bar.Add(SELECTED_BAR_ANIME_SPEED);
		}

		if (SONG_BAR(m_now_select).bar_type == MusicGame::SongSelect::BAR_FOLDER)
		{
			if (m_bgm_play_flag == true)
			{
				SongSelectBgmStart();
				m_bgm_play_flag = false;
			}


			m_demo_play_flag = true;
			m_demo_load_success = false;
		}
		else if (SONG_BAR(m_now_select).bar_type == MusicGame::SongSelect::BAR_FUMEN)
		{
			//曲選択BGMを止める
			Audio::Stop(bgm_IN);
			Audio::Stop(bgm_SONGSELECT);
			m_bgm_play_flag = true;



			if (m_demo_load_success == true && m_demo_play_flag == true)
			{
				m_demo_play_flag = false;
				Audio::Start(bgm_MUSIC, SONG_BAR(m_now_select).demo_start);
			}
		}


	}
	else if (m_move_direction != 0 && m_demo_play_flag == false)
	{
		Audio::Stop(bgm_MUSIC);
		m_demo_load_success = false;
		m_demo_play_flag = true;
	}

	m_ani_folder_open_out_scale_x.Action();
	m_ani_folder_open_in_scale_x.Action();

	if (m_ani_folder_open_out_scale_x.GetEnd())
	{
		m_ani_folder_open_out_scale_x.Start();
		m_ani_folder_open_out_scale_x.End();
		m_ani_folder_open_in_scale_x.Start();

		int select = SONG_BAR(m_now_select).id;

		if (SONG_BAR(m_now_select).bar_type == MusicGame::SongSelect::BAR_FOLDER)
		{
			FolderClose();
			//他のフォルダーを閉じてから開くフォルダにカーソルを合わせて開く
			m_now_select = select;//閉じたのでフォルダーにカーソルを合わせる
			FolderOpen();
		}
		else if (SONG_BAR(m_now_select).bar_type == MusicGame::SongSelect::BAR_CLOSE)
		{
			FolderClose();
		}
	}

	if (m_fadeout_to_entry.GetEnd())
	{
		system->SongSelectEnd();
		system->EntryStart();
		return;
	}

	//入力を拒否
	if (m_move_direction != 0 || m_phase != PHASE_SONG_SELECT ||
		!m_ani_folder_open_in_scale_x.GetEnd() || m_ani_folder_open_out_scale_x.GetStart())return;

	//ドン左
	if (m_ani_selected_bar.GetMaxReached())
	{
		if (system->GetInput(LEFT_DON, 0) || system->GetInput(RIGHT_DON, 0))
		{
			Decide();
		}
	}
	//カッ左
	if (Input::GetVKey('D'))
	{
		if (m_key_flag[2] == true)
		{
			SelectLeft();
			Audio::Start(se_KA);
		}
		m_key_flag[2] = false;
	}
	else
		m_key_flag[2] = true;

	//カッ右
	if (Input::GetVKey('K'))
	{
		if (m_key_flag[3] == true)
		{
			SelectRight();
			Audio::Start(se_KA);
		}
		m_key_flag[3] = false;
	}
	else
		m_key_flag[3] = true;

	if (Input::GetVKey(VK_LCONTROL))
	{
		if (m_key_flag_skip[0] == true)
		{
			PreviousSkip();
			Audio::Start(se_SKIP);
		}
		m_key_flag_skip[0] = false;
	}
	else
		m_key_flag_skip[0] = true;

	if (Input::GetVKey(VK_RCONTROL))
	{
		if (m_key_flag_skip[1] == true)
		{
			NextSkip();
			Audio::Start(se_SKIP);
		}
		m_key_flag_skip[1] = false;
	}
	else
		m_key_flag_skip[1] = true;

	if (Input::GetVKey(VK_BACK))
	{
		m_phase = E_SONGSELECT_PHASE::PHASE_EXIT;
		Audio::Start(se_CANCEL);
		m_fadeout_to_entry.Start();
		Audio::Stop(bgm_MUSIC);
		Audio::Stop(bgm_SONGSELECT);
	}
}
void CObjSongSelect::ActionSub()
{

}

//描画
void CObjSongSelect::Draw()
{

	//スコアパネルの描画
	if (SONG_BAR(m_now_select).bar_type == MusicGame::SongSelect::BAR_FUMEN)
	{
		CObjScorePanel* panel = (CObjScorePanel*)Objs::GetObj(OBJ_SCOREPANEL);

		E_DIFFCULTY show_diff = (E_DIFFCULTY)USER_DATA->m_default_diffculty;

		if (show_diff == E_DIFFCULTY::DIFF_EDIT)
		{
			if (SONG_BAR(m_now_select).level[(int)E_DIFFCULTY::DIFF_EDIT] > 0)
				show_diff = (E_DIFFCULTY)m_ani_ura.GetValue(0).pattern;
			else
				show_diff = DIFF_ONI;
		}

		panel->Draw(show_diff, SONG_BAR(m_now_select).bestscore[(int)show_diff]);
	}
	//ステータスパネルの描画
	CObjStatusPanel* sta = (CObjStatusPanel*)Objs::GetObj(OBJ_STATUSPANEL);
	sta->Draw(STATUS_PANEL_POS, (E_DIFFCULTY)USER_DATA->m_default_diffculty);

	//テクスチャIDを使いまわしている以上、透明度をこっちで勝手に
	//変えられると厄介なので処理をすべて行わない。
	if (m_phase == PHASE_DECIDE)return;


	wchar_t wcr[64];
	float fadeout_opacity = m_ani_songselect_fadeout.GetValue();

	//フェードアウト用透明度処理
	for (int i = 0; i < GENRE_Count; i++)
	{
		Draw::SetOpacity(tex_BOX_NONE + i, fadeout_opacity);
	}
	Draw::SetOpacity(tex_BOX_CLOSE, fadeout_opacity);
	Draw::SetOpacity(tex_BOX_CLOSE_TEXT, fadeout_opacity);
	COLOR_A title_color = { 1.0f,1.0f,1.0f,fadeout_opacity };
	tex_songselect_crown.m_opacity = fadeout_opacity;
	tex_songselect_rank.m_opacity = fadeout_opacity;
	MusicGame::SongSelect::g_tex_box_overlay.m_opacity = fadeout_opacity * 0.5f;


	for (int i = 0; i < BAR_AMOUNT; i++)
	{
		float x = m_bar_pos[i].x;
		float y = m_bar_pos[i].y;

		float x_anime = 0.0f;
		float y_anime = 0.0f;
		float x_move = 0.0f;
		float y_move = 0.0f;

		//バーの移動距離を加算
		if (i >= 1 && i < MusicGame::SONGSELECT_BAR_AMOUNT - 1)
		{
			//
			x_anime = (m_bar_pos[i - m_move_direction].x - x) * m_ct_bar_move.NowValue;
			y_anime = (m_bar_pos[i - m_move_direction].y - y) * m_ct_bar_move.NowValue;
		}
		x += x_anime;
		y += y_anime;
		
		if (m_ct_open_bar_move_delay.GetProgress())
		{
			x_move += i < BAR_SHOW_AMOUNT ? -m_ani_open_bar_move_out[i].GetValue().x : m_ani_open_bar_move_out[i].GetValue().x;
			y_move += i < BAR_SHOW_AMOUNT ? -m_ani_open_bar_move_out[i].GetValue().y : m_ani_open_bar_move_out[i].GetValue().y;

			x_move += i < BAR_SHOW_AMOUNT ? m_ani_open_bar_move_in[i].GetValue().x : -m_ani_open_bar_move_in[i].GetValue().x;
			y_move += i < BAR_SHOW_AMOUNT ? m_ani_open_bar_move_in[i].GetValue().y : -m_ani_open_bar_move_in[i].GetValue().y;
		}

		int num = m_now_select - BAR_SHOW_AMOUNT + i;

		if (num >= (int)m_vec_songselect_fumen.size())
		{
			num -= m_vec_songselect_fumen.size();
		}
		if (num < 0)
		{
			num += m_vec_songselect_fumen.size();
		}

	
		//真ん中のバー
		if (i == BAR_SHOW_AMOUNT)
		{
			float scale_x = 1.0f;
			scale_x = m_ani_folder_open_in_scale_x.GetValue() * m_ani_folder_open_out_scale_x.GetValue();

			if (SONG_BAR(num).bar_type == MusicGame::SongSelect::BAR_CLOSE)
				Draw::SetScaleX(tex_BOX_CLOSE, scale_x);
			else// if (SONG_BAR(num).bar_type == MusicGame::SongSelect::BAR_FUMEN)
			{
				int color = GetBarColor(num);

				Draw::SetScaleX(tex_BOX_NONE + color, scale_x);
				MusicGame::SongSelect::g_tex_box_overlay.m_scale_x =  scale_x;
			}

			CursorDraw(x, y);

			switch (SONG_BAR(num).bar_type)
			{
			case MusicGame::SongSelect::BAR_FUMEN:
			{
				title_color.a *= m_ani_open_title_opacity.GetValue().opacity;

				//真ん中のバー
				SelectBarDraw(num, x, y);

				wstring str = MusicGame::StringToWString(SONG_BAR(num).title);
				swprintf_s(wcr, L"%s", str.c_str());
				Font::StrCenterDraw(wcr, x, y + m_ani_selected_bar.GetValue("TitleMove").y, TITLE_FONT_SIZE, title_color);

				DiffcultyBarDraw(BAR_DIFFCULTY_OFFSET.x + x_anime, BAR_DIFFCULTY_OFFSET.y + y_anime,num);

			}
			break;

			case MusicGame::SongSelect::BAR_FOLDER:
			{
				title_color.a *= m_ani_open_title_opacity.GetValue().opacity;
				SelectBarDraw(num, x, y);
				wstring str = MusicGame::StringToWString(SONG_BAR(num).title);
				swprintf_s(wcr, L"%s", str.c_str());
				Font::StrCenterDraw(wcr, x, y + m_ani_selected_bar.GetValue("TitleMove").y, TITLE_FONT_SIZE, title_color);
			}
			break;
			case MusicGame::SongSelect::BAR_CLOSE:
			{
				SelectBarDraw(num, x, y);
			}

			break;
			case MusicGame::SongSelect::BAR_RANDOM:
				break;
			default:
				break;
			}

			if (SONG_BAR(num).bar_type == MusicGame::SongSelect::BAR_CLOSE)
				Draw::SetScaleX(tex_BOX_CLOSE, 1.0f);
			else //if (m_vec_songselect_fumen[bar_num].bar_type == MusicGame::SongSelect::BAR_CLOSE)
			{
				Draw::SetScaleX(tex_BOX_NONE + SONG_BAR(num).genre, 1.0f);
				MusicGame::SongSelect::g_tex_box_overlay.m_scale_x = 1.0f;
			}

		}
		//上下に描画されるバー
		else
		{
			x += x_move;
			y += y_move;

			switch (SONG_BAR(num).bar_type)
			{
			case MusicGame::SongSelect::BAR_FUMEN:
			{
				//真ん中のバー
				NotSelectFolderDraw(num, x, y);

				wstring str = MusicGame::StringToWString(SONG_BAR(num).title);
				swprintf_s(wcr, L"%s", str.c_str());
				Font::StrCenterDraw(wcr, x, y, TITLE_FONT_SIZE, title_color);
			}
			break;

			case MusicGame::SongSelect::BAR_FOLDER:
			{
				NotSelectFolderDraw(num, x, y);

				wstring str = MusicGame::StringToWString(SONG_BAR(num).title);
				swprintf_s(wcr, L"%s", str.c_str());
				Font::StrCenterDraw(wcr, x, y, TITLE_FONT_SIZE, title_color);
			}
			break;
			case MusicGame::SongSelect::BAR_CLOSE:
			{
				NotSelectFolderDraw(num, x, y);
			}
			break;
			case MusicGame::SongSelect::BAR_RANDOM:
				break;
			default:
				break;
			}
		}
		


	}


	m_fade_in.ActionDraw();
	m_fadeout_to_entry.ActionDraw();
}

void CObjSongSelect::LoadDirectory(string path)
{//"./"

}

void CObjSongSelect::Decide()
{
	CObjSongSelectCharacter* chara = (CObjSongSelectCharacter*)Objs::GetObj(OBJ_SONGSELECT_CHARA);

	switch (m_phase)
	{
		//楽曲を選ぶ
	case PHASE_SONG_SELECT:
		switch (SONG_BAR(m_now_select).bar_type)
		{
		case MusicGame::SongSelect::BAR_FUMEN:
		{
			Audio::Start(se_DON);
			m_ani_songselect_fadeout.Start();
			m_phase = PHASE_DIFFCULTY_SELECT;
			CObjDiffcultySelect* diff = new CObjDiffcultySelect(GetBarColor(m_now_select));
			Objs::InsertObj(diff, OBJ_DIFFCULTY_SELECT, PRIO_SONGSELECT_DIFFCULTY);
			m_ani_cursor_decide_yellow.Start();
			m_ani_cursor_decide_white.Start();
			m_key_flag[0] = false;
			m_key_flag[1] = false;

			if (chara != nullptr)
				chara->Select();
		}
			break;
		case MusicGame::SongSelect::BAR_FOLDER:
		case MusicGame::SongSelect::BAR_CLOSE:
		{
			Audio::Start(se_DON);
			m_ani_folder_open_out_scale_x.Start();
			FolderOpenStart();
			m_ani_cursor_decide_yellow.Start();
			m_ani_cursor_decide_white.Start();
			break;
		}
		case MusicGame::SongSelect::BAR_RANDOM:
			break;
		}
		break;
	case PHASE_DIFFCULTY_SELECT:
	case PHASE_DIFFCULTY_SELECT_OPTION:
	case PHASE_DECIDE:
		break;

	}

}
 
void CObjSongSelect::SelectLeft()
{
	switch (m_phase)
	{
		//楽曲を選ぶ
	case PHASE_SONG_SELECT:
		m_move_direction = -1;
		m_ani_edit_score_fade.Start();
		break;
	case PHASE_DIFFCULTY_SELECT:
	case PHASE_DIFFCULTY_SELECT_OPTION:
	case PHASE_DECIDE:
		break;

	}
}

void CObjSongSelect::SelectRight()
{
	switch (m_phase)
	{
		//楽曲を選ぶ
	case PHASE_SONG_SELECT:
		m_move_direction = +1;
		m_ani_edit_score_fade.Start();
		break;
	case PHASE_DIFFCULTY_SELECT:
	case PHASE_DIFFCULTY_SELECT_OPTION:
	case PHASE_DECIDE:
		break;

	}
}

void CObjSongSelect::FolderOpen()
{
	if (SONG_BAR(m_now_select).bar_type != MusicGame::SongSelect::BAR_FOLDER)return;
	m_open_folder = SONG_BAR(m_now_select).id;

	m_vec_songselect_fumen.erase(m_vec_songselect_fumen.begin() + m_now_select);
	m_vec_songselect_fumen.insert(m_vec_songselect_fumen.begin() + m_now_select, MusicGame::SongSelect::g_vec_folder_fumen[m_open_folder].begin(), MusicGame::SongSelect::g_vec_folder_fumen[m_open_folder].end());

	m_now_select = m_open_folder;

	//とじるボックスにカーソルが合わさってしまうので次の曲へ移動する。
	NextSong();
}

//オープン中のフォルダにあるバーをすべて削除して、
//フォルダを再挿入する。
void CObjSongSelect::FolderClose()
{
	//開かれているフォルダがない
	if (m_open_folder == -1)return;

	int start = m_open_folder;
	int end = start + MusicGame::SongSelect::g_vec_folder_fumen[m_open_folder].size();
	m_vec_songselect_fumen.erase(m_vec_songselect_fumen.begin() + start, m_vec_songselect_fumen.begin() + end);
	m_vec_songselect_fumen.insert(m_vec_songselect_fumen.begin() + start, m_open_folder);
	m_vec_songselect_fumen.shrink_to_fit();
	m_now_select = m_open_folder;
	m_open_folder = -1;
}

void CObjSongSelect::NotSelectFolderDraw(int bar_num,int x,int y)
{
	float overlay_up = m_ani_not_selected_bar.GetValue("BarOverlayCenter").y;
	float overlay_down = m_ani_not_selected_bar.GetValue("BarOverlayCenter").y;
	float center_scale_y = m_ani_not_selected_bar.GetValue("BarCenterScale").scale_y;
	int yOffset = (RECT_BAR_CENTER.m_height * center_scale_y) / 2.0f + (RECT_BAR_TOP.m_height / 2.0f);
	int color = 0;

	if (SONG_BAR(bar_num).bar_type == MusicGame::SongSelect::BAR_FOLDER)
	{
		color = SONG_BAR(bar_num).genre;
	}
	else if (SONG_BAR(bar_num).bar_type == MusicGame::SongSelect::BAR_FUMEN)
	{
		color = MusicGame::SongSelect::g_vec_folder_bar[m_open_folder].genre;
	}



	int tex_id = tex_BOX_NONE;


	switch (SONG_BAR(bar_num).bar_type)
	{
	case MusicGame::SongSelect::BAR_FUMEN:
	case MusicGame::SongSelect::BAR_FOLDER:
	{
		//真ん中の拡大率を変更
		Draw::SetScaleY(tex_BOX_NONE + color,center_scale_y);
		Draw::CenterDraw(tex_BOX_NONE + color, x, y, RECT_BAR_CENTER);

		//拡大率をもとに戻して、上下を描画する
		Draw::SetScaleY(tex_BOX_NONE + color, 1.0f);
		Draw::CenterDraw(tex_BOX_NONE + color, x, y - yOffset, RECT_BAR_TOP);
		Draw::CenterDraw(tex_BOX_NONE + color, x, y + yOffset, RECT_BAR_BOTTOM);
		MusicGame::SongSelect::g_tex_box_overlay.m_flip_y = false;
		MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y - overlay_up, RECT_OVERLAY_TOP, ref_Center, ref_Bottom);
		MusicGame::SongSelect::g_tex_box_overlay.m_flip_y = true;
		MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y + overlay_down, RECT_OVERLAY_TOP, ref_Center, ref_Top);
		//バー真ん中
		int center_overlay = y - overlay_up;
		while (center_overlay < y + overlay_down)
		{
			int height_remain = y + overlay_down - center_overlay;
			if (height_remain >= RECT_OVERLAY_CENTER.m_height)
			{
				MusicGame::SongSelect::g_tex_box_overlay.Draw(x, center_overlay, RECT_OVERLAY_CENTER, ref_Center, ref_Top);
			}
			else
			{
				RECT_N rect = RECT_OVERLAY_CENTER;
				rect.m_height = height_remain;
				MusicGame::SongSelect::g_tex_box_overlay.Draw(x, center_overlay, rect, ref_Center, ref_Top);
			}
			center_overlay += RECT_OVERLAY_CENTER.m_height;
		}
		if (SONG_BAR(bar_num).bar_type == MusicGame::SongSelect::BAR_FUMEN)
		{
			//王冠の描画
			if (SONG_BAR(bar_num).show_score.crown_color != E_CROWN::CROWN_NONE)
			{
				RECT_N rect_crown = RECT_CROWN;
				rect_crown.m_x = (int)SONG_BAR(bar_num).show_score.crown_diff * rect_crown.m_width;
				rect_crown.m_y = (int)SONG_BAR(bar_num).show_score.crown_color * rect_crown.m_height;

				tex_songselect_crown.m_scale_x = m_ani_not_selected_bar.GetValue("Crown").scale_x;
				tex_songselect_crown.m_scale_y = m_ani_not_selected_bar.GetValue("Crown").scale_y;
				tex_songselect_crown.Draw(x + BAR_CROWN_OFFSET.x, y + m_ani_not_selected_bar.GetValue("Crown").y, rect_crown, ref_Center, ref_Center);
			}
			//王冠の描画
			if (SONG_BAR(bar_num).show_score.rank_color != E_SCORE_RANK::RANK_NONE)
			{
				RECT_N rect_rank = RECT_RANK;
				rect_rank.m_x = (int)SONG_BAR(bar_num).show_score.rank_diff * rect_rank.m_width;
				rect_rank.m_y = (int)SONG_BAR(bar_num).show_score.rank_color * rect_rank.m_height;
				tex_songselect_rank.m_scale_x = m_ani_not_selected_bar.GetValue("Rank").scale_x;
				tex_songselect_rank.m_scale_y = m_ani_not_selected_bar.GetValue("Rank").scale_y;
				tex_songselect_rank.Draw(x + BAR_CROWN_NOT_SELECT_OFFSET.x, y + m_ani_not_selected_bar.GetValue("Rank").y, rect_rank, ref_Center, ref_Center);
			}


		}
		break;
	}
	case MusicGame::SongSelect::BAR_CLOSE:

		//真ん中の拡大率を変更
		Draw::SetScaleY(tex_BOX_CLOSE, center_scale_y);
		Draw::CenterDraw(tex_BOX_CLOSE, x, y, RECT_BAR_CENTER);

		//拡大率をもとに戻して、上下を描画する
		Draw::SetScaleY(tex_BOX_CLOSE, 1.0f);
		Draw::CenterDraw(tex_BOX_CLOSE, x, y - yOffset, RECT_BAR_TOP);
		Draw::CenterDraw(tex_BOX_CLOSE, x, y + yOffset, RECT_BAR_BOTTOM);
		Draw::CenterDraw(tex_BOX_CLOSE_TEXT, x, y);

		break;
	case MusicGame::SongSelect::BAR_RANDOM:
		break;
	}




	//switch (SONG_BAR(bar_num).bar_type)
	//{
	//case MusicGame::SongSelect::BAR_FUMEN:
	//case MusicGame::SongSelect::BAR_FOLDER:
	//	Draw::CenterDraw(tex_BOX_NONE + color, x, y);
	//	Draw::CenterDraw(tex_BOX_OVERLAY, x, y);
	//	break;
	//case MusicGame::SongSelect::BAR_CLOSE:
	//	Draw::CenterDraw(tex_BOX_CLOSE, x, y);
	//	Draw::CenterDraw(tex_BOX_CLOSE_TEXT, x, y);
	//	break;
	//case MusicGame::SongSelect::BAR_RANDOM:
	//	break;
	//}

}

void CObjSongSelect::SelectBarDraw(int bar_num, int x, int y)
{
	float overlay_up = m_ani_selected_bar.GetValue("BarOverlayCenter").y;
	float overlay_down = m_ani_selected_bar.GetValue("BarOverlayCenter").y;
	float center_scale_y = m_ani_selected_bar.GetValue("BarCenterScale").scale_y;
	int yOffset =( RECT_BAR_CENTER.m_height * center_scale_y) / 2.0f + (RECT_BAR_TOP.m_height / 2.0f);
	int color = 0;

	if (SONG_BAR(bar_num).bar_type == MusicGame::SongSelect::BAR_FOLDER)
	{
		//上部のみ未選択のものを使う
		overlay_up = m_ani_not_selected_bar.GetValue("BarOverlayCenter").y;
		color = SONG_BAR(bar_num).genre;
	}
	else if (SONG_BAR(bar_num).bar_type == MusicGame::SongSelect::BAR_FUMEN)
	{
		color = MusicGame::SongSelect::g_vec_folder_bar[m_open_folder].genre;
	}



	int tex_id = tex_BOX_NONE;


	switch (SONG_BAR(bar_num).bar_type)
	{
	case MusicGame::SongSelect::BAR_FUMEN:
	case MusicGame::SongSelect::BAR_FOLDER:
	{
		//真ん中の拡大率を変更
		Draw::SetScaleY(tex_BOX_NONE + color, center_scale_y);
		Draw::CenterDraw(tex_BOX_NONE + color, x, y, RECT_BAR_CENTER);

		//拡大率をもとに戻して、上下を描画する
		Draw::SetScaleY(tex_BOX_NONE + color, 1.0f);
		Draw::CenterDraw(tex_BOX_NONE + color, x, y - yOffset, RECT_BAR_TOP);
		Draw::CenterDraw(tex_BOX_NONE + color, x, y + yOffset, RECT_BAR_BOTTOM);

		MusicGame::SongSelect::g_tex_box_overlay.m_flip_y = false;
		MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y - overlay_up, RECT_OVERLAY_TOP, ref_Center, ref_Bottom);
		MusicGame::SongSelect::g_tex_box_overlay.m_flip_y = true;
		MusicGame::SongSelect::g_tex_box_overlay.Draw(x, y + overlay_down, RECT_OVERLAY_TOP, ref_Center, ref_Top);
		//バー真ん中
		int center_overlay = y - overlay_up;
		while (center_overlay < y + overlay_down)
		{
			int height_remain = y + overlay_down - center_overlay;
			if (height_remain >= RECT_OVERLAY_CENTER.m_height)
			{
				MusicGame::SongSelect::g_tex_box_overlay.Draw(x, center_overlay, RECT_OVERLAY_CENTER, ref_Center, ref_Top);
			}
			else
			{
				RECT_N rect = RECT_OVERLAY_CENTER;
				rect.m_height = height_remain;
				MusicGame::SongSelect::g_tex_box_overlay.Draw(x, center_overlay, rect, ref_Center, ref_Top);
			}
			center_overlay += RECT_OVERLAY_CENTER.m_height;
		}
		if (SONG_BAR(bar_num).bar_type == MusicGame::SongSelect::BAR_FUMEN)
		{
			//王冠の描画
			if (SONG_BAR(bar_num).show_score.crown_color != E_CROWN::CROWN_NONE)
			{
				RECT_N rect_crown = RECT_CROWN;
				rect_crown.m_x = (int)SONG_BAR(bar_num).show_score.crown_diff * rect_crown.m_width;
				rect_crown.m_y = (int)SONG_BAR(bar_num).show_score.crown_color * rect_crown.m_height;

				tex_songselect_crown.m_scale_x = m_ani_selected_bar.GetValue("Crown").scale_x;
				tex_songselect_crown.m_scale_y = m_ani_selected_bar.GetValue("Crown").scale_y;
				tex_songselect_crown.Draw(x + BAR_CROWN_OFFSET.x, y + m_ani_selected_bar.GetValue("Crown").y, rect_crown, ref_Center, ref_Center);
			}
			//王冠の描画
			if (SONG_BAR(bar_num).show_score.rank_color != E_SCORE_RANK::RANK_NONE)
			{
				RECT_N rect_rank = RECT_RANK;
				rect_rank.m_x = (int)SONG_BAR(bar_num).show_score.rank_diff * rect_rank.m_width;
				rect_rank.m_y = (int)SONG_BAR(bar_num).show_score.rank_color * rect_rank.m_height;
				tex_songselect_rank.m_scale_x = m_ani_selected_bar.GetValue("Rank").scale_x;
				tex_songselect_rank.m_scale_y = m_ani_selected_bar.GetValue("Rank").scale_y;
				tex_songselect_rank.Draw(x + BAR_CROWN_NOT_SELECT_OFFSET.x, y + m_ani_selected_bar.GetValue("Rank").y, rect_rank, ref_Center, ref_Center);
			}


		}
		break;
	}
	case MusicGame::SongSelect::BAR_CLOSE:

		//真ん中の拡大率を変更
		Draw::SetScaleY(tex_BOX_CLOSE, center_scale_y);
		Draw::CenterDraw(tex_BOX_CLOSE, x, y, RECT_BAR_CENTER);

		//拡大率をもとに戻して、上下を描画する
		Draw::SetScaleY(tex_BOX_CLOSE, 1.0f);
		Draw::CenterDraw(tex_BOX_CLOSE, x, y - yOffset, RECT_BAR_TOP);
		Draw::CenterDraw(tex_BOX_CLOSE, x, y + yOffset, RECT_BAR_BOTTOM);
		Draw::CenterDraw(tex_BOX_CLOSE_TEXT, x, y);

		break;
	case MusicGame::SongSelect::BAR_RANDOM:
		break;
	}


}

void CObjSongSelect::PreviousSong()
{
	m_now_select--;

	if (m_now_select < 0)
		m_now_select = m_vec_songselect_fumen.size() - 1;

	BackGroundColorChange();
}

void CObjSongSelect::NextSong()
{
	CObjSongSelectBG* bg = (CObjSongSelectBG*)Objs::GetObj(OBJ_SONGSELECT_BG);

	m_now_select++;

	if (m_now_select >= m_vec_songselect_fumen.size())
		m_now_select = 0;

	BackGroundColorChange();
}

void CObjSongSelect::PreviousSkip()
{
	for (int i = 0; i < SKIP_BAR - 1; i++)
		PreviousSong();

	SelectLeft();
}

void CObjSongSelect::NextSkip()
{
	for (int i = 0; i < SKIP_BAR - 1; i++)
		NextSong();

	SelectRight();
}
void CObjSongSelect::DiffcultyToSongSelect()
{
	//数値をリセットしてからフラグを変える
	m_ani_songselect_fadeout.Start();
	m_ani_songselect_fadeout.End();
	m_phase = PHASE_SONG_SELECT;
}

void CObjSongSelect::FolderOpenStart()
{
	m_ani_folder_open_out_scale_x.Start();
	m_ani_open_title_opacity.Start();

	for (int i = 0; i < MusicGame::SONGSELECT_BAR_AMOUNT; i++)
	{
		m_ani_open_bar_move_out[i].Start();
		m_ani_open_bar_move_out[i].End();
		m_ani_open_bar_move_in[i].Start();
		m_ani_open_bar_move_in[i].End();
	}

	m_ct_open_bar_move_delay.Start(0, MusicGame::SongSelect::BAR_OPEN_IN_DELAY + BAR_SHOW_AMOUNT * MusicGame::SongSelect::BAR_OPEN_INTERVAL, 1);
}


void CObjSongSelect::ResultToSongSelect()
{
	//キーフラグの初期化
	for (int i = 0; i < MusicGame::TAIKO_FLUSH_TYPE; i++)
		m_key_flag[i] = false;

	m_ct_bar_move.Reset();
//	m_ct_bar_scale_y.Reset();
//	m_ct_folder_scale_y.Reset();
//	m_ct_bar_title_move.Reset();
	m_ct_bar_scale_y_delay = { CTimeCounter(0,BAR_MOVE_SCALE_DELAY,1) };

	m_move_direction = 0;
	m_ani_folder_open_in_scale_x.Start();

	m_ani_songselect_fadeout.Start();
	m_ani_songselect_fadeout.End();

	int select = m_open_folder;
	FolderClose();
	m_now_select = select;//閉じたのでフォルダーにカーソルを合わせる

	m_fade_in.Start();

	SongSelectBgmStart();
	m_bgm_play_flag = false;
	m_demo_play_flag = true;
	m_phase = PHASE_SONG_SELECT;


	FavoliteFolderSet();
}

void CObjSongSelect::SongDecide()
{
	m_phase = PHASE_DECIDE;
}

void CObjSongSelect::SongSelectBgmStart()
{

	m_bgm_loop_flag = true;

	Audio::Start(bgm_IN);
	m_ct_bgm_loop_start.Start(0, BGM_LOOP_START_DELAY, 1);
}

void CObjSongSelect::CursorDraw(int x, int y)
{

	float center_scale_y = m_ani_selected_bar.GetValue("Cursor").scale_y;
	int yOffset = (RECT_CURSOR_CENTER.m_height * center_scale_y) / 2.0f + (RECT_CURSOR_TOP.m_height / 2.0f);
	float opacity = m_ani_selected_bar.GetValue("Cursor").opacity * m_ani_songselect_fadeout.GetValue();

	if (m_ani_cursor_decide_yellow.GetStart())
	{
		opacity *= m_ani_cursor_decide_yellow.GetValue().opacity;
	}
	float effect_opacity = opacity * m_ani_cursor_effect_loop.GetValue().opacity;

	//黄色いカーソルを描画
	Draw::SetOpacity(tex_SONGSELECT_CURSOR, opacity);

	//真ん中の拡大率を変更
	Draw::SetScaleY(tex_SONGSELECT_CURSOR, center_scale_y);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y, RECT_CURSOR_CENTER);

	//エフェクト描画
	RECT_F rect_center = RECT_CURSOR_CENTER;
	rect_center.m_y += RECT_CURSOR_YELLOW.m_height;
	Draw::SetOpacity(tex_SONGSELECT_CURSOR, effect_opacity);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y, rect_center);

	RECT_F rect_top = RECT_CURSOR_TOP;
	RECT_F rect_bottom = RECT_CURSOR_BOTTOM;
	Draw::SetOpacity(tex_SONGSELECT_CURSOR, opacity);

	//拡大率をもとに戻して、上下を描画する
	Draw::SetScaleY(tex_SONGSELECT_CURSOR, 1.0f);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y - yOffset, rect_top);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y + yOffset, rect_bottom);

	//エフェクト描画
	Draw::SetOpacity(tex_SONGSELECT_CURSOR, effect_opacity);

	rect_top.m_y += RECT_CURSOR_YELLOW.m_height;
	rect_bottom.m_y += RECT_CURSOR_YELLOW.m_height;
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y - yOffset, rect_top);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y + yOffset, rect_bottom);

	//白いカーソルを描画
	Draw::SetOpacity(tex_SONGSELECT_CURSOR, m_ani_cursor_decide_white.GetValue().opacity);
	Draw::CenterDraw(tex_SONGSELECT_CURSOR, x, y, RECT_CURSOR_WHITE);

}

void CObjSongSelect::DiffcultyBarDraw(int x, int y, int bar_num)
{
	float fadeout_opacity = m_ani_songselect_fadeout.GetValue();

	int count = 0;
	for (int i = DIFF_EASY; i < DIFF_Count; i++)
	{
		//おにを解放しておらず、またむずかしい以下に譜面がある場合はおにで終了する
		if (USER_DATA->m_oni_unlock == false && i >= DIFF_ONI && count >= 1)
			break;

		//レベルが0以上
		if (SONG_BAR(bar_num).level[i] > 0)
		{
			count++;

			//表譜面があればカウントを終了する
			if (i == DIFF_ONI)
				break;
		}
	}

	float x_offset = count * -(RECT_BAR_DIFFCULTY.m_width * 0.5f);
	//難易度パネルを描画。
	for (int i = 0; i <= DIFF_EDIT; i++)
	{
		RECT_F rect_diff = { RECT_BAR_DIFFCULTY.m_width * i,0.0f,RECT_BAR_DIFFCULTY.m_width,RECT_BAR_DIFFCULTY.m_height };

		//レベルが0以上
		if (SONG_BAR(bar_num).level[i] > 0)
		{
			if (i >= DIFF_ONI && USER_DATA->m_oni_unlock == false && count >= 2)
				return;

			float opacity = m_ani_selected_bar.GetValue("DiffcultyOpacity").opacity * fadeout_opacity * m_ani_open_title_opacity.GetValue().opacity;

			Draw::SetOpacity(tex_BOX_DIFFCULTY, opacity);
			Draw::Draw(tex_BOX_DIFFCULTY, x +x_offset, y, rect_diff);

			RECT_F rect_num = { RECT_BAR_DIFFCULTY_NUM.m_width * SONG_BAR(bar_num).level[i],0.0f,RECT_BAR_DIFFCULTY_NUM.m_width,RECT_BAR_DIFFCULTY_NUM.m_height };
			Draw::SetOpacity(tex_BOX_DIFFCULTY_NUMBER, opacity);
			Draw::Draw(tex_BOX_DIFFCULTY_NUMBER, x + BAR_DIFFCULTY_NUM_OFFSET.x + x_offset, y + BAR_DIFFCULTY_NUM_OFFSET.y , rect_num);

			if (i == DIFF_ONI && SONG_BAR(bar_num).level[DIFF_EDIT] > 0)
			{
				rect_diff.m_x = RECT_BAR_DIFFCULTY.m_width * DIFF_EDIT;

				float opacity = m_ani_selected_bar.GetValue("DiffcultyOpacity").opacity * fadeout_opacity * m_ani_open_title_opacity.GetValue().opacity * m_ani_edit_score_fade.GetValue().opacity;

				Draw::SetOpacity(tex_BOX_DIFFCULTY, opacity);
				Draw::SetOpacity(tex_BOX_DIFFCULTY_NUMBER, opacity);
				rect_num.m_x = RECT_BAR_DIFFCULTY_NUM.m_width * SONG_BAR(bar_num).level[DIFF_EDIT];
				Draw::Draw(tex_BOX_DIFFCULTY, x + x_offset,y, rect_diff);
				Draw::Draw(tex_BOX_DIFFCULTY_NUMBER, x + x_offset + BAR_DIFFCULTY_NUM_OFFSET.x, y + BAR_DIFFCULTY_NUM_OFFSET.y, rect_num);
				return;
			}


			x_offset += RECT_BAR_DIFFCULTY.m_width;
		}
		else
		{

		}


	}
}



//お気に入りフォルダと最近遊んだ曲フォルダの再セットをする
void CObjSongSelect::FavoliteFolderSet()
{
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	for (int i = 0; i < MusicGame::SongSelect::g_vec_folder_bar.size(); i++)
	{
		if (MusicGame::SongSelect::g_vec_folder_bar[i].genre == GENRE_HISTORY)
		{
			//同じ曲がある場合削除する
			for (auto itr = system->m_list_history_fumen_path.begin(); itr != system->m_list_history_fumen_path.end();itr++)
			{
				auto itr2 = std::next(itr);
				if (itr2 == system->m_list_history_fumen_path.end())break;

				for(itr2++; itr2 != system->m_list_history_fumen_path.end();)
				{
					if (*itr == *itr2)
					{
						itr2 = system->m_list_history_fumen_path.erase(itr2);
					}
					else
					{
						itr2++;
					}
				}
			}

			//さいだいきょくすうをこえているばあい最後から削除する
			while (system->m_list_history_fumen_path.size() > MusicGame::HISTORY_MAX)
			{
				system->m_list_history_fumen_path.pop_back();
			}


			for (auto ritr = system->m_list_history_fumen_path.begin(); ritr != system->m_list_history_fumen_path.end();)
			{
				bool success = false;

				for (int j = 0; j < MusicGame::SongSelect::g_vec_all_fumen_bar.size(); j++)
				{
					string fumen_path = *ritr;

					//譜面パスが一致
					if (fumen_path == MusicGame::SongSelect::g_vec_all_fumen_bar[j].folder_path)
					{
						//ファイルを開く
						ifstream ifs(fumen_path);

						//開けなかった場合削除する
						if (!ifs)
						{
							ifs.close();

							break;
						}

						MusicGame::SongSelect::g_vec_folder_fumen[i].push_back(j);
						success = true;
						break;
					}
				}

				if (success == true)
				{
					ritr++;
				}
				else
				{
					ritr = system->m_list_history_fumen_path.erase(ritr);
				}
			}


		
		}
		//else if (m_vec_folder_info[i].genre == GENRE_FAVOLITE)
		//{
		//	m_vec_fumen_bar[i].clear();

		//}
	}
}

void CObjSongSelect::SongBarCreate()
{

}

void CObjSongSelect::BackGroundColorChange()
{
	CObjSongSelectBG* bg = (CObjSongSelectBG*)Objs::GetObj(OBJ_SONGSELECT_BG);

	int color = GetBarColor(m_now_select);
	bg->GenreChange(color);
}

/// <summary>
/// バー情報をバーカラーに変換する。
/// </summary>
/// <param name="bar_num"></param>
/// <returns></returns>
int CObjSongSelect::GetBarColor(int bar_num)
{
	int color = 0;
	switch (SONG_BAR(bar_num).bar_type)
	{
	case MusicGame::SongSelect::BAR_FUMEN:
	case MusicGame::SongSelect::BAR_CLOSE:
	case MusicGame::SongSelect::BAR_RANDOM:
		color = MusicGame::SongSelect::g_vec_folder_bar[m_open_folder].genre;
		break;
	case MusicGame::SongSelect::BAR_FOLDER:
		color = SONG_BAR(bar_num).genre;
		break;
	}
	return color;
}


/// <summary>
/// 曲の読み込みと再生をサブスレッドで行う。
/// </summary>
void CObjSongSelect::SubThrActionDraw()
{
	while (m_phase != PHASE_DECIDE && USER_DATA->m_bgm_demo_play == true && this->GetStatus() == true) 
	{
		if (m_move_direction == 0 && m_ani_folder_open_in_scale_x.GetEnd() &&
			m_now_select >= 0 && m_now_select < MusicGame::SongSelect::g_vec_all_fumen_bar.size())
		{
			if (SONG_BAR(m_now_select).bar_type == MusicGame::SongSelect::BAR_FUMEN)
			{
				string wave_file = SONG_BAR(m_now_select).wave_file;

				if (m_demo_load_success == false)
				{


					Audio::LoadAudio2(bgm_MUSIC, SONG_BAR(m_now_select).wave_file.c_str(), BACK_MUSIC);


					//音楽をロードしてから、あらためてファイル名が一致しているかどうか調べてから再生する
					//サブスレッドで実行されているためロード中に曲が変わる可能性があるため。
					if (wave_file == SONG_BAR(m_now_select).wave_file &&
						m_move_direction == 0)
					{
						m_demo_load_success = true;
					}
				}
			}
		}
	}
}