#pragma once
#include "MusicGame.h"
#include "GameHead.h"
#include "GameL\SceneObjManager.h"
using namespace GameL;



class CObjEnsoOption : public CObj
{
public:
//	CObjEnsoOption() {}
	CObjEnsoOption(ST_ENSO_OPTION* p_option, int player) { m_p_option = p_option; m_player = player; }
	~CObjEnsoOption() {}
	void Init();
	void Action();
	void Draw();

private:
	enum E_OPTION_ITEM
	{
		OPTION_SCROLL,
		OPTION_DORON,
		OPTION_ABEKOBE,
		OPTION_RANDOM,
		OPTION_SKIP,
		OPTION_OFFSET,
		OPTION_VOICE,
		OPTION_NEIRO,
		OPTION_Count,
	};

	vector<float> SCROLL_SPEED =
	{
		1.0f,
		1.1f,
		1.2f,
		1.3f,
		1.4f,
		1.5f,
		1.6f,
		1.7f,
		1.8f,
		1.9f,
		2.0f,
		2.5f,
		3.0f,
		3.5f,
		4.0f,
	};


	const Point OPTION_PANEL_POS = { 0,304 };
	const Point OPTION_TEXT_OFFSET = { 29,77 };
	const Point OPTION_INFO_OFFSET = { 198,85 };
	const Point OPTION_ARROW_LEFT_OFFSET = { 138,69 };
	const Point OPTION_ARROW_RIGHT_OFFSET = { 229,69 };
	const float OPTION_HEIGHT = 40.78571428571429f;
	const float OPTION_TEXT_SIZE = 17.0f;
	
	bool m_key_flag[TAIKO_FLUSH_Count];
	int m_now_select;
	int m_scroll_select;
	int m_player;
	ST_ENSO_OPTION* m_p_option;

	CAnime2 m_ani_option_in = {"Animation/SongSelect/DiffcultySelect/OptionIn"};
	CAnime2 m_ani_option_out = { "Animation/SongSelect/DiffcultySelect/OptionOut" };
	CAnime2 m_ani_option_bar = { "Animation/SongSelect/DiffcultySelect/OptionBarYellow" };
	CAnime2 m_ani_option_arrow_left = { "Animation/SongSelect/DiffcultySelect/OptionArrow" };
	CAnime2 m_ani_option_arrow_right = { "Animation/SongSelect/DiffcultySelect/OptionArrow" };

	
	void Decide();
	void SelectLeft();
	void SelectRight();
};
