#pragma once

//STLデバッグ機能をOFFにする
#define _HAS_ITERATOR_DEBUGGING	(0)
//使用するヘッダーファイル
#include "MusicGame.h"

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_MAIN,
	OBJ_LANE,
	OBJ_NOTES,
	OBJ_ENSO,
	OBJ_GAUGE,
	OBJ_JUDGE,
	OBJ_COMBO,
	OBJ_TAIKO,
	OBJ_SCORE,
	OBJ_BALLOON,
	OBJ_ROLL,
	OBJ_END,
	OBJ_CHARACTER,
	OBJ_FLYINGNOTES,
	OBJ_BG,
	OBJ_COMBOBALLOON,
	OBJ_RESULT_BG,
	OBJ_DANC,
	OBJ_TITLEPANEL,
	OBJ_SPARK,
	OBJ_DANCER,
	OBJ_KUSUDAMA,
	OBJ_FOOTER,

	OBJ_SONGSELECT,
	OBJ_SONGSELECT_BG,
	OBJ_SONGSELECT_CHARA,
	OBJ_DIFFCULTY_SELECT,
	OBJ_RESULT,
	OBJ_LOADING,
	OBJ_OPTION_SELECT,
	OBJ_NOWSONG,
	OBJ_TIMER,
	OBJ_SCOREPANEL,
	OBJ_STATUSPANEL,
	OBJ_CONTROLL_GUIDE,

	OBJ_DANRESULT,
	OBJ_DANRESULT_SONG,
	OBJ_DANRESULT_STATE,

	OBJ_DANSELECT,
	OBJ_DANSELECT_CONFIRM,

	OBJ_ENTRY,
	OBJ_ENTRY_BG,
	OBJ_MODESELECT,
	OBJ_HEYA,
	OBJ_NAMEPLATE,

	OBJ_BATTLE_GAUGE,
	OBJ_BATTLE_CHARA,
	OBJ_BATTLE,

	OBJ_TITLE,

	OBJ_EXIT,
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_HINT,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
};
//テクスチャネーム----------------------------------
enum TEXTURE_NAME
{
	tex_TILE,
	tex_OPTION,
	tex_DAN_PLATE,
	tex_NOW_SONG,
	tex_NOW_SONG_NUMBER,
	tex_CONTROLL_GUIDE,

	tex_ENTRY_BACKGROUND,
	tex_ENTRY_BG_BOKE,
	tex_ENTRY_BG_BOKE_B,
	tex_ENTRY_ENTRY,
	tex_ENTRY_FIREWORKS,
	tex_ENTRY_LIGHT,
	tex_ENTRY_ENSO_BAR,
	tex_ENTRY_ENSO_CHARA,
	tex_ENTRY_ENSO_TEXT,
	tex_ENTRY_ENSO_CURSOR,
	tex_ENTRY_MODESELECT_OVERLAY,


	//SongSelect
	tex_BOX_NONE,
	tex_BOX_CLOSE = tex_BOX_NONE + GENRE_Count,
	tex_BOX_CLOSE_TEXT,
	tex_BOX_DIFFCULTY,
	tex_BOX_DIFFCULTY_NUMBER,
	tex_DIFFCULTY_BOX_NONE,
	tex_DIFFCULTY_BAR = tex_DIFFCULTY_BOX_NONE + GENRE_Count,
	tex_DIFFCULTY_TEXT,
	tex_DIFFCULTY_ICON,
	tex_DIFFCULTY_CURSOR,
	tex_DIFFCULTY_COURSESYMBOL,
	tex_BACKGROUND_NONE,
	tex_SONGSELECT_CURSOR = tex_BACKGROUND_NONE + GENRE_Count,
	tex_DIFFCULTY_CURSOR2,
	tex_DIFFCULTY_ONI_APPEAR,
	tex_DIFFCULTY_NUM,
	tex_DIFFCULTY_STAR,
	tex_DIFFCULTY_BRANCH,
	tex_DIFFCULTY_OPTION,
	tex_DIFFCULTY_OPTION_ARROW,
	tex_DIFFCULTY_OPTION_BAR,
	tex_DIFFCULTY_OPTION_BAR_BACK,

	
	//Enso
	tex_LINE,
	tex_LINE_YELLOW,
	tex_NOTES,
	tex_JUDGE,
	tex_COMBO,
	tex_COMBO_SILVER,
	tex_COMBO_GOLD,
	tex_COMBO_TEXT,
	tex_NUMBER,
	tex_GAUGE_BASE,
	tex_GAUGE,
	tex_GAUGE_RAINBOW,
	tex_GAUGE_LINE,
	tex_DAN_1P_GAUGE_BASE,
	tex_DAN_1P_GAUGE_BASE_YELLOW,
	tex_DAN_1P_GAUGE,
	tex_DAN_1P_GAUGE_YELLOW,
	tex_DAN_1P_GAUGE_RAINBOW,
	tex_SCORE,
	tex_SCORE_1P,
	tex_HIT_EFFECT,
	tex_HIT_EXPLOSION,
	tex_HIT_EXPLOSION_BIG,
	tex_BALLOON_FUKIDASHI,
	tex_ROLL_NUMBER,
	tex_BALLOON_NUMBER,
	tex_KUSUDAMA_NUMBER,
	tex_ROLL,
	tex_LANE_FLUSH,
	tex_LANE_GOGO,
	tex_FIRE,
	tex_SOUL,
	tex_SOUL_FIRE,

	tex_END_UCHIWA,
	tex_END_BG,
	tex_END_BACHIO, 
	tex_END_TEXT,
	tex_SCORE_RANK,
	tex_DIFFCULTY,
	tex_GAUGE_EXPLOSION,
	tex_NOTES_EFFECT,
	tex_COMBOBALLOON,
	tex_COMBOBALLOON_NUMBER,
	tex_BG_BOTTOM_0,
	tex_BG_BOTTOM_1,
	tex_BG_BOTTOM_CLEAR_0,
	tex_BG_BOTTOM_CLEAR_1,
	tex_BG_BOTTOM_CLEAR_2,
	tex_BG_BOTTOM_CLEAR_3,
	tex_BG_BOTTOM_CLEAR_4,
	tex_BG_BOTTOM_CLEAR_5,
	tex_FOOTER,
	tex_LOADING_FADE,
	tex_LOADING_BG,
	tex_LOADING_WAIT,
	tex_LOADING_PLATE,
	tex_LOADING_CHARA,
	tex_BALLOON_FRAME,
	tex_COMBO_EFFECT,
	tex_GAUGE_YELLOW,
	tex_BRANCH_TEXT,
	tex_BRANCH_LANE,
	tex_NOTES_FIREWORK,
		tex_SPARK,
		tex_CHARACTER_EFFECT, 
		tex_PAPER_IN,
		tex_PAPER_LOOP,
		tex_GAUGE_UPDATE,
		tex_SE_NOTES,
		tex_SCORE_EFFECT,
		tex_ENSO_BESTSCORE,
		tex_JUDGE_PANEL,
		tex_JUDGE_PANEL_NUMBER,
	//段位道場
	tex_DAN_BACKGROUND,
	tex_DAN_GAUGE_BASE,
	tex_DAN_GAUGE,
	tex_DAN_GAUGE_TRIPLE,
	tex_DAN_NUMBER,
	tex_DAN_EXAM_TYPE,
	tex_DAN_EXAM_RANGE,
	tex_DAN_EXAM_NUMBER,
	tex_DAN_GAUGE_NORMA,
	tex_DAN_FAILED,
	tex_DAN_SMALL_NUMBER,
	tex_DAN_BG_TOP0,
	tex_DAN_BG_TOP1,
	tex_DAN_BG_TOP2,
	tex_DAN_BG_TOP3,
	tex_DAN_BG_TOP4,
	tex_DAN_BG_TOP5,
	tex_DAN_GAUGE_ASSIGNMENT,
	tex_DAN_SCREEN,
	tex_DAN_GAUGE_MINI,
	tex_DAN_NUMBER_MINI,
	tex_DAN_GAUGE_BASE_MINI,
		tex_GENRE,
		tex_SONG_NUMBER,
		tex_DAN_RAINBOW,



	//Result
	tex_RESULT_BG,
	tex_RESULT_YAMA,
	tex_RESULT_CLEAR,
	tex_RESULT_CLEAR_YAMA,
	tex_RESULT_HEADER,
	tex_RESULT_PANEL,
	tex_RESULT_PANEL_DIFFCULTY,

	tex_RESULT_NUMBER,
	tex_RESULT_SCORE_NUMBER,
	tex_RESULT_RANK,
	tex_RESULT_CROWN,
	tex_RESULT_SOUL,
	tex_RESULT_FIRE,

	//ResultDan
	tex_DANRESULT_BG,
	tex_DANRESULT_GAUGE_BG,
	tex_DANRESULT_GAUGE_BASE,
	tex_DANRESULT_SONGPANEL,
	tex_DANRESULT_STATEPANEL,
	tex_DANRESULT_SONGPANEL_BG,
	tex_DANRESULT_STATEPANEL_BG,
	tex_DANRESULT_SONGPANEL_NUMBER,
	tex_DANRESULT_STATEPANEL_NUMBER,
	tex_DANRESULT_GAUGE_NUMBER,
	tex_DANRESULT_CLEAR,
	tex_DANRESULT_FAILED,
	tex_DANRESULT_EFFECT,
	tex_DANRESULT_GAUGE_BASE_TRIPLE,
	tex_DANRESULT_GAUGE_TRIPLE,
	tex_DANRESULT_NORMAGAUGE_BG,
	tex_DANRESULT_NORMAGAUGE_BASE,
	tex_DANRESULT_NORMAGAUGE,
	tex_DANRESULT_SCORE_NUMBER,
	tex_DANRESULT_PERCENT,
	tex_DANRESULT_EXAMNUMBER_TRIPLE,
	tex_DANRESULT_EXAMRANGE_TRIPLE,
	tex_DANRESULT_NOTREACH,

	//DanSelect
	tex_DANSELECT_BG,
	tex_DANSELECT_FUSUMA,
	tex_DANSELECT_TEXT,
	tex_DANSELECT_BAR,
	tex_DANSELECT_INFO_BACK,
	tex_DANSELECT_INFO_SONG,
	tex_DANSELECT_INFO_INFO,
	tex_DANSELECT_INFO_GAUGE,
	tex_DANSELECT_INFO_GAUGE_NUMBER,
	tex_DANSELECT_INFO_GAUGE_RANGE,
	tex_DANSELECT_INFO_EXAM_NUMBER,
	tex_DANSELECT_INFO_PERCENT,
	tex_DANSELECT_INFO_EXAM_RANGE,
	tex_DANSELECT_INFO_EXAM_TYPE,
		tex_DANSELECT_CONFIRM_WINDOW,
		tex_DANSELECT_CONFIRM_ICON,
		tex_DANSELECT_CONFIRM_CURSOR,

		tex_EXIT_CHARA,
		tex_EXIT_TEXT,
		tex_EXIT_CURTAIN_LEFT,
		tex_EXIT_CURTAIN,

			tex_HEYA_BG,

			tex_TIMER,
			tex_SCOREPANEL,
		tex_STATUSPANEL,

	tex_DANSELECT_DAN_PLATE,//ここより下には追加しない


};
//オブジェクト番号
enum MapObjects 
{

};

enum SOUND_NAME
{
	//共通
	se_DON,
	se_DON_1P,
	se_DON_2P,
	se_KA,
	se_KA_1P,
	se_KA_2P,
	se_CANCEL,
	se_ERROR,
	bgm_MUSIC,
	bgm_IN,
	se_END,

	//曲選択
	se_SKIP = 11,
	bgm_SONGSELECT,
	se_ONI_APPEAR,
	se_ONI_SWITCHING,

	//演奏
	se_BALLOON = 11,
	se_KUSUDAMA,
	se_EFFECT1,
	se_BATTLE_RESULT,
	bgm_SONG1,
	bgm_SONG2,
	bgm_SONG3,
	se_DAN_NEXTSONG,
	se_DAN_FAILED,
	voice_END,
	voice_50,
	voice_100,//この後には効果音IDを入れない
	voice_50_2 = voice_100 + 50,
	voice_100_2,
	
	//リザルト
	se_RESULT_PON = 11,
	se_RESULT_GAUGE,
	se_RESULT_CROWN,
	se_RESULT_RANK,

	//段位道場
	se_DANRESULT_IN,
	se_DANRESULT_STATEPANEL_SLIDE,
	se_DANRESULT_GAUGE,
	se_DANRESULT_FAILURE,
	se_DANRESULT_CLEAR,
	se_DANRESULT_GOLDCLEAR,

	se_DANSELECT_IN = 11,
	se_DANSELECT_CONFIRM,
	se_DANSELECT_OPTIONCLOSE,
	se_DANSELECT_DECIDE,

	bgm_HEYA = 11,
};

enum PRIORITY
{
	PRIO_TITLE,

	PRIO_ENTRY_BG,
	PRIO_ENTRY,
	PRIO_ENTRY_TIMER,
	PRIO_ENTRY_MODESELECT,

	PRIO_HEYA,

	PRIO_SONGSELECT_BG,
	PRIO_SONGSELECT_DIFFCULTY,
	PRIO_SONGSELECT_CHARA,
	PRIO_SONGSELECT_NOWSONG,
	PRIO_SONGSELECT_TIMER,
	PRIO_SONGSELECT_SCORE,
	PRIO_SONGSELECT_STATUS,
	PRIO_SONGSELECT_GUIDE,
	PRIO_SONGSELECT_SONGSELECT,

	PRIO_DANSELECT,
	PRIO_DANSELECT_CONFIRM,
	PRIO_SONGSELECT_OPTION,

	PRIO_ENSO_BG,
	PRIO_ENSO_DANCER,
	PRIO_ENSO_FOOTER,
	PRIO_BATTLE_CHARACTER,
	PRIO_ENSO_LANE,
	PRIO_ENSO_GAUGE,
	PRIO_ENSO_HIT,
	PRIO_ENSO_NOTES,
	PRIO_ENSO_DANC,
	PRIO_ENSO_TAIKO,
	PRIO_ENSO_FLYINGNOTES,
	PRIO_ENSO_JUDGE,
	PRIO_ENSO_COMBO,
	PRIO_ENSO_CHARACTER,
	PRIO_ENSO_SCORE,
	PRIO_ENSO_COMBOBALLOON,
	PRIO_ENSO_ROLL,
	PRIO_ENSO_BALLOON,
	PRIO_ENSO_KUSUDAMA,
	PRIO_BATTLE_GAUGE,
	PRIO_BATTLE_ANIME,
	PRIO_BATTLE_RESULT,
	PRIO_ENSO_END,
	PRIO_ENSO_TITLE,
	PRIO_ENSO_SPARK,
	PRIO_ENSO_ENSO,

	PRIO_LOADING,

	PRIO_RESULT_BG,
	PRIO_RESULT,

	PRIO_DANRESULT_SONG,
	PRIO_DANRESULT_PANEL,
	PRIO_DANRESULT,

	PRIO_EXIT,
};

//------------------------------------------------

//extern int g_now_select_diffculty;
//extern CNumTexSource g_number_tex;
//------------------------------------------------
//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int m_now_select_diffculty[MusicGame::MAX_PLAYER_AMOUNT];
	bool m_oni_unlock;
	ST_ENSO_OPTION m_default_option;
	bool m_panel_showing;
	int m_default_diffculty;
	unsigned int m_max_song;
	int m_auto_play_roll;
	int m_player_amount;
	bool m_auto_play[MusicGame::MAX_PLAYER_AMOUNT];
	bool m_better_performance[MusicGame::bp_Count];
	bool m_judge_showing;
	bool m_judge_sec_showimg;
	bool m_save_score;
	bool m_bgm_demo_play;
};
//------------------------------------------------

//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------
#include "CCounter.h"
#include "CFIFO.h"
#include "CNumTexSource.h"
#include "CTimeCounter.h"
#include "Function.h"
#include "CEnsoData.h"
#include "CAnime.h"
#include "CAnime2.h"
#include "CAnime3.h"
#include "CLayout.h"
#include "CLayout2.h"
#include "CLayoutGroup.h"
#include "DanC.h"
//----------------------------------------------

//ゲームシーンオブジェクトヘッダ-----------------
#include "CObjLane.h"
#include "CObjNotes.h"
#include "CObjEnso.h"
#include "CObjCombo.h"
#include "CObjJudgeMoji.h"

#include "CObjResult.h"
#include "CObjResultBg.h"
#include "CObjMTaiko.h"
#include "CObjNormaGauge.h"
#include "CObjScore.h"
#include "CObjRoll.h"
#include "CObjBalloon.h"
#include "CObjSystem.h"
#include "CObjCharacter.h"
#include "CObjFlyingNotes.h"
#include "CObjBg.h"
#include "CObjComboBalloon.h"
#include "CObjDanC.h"
#include "CObjTitlePanel.h"
#include "CObjSpark.h"
#include "CObjDancer.h"
#include "CObjKusudama.h"
#include "CObjFooter.h"

#include "CObjSongSelect.h"
#include "CObjSongSelectBG.h"
#include "CObjSongSelectCharacter.h"
#include "CObjDiffcultySelect.h"
#include "CObjEnsoEndEffect.h"
#include "CObjLoading.h"
#include "CObjEnsoOption.h"

#include "CObjDanResult.h"
#include "CObjDanResultPanel.h"
#include "CObjDanResultSongPanel.h"

#include "CObjDanSelect.h"
#include "CObjDanSelectConfirm.h"

#include "CObjEntry.h"
#include "CObjEntryBG.h"
#include "CObjModeSelect.h"
#include "CObjHeya.h"

#include "CObjNowSong.h"
#include "CObjTimer.h"

#include "CObjExit.h"
#include "CObjBattleGauge.h"
#include "CObjEnsoBattle.h"
#include "CObjBattleEndEffect.h"
#include "CObjBattleCharacter.h"

#include "CObjScorePanel.h"
#include "CObjStatusPanel.h"
#include "CObjNamePlate.h"
#include "CObjControllGuide.h"
#include "CObjTitle.h"

//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"
#include "SceneSongSelect.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START SceneMain
//-----------------------------------------------