#include "CObjEnsoOption.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL/WinInputs.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/Userdata.h"

//初期化
void CObjEnsoOption::Init()
{
	for (int i = 0; i < TAIKO_FLUSH_Count; i++)
		m_key_flag[i] = false;

	m_now_select = OPTION_SCROLL;
	m_scroll_select = 0;

	for (int i = 0; i < SCROLL_SPEED.size(); i++)
	{
		if (m_p_option->scroll_speed == SCROLL_SPEED[i])
			m_scroll_select = i;

	}

	m_ani_option_in.Start();
	m_ani_option_bar.Start();

	//	OPTION_SCROLL,
	//	OPTION_DORON,
	//	OPTION_ABEKOBE,
	//	OPTION_RANDOM,
	//	OPTION_SKIP,
	//	OPTION_OFFSET,
	//	OPTION_VOICE,
	//	OPTION_NEIRO,
}
//進行
void CObjEnsoOption::Action()
{
	m_ani_option_in.Action();
	m_ani_option_out.Action();
	m_ani_option_arrow_left.Action();
	m_ani_option_arrow_right.Action();
	m_ani_option_bar.ActionLoop();

	if (m_ani_option_out.GetEnd())
		this->SetStatus(false);

	if (!m_ani_option_in.GetEnd() || m_ani_option_out.GetStart())return;

	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
	if (system->GetInput(LEFT_DON, m_player) || system->GetInput(RIGHT_DON, m_player))
	{
		Decide();
	}
	if (system->GetInput(LEFT_KA, m_player))
	{
		SelectLeft();
	}
	if (system->GetInput(RIGHT_KA, m_player))
	{
		SelectRight();
	}
}

//描画
void CObjEnsoOption::Draw()
{
	float move_y = m_ani_option_in.GetValue().y + m_ani_option_out.GetValue().y;

	Draw::Draw(tex_DIFFCULTY_OPTION, OPTION_PANEL_POS.x, OPTION_PANEL_POS.y + move_y);



	for (int i = 0; i < OPTION_Count; i++)
	{
		COLOR bar_col = { 0.882f,0.952f,0.702f };

		if (m_now_select == i)
		{
			bar_col.b = m_ani_option_bar.GetValue().b;
		}

		Draw::SetColor(tex_DIFFCULTY_OPTION_BAR_BACK, bar_col);
		Draw::Draw(tex_DIFFCULTY_OPTION_BAR_BACK, OPTION_PANEL_POS.x, OPTION_PANEL_POS.y + move_y + i * OPTION_HEIGHT);
	

		bool yellow = false;

		switch ((E_OPTION_ITEM)i)
		{
		case OPTION_SCROLL:
			if (m_p_option->scroll_speed != ST_ENSO_OPTION().scroll_speed)yellow = true;
			break;
		case OPTION_DORON:
			if (m_p_option->doron != ST_ENSO_OPTION().doron)yellow = true;
			break;
		case OPTION_ABEKOBE:
			if (m_p_option->abekobe != ST_ENSO_OPTION().abekobe)yellow = true;
			break;
		case OPTION_RANDOM:
			if (m_p_option->random != ST_ENSO_OPTION().random)yellow = true;
			break;
		case OPTION_SKIP:
		//	if (m_p_option->skip != ST_ENSO_OPTION().skip)yellow = true;
			if (((UserData*)Save::GetData())->m_auto_play[m_player] != false)yellow = true;
			break;
		case OPTION_OFFSET:
			if (m_p_option->offset != ST_ENSO_OPTION().offset)yellow = true;
			break;
		case OPTION_VOICE:
			if (m_p_option->voice != ST_ENSO_OPTION().voice)yellow = true;
			break;
		case OPTION_NEIRO:
			break;
		}

		if (yellow == true)
		{
			Draw::SetColor(tex_DIFFCULTY_OPTION_BAR, Color::Yellow);
			Draw::Draw(tex_DIFFCULTY_OPTION_BAR, OPTION_PANEL_POS.x, OPTION_PANEL_POS.y + move_y + i * OPTION_HEIGHT);
		}
		else
		{
			Draw::SetColor(tex_DIFFCULTY_OPTION_BAR, Color::White);
			Draw::Draw(tex_DIFFCULTY_OPTION_BAR, OPTION_PANEL_POS.x, OPTION_PANEL_POS.y + move_y + i * OPTION_HEIGHT);
		}
	}

	if (!m_ani_option_out.GetStart())
	{
		Draw::Draw(tex_DIFFCULTY_OPTION_ARROW, OPTION_PANEL_POS.x + OPTION_ARROW_LEFT_OFFSET.x - m_ani_option_arrow_left.GetValue().x, OPTION_PANEL_POS.y + move_y + OPTION_ARROW_LEFT_OFFSET.y + m_now_select * OPTION_HEIGHT);
		Draw::Draw(tex_DIFFCULTY_OPTION_ARROW, OPTION_PANEL_POS.x + OPTION_ARROW_RIGHT_OFFSET.x + m_ani_option_arrow_right.GetValue().x, OPTION_PANEL_POS.y + move_y + OPTION_ARROW_RIGHT_OFFSET.y + m_now_select * OPTION_HEIGHT, true);
	}

	wchar_t wcr[OPTION_Count][8] =
	{
		{L"はやさ"},
		{L"ドロン"},
		{L"あべこべ"},
		{L"ランダム"},
	//	{L"演奏スキップ"},
		{L"オートプレイ"},
		{L"音符位置調整"},
		{L"ボイス"},
		{L"音色"},
	};

	wchar_t wcrinfo[8];

	for (int i = 0; i < OPTION_Count; i++)
	{
		switch ((E_OPTION_ITEM)i)
		{
		case OPTION_SCROLL:
			swprintf_s(wcrinfo, L"%.1f", m_p_option->scroll_speed);
			break;
		case OPTION_DORON:
			swprintf_s(wcrinfo, m_p_option->doron == true ? L"する" : L"しない");
			break;
		case OPTION_ABEKOBE:
			swprintf_s(wcrinfo, m_p_option->abekobe == true ? L"する" : L"しない");
			break;
		case OPTION_RANDOM:
			swprintf_s(wcrinfo, m_p_option->random == ST_ENSO_OPTION::RANDOM_OFF ? L"なし" : m_p_option->random == ST_ENSO_OPTION::RANDOM_KIMAGURE ? L"きまぐれ":L"でたらめ");
			break;
		case OPTION_SKIP:
		//	swprintf_s(wcrinfo, m_p_option->skip == true ? L"する" : L"しない");
			swprintf_s(wcrinfo, ((UserData*)Save::GetData())->m_auto_play[m_player] == true ? L"する" : L"しない");
			break;
		case OPTION_OFFSET:
		//	swprintf_s(wcrinfo, m_p_option->offset == true ? L"する" : L"しない");
			swprintf_s(wcrinfo, L"%d", m_p_option->offset);
			break;
		case OPTION_VOICE:
			swprintf_s(wcrinfo, m_p_option->voice == true ? L"あり" : L"なし");
			break;
		case OPTION_NEIRO:
			swprintf_s(wcrinfo, L"太鼓");
			break;
		}

		Font::StrDraw(wcr[i], OPTION_PANEL_POS.x + OPTION_TEXT_OFFSET.x, OPTION_PANEL_POS.y + OPTION_TEXT_OFFSET.y + move_y + i * OPTION_HEIGHT, OPTION_TEXT_SIZE,ColorA::Black);
		Font::StrCenterDraw(wcrinfo, OPTION_PANEL_POS.x + OPTION_INFO_OFFSET.x, OPTION_PANEL_POS.y + OPTION_INFO_OFFSET.y + move_y +  i * OPTION_HEIGHT, OPTION_TEXT_SIZE,ColorA::Black);

	}
}
void CObjEnsoOption::Decide()
{
	m_now_select++;
	Audio::Start(se_DON);

	if (m_now_select >= OPTION_Count)
		m_ani_option_out.Start();
}
void CObjEnsoOption::SelectLeft()
{
	Audio::Start(se_KA);
	m_ani_option_arrow_left.Start();

	switch ((E_OPTION_ITEM)m_now_select)
	{
	case OPTION_SCROLL:
		m_scroll_select--;

		if (m_scroll_select < 0)
			m_scroll_select = SCROLL_SPEED.size() - 1;
		m_p_option->scroll_speed = SCROLL_SPEED[m_scroll_select];
		break;
	case OPTION_DORON:
		m_p_option->doron = m_p_option->doron == true ? false : true;
		break;
	case OPTION_ABEKOBE:
		m_p_option->abekobe = m_p_option->abekobe == true ? false : true;
		break;
	case OPTION_RANDOM:
		m_p_option->random--;

		if (m_p_option->random < 0)
			m_p_option->random = ST_ENSO_OPTION::RANDOM_DETARAME;
		break;
	case OPTION_SKIP:
	//	m_p_option->skip = m_p_option->skip == true ? false : true;
		((UserData*)Save::GetData())->m_auto_play[m_player] = ((UserData*)Save::GetData())->m_auto_play[m_player] == true ? false : true;
		break;
	case OPTION_OFFSET:
		m_p_option->offset -= 1;
		break;
	case OPTION_VOICE:
		m_p_option->voice = m_p_option->voice == true ? false : true;
		break;
	case OPTION_NEIRO:
		break;
	}

}
void CObjEnsoOption::SelectRight()
{
	Audio::Start(se_KA);
	m_ani_option_arrow_right.Start();

	switch ((E_OPTION_ITEM)m_now_select)
	{
	case OPTION_SCROLL:
		m_scroll_select++;

		if (m_scroll_select >= SCROLL_SPEED.size())
			m_scroll_select = 0;
		m_p_option->scroll_speed = SCROLL_SPEED[m_scroll_select];
		break;
	case OPTION_DORON:
		m_p_option->doron = m_p_option->doron == true ? false : true;
		break;
	case OPTION_ABEKOBE:
		m_p_option->abekobe = m_p_option->abekobe == true ? false : true;
		break;
	case OPTION_RANDOM:
		m_p_option->random++;

		if (m_p_option->random > ST_ENSO_OPTION::RANDOM_DETARAME)
			m_p_option->random = ST_ENSO_OPTION::RANDOM_OFF;
		break;
	case OPTION_SKIP:
		//	m_p_option->skip = m_p_option->skip == true ? false : true;
		((UserData*)Save::GetData())->m_auto_play[m_player] = ((UserData*)Save::GetData())->m_auto_play[m_player] == true ? false : true;
		break;
	case OPTION_OFFSET:
		m_p_option->offset += 1;
		break;
	case OPTION_VOICE:
		m_p_option->voice = m_p_option->voice == true ? false : true;
		break;
	case OPTION_NEIRO:
		break;
	}

}