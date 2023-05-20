#pragma once
#include "MusicGame.h"
#include "GameHead.h"
#include "GameL\SceneObjManager.h"
using namespace GameL;

class CObjHeya : public CObj
{
public:



	CObjHeya() {}
	~CObjHeya() {}
	void Init();
	void Action();
	void Draw();
private:

	enum class E_HEYA_ITEM
	{
		//システム
		MAX_SONG,
		AUTOPLAY_ROLLSPEED,
		PLAYER_AMOUNT,
		SCORE_SAVE,
		SCORE_DELETE,
		DEMO_PLAY,
		//データ
		PANEL_SHOW,
		AUTOPLAY_1P,
		AUTOPLAY_2P,
		DEFAULT_DIFFCULTY,
		DEFAULT_OPTION,
		JUDGEPANEL_SHOWING,
		JUDGESEC_SHOWING,
		//もどる
		EXIT,
		ITEM_Count,
	};

	enum class E_HEYA_PHASE
	{
		SELECT,
		MAX_SONG,
		AUTOPLAY_ROLLSPEED,
		PLAYER_AMOUNT,
		SCORE_DELETE,
		DEFAULT_DIFFCULTY,
		DEFAULT_OPTION,
		EXIT,
	};

	vector<int> m_vec_heya_item;

	string m_fumen_file_path;


	int m_now_select;
	CFIFO m_fade_in;
	E_HEYA_PHASE m_phase;

	void Decide();
	void SelectLeft();
	void SelectRight();
	void PreviousSong();
	void NextSong();
	void NotSelectFolderDraw(int bar_num, int x, int y);
	void SelectFolderDraw(int bar_num, int x, int y);
	void NotSelectBarDraw(int bar_num);
	void SelectBarDraw(int bar_num, int x, int y);

	void CursorDraw(int x, int y);


	const static int BAR_SHOW_AMOUNT = 6;//上下に描画するバーの数

	CAnime m_ani_bar_pos_x = { "Animation/SongSelect/SongBarPositionX" };
	CAnime m_ani_bar_pos_y = { "Animation/SongSelect/SongBarPositionY" };
	CAnime2 m_ani_cursor_decide_yellow = { "Animation/SongSelect/DecideCursorYellow" };
	CAnime2 m_ani_cursor_decide_white = { "Animation/SongSelect/DecideCursorWhite" };
	CAnime2 m_ani_cursor_effect_loop = { "Animation/SongSelect/CursorEffectLoop" };

	const RECT_F RECT_BAR_TOP = { 0.0f,0.0f,640.0f,32.0f };
	const RECT_F RECT_BAR_CENTER = { 0.0f,64.0f,640.0f,160.0f };
	const RECT_F RECT_BAR_BOTTOM = { 0.0f,32.0f,640.0f,32.0f };
	const RECT_F RECT_CURSOR_YELLOW = { 0.0f,0.0f,704.0f,256.0f };
	const RECT_F RECT_CURSOR_YELLOW_EFFECT = { 0.0f,256.0f,704.0f,256.0f };
	const RECT_F RECT_CURSOR_WHITE = { 0.0f,512.0f,704.0f,256.0f };
	const RECT_F RECT_CURSOR_TOP = { 0.0f,0.0f,704.0f,48.0f };
	const RECT_F RECT_CURSOR_CENTER = { 0.0f,48.0f,704.0f,160.0f };
	const RECT_F RECT_CURSOR_BOTTOM = { 0.0f,208.0f,704.0f,48.0f };
	const RECT_N RECT_OVERLAY_TOP = { 0,0,640,12 };
	const RECT_N RECT_OVERLAY_CENTER = { 0,12,640,4 };

	//値は固定
	Point m_bar_pos[MusicGame::SONGSELECT_BAR_AMOUNT];
	const float BAR_MOVE_TIME = 0.15f;//バーの移動にかける時間[sec]

	const float BAR_CENTER_MIN_HEIGHT = 34.0f;
	const float BAR_CENTER_MAX_HEIGHT = 160.0f;
	const float SELECTED_BAR_ANIME_SPEED = 0.126f;


	CCounter m_ct_bar_move;
	CAnime3 m_ani_selected_bar;
	//未選択時用
	CAnime3 m_ani_not_selected_bar;

	int m_move_direction;
	bool m_first_action;
	const float TITLE_FONT_SIZE = 40.0f;

};
