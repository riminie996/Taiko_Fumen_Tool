#include "CObjSystem.h"
#include "GameHead.h"
#include "GameL\Audio.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\WinInputs.h"
#include "GameL\MultiThread.h"
//メモリリーク検出用
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#define new DBG_NEW
#endif  // _DEBUG

CObjSystem::~CObjSystem()
{
	MusicGame::SongSelect::g_vec_all_fumen_bar.clear();
	MusicGame::SongSelect::g_vec_all_fumen_bar.shrink_to_fit();
	MusicGame::SongSelect::g_vec_folder_bar.clear();
	MusicGame::SongSelect::g_vec_folder_bar.shrink_to_fit();
	MusicGame::SongSelect::g_vec_folder_fumen.clear();
	MusicGame::SongSelect::g_vec_folder_fumen.shrink_to_fit();
	m_list_history_fumen_path.clear();
	std::string().swap(MusicGame::g_now_select_songtitle);

	//キャラクターテクスチャの解放
	MusicGame::g_tex_normal.clear();
	MusicGame::g_tex_normal.shrink_to_fit();
	MusicGame::g_tex_10combo.clear();
	MusicGame::g_tex_10combo.shrink_to_fit();
	MusicGame::g_tex_10combo_max.clear();
	MusicGame::g_tex_10combo_max.shrink_to_fit();
	MusicGame::g_tex_clear.clear();
	MusicGame::g_tex_clear.shrink_to_fit();
	MusicGame::g_tex_clear_in.clear();
	MusicGame::g_tex_clear_in.shrink_to_fit();
	MusicGame::g_tex_gogostart.clear();
	MusicGame::g_tex_gogostart.shrink_to_fit();
	MusicGame::g_tex_gogo.clear();
	MusicGame::g_tex_gogo.shrink_to_fit();
	MusicGame::g_tex_soulin.clear();
	MusicGame::g_tex_soulin.shrink_to_fit();
	MusicGame::g_tex_balloon_broke.clear();
	MusicGame::g_tex_balloon_broke.shrink_to_fit();
	MusicGame::g_tex_balloon_miss.clear();
	MusicGame::g_tex_balloon_miss.shrink_to_fit();
	MusicGame::g_tex_balloon_break.clear();
	MusicGame::g_tex_balloon_break.shrink_to_fit();

	MusicGame::SongSelect::g_tex_chara_start.clear();
	MusicGame::SongSelect::g_tex_chara_start.shrink_to_fit();
	MusicGame::SongSelect::g_tex_chara_select.clear();
	MusicGame::SongSelect::g_tex_chara_select.shrink_to_fit();
	MusicGame::SongSelect::g_tex_chara_loop.clear();
	MusicGame::SongSelect::g_tex_chara_loop.shrink_to_fit();


//	GameLoop::DeleteThread(thr_loading);
}
//初期化
void CObjSystem::Init()
{

	Draw::LoadImageW(L"Graphics/tile.png", tex_TILE, TEX_SIZE_64);
	m_first_action = false;
	m_load_fumen = false;
	m_load_tex = false;
	m_load_sound = false;
	m_load_game = false;
	thr_loading = new thread(&CObjSystem::FirstAction, this);
//	GameLoop::AddThread(thr_loading);
}
void CObjSystem::Delete()
{
	thr_loading->join();
	delete thr_loading;
}

void CObjSystem::FirstAction()
{
	if (m_first_action == true)return;



	list<string> fumen_path;
	list<string> folder_path;
	MusicGame::SongSelect::LoadDirectory(fumen_path, folder_path, "Fumen\\");


	MusicGame::SongSelect::FumenListCreate(fumen_path);

	for (int i = 0; i < MusicGame::SongSelect::g_vec_folder_fumen.size(); i++)
	{
		MusicGame::SongSelect::CloseBoxInsert(MusicGame::SongSelect::g_vec_folder_fumen[i]);
	}

	string str_fumen_command;
	//ファイルを開く
	ifstream ifs(SONG_HISTORY_PATH);
	if (!ifs)
	{
		ifs.close();
	}

	while (getline(ifs, str_fumen_command))
	{
		m_list_history_fumen_path.push_back(str_fumen_command);
	}

	m_load_fumen = true;

	for (int i = 0; i < TAIKO_FLUSH_Count; i++)
	{
		m_key_flag[i] = false;
		m_key[i] = false;
	}
	m_song_number = 1;

	Draw::LoadImageW(L"Graphics/NowSong.png", tex_NOW_SONG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/NowSongNumber.png", tex_NOW_SONG_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/8_End/Chara.png", tex_EXIT_CHARA, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/8_End/Text.png", tex_EXIT_TEXT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/8_End/CurtainLeft.png", tex_EXIT_CURTAIN_LEFT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/8_End/Curtain.png", tex_EXIT_CURTAIN, TEX_SIZE_64);


	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/EnsoOption.png", tex_DIFFCULTY_OPTION, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/OptionArrow.png", tex_DIFFCULTY_OPTION_ARROW, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/EnsoOptionBar.png", tex_DIFFCULTY_OPTION_BAR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/EnsoOptionBarBack.png", tex_DIFFCULTY_OPTION_BAR_BACK, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/Timer.png", tex_TIMER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/Score/Score.png", tex_SCOREPANEL, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/StatePanel.png", tex_STATUSPANEL, TEX_SIZE_64);


	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Combo.png", tex_NUMBER, TEX_SIZE_64);

	MusicGame::CommonTextureLoader();
	m_load_tex = true;


	//共通効果音読み込み
	Audio::LoadAudio2(se_DON, "Sound/Taiko/dong.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_DON_1P, "Sound/Taiko/dong1P.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_DON_2P, "Sound/Taiko/dong2P.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_KA, "Sound/Taiko/ka.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_KA_1P, "Sound/Taiko/ka1P.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_KA_2P, "Sound/Taiko/ka2P.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_CANCEL, "Sound/Cancel.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_ERROR, "Sound/Error.ogg", SOUND_TYPE::EFFECT);

	m_load_sound = true;


	//ロード時間を短くするためデバッグするときはコメントアウトしておく
//	SongSelectStart();

	ST_ENSO_OPTION option;
	//	option.random = option.RANDOM_DETARAME;
	//	option.doron = true;
	//	((UserData*)Save::GetData())->m_now_select_diffculty = DIFF_DAN;
	//	EnsoStart("Fumen/段位道場/挑戦！「#コンパス」コース！/挑戦！「#コンパス」コース！.tja",option);
	((UserData*)Save::GetData())->m_now_select_diffculty[0] = DIFF_ONI;
	//	EnsoBattleStart("Fumen_Battle/hikarinokanatahe-ura/ヒカリノカナタヘ(裏).tja",option);
	//	EnsoBattleStart("Fumen_Battle/闇の魂/闇の魂.tja",option);
	//	EnsoBattleStart("hikarinokanatahe-ura/夜桜繚乱感謝祭.tja",option);
	//	EnsoStart("Fumen/03-Vocaloid/01/95 KING/KING.tja",option);


	//	DanResultStart();



		//ST_SCORE_DATA score;

		//score.max_combo = 55555;
		//score.ct_gauge = { CCounter(100,0,100,STOP) };
		//for (int i = 0; i < JUDGE_COUNT; i++)
		//	score.judge[i] = i * 100;
		//score.score = 4000;
		//score.score_rank = E_SCORE_RANK::RANK_IKI_BRONZE;
		//score.crown = E_CROWN::CROWN_NONE;
		//ResultStart(score);

	//	DanSelectStart();

	//	EntryStart();

	//	HeyaStart();
	TitleStart();
	//	((UserData*)Save::GetData())->m_player_amount = 1;
	//	MusicGame::g_mode = E_GAME_MODE::ENSO;

	if (USER_DATA->m_player_amount <= 0)
	{
		USER_DATA->m_player_amount = 1;
	}

	m_first_action = true;


}
//進行
void CObjSystem::Action()
{

	for (int i = 0; i < TAIKO_FLUSH_Count * ((UserData*)Save::GetData())->m_player_amount; i++)
		m_key[i] = false;

	char key[] =
	{
		'F',
		'J',
		'D',
		'K',
		'C',
		'N',
		'X',
		'M',
	};

	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{
		if (Input::GetVKey(key[0 + TAIKO_FLUSH_Count * i]))
		{
			if (m_key_flag[LEFT_DON + TAIKO_FLUSH_Count * i] == true)
				m_key[LEFT_DON + TAIKO_FLUSH_Count * i] = true;
			m_key_flag[LEFT_DON + TAIKO_FLUSH_Count * i] = false;
		}
		else
			m_key_flag[LEFT_DON + TAIKO_FLUSH_Count * i] = true;

		if (Input::GetVKey(key[1 + TAIKO_FLUSH_Count * i]))
		{
			if (m_key_flag[RIGHT_DON + TAIKO_FLUSH_Count * i] == true)
				m_key[RIGHT_DON + TAIKO_FLUSH_Count * i] = true;
			m_key_flag[RIGHT_DON + TAIKO_FLUSH_Count * i] = false;
		}
		else
			m_key_flag[RIGHT_DON + TAIKO_FLUSH_Count * i] = true;

		if (Input::GetVKey(key[2 + TAIKO_FLUSH_Count * i]))
		{
			if (m_key_flag[LEFT_KA + TAIKO_FLUSH_Count * i] == true)
				m_key[LEFT_KA + TAIKO_FLUSH_Count * i] = true;
			m_key_flag[LEFT_KA + TAIKO_FLUSH_Count * i] = false;
		}
		else
			m_key_flag[LEFT_KA + TAIKO_FLUSH_Count * i] = true;

		if (Input::GetVKey(key[3 + TAIKO_FLUSH_Count * i]))
		{
			if (m_key_flag[RIGHT_KA + TAIKO_FLUSH_Count * i] == true)
				m_key[RIGHT_KA + TAIKO_FLUSH_Count * i] = true;
			m_key_flag[RIGHT_KA + TAIKO_FLUSH_Count * i] = false;
		}
		else
			m_key_flag[RIGHT_KA + TAIKO_FLUSH_Count * i] = true;
	}
}
//描画
void CObjSystem::Draw()
{
	if (m_first_action == true)return;

	DrawFill(tex_TILE, MusicGame::RECT_TILE_BLACK);

	Font::StrDraw(L"LOADING Fumen...", 312, 192, 48, ColorA::White);
	Font::StrDraw(L"LOADING Texture...", 312, 240, 48, ColorA::White);
	Font::StrDraw(L"LOADING Sound...", 312, 288, 48, ColorA::White);
	if (m_load_sound == true)
		Font::StrDraw(L"GAME START", 312, 336, 48, ColorA::White);

	if(m_load_fumen == true)
	Font::StrDraw(L"OK", 840, 192, 48, ColorA::Green);
	if(m_load_tex == true)
	Font::StrDraw(L"OK", 840, 240, 48, ColorA::Green);
	if(m_load_sound == true)
	Font::StrDraw(L"OK", 840, 288, 48, ColorA::Green);
}

void CObjSystem::SubThrActionDraw()
{
	FirstAction();
}

bool CObjSystem::GetInput(E_TAIKO_FLUSH taiko,int player)
{
	bool status = m_key[taiko + TAIKO_FLUSH_Count * player];
	m_key[taiko + TAIKO_FLUSH_Count * player] = false;
	return status;
}

void CObjSystem::SongSelectStart()
{

	Audio::LoadAudio2(se_SKIP, "Sound/2_Songselect/Skip.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_ONI_APPEAR, "Sound/2_Songselect/Oni_Appear.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_ONI_SWITCHING, "Sound/2_Songselect/Switch.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(bgm_IN, "Sound/2_Songselect/BGM_START.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(bgm_SONGSELECT, "Sound/2_Songselect/BGM_LOOP.ogg", SOUND_TYPE::BACK_MUSIC);

	Draw::InfoReset();


	CObjSongSelect* lselect = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);

	//ステージセレクトが既に存在する場合生成しない
	if (lselect != nullptr)
	{
		lselect->ResultToSongSelect();
	}
	else
	{
		CObjSongSelect* select = new CObjSongSelect();
		Objs::InsertObj(select, OBJ_SONGSELECT, PRIO_SONGSELECT_SONGSELECT);
	}

	CObjSongSelectBG* bg = new CObjSongSelectBG();
	Objs::InsertObj(bg, OBJ_SONGSELECT_BG, PRIO_SONGSELECT_BG);
	CObjNowSong* nowsong = new CObjNowSong(MusicGame::SONGSELECT_NOW_SONG);
	Objs::InsertObj(nowsong, OBJ_NOWSONG, PRIO_SONGSELECT_NOWSONG);
	if (((UserData*)Save::GetData())->m_better_performance[MusicGame::E_BETTER_PERFORMANCE::bp_CHARA] == true)
	{
		CObjSongSelectCharacter* chara = new CObjSongSelectCharacter();
		Objs::InsertObj(chara, OBJ_SONGSELECT_CHARA, PRIO_SONGSELECT_CHARA);
	}

	Point timer_pos = { 1193,88 };
	CObjTimer* timer = new CObjTimer(timer_pos, 100,true);
	Objs::InsertObj(timer, OBJ_TIMER,PRIO_SONGSELECT_TIMER);
	CObjScorePanel* scorepanel = new CObjScorePanel();
	Objs::InsertObj(scorepanel, OBJ_SCOREPANEL, PRIO_SONGSELECT_SCORE);
	CObjStatusPanel* sta = new CObjStatusPanel();
	Objs::InsertObj(sta, OBJ_STATUSPANEL, PRIO_SONGSELECT_STATUS);
	CObjControllGuide* guide = new CObjControllGuide();
	Objs::InsertObj(guide, OBJ_CONTROLL_GUIDE, PRIO_SONGSELECT_GUIDE);

	AddSongNumber();//1曲増やす
}

void CObjSystem::SongSelectEnd()
{
	CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);
	select->SetStatus(false);
	CObjSongSelectBG* bg = (CObjSongSelectBG*)Objs::GetObj(OBJ_SONGSELECT_BG);
	bg->SetStatus(false);
	CObjDiffcultySelect* diffculty = (CObjDiffcultySelect*)Objs::GetObj(OBJ_DIFFCULTY_SELECT);
	if (diffculty != nullptr)
		diffculty->SetStatus(false); 
	CObjSongSelectCharacter* chara = (CObjSongSelectCharacter*)Objs::GetObj(OBJ_SONGSELECT_CHARA);
	CObjNowSong* nowsong = (CObjNowSong*)Objs::GetObj(OBJ_NOWSONG);
	nowsong->SetStatus(false);
	CObjTimer* timer = (CObjTimer*)Objs::GetObj(OBJ_TIMER);
	timer->SetStatus(false);
	CObjStatusPanel* sta = (CObjStatusPanel*)Objs::GetObj(OBJ_STATUSPANEL);
	sta->SetStatus(false);
	CObjControllGuide* guide = (CObjControllGuide*)Objs::GetObj(OBJ_CONTROLL_GUIDE);
	guide->SetStatus(false);

	if(chara!=nullptr)
	chara->SetStatus(false);
}

void CObjSystem::EnsoStart(string fumen_path, ST_ENSO_OPTION option)
{

	//段位道場用

	if (((UserData*)Save::GetData())->m_now_select_diffculty[0] == DIFF_DAN)
	{


		Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Base_Dan.png", tex_GAUGE_BASE, TEX_SIZE_64);
		Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Base_Dan_Yellow.png", tex_DAN_1P_GAUGE_BASE_YELLOW, TEX_SIZE_64);
		Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Dan_Yellow.png", tex_DAN_1P_GAUGE_YELLOW, TEX_SIZE_64);
		Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/Rainbow_Dan.png", tex_DAN_1P_GAUGE_RAINBOW, TEX_SIZE_64);


		Audio::LoadAudio2(se_DAN_NEXTSONG, "Sound/6_DanEnso/Section.ogg", EFFECT);
		Audio::LoadAudio2(se_DAN_FAILED, "Sound/6_DanEnso/Failed.ogg", EFFECT);
	}
	else
	{
		Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Base.png", tex_GAUGE_BASE, TEX_SIZE_64);
		Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Rainbow.png", tex_GAUGE_RAINBOW, TEX_SIZE_64);

		Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Line.png", tex_GAUGE_LINE, TEX_SIZE_64);
	}
		Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P.png", tex_GAUGE, TEX_SIZE_64);
		Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Yellow.png", tex_GAUGE_YELLOW, TEX_SIZE_64);

	Draw::InfoReset();

	CObjLane* lane = new CObjLane();
	Objs::InsertObj(lane, OBJ_LANE, PRIO_ENSO_LANE);




	CObjNormaGauge* gauge = new CObjNormaGauge();
	Objs::InsertObj(gauge, OBJ_GAUGE, PRIO_ENSO_GAUGE);

	CObjJudgeMoji* judge = new CObjJudgeMoji();
	Objs::InsertObj(judge, OBJ_JUDGE, PRIO_ENSO_JUDGE);

	CObjMTaiko* taiko = new CObjMTaiko();
	Objs::InsertObj(taiko, OBJ_TAIKO, PRIO_ENSO_TAIKO);

	CObjCombo* combo = new CObjCombo();
	Objs::InsertObj(combo, OBJ_COMBO, PRIO_ENSO_COMBO);

	CObjScore* score = new CObjScore();
	Objs::InsertObj(score, OBJ_SCORE, PRIO_ENSO_SCORE);

	CObjBalloon* balloon = new CObjBalloon();
	Objs::InsertObj(balloon, OBJ_BALLOON, PRIO_ENSO_BALLOON);


	CObjRoll* roll = new CObjRoll();
	Objs::InsertObj(roll, OBJ_ROLL, PRIO_ENSO_ROLL);
	CObjFlyingNotes* flying = new CObjFlyingNotes();
	Objs::InsertObj(flying, OBJ_FLYINGNOTES, PRIO_ENSO_FLYINGNOTES);

	if (((UserData*)Save::GetData())->m_better_performance[MusicGame::E_BETTER_PERFORMANCE::bp_CHARA] == true)
	{
		CObjCharacter* chara = new CObjCharacter();
		Objs::InsertObj(chara, OBJ_CHARACTER, PRIO_ENSO_CHARACTER);
	}




	CObjComboBalloon* cballoon = new CObjComboBalloon();
	Objs::InsertObj(cballoon, OBJ_COMBOBALLOON, PRIO_ENSO_COMBOBALLOON);

	CObjTitlePanel* title = new CObjTitlePanel();
	Objs::InsertObj(title, OBJ_TITLEPANEL, PRIO_ENSO_TITLE);

	if (USER_DATA->m_now_select_diffculty[0] != DIFF_DAN)
	{
		CObjKusudama* kusudama = new CObjKusudama();
		Objs::InsertObj(kusudama, OBJ_KUSUDAMA, PRIO_ENSO_KUSUDAMA);
	}
	if (USER_DATA->m_player_amount == 1)
	{
		CObjSpark* spark = new CObjSpark();
		Objs::InsertObj(spark, OBJ_SPARK, PRIO_ENSO_SPARK);
	}


	Audio::LoadAudio2(se_BALLOON, "Sound/3_Enso/Balloon.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_KUSUDAMA, "Sound/3_Enso/Kusudama.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(voice_50, "Sound/3_Enso/Combo/50.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(voice_50_2, "Sound/3_Enso/Combo_2P/50.ogg", SOUND_TYPE::EFFECT);

	int count = 0;

	for (int i = 100; i <= 5000; i += 100)
	{
		string str = "Sound/3_Enso/Combo/" + to_string(i) + ".ogg";
		Audio::LoadAudio2(voice_100 + count, str.c_str(), SOUND_TYPE::EFFECT);
		count++;
	}
	count = 0;
	if (((UserData*)Save::GetData())->m_player_amount >= 2)
	{
		for (int i = 100; i <= 5000; i += 100)
		{
			string str = "Sound/3_Enso/Combo_2P/" + to_string(i) + ".ogg";
			Audio::LoadAudio2(voice_100_2 + count, str.c_str(), SOUND_TYPE::EFFECT);
			count++;
		}
	}
	CObjEnso* enso = new CObjEnso(fumen_path,option);
	Objs::InsertObj(enso, OBJ_ENSO, PRIO_ENSO_ENSO);


	//CObjEnsoEndEffect* end = new CObjEnsoEndEffect();
	//Objs::InsertObj(end, OBJ_END, PRIO_ENSO_END);

}

void CObjSystem::EnsoEnd()
{

	CObjNotes* notes = (CObjNotes*)Objs::GetObj(OBJ_NOTES);
	notes->SetStatus(false);
	CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);
	lane->SetStatus(false);

	CObjJudgeMoji* judge = (CObjJudgeMoji*)Objs::GetObj(OBJ_JUDGE);
	judge->SetStatus(false);
	CObjMTaiko* taiko = (CObjMTaiko*)Objs::GetObj(OBJ_TAIKO);
	taiko->SetStatus(false);
	CObjCombo* combo = (CObjCombo*)Objs::GetObj(OBJ_COMBO);
	combo->SetStatus(false);
	CObjScore* score = (CObjScore*)Objs::GetObj(OBJ_SCORE);
	score->SetStatus(false);
	CObjBalloon* balloon = (CObjBalloon*)Objs::GetObj(OBJ_BALLOON);
	balloon->SetStatus(false);
	CObjRoll* roll = (CObjRoll*)Objs::GetObj(OBJ_ROLL);
	roll->SetStatus(false);
	CObjEnsoEndEffect* end = (CObjEnsoEndEffect*)Objs::GetObj(OBJ_END);
	end->SetStatus(false);

	CObjCharacter* chara = (CObjCharacter*)Objs::GetObj(OBJ_CHARACTER);
	if (chara != nullptr)
		chara->SetStatus(false);

	CObjFlyingNotes* flying = (CObjFlyingNotes*)Objs::GetObj(OBJ_FLYINGNOTES);
	flying->SetStatus(false);

	CObjBg* bg = (CObjBg*)Objs::GetObj(OBJ_BG);
	if (bg != nullptr)
		bg->SetStatus(false);

	CObjComboBalloon* cballoon = (CObjComboBalloon*)Objs::GetObj(OBJ_COMBOBALLOON);
	cballoon->SetStatus(false);
	CObjLoading* loading = (CObjLoading*)Objs::GetObj(OBJ_LOADING);
	if(loading != nullptr)
	loading->SetStatus(false);
	CObjTitlePanel* title = (CObjTitlePanel*)Objs::GetObj(OBJ_TITLEPANEL);
	title->SetStatus(false);
	CObjSpark* spark = (CObjSpark*)Objs::GetObj(OBJ_SPARK);

	if (spark != nullptr)
		spark->SetStatus(false);

	CObjDancer* dancer = (CObjDancer*)Objs::GetObj(OBJ_DANCER);
	if (dancer != nullptr)
		dancer->SetStatus(false);

	CObjFooter* footer = (CObjFooter*)Objs::GetObj(OBJ_FOOTER);
	if (footer != nullptr)
		footer->SetStatus(false);
	CObjKusudama* kusudama = (CObjKusudama*)Objs::GetObj(OBJ_KUSUDAMA);
	if(kusudama!=nullptr)
	kusudama->SetStatus(false);
}

void CObjSystem::ResultStart(ST_SCORE_DATA score_data)
{
	Audio::LoadAudio2(se_RESULT_PON, "Sound/4_Result/Pon.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_RESULT_GAUGE, "Sound/4_Result/Gauge.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_RESULT_CROWN, "Sound/4_Result/CrownIn.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_RESULT_RANK, "Sound/4_Result/RankIn.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(bgm_IN, "Sound/4_Result/ResultIn.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(bgm_MUSIC, "Sound/4_Result/Result.ogg", SOUND_TYPE::BACK_MUSIC);



	CObjResult* result = new CObjResult(score_data);
	Objs::InsertObj(result, OBJ_RESULT, PRIO_RESULT);
	CObjResultBg* bg = new CObjResultBg();
	Objs::InsertObj(bg, OBJ_RESULT_BG, PRIO_RESULT_BG);


	Draw::InfoReset();
}

void CObjSystem::ResultEnd()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	if(enso!=nullptr)
	enso->SetStatus(false);
	CObjNormaGauge* gauge = (CObjNormaGauge*)Objs::GetObj(OBJ_GAUGE);
	if (gauge != nullptr)
	gauge->SetStatus(false);

	CObjResult* result = (CObjResult*)Objs::GetObj(OBJ_RESULT);
	
	if(result!=nullptr)
		result->SetStatus(false);
	CObjResultBg* bg = (CObjResultBg*)Objs::GetObj(OBJ_RESULT_BG);
	if(bg!=nullptr)
	bg->SetStatus(false);
}

void CObjSystem::DanResultStart(ST_SCORE_DATA score_data)
{
	Audio::LoadAudio2(se_RESULT_PON, "Sound/4_Result/Pon.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_RESULT_GAUGE, "Sound/4_Result/Gauge.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_RESULT_CROWN, "Sound/4_Result/CrownIn.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_RESULT_RANK, "Sound/4_Result/RankIn.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(bgm_IN, "Sound/7_DanResult/ResultIn_Dan.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(bgm_MUSIC, "Sound/7_DanResult/Result_Dan.ogg", SOUND_TYPE::BACK_MUSIC);




	Audio::LoadAudio2(se_DANRESULT_IN, "Sound/7_DanResult/ResultInVoice.ogg", EFFECT);
	Audio::LoadAudio2(se_DANRESULT_STATEPANEL_SLIDE, "Sound/7_DanResult/Dan_Slide.ogg", EFFECT);
	Audio::LoadAudio2(se_DANRESULT_GAUGE, "Sound/7_DanResult/Dan_Gauge.ogg", BACK_MUSIC);
	Audio::LoadAudio2(se_DANRESULT_FAILURE, "Sound/7_DanResult/Failure.ogg", EFFECT);
	Audio::LoadAudio2(se_DANRESULT_CLEAR, "Sound/7_DanResult/Success.ogg", EFFECT);
	Audio::LoadAudio2(se_DANRESULT_GOLDCLEAR, "Sound/7_DanResult/BetterSuccess.ogg", EFFECT);

	Draw::InfoReset();

	CObjDanResult* bg = new CObjDanResult(score_data);
	Objs::InsertObj(bg, OBJ_DANRESULT, PRIO_DANRESULT);
	CObjDanResultSongPanel* song = new CObjDanResultSongPanel();
	Objs::InsertObj(song, OBJ_DANRESULT_SONG, PRIO_DANRESULT_SONG);
}
void CObjSystem::DanResultEnd()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	if (enso != nullptr)
		enso->SetStatus(false);
	CObjDanResult* bg = (CObjDanResult*)Objs::GetObj(OBJ_DANRESULT);
	if(bg != nullptr)
	bg->SetStatus(false);
	CObjDanResultPanel* panel = (CObjDanResultPanel*)Objs::GetObj(OBJ_DANRESULT_STATE);
	if (panel != nullptr)
		panel->SetStatus(false);
	CObjDanResultSongPanel* song = (CObjDanResultSongPanel*)Objs::GetObj(OBJ_DANRESULT_SONG);
	if(song != nullptr)
	song->SetStatus(false);
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);
	if (dan != nullptr)
		dan->SetStatus(false);
}

void CObjSystem::DanSelectStart()
{
	Audio::LoadAudio2(se_DANSELECT_IN, "Sound/5_DanSelect/Start.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_DANSELECT_CONFIRM, "Sound/5_DanSelect/Select.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_DANSELECT_OPTIONCLOSE, "Sound/5_DanSelect/OptionClose.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_DANSELECT_DECIDE, "Sound/5_DanSelect/Decide.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(bgm_IN, "Sound/5_DanSelect/BGM_IN.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(bgm_MUSIC, "Sound/5_DanSelect/BGM_LOOP.ogg", SOUND_TYPE::BACK_MUSIC);




	CObjDanSelect* select = new CObjDanSelect();
	Objs::InsertObj(select, OBJ_DANSELECT, PRIO_DANSELECT);

	USER_DATA->m_player_amount = 1;
}

void CObjSystem::DanSelectEnd()
{
	CObjDanSelect* select = (CObjDanSelect*)Objs::GetObj(OBJ_DANSELECT);
	select->SetStatus(false);
	CObjDanSelectConfirm* confirm = (CObjDanSelectConfirm*)Objs::GetObj(OBJ_DANSELECT_CONFIRM);
	confirm->SetStatus(false);
}

void CObjSystem::EntryStart()
{


	CObjEntry* entry = new CObjEntry();
	Objs::InsertObj(entry, OBJ_ENTRY, PRIO_ENTRY);
	CObjEntryBG * bg = new CObjEntryBG();
	Objs::InsertObj(bg, OBJ_ENTRY_BG, PRIO_ENTRY_BG);

	Point timer_pos = { 1193,88 };
	CObjTimer* timer = new CObjTimer(timer_pos, 60,false);
	Objs::InsertObj(timer, OBJ_TIMER, PRIO_ENTRY_TIMER);
}
void CObjSystem::EntryEnd()
{
	CObjEntry* entry = (CObjEntry*)Objs::GetObj(OBJ_ENTRY);
	entry->SetStatus(false);
	CObjEntryBG* bg = (CObjEntryBG*)Objs::GetObj(OBJ_ENTRY_BG);
	bg->SetStatus(false);
	CObjModeSelect* select = (CObjModeSelect*)Objs::GetObj(OBJ_MODESELECT);
	select->SetStatus(false);
	CObjTimer* timer = (CObjTimer*)Objs::GetObj(OBJ_TIMER);
	timer->SetStatus(false);
}

void CObjSystem::HeyaStart()
{

	Audio::LoadAudio2(bgm_HEYA, "Sound/9_Heya/BGM.ogg", BACK_MUSIC);

	Draw::InfoReset();


	CObjHeya* heya = new CObjHeya();
	Objs::InsertObj(heya, OBJ_HEYA, PRIO_HEYA);
	
}

void CObjSystem::HeyaEnd()
{
	CObjHeya* heya = (CObjHeya*)Objs::GetObj(OBJ_HEYA);
	heya->SetStatus(false);
	Audio::Stop(bgm_HEYA);
}
void CObjSystem::EnsoBattleStart(string fumen_path, ST_ENSO_OPTION option)
{
	USER_DATA->m_player_amount = 1;
	MusicGame::g_mode = E_GAME_MODE::ENSO_BATTLE;
	USER_DATA->m_max_song = 1;
	USER_DATA->m_auto_play[0] = false;

	Draw::InfoReset();

	CObjLane* lane = new CObjLane();
	Objs::InsertObj(lane, OBJ_LANE, PRIO_ENSO_LANE);

	CObjJudgeMoji* judge = new CObjJudgeMoji();
	Objs::InsertObj(judge, OBJ_JUDGE, PRIO_ENSO_JUDGE);

	CObjMTaiko* taiko = new CObjMTaiko();
	Objs::InsertObj(taiko, OBJ_TAIKO, PRIO_ENSO_TAIKO);

	CObjCombo* combo = new CObjCombo();
	Objs::InsertObj(combo, OBJ_COMBO, PRIO_ENSO_COMBO);

	CObjBalloon* balloon = new CObjBalloon();
	Objs::InsertObj(balloon, OBJ_BALLOON, PRIO_ENSO_BALLOON);


	CObjScore* score = new CObjScore();
	Objs::InsertObj(score, OBJ_SCORE, PRIO_ENSO_SCORE);

	CObjRoll* roll = new CObjRoll();
	Objs::InsertObj(roll, OBJ_ROLL, PRIO_ENSO_ROLL);
	if (((UserData*)Save::GetData())->m_better_performance[MusicGame::E_BETTER_PERFORMANCE::bp_CHARA] == true)
	{
		CObjCharacter* chara = new CObjCharacter();
		Objs::InsertObj(chara, OBJ_CHARACTER, PRIO_ENSO_CHARACTER);
	}
	CObjFlyingNotes* flying = new CObjFlyingNotes();
	Objs::InsertObj(flying, OBJ_FLYINGNOTES, PRIO_ENSO_FLYINGNOTES);

	//	if (((UserData*)Save::GetData())->m_better_performance[MusicGame::E_BETTER_PERFORMANCE::bp_BG] == true)
	{
		CObjBg* bg = new CObjBg();
		Objs::InsertObj(bg, OBJ_BG, PRIO_ENSO_BG);
	}
	//CObjComboBalloon* cballoon = new CObjComboBalloon();
	//Objs::InsertObj(cballoon, OBJ_COMBOBALLOON, PRIO_ENSO_COMBOBALLOON);

	CObjTitlePanel* title = new CObjTitlePanel();
	Objs::InsertObj(title, OBJ_TITLEPANEL, PRIO_ENSO_TITLE);


	//if (USER_DATA->m_player_amount == 1)
	//{
	//	CObjDancer* dancer = new CObjDancer();
	//	Objs::InsertObj(dancer, OBJ_DANCER, PRIO_ENSO_DANCER);

		CObjFooter* footer = new CObjFooter();
		Objs::InsertObj(footer, OBJ_FOOTER, PRIO_ENSO_FOOTER);


	//	CObjSpark* spark = new CObjSpark();
	//	Objs::InsertObj(spark, OBJ_SPARK, PRIO_ENSO_SPARK);
	//}
	//CObjKusudama* kusudama = new CObjKusudama();
	//Objs::InsertObj(kusudama, OBJ_KUSUDAMA, PRIO_ENSO_KUSUDAMA);
	if (((UserData*)Save::GetData())->m_now_select_diffculty[0] == DIFF_DAN)
	{

	}
	Audio::LoadAudio2(se_BALLOON, "Sound/3_Enso/Balloon.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(se_KUSUDAMA, "Sound/3_Enso/Kusudama.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(voice_50, "Sound/3_Enso/Combo/50.ogg", SOUND_TYPE::EFFECT);
	Audio::LoadAudio2(voice_50_2, "Sound/3_Enso/Combo_2P/50.ogg", SOUND_TYPE::EFFECT);

	int count = 0;

	for (int i = 100; i <= 5000; i += 100)
	{
		string str = "Sound/3_Enso/Combo/" + to_string(i) + ".ogg";
		Audio::LoadAudio2(voice_100 + count, str.c_str(), SOUND_TYPE::EFFECT);
		count++;
	}
	count = 0;
	if (((UserData*)Save::GetData())->m_player_amount >= 2)
	{
		for (int i = 100; i <= 5000; i += 100)
		{
			string str = "Sound/3_Enso/Combo_2P/" + to_string(i) + ".ogg";
			Audio::LoadAudio2(voice_100_2 + count, str.c_str(), SOUND_TYPE::EFFECT);
			count++;
		}
	}

	CObjBattleGauge* gague = new CObjBattleGauge();
	Objs::InsertObj(gague, OBJ_BATTLE_GAUGE, PRIO_BATTLE_GAUGE);
	CObjEnsoBattle* battle = new CObjEnsoBattle(fumen_path + "/../Effect/");
	Objs::InsertObj(battle, OBJ_BATTLE, PRIO_BATTLE_ANIME);
	CObjBattleCharacter* battlec = new CObjBattleCharacter(fumen_path + "/../Effect/");
	Objs::InsertObj(battlec, OBJ_BATTLE_CHARA, PRIO_BATTLE_CHARACTER);


	CObjEnso* enso = new CObjEnso(fumen_path, option);
	Objs::InsertObj(enso, OBJ_ENSO, PRIO_ENSO_ENSO);


	//CObjEnsoEndEffect* end = new CObjEnsoEndEffect();
	//Objs::InsertObj(end, OBJ_END, PRIO_ENSO_END);
}
void CObjSystem::EnsoBattleEnd()
{

	CObjNotes* notes = (CObjNotes*)Objs::GetObj(OBJ_NOTES);
	notes->SetStatus(false);
	CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);
	lane->SetStatus(false);
	CObjNormaGauge* gauge = (CObjNormaGauge*)Objs::GetObj(OBJ_GAUGE);
	gauge->SetStatus(false);
	CObjJudgeMoji* judge = (CObjJudgeMoji*)Objs::GetObj(OBJ_JUDGE);
	judge->SetStatus(false);
	CObjMTaiko* taiko = (CObjMTaiko*)Objs::GetObj(OBJ_TAIKO);
	taiko->SetStatus(false);
	CObjCombo* combo = (CObjCombo*)Objs::GetObj(OBJ_COMBO);
	combo->SetStatus(false);
	CObjScore* score = (CObjScore*)Objs::GetObj(OBJ_SCORE);
	score->SetStatus(false);
	CObjBalloon* balloon = (CObjBalloon*)Objs::GetObj(OBJ_BALLOON);
	balloon->SetStatus(false);
	CObjRoll* roll = (CObjRoll*)Objs::GetObj(OBJ_ROLL);
	roll->SetStatus(false);

	CObjCharacter* chara = (CObjCharacter*)Objs::GetObj(OBJ_CHARACTER);
	if (chara != nullptr)
		chara->SetStatus(false);

	CObjFlyingNotes* flying = (CObjFlyingNotes*)Objs::GetObj(OBJ_FLYINGNOTES);
	if (flying != nullptr)
	flying->SetStatus(false);

	CObjBg* bg = (CObjBg*)Objs::GetObj(OBJ_BG);
	if (bg != nullptr)
		bg->SetStatus(false);

	CObjTitlePanel* title = (CObjTitlePanel*)Objs::GetObj(OBJ_TITLEPANEL);
	title->SetStatus(false);


	CObjFooter* footer = (CObjFooter*)Objs::GetObj(OBJ_FOOTER);
	if (footer != nullptr)
		footer->SetStatus(false);
}
void CObjSystem::TitleStart()
{
	CObjTitle* title = new CObjTitle();
	Objs::InsertObj(title, OBJ_TITLE, PRIO_TITLE);
}
void CObjSystem::TitleEnd()
{
	CObjTitle* title = (CObjTitle*)Objs::GetObj(OBJ_TITLE);
	title->SetStatus(false);
}

void CObjSystem::GameEnd()
{
	
}


void CObjSystem::CharacterTexLoad()
{

}