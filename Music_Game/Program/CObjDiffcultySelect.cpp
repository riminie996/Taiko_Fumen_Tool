#include "CObjDiffcultySelect.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL/WinInputs.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/Userdata.h"

//初期化
void CObjDiffcultySelect::Init()
{
	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		m_ani_cursor[i].ani_cursor_in.LoadData("Animation/SongSelect/DiffcultySelect/CursorIn");
		m_ani_cursor[i].ani_cursor_select.LoadData("Animation/SongSelect/DiffcultySelect/CursorSelect");
		m_ani_cursor[i].ani_cursor_decide.LoadData("Animation/SongSelect/Decidecursor");
		m_ani_cursor[i].ani_course_appear.LoadData("Animation/SongSelect/DiffcultySelect/CourseSymbolAppear");
		m_ani_cursor[i].ani_course_select.LoadData("Animation/SongSelect/DiffcultySelect/CourseSymbolSelect");
		m_ani_cursor[i].ani_course_decide.LoadData("Animation/SongSelect/DiffcultySelect/CourseSymbolDecide");
		m_ani_cursor[i].now_select = ICON_CLOSE;
		m_ani_cursor[i].right_count = 0;
	}

	m_ani_diffculty_select_in.Start();
	m_edit_flag = false;

	//キーフラグの初期化
	for (int i = 0; i < MusicGame::TAIKO_FLUSH_TYPE; i++)
		m_key_flag[i] = false;


	m_ani_cursor_effect_loop.Start();

	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		m_ani_cursor[i].ani_cursor_in.Start();
		m_ani_cursor[i].ani_cursor_select.Start();
		m_ani_cursor[i].ani_course_appear.Start();
	}
	m_decide_player_count = 0;
}
//進行
void CObjDiffcultySelect::Action()
{
	m_ani_diffculty_select_in.Action();


	m_ani_cursor_effect_loop.ActionLoop();

	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		m_ani_cursor[i].ani_cursor_in.Action();
		m_ani_cursor[i].ani_cursor_select.Action();
		m_ani_cursor[i].ani_cursor_decide.Action();
		m_ani_cursor[i].ani_course_appear.Action();
		m_ani_cursor[i].ani_course_select.Action(); 
		m_ani_cursor[i].ani_course_decide.Action();
	}

	//おに登場演出用。
	m_ct_oni_appear.Action();
	m_ani_oni_appear_hole.Action();
	m_ani_oni_appear_oni.Action();
	m_ani_oni_appear_symbol_effect.Action();
	m_ani_oni_appear_bar.Action();

	m_ani_oni_switch_circle_fuchi.Action();
	m_ani_oni_switch_circle_oni.Action();
	m_ani_oni_switch_circle_edit.Action();
	m_ani_oni_switch_symbol_effect.Action();
	m_ani_oni_switch_bar.Action();
	m_ani_oni_switch_big_symbol.Action();


	m_ct_decide.Action();

	CObjLoading* lloading = (CObjLoading*)Objs::GetObj(OBJ_LOADING);
	if (m_ct_decide.GetProgress() && m_ct_decide.GetEndValueReached() && lloading == nullptr)
	{
		CObjLoading* loading = new CObjLoading();
		Objs::InsertObj(loading, OBJ_LOADING, PRIO_LOADING);

	}
	
	if (m_ani_oni_appear_oni.GetEnd())
	{
		USER_DATA->m_oni_unlock = true;
	}

	CObjEnsoOption* option = (CObjEnsoOption*)Objs::GetObj(OBJ_OPTION_SELECT);

	//入力を受け付けない
	if (!m_ani_diffculty_select_in.GetEnd() || m_ct_decide.GetProgress() ||
		!m_ct_oni_appear.GetEndValueReached() || option != nullptr)return;
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);

	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		if (system->GetInput(LEFT_DON, i) || system->GetInput(RIGHT_DON, i))
		{
			Decide(i);
		}
		//カッ左
		if (system->GetInput(LEFT_KA, i))
		{
			SelectLeft(i);
			Audio::Start(se_KA);
		}

		//カッ右
		if (system->GetInput(RIGHT_KA, i))
		{
			SelectRight(i);
			Audio::Start(se_KA);
		}
	}
}

//描画
void CObjDiffcultySelect::Draw()
{
	wchar_t wcr[64];
	//登場用透明度処理。
	float fade_opacity = m_ani_diffculty_select_in.GetValue();

	for (int i = 0; i < GENRE_Count; i++)
		Draw::SetOpacity(tex_DIFFCULTY_BOX_NONE + i, fade_opacity);
	Draw::SetOpacity(tex_DIFFCULTY_ICON, fade_opacity);
	Draw::SetOpacity(tex_DIFFCULTY_BAR, fade_opacity);
	Draw::SetOpacity(tex_DIFFCULTY_NUM, fade_opacity);
	Draw::SetOpacity(tex_DIFFCULTY_STAR, fade_opacity);
	Draw::SetOpacity(tex_DIFFCULTY_TEXT, fade_opacity);
	Draw::SetOpacity(tex_DIFFCULTY_BRANCH, fade_opacity);


	COLOR_A title_color = { 1.0f,1.0f,1.0f,fade_opacity };

	CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);
	MusicGame::SongSelect::ST_BAR_INFO bar = select->GetNowSelectSong();

	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		CourseSymbolDraw(i);
	}
	Draw::CenterDraw(tex_DIFFCULTY_BOX_NONE + m_back_color, BACK_POS.x, BACK_POS.y);
	COLOR col_gray = { 0.5f,0.5f,0.5f };

	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		if (m_ani_cursor[i].ani_cursor_in.GetEnd() && !m_ani_cursor[i].ani_cursor_decide.GetEnd() && m_ct_oni_appear.GetStoped())
			CursorDraw(i);
	}


	for (int i = 0; i < ICON_Count; i++)
	{
		int level = 0;

		switch (i)
		{
		case ICON_CLOSE:
		case ICON_OPTION:

			Draw::CenterDraw(tex_DIFFCULTY_ICON, ICON_POS[i].x, ICON_POS[i].y, RECT_ICON[i]);

			break;
		case ICON_EASY:
		case ICON_NORMAL:
		case ICON_HARD:
		case ICON_ONI:
		case ICON_EDIT:

			if (i == ICON_EDIT && m_edit_flag == false)break;

			int diffculty = i - 2;
			level = select->GetNowSelectSong().level[diffculty];
			if (level > 0)
			{
				Draw::SetColor(tex_DIFFCULTY_BAR, Color::White);
				Draw::SetColor(tex_DIFFCULTY_NUM, Color::White);
				Draw::SetColor(tex_DIFFCULTY_TEXT, Color::White);
			}
			else
			{
				Draw::SetColor(tex_DIFFCULTY_BAR, col_gray);
				Draw::SetColor(tex_DIFFCULTY_NUM, col_gray);
				Draw::SetColor(tex_DIFFCULTY_TEXT, col_gray);
			}
			//描画しない
			if (i == ICON_ONI && USER_DATA->m_oni_unlock == false)break;

			//バーを描画。
			Draw::CenterDraw(tex_DIFFCULTY_BAR, ICON_POS[i].x, ICON_POS[i].y, RECT_ICON[i]);

			//難易度テキストを描画。
			RECT_F rect_text = RECT_COURSE_TEXT;
			rect_text.m_y = (i - 2) * RECT_COURSE_TEXT.m_height;
			Draw::CenterDraw(tex_DIFFCULTY_TEXT, ICON_POS[i].x + COURSE_TEXT_OFFSET.x, ICON_POS[i].y + COURSE_TEXT_OFFSET.y, rect_text);

			//レベル☆を描画。
			Draw::Draw(tex_DIFFCULTY_NUM, ICON_POS[i].x + BAR_STAR_OFFSET.x, ICON_POS[i].y + BAR_STAR_OFFSET.y, RECT_NUM_STAR);

		
			//レベル数字を描画。
			Draw::Draw(tex_DIFFCULTY_NUM, ICON_POS[i].x + BAR_STAR_OFFSET.x, ICON_POS[i].y + BAR_STAR_OFFSET.y, RECT_NUM_STAR);
			RECT_F rect_num = RECT_NUM;
			if(level >= 11)
			rect_num.m_x = 11 * RECT_NUM.m_width;
			else		
			rect_num.m_x = level * RECT_NUM.m_width;
			Draw::Draw(tex_DIFFCULTY_NUM, ICON_POS[i].x + BAR_NUMBER_OFFSET.x, ICON_POS[i].y + BAR_NUMBER_OFFSET.y, rect_num);
			
			//星の数を描画。
			Draw::Draw(tex_DIFFCULTY_STAR, ICON_POS[i].x + BAR_STAR_BAR_OFFSET.x, ICON_POS[i].y + BAR_STAR_BAR_OFFSET.y,RECT_STAR_BAR);
			for (int j = 0; j < level && j < 10; j++)
			{
				float star_x = ICON_POS[i].x + BAR_STAR_BAR_OFFSET.x + BAR_STAR_BAR_STAR_OFFSET.x + BAR_STAR_PADDING * j;
				float star_y = ICON_POS[i].y + BAR_STAR_BAR_OFFSET.y;
				Draw::Draw(tex_DIFFCULTY_STAR, star_x, star_y, RECT_STAR_BAR_STAR);
			}

			if(select->GetNowSelectSong().branch[diffculty] == true)
			Draw::Draw(tex_DIFFCULTY_BRANCH, ICON_POS[i].x + BRANCH_TEXT_OFFSET.x, ICON_POS[i].y + BRANCH_TEXT_OFFSET.y);

			break;
		}


	}

	//おに登場演出中
	if (m_ani_oni_appear_hole.GetStart())
	{
		if (!m_ani_oni_appear_hole.GetEnd())
		{
			Draw::SetRotationZ(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_hole.GetValue().rotate_z);
			Draw::SetOpacity(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_hole.GetValue().opacity);
			Draw::SetScaleX(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_hole.GetValue().scale_x);
			Draw::SetScaleY(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_hole.GetValue().scale_y);
			Draw::CenterDraw(tex_DIFFCULTY_ONI_APPEAR, ONI_APPEAR_SYMBOL_POS.x, ONI_APPEAR_SYMBOL_POS.y, RECT_ONI_HOLE);
		}
		Draw::SetRotationZ(tex_DIFFCULTY_ONI_APPEAR, 0.0f);
		if (!m_ani_oni_appear_oni.GetEnd())
		{
			COLOR col = { m_ani_oni_appear_oni.GetValue().r,m_ani_oni_appear_oni.GetValue().g ,m_ani_oni_appear_oni.GetValue().b };
			Draw::SetOpacity(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_oni.GetValue().opacity);
			Draw::SetScaleX(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_oni.GetValue().scale_x);
			Draw::SetScaleY(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_oni.GetValue().scale_y);
			Draw::SetColor(tex_DIFFCULTY_ONI_APPEAR, col);
			Draw::CenterDraw(tex_DIFFCULTY_ONI_APPEAR, ONI_APPEAR_SYMBOL_POS.x, ONI_APPEAR_SYMBOL_POS.y, RECT_ONI_SYMBOL_BIG);

		}
			Draw::SetColor(tex_DIFFCULTY_ONI_APPEAR, Color::White);
		if (!m_ani_oni_appear_symbol_effect.GetEnd())
		{
			Draw::SetOpacity(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_symbol_effect.GetValue().opacity);
			Draw::SetScaleX(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_symbol_effect.GetValue().scale_x);
			Draw::SetScaleY(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_symbol_effect.GetValue().scale_y);
			Draw::CenterDraw(tex_DIFFCULTY_ONI_APPEAR, ONI_APPEAR_SYMBOL_POS.x, ONI_APPEAR_SYMBOL_POS.y, RECT_ONI_SYMBOL);

		}
		if (!m_ani_oni_appear_bar.GetEnd())
		{
			Draw::SetOpacity(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_appear_bar.GetValue().opacity);
			Draw::SetScaleX(tex_DIFFCULTY_ONI_APPEAR, 1.0f);
			Draw::SetScaleY(tex_DIFFCULTY_ONI_APPEAR, 1.0f);
			Draw::CenterDraw(tex_DIFFCULTY_ONI_APPEAR, ICON_POS[ICON_ONI].x, ICON_POS[ICON_ONI].y, RECT_BAR_LIGHT);

		}
	}

	//おに裏切り替え演出中
	if (m_ani_oni_switch_circle_fuchi.GetStart())
	{
		if (!m_ani_oni_switch_circle_fuchi.GetEnd())
		{
			Draw::SetOpacity(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_fuchi.GetValue().opacity);
			Draw::SetScaleX(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_fuchi.GetValue().scale_x);
			Draw::SetScaleY(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_fuchi.GetValue().scale_y);
			Draw::CenterDraw(tex_DIFFCULTY_ONI_APPEAR, ONI_APPEAR_SYMBOL_POS.x, ONI_APPEAR_SYMBOL_POS.y, RECT_CIRCLE_FUCHI);
		}
		if (!m_ani_oni_switch_circle_oni.GetEnd())
		{
			RECT_F rect_circle = m_edit_flag == true ? RECT_CIRCLE_ONI : RECT_CIRCLE_EDIT;

		

			Draw::SetRotationZ(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_oni.GetValue().rotate_z);
			Draw::SetOpacity(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_oni.GetValue().opacity);
			Draw::SetScaleX(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_oni.GetValue().scale_x);
			Draw::SetScaleY(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_oni.GetValue().scale_y);
			Draw::CenterDraw(tex_DIFFCULTY_ONI_APPEAR, ONI_APPEAR_SYMBOL_POS.x, ONI_APPEAR_SYMBOL_POS.y, rect_circle);
		}
		if (!m_ani_oni_switch_circle_edit.GetEnd())
		{
			RECT_F rect_circle = m_edit_flag == true ? RECT_CIRCLE_EDIT : RECT_CIRCLE_ONI;

			Draw::SetRotationZ(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_edit.GetValue().rotate_z);
			Draw::SetOpacity(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_edit.GetValue().opacity);
			Draw::SetScaleX(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_edit.GetValue().scale_x);
			Draw::SetScaleY(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_circle_edit.GetValue().scale_y);
			Draw::CenterDraw(tex_DIFFCULTY_ONI_APPEAR, ONI_APPEAR_SYMBOL_POS.x, ONI_APPEAR_SYMBOL_POS.y, rect_circle);
		}
		//回転率をもどす
		Draw::SetRotationZ(tex_DIFFCULTY_ONI_APPEAR, 1.0f);

		if (!m_ani_oni_switch_big_symbol.GetEnd())
		{
			RECT_F rect_symbol = m_edit_flag == true ? RECT_ONI_ICON : RECT_EDIT_ICON;
			if (m_ani_oni_switch_big_symbol.GetValue().pattern >= 1)
				rect_symbol = m_edit_flag == true ? RECT_EDIT_ICON : RECT_ONI_ICON;

			Draw::SetOpacity(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_big_symbol.GetValue().opacity);
			Draw::SetScaleX(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_big_symbol.GetValue().scale_x);
			Draw::SetScaleY(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_big_symbol.GetValue().scale_y);
			Draw::CenterDraw(tex_DIFFCULTY_ONI_APPEAR, ONI_APPEAR_SYMBOL_POS.x, ONI_APPEAR_SYMBOL_POS.y, rect_symbol);
		}
		if (!m_ani_oni_switch_symbol_effect.GetEnd())
		{
			Draw::SetOpacity(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_symbol_effect.GetValue().opacity);
			Draw::SetScaleX(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_symbol_effect.GetValue().scale_x);
			Draw::SetScaleY(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_symbol_effect.GetValue().scale_y);
			Draw::CenterDraw(tex_DIFFCULTY_ONI_APPEAR, ONI_APPEAR_SYMBOL_POS.x, ONI_APPEAR_SYMBOL_POS.y, RECT_EFFECT_SYMBOL);
		}
		if (!m_ani_oni_switch_bar.GetEnd())
		{
			Draw::SetOpacity(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_bar.GetValue().opacity);
			Draw::SetScaleX(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_bar.GetValue().scale_x);
			Draw::SetScaleY(tex_DIFFCULTY_ONI_APPEAR, m_ani_oni_switch_bar.GetValue().scale_y);
			Draw::CenterDraw(tex_DIFFCULTY_ONI_APPEAR, ICON_POS[ICON_ONI].x, ICON_POS[ICON_ONI].y, RECT_BAR_LIGHT);
		}
	}
	for (int i = 0; i < USER_DATA->m_player_amount; i++)
	{
		int x_offset = 0;

		if (USER_DATA->m_player_amount == 2 &&
			m_ani_cursor[0].now_select == m_ani_cursor[1].now_select)
			x_offset = i == 0 ? -CURSOR_PLAYER_WIDTH : CURSOR_PLAYER_WIDTH;

		//[1P]カーソルの描画
		if (m_ct_oni_appear.GetStoped())
		{
			float y_anime = m_ani_cursor[i].ani_cursor_in.GetValue("Player").y + m_ani_cursor[i].ani_cursor_select.GetValue("Player").y;
			Draw::SetOpacity(tex_DIFFCULTY_CURSOR, m_ani_cursor[i].ani_cursor_in.GetValue("Player").opacity);

			RECT_F rect_cursor = RECT_CURSOR;
			rect_cursor.m_x = i * rect_cursor.m_width;
			Draw::CenterDraw(tex_DIFFCULTY_CURSOR, ICON_POS[m_ani_cursor[i].now_select].x + x_offset, CURSOR_POS_Y + y_anime, rect_cursor);
			rect_cursor.m_y = rect_cursor.m_height;
			Draw::CenterDraw(tex_DIFFCULTY_CURSOR, ICON_POS[m_ani_cursor[i].now_select].x + x_offset, CURSOR_POS_Y + y_anime, rect_cursor);
		}
	}
}

void CObjDiffcultySelect::DiffcultySelectClose()
{
	this->SetStatus(false);
	CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);
	select->DiffcultyToSongSelect();
}

void CObjDiffcultySelect::SelectLeft(int player)
{
	if (m_ani_cursor[player].now_select == ICON_EDIT)
	{
		m_ani_cursor[player].now_select = ICON_HARD;
		m_ani_cursor[player].ani_cursor_select.Start();
	}
	else if (m_ani_cursor[player].now_select > 0)
	{
		m_ani_cursor[player].now_select--;
		m_ani_cursor[player].ani_cursor_select.Start();
	}

	m_ani_cursor[player].right_count = 0;
	m_ani_cursor[player].ani_course_select.Start();
}

void CObjDiffcultySelect::SelectRight(int player)
{
	CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);

	if (m_ani_cursor[player].now_select == ICON_HARD && USER_DATA->m_oni_unlock == false)
	{
		m_ani_cursor[player].right_count++;

		if (m_ani_cursor[player].right_count == 10)
		{
			m_ani_cursor[player].right_count = 0;
			m_ani_cursor[player].now_select = ICON_ONI;
			m_ani_cursor[player].ani_course_select.Start();

			//おに登場演出開始
			m_ani_oni_appear_hole.Start();
			m_ani_oni_appear_oni.Start();
			m_ani_oni_appear_symbol_effect.Start();
			m_ani_oni_appear_bar.Start();

			m_ct_oni_appear.Start(0, ONI_APPEAR_TIME, 1);
			Audio::Start(se_ONI_APPEAR);
		}
		return;
	}
	if ((m_ani_cursor[player].now_select == ICON_ONI && select->GetNowSelectSong().level[DIFF_EDIT] > 0) ||
		m_ani_cursor[player].now_select == ICON_EDIT)
	{
		m_ani_cursor[player].right_count++;

		if (m_ani_cursor[player].right_count == 10)
		{
			m_ani_cursor[player].right_count = 0;
			if (m_edit_flag == false)
				m_edit_flag = true;
			else if (m_edit_flag == true)
				m_edit_flag = false;
			m_ani_cursor[player].ani_course_select.Start();
			m_ani_cursor[player].now_select = m_edit_flag == true ? ICON_EDIT : ICON_ONI;

			//演出スタート
			m_ani_oni_switch_circle_fuchi.Start();
			m_ani_oni_switch_circle_oni.Start();
			m_ani_oni_switch_circle_edit.Start();
			m_ani_oni_switch_symbol_effect.Start();
			m_ani_oni_switch_bar.Start();
			m_ani_oni_switch_big_symbol.Start();

			m_ct_oni_appear.Start(0, ONI_APPEAR_TIME, 1);
			Audio::Start(se_ONI_SWITCHING);
		}
		return;
	}

	if (m_ani_cursor[player].now_select == ICON_HARD && m_edit_flag == true)
	{
		m_ani_cursor[player].now_select = ICON_EDIT;
		m_ani_cursor[player].ani_cursor_select.Start();
		m_ani_cursor[player].ani_course_select.Start();
	}
	else if (m_ani_cursor[player].now_select < ICON_ONI)
	{
		m_ani_cursor[player].now_select++;
		m_ani_cursor[player].ani_cursor_select.Start();
		m_ani_cursor[player].ani_course_select.Start();
	}
}

void CObjDiffcultySelect::Decide(int player)
{
	CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);
	CObjSongSelectCharacter* chara = (CObjSongSelectCharacter*)Objs::GetObj(OBJ_SONGSELECT_CHARA);

	int select_diffculty = m_ani_cursor[player].now_select - 2;

	switch (m_ani_cursor[player].now_select)
	{
	case ICON_CLOSE:
		DiffcultySelectClose();
		Audio::Start(se_DON);
		break;
	case ICON_OPTION:
	{
		CObjEnsoOption* option = new CObjEnsoOption(&select->m_enso_option,0);
		Objs::InsertObj(option, OBJ_OPTION_SELECT, PRIO_SONGSELECT_OPTION);
		m_key_flag[LEFT_DON] = false;
		m_key_flag[RIGHT_DON] = false;
		Audio::Start(se_DON);
		break;
	}
	case ICON_EASY:
	case ICON_NORMAL:
	case ICON_HARD:
	case ICON_ONI:
	case ICON_EDIT:
		if (select->GetNowSelectSong().level[select_diffculty] > 0)
		{
			m_ani_cursor[player].ani_course_decide.Start();
			((UserData*)Save::GetData())->m_now_select_diffculty[player] = select_diffculty;
		
			m_ani_cursor[player].ani_cursor_decide.Start();
			Audio::Start(se_DON);

			m_decide_player_count++;

			if (m_decide_player_count == USER_DATA->m_player_amount)
			{
				m_ct_decide.Start(0, DECIDE_LOADING_DELAY, 1);
				MusicGame::g_now_select_songtitle = select->GetNowSelectSong().title;
				MusicGame::g_confirm_song_id = select->GetNowSelectNumber();
				select->SongDecide();
			}

			if (chara != nullptr)
				chara->SongStart();
		}
		else
		{
			Audio::Start(se_ERROR);
		}
		break;
	}
}

void CObjDiffcultySelect::CourseSymbolDraw(int player)
{
	if (m_ani_cursor[player].now_select < ICON_EASY)return;
	
	RECT_F rect_coursesymbol = RECT_COURSESYMBOL;
	rect_coursesymbol.m_x = (m_ani_cursor[player].now_select - ICON_EASY) * RECT_COURSESYMBOL.m_width;

	RECT_F rect_effect = rect_coursesymbol;
	rect_effect.m_y = RECT_COURSESYMBOL.m_height;


	//登場中
	if (!m_ani_diffculty_select_in.GetEnd())
	{
		Draw::SetScaleY(tex_DIFFCULTY_COURSESYMBOL, 1.0f);
		Draw::SetOpacity(tex_DIFFCULTY_COURSESYMBOL, m_ani_cursor[player].ani_course_appear.GetValue(0).opacity);
		Draw::CenterDraw(tex_DIFFCULTY_COURSESYMBOL, COURSESYMBOL_POS[player].x, COURSESYMBOL_POS[player].y, rect_coursesymbol);
	}
	//決定後
	else if (m_ani_cursor[player].ani_course_decide.GetStart())
	{
		Draw::SetScaleY(tex_DIFFCULTY_COURSESYMBOL, m_ani_cursor[player].ani_course_decide.GetValue("CourseSymbol").scale_y);
		Draw::SetOpacity(tex_DIFFCULTY_COURSESYMBOL,m_ani_cursor[player].ani_course_decide.GetValue("BackEffect").opacity);

		//背面にエフェクト1つ描画
		Draw::CenterDraw(tex_DIFFCULTY_COURSESYMBOL, COURSESYMBOL_POS[player].x, COURSESYMBOL_POS[player].y, rect_effect);


		Draw::SetOpacity(tex_DIFFCULTY_COURSESYMBOL, m_ani_cursor[player].ani_course_decide.GetValue("CourseSymbol").opacity);
		Draw::CenterDraw(tex_DIFFCULTY_COURSESYMBOL, COURSESYMBOL_POS[player].x, COURSESYMBOL_POS[player].y, rect_coursesymbol);

		//前面にもエフェクト描画
		Draw::SetOpacity(tex_DIFFCULTY_COURSESYMBOL, m_ani_cursor[player].ani_course_decide.GetValue("FrontEffect").opacity);
		Draw::CenterDraw(tex_DIFFCULTY_COURSESYMBOL, COURSESYMBOL_POS[player].x, COURSESYMBOL_POS[player].y, rect_effect);
	}
	//選択中
	else
	{
		Draw::SetScaleY(tex_DIFFCULTY_COURSESYMBOL, m_ani_cursor[player].ani_course_select.GetValue(0).scale_y);
		Draw::SetOpacity(tex_DIFFCULTY_COURSESYMBOL, m_ani_cursor[player].ani_course_select.GetValue(0).opacity);

		float y_offset = RECT_COURSESYMBOL.m_height * m_ani_cursor[player].ani_course_select.GetValue(0).scale_y *0.5f;

		Draw::CenterDraw(tex_DIFFCULTY_COURSESYMBOL, COURSESYMBOL_POS[player].x, m_ani_cursor[player].ani_course_select.GetValue(0).y - y_offset, rect_coursesymbol);

	}
}

void CObjDiffcultySelect::CursorDraw(int player)
{
	RECT_F rect_cursor_yellow;
	RECT_F rect_cursor_effect;
	RECT_F rect_cursor_white;
	switch (m_ani_cursor[player].now_select)
	{
	case ICON_CLOSE:
	case ICON_OPTION:
		rect_cursor_yellow = RECT_CURSOR_ICON_YELLOW;
		rect_cursor_effect = RECT_CURSOR_ICON_EFFECT;
		rect_cursor_white = RECT_CURSOR_ICON_WHITE;
		break;
	case ICON_EASY:
	case ICON_NORMAL:
	case ICON_HARD:
	case ICON_ONI:
	case ICON_EDIT:
		rect_cursor_yellow = RECT_CURSOR_BAR_YELLOW;
		rect_cursor_effect = RECT_CURSOR_BAR_EFFECT;
		rect_cursor_white = RECT_CURSOR_BAR_WHITE;
		break;
	}

	float opacity = 1.0f;

	if (m_ani_cursor[player].ani_cursor_decide.GetStart())
		opacity *= m_ani_cursor[player].ani_cursor_decide.GetValue("CursorYellow").opacity;

	//カーソル描画
	Draw::SetOpacity(tex_DIFFCULTY_CURSOR2, opacity);
	Draw::CenterDraw(tex_DIFFCULTY_CURSOR2, ICON_POS[m_ani_cursor[player].now_select].x, ICON_POS[m_ani_cursor[player].now_select].y, rect_cursor_yellow);
	//黄色ループエフェクト
	opacity = opacity * m_ani_cursor_effect_loop.GetValue().opacity;
	Draw::SetOpacity(tex_DIFFCULTY_CURSOR2, opacity);
	Draw::CenterDraw(tex_DIFFCULTY_CURSOR2, ICON_POS[m_ani_cursor[player].now_select].x, ICON_POS[m_ani_cursor[player].now_select].y, rect_cursor_effect);
	//白エフェクト
	opacity = m_ani_cursor[player].ani_cursor_decide.GetValue("CursorWhite").opacity;
	Draw::SetOpacity(tex_DIFFCULTY_CURSOR2, opacity);
	Draw::CenterDraw(tex_DIFFCULTY_CURSOR2, ICON_POS[m_ani_cursor[player].now_select].x, ICON_POS[m_ani_cursor[player].now_select].y, rect_cursor_white);
}