#pragma once
#include "MusicGame.h"
#include "GameHead.h"
#include "GameL\SceneObjManager.h"
using namespace GameL;



class CObjDiffcultySelect : public CObj
{
public:
	CObjDiffcultySelect(int color) { m_back_color = color; }
	~CObjDiffcultySelect() {}
	void Init();
	void Action();
	void Draw();

private:
	enum E_ICON_TYPE
	{
		ICON_CLOSE,//����
		ICON_OPTION,//�I�v�V����
		ICON_EASY,
		ICON_NORMAL,
		ICON_HARD,
		ICON_ONI,
		ICON_EDIT,
		ICON_Count
	};

	struct ST_CURSOR_ANIME
	{
		CAnime3 ani_cursor_in;
		CAnime3 ani_cursor_loop;
		CAnime3 ani_cursor_select;
		CAnime3 ani_cursor_decide;

		CAnime3 ani_course_appear;
		CAnime3 ani_course_select;
		CAnime3 ani_course_decide;
		int now_select;
		int right_count;
	};

	const Point BACK_POS = { 640,280 };
	const Point ICON_POS[ICON_Count] =
	{
		{294,309},//����
		{382,309},//�I�v�V����
		{497,390},//���񂽂�
		{640,390},
		{783,390},
		{926,390},//����
		{926,390},//���ɗ�
	};
	const RECT_F RECT_ICON[ICON_Count] =
	{
		{0.0f,0.0f,90.0f,90.0f},
		{0.0f,90.0f,90.0f,90.0f},
		{0.0f,0.0f,139.0f,246.0f},
		{139.0f,0.0f,139.0f,246.0f},
		{278.0f,0.0f,139.0f,246.0f},
		{417.0f,0.0f,139.0f,246.0f},
		{556.0f,0.0f,139.0f,246.0f},
	};
	const RECT_F RECT_NUM = { 0.0f,0.0f,36.0f,24.0f };
	const RECT_F RECT_NUM_STAR = { 432.0f,0.0f,24.0f,24.0f };
	const RECT_F RECT_STAR_BAR = { 0.0f,0.0f,114.0f,16.0f };
	const RECT_F RECT_STAR_BAR_STAR = { 114.0f,0.0f,16.0f,16.0f };
	const float CURSOR_POS_Y = 250.0f;
	const int DECIDE_LOADING_DELAY = 2700;//���肩�牉�t��ʓǂݍ��ݎn�߂�܂ł̎��ԁB
	const RECT_F RECT_COURSESYMBOL = { 0.0f,0.0f,412.0f,407.0f };
	const RECT_F RECT_COURSE_TEXT = { 0.0f,0.0f,128.0f,32.0f };
	const Point COURSESYMBOL_POS[2] = { { 134,269 },{1146,269 } };
	const Point COURSE_TEXT_OFFSET = { 0,31 };
	const Point ONI_APPEAR_SYMBOL_POS = { 926,357 };
	const int ONI_APPEAR_TIME = 1550;
	const int ONI_SWITCH_TIME = 1550;
	const Point BAR_STAR_OFFSET = { -24,45 };
	const Point BAR_NUMBER_OFFSET = { -7,46 };
	const Point BAR_STAR_BAR_OFFSET = { -56,69 };
	const Point BAR_STAR_BAR_STAR_OFFSET = { 4,0 };
	const float BAR_STAR_PADDING = 10.0f;
	const Point BRANCH_TEXT_OFFSET = { -43,78 };

	const RECT_F RECT_CURSOR_BAR_YELLOW = { 0.0f,0.0f,171.0f,270.0f };
	const RECT_F RECT_CURSOR_BAR_EFFECT = { 171.0f,0.0f,171.0f,270.0f };
	const RECT_F RECT_CURSOR_BAR_WHITE = { 342.0f,0.0f,171.0f,270.0f };
	const RECT_F RECT_CURSOR_ICON_YELLOW = { 0.0f,270.0f,114.0f,114.0f };
	const RECT_F RECT_CURSOR_ICON_EFFECT = { 114.0f,270.0f,114.0f,114.0f };
	const RECT_F RECT_CURSOR_ICON_WHITE = { 114.0f,270.0f,114.0f,114.0f };

	const RECT_F RECT_CURSOR = { 0.0f,0.0f,88.0f,88.0f };
	const RECT_F RECT_CURSOR_PLAYER = { 0.0f,88.0f,88.0f,88.0f };

	//�ނ��������{���ɗ����o�p
	const RECT_F RECT_ONI_HOLE = { 0.0f,0.0f,250.0f,250.0f };
	const RECT_F RECT_CIRCLE_FUCHI = { 250.0f,0.0f,191.0f,191.0f };
	const RECT_F RECT_CIRCLE_ONI = { 441.0f,0.0f,144.0f,145.0f };
	const RECT_F RECT_CIRCLE_EDIT = { 441.0f,145.0f,144.0f,145.0f };
	const RECT_F RECT_ONI_ICON = { 585.0f,0.0f,191.0f,191.0f };
	const RECT_F RECT_EDIT_ICON = { 585.0f,191.0f,191.0f,191.0f };
	const RECT_F RECT_ONI_SYMBOL_BIG = { 776.0f,0.0f,191.0f,191.0f };
	const RECT_F RECT_EDIT_SYMBOL_BIG = { 776.0f,191.0f,191.0f,191.0f };
	const RECT_F RECT_BAR_LIGHT = { 967.0f,0.0f,171.0f,270.0f };
	const RECT_F RECT_ONI_SYMBOL = { 0.0f,250.0f,96.0f,96.0f };
	const RECT_F RECT_EDIT_SYMBOL = { 96.0f,250.0f,96.0f,96.0f };
	const RECT_F RECT_EFFECT_SYMBOL = { 192.0f,250.0f,96.0f,96.0f };

	const static int CURSOR_PLAYER_WIDTH = 27;

	CAnime m_ani_diffculty_select_in = { "Animation/SongSelect/DiffcultySelectIn" };


	//�J�[�\���G�t�F�N�g�A�j���𗬗p
	CAnime2 m_ani_cursor_effect_loop = { "Animation/SongSelect/CursorEffectLoop" };

	CAnime2 m_ani_oni_appear_hole = { "Animation/SongSelect/DiffcultySelect/AppearHole" };
	CAnime2 m_ani_oni_appear_oni = { "Animation/SongSelect/DiffcultySelect/AppearOni" };
	CAnime2 m_ani_oni_appear_symbol_effect = { "Animation/SongSelect/DiffcultySelect/AppearSymbolEffect" };
	CAnime2 m_ani_oni_appear_bar = { "Animation/SongSelect/DiffcultySelect/AppearBarEffect" };

	CAnime2 m_ani_oni_switch_circle_fuchi = { "Animation/SongSelect/DiffcultySelect/SwitchCircleFuchi" };
	CAnime2 m_ani_oni_switch_circle_oni = { "Animation/SongSelect/DiffcultySelect/SwitchCircleOni" };
	CAnime2 m_ani_oni_switch_circle_edit = { "Animation/SongSelect/DiffcultySelect/SwitchCircleEdit" };
	CAnime2 m_ani_oni_switch_symbol_effect = { "Animation/SongSelect/DiffcultySelect/SwitchSymbolEffect" };
	CAnime2 m_ani_oni_switch_bar = { "Animation/SongSelect/DiffcultySelect/SwitchBarEffect" };
	CAnime2 m_ani_oni_switch_big_symbol = { "Animation/SongSelect/DiffcultySelect/SwitchBigSymbol" };
	void DiffcultySelectClose();

	bool m_edit_flag;
	bool m_key_flag[MusicGame::TAIKO_FLUSH_TYPE];
	CTimeCounter m_ct_decide;
	CTimeCounter m_ct_oni_appear;
	CNumTexSource m_num_level;
	int m_back_color;
	int m_decide_player_count;

	ST_CURSOR_ANIME m_ani_cursor[MusicGame::MAX_PLAYER_AMOUNT];

	void Decide(int player);
	void SelectLeft(int player);
	void SelectRight(int player);

	void CourseSymbolDraw(int player);

	void CursorDraw(int player);
};
