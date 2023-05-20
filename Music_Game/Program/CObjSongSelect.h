#pragma once
#include "MusicGame.h"
#include "GameHead.h"
#include "GameL\SceneObjManager.h"
#include <thread>
using namespace GameL;

#define BAR_AMOUNT (1 + BAR_SHOW_AMOUNT + BAR_SHOW_AMOUNT)

namespace MusicGame
{
	namespace SongSelect
	{
		const static int BAR_OPEN_OUT_DELAY = 360;//一番上のバー移動開始までの時間
		const static int BAR_OPEN_IN_DELAY = 1270;//一番真ん中に近いバー移動開始までの時間
		const static int BAR_OPEN_INTERVAL = 70;
	}
}

class CObjSongSelect : public CObj
{
public:



	CObjSongSelect() {}
//	CObjSongSelect(vector< vector<ST_FUMEN_DATA>>& vec_fumen) { m_vec_fumen_bar = vec_fumen; }
	~CObjSongSelect();
	void Init();
	void Action();
	void Draw();
	void Delete();
	void SubThrActionDraw();
	void ResultToSongSelect();
	//難易度選択画面から選曲に戻ってきたとき用
	void DiffcultyToSongSelect();
	MusicGame::SongSelect::ST_BAR_INFO GetNowSelectSong() { return MusicGame::SongSelect::g_vec_all_fumen_bar[m_vec_songselect_fumen[m_now_select]]; }
	ST_ENSO_OPTION GetEnsoOption() { return m_enso_option; }
	void SongDecide();
	ST_ENSO_OPTION m_enso_option;
	int GetNowSelectNumber() { return m_vec_songselect_fumen[m_now_select]; }

private:
	

	enum E_SONGSELECT_PHASE
	{
		PHASE_SONG_SELECT,
		PHASE_DIFFCULTY_SELECT,
		PHASE_DIFFCULTY_SELECT_OPTION,
		PHASE_DECIDE,
		PHASE_EXIT,
	};


	const int CLOSE_BOX_INTERVAL = 7;


	list<string> m_list_fumen_path;
	list<string> m_list_folder_path;


	vector<int> m_vec_songselect_fumen;

	string m_fumen_file_path;


	int m_now_select;
	int m_now_folder;
	int m_open_folder;
	int m_before_background_color;

	bool m_key_flag[MusicGame::TAIKO_FLUSH_TYPE];
	bool m_key_flag_skip[2];

	CFIFO m_fade_in;

	void LoadDirectory(string path);

	void Decide();
	void SelectLeft();
	void SelectRight();
	void FolderOpen();
	void FolderClose();

	void FolderOpenStart();

	void NotSelectFolderDraw(int bar_num,int x,int y);
	void SelectFolderDraw(int bar_num, int x, int y);
	void NotSelectBarDraw(int bar_num);
	void SelectBarDraw(int bar_num, int x, int y);
	void PreviousSong();
	void NextSong();
	void PreviousSkip();
	void NextSkip();

	void FumenListDelete();
	void SongSelectBgmStart();
	void CursorDraw(int x,int y);
	void FavoliteFolderSet();
	void DiffcultyBarDraw(int x,int y,int bar_num);

	void BackGroundColorChange();
	int GetBarColor(int bar_num);

	void SongBarCreate();

	void ActionSub();

	const static int BAR_SHOW_AMOUNT = 6;//上下に描画するバーの数

	E_SONGSELECT_PHASE m_phase;
	CAnime m_ani_bar_pos_x = { "Animation/SongSelect/SongBarPositionX" };
	CAnime m_ani_bar_pos_y = { "Animation/SongSelect/SongBarPositionY" };
	CAnime m_ani_folder_open_in_scale_x = { "Animation/SongSelect/SongBarFolderOpenInScaleX" };
	CAnime m_ani_folder_open_out_scale_x = { "Animation/SongSelect/SongBarFolderOpenOutScaleX" };
	CAnime m_ani_songselect_fadeout = { "Animation/SongSelect/SongTexFadeout" };
	CAnime2 m_ani_open_bar_move_in[BAR_AMOUNT];
	CAnime2 m_ani_open_bar_move_out[BAR_AMOUNT];
	CAnime2 m_ani_open_title_opacity = { "Animation/SongSelect/FolderOpenTitleOpacity" };
	CAnime2 m_ani_background_scroll = { "Animation/SongSelect/BackGroundScroll" };
	CAnime2 m_ani_background_fade = { "Animation/SongSelect/BackGroundFade" };
	CAnime2 m_ani_edit_score_fade = { "Animation/SongSelect/EditScoreFade" };
	CAnime2 m_ani_cursor_decide_yellow = { "Animation/SongSelect/DecideCursorYellow" };
	CAnime2 m_ani_cursor_decide_white = { "Animation/SongSelect/DecideCursorWhite" };
	CAnime2 m_ani_cursor_effect_loop = { "Animation/SongSelect/CursorEffectLoop" };

	const RECT_F RECT_BAR_TOP = { 0.0f,0.0f,640.0f,32.0f };
	const RECT_F RECT_BAR_CENTER = { 0.0f,64.0f,640.0f,160.0f };
	const RECT_F RECT_BAR_BOTTOM = { 0.0f,32.0f,640.0f,32.0f };
	const RECT_F RECT_CURSOR_YELLOW = { 0.0f,0.0f,704.0f,256.0f };
	const RECT_F RECT_CURSOR_YELLOW_EFFECT = { 0.0f,256.0f,704.0f,256.0f };
	const RECT_F RECT_CURSOR_WHITE = { 0.0f,512.0f,704.0f,256.0f };
	const int SKIP_BAR = 7;//スキップした時に何曲分スキップするか。
	const RECT_F RECT_CURSOR_TOP =		{ 0.0f,0.0f,704.0f,48.0f };
	const RECT_F RECT_CURSOR_CENTER =	{ 0.0f,48.0f,704.0f,160.0f };
	const RECT_F RECT_CURSOR_BOTTOM =	{ 0.0f,208.0f,704.0f,48.0f };
	const RECT_N RECT_OVERLAY_TOP =	{ 0,0,640,12 };
	const RECT_N RECT_OVERLAY_CENTER =	{ 0,12,640,4 };

	//値は固定
	Point m_bar_pos[MusicGame::SONGSELECT_BAR_AMOUNT];
	const float BAR_MOVE_TIME = 0.15f;//バーの移動にかける時間[sec]

	const float BAR_CENTER_MIN_HEIGHT = 34.0f;
	const float BAR_CENTER_MAX_HEIGHT = 160.0f;
	const int BAR_MOVE_SCALE_DELAY = 400;//バーの移動終了後縦に広がり始めるまでの時間[ms]
	const float BAR_ANIME_SPEED = 0.167f;
	const Point BAR_DIFFCULTY_OFFSET = { 640,378 };
	const RECT_F RECT_BAR_DIFFCULTY = { 0.0f,0.0f,120.0f,64.0f };
	const Point BAR_DIFFCULTY_NUM_OFFSET = { 89,17 };
	const RECT_F RECT_BAR_DIFFCULTY_NUM = { 0.0f,0.0f,24.0f,28.0f };
	const Point BAR_CROWN_OFFSET = { -284,-75 };
	const Point BAR_CROWN_NOT_SELECT_OFFSET = { -284,-12 };
	const float SELECTED_BAR_ANIME_SPEED = 0.126f;


	CCounter m_ct_bar_move;
	CTimeCounter m_ct_bar_scale_y_delay;
	const int BGM_LOOP_START_DELAY = 1537;
	CTimeCounter m_ct_bgm_loop_start;
	CTimeCounter m_ct_open_bar_move_delay;
	CAnime3 m_ani_selected_bar;
	//未選択時用
	CAnime3 m_ani_not_selected_bar;

	bool m_bgm_play_flag;
	bool m_bgm_loop_flag;
	bool m_demo_play_flag;
	bool m_demo_load_success;
	int m_move_direction;
	bool m_first_action;
	const float TITLE_FONT_SIZE = 40.0f;
	CAnime3 m_ani_ura;

	CTexture tex_songselect_crown;
	CTexture tex_songselect_rank;
	const RECT_N RECT_CROWN = { 0,0,48,48 };
	const RECT_N RECT_RANK = { 0,0,48,48 };
	const Point STATUS_PANEL_POS = { 11,209 };

	CFIFO m_fadeout_to_entry;

	thread* thr_load_music;
};
