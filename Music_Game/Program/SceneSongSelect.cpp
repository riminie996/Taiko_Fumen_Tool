//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)

//GameLで使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/UserData.h"
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "dirent.h"
#include "SceneSongSelect.h"
#include "GameHead.h"

//コンストラクタ
SceneSongSelect::SceneSongSelect()
{

}

//デストラクタ
SceneSongSelect::~SceneSongSelect()
{

}
//初期化
void SceneSongSelect::InitScene()
{
	m_debug_num.SetTex(tex_NUMBER, RECT_NUM.m_width, RECT_NUM.m_height);
	////セーブデータ
	//static bool init_flag = false;

	//if (init_flag == false)
	//{

	//	((UserData*)Save::GetData())->m_default_option = ST_ENSO_OPTION();
	//	((UserData*)Save::GetData())->m_default_diffculty = DIFF_ONI;
	//	((UserData*)Save::GetData())->m_max_song = 0;
	//	((UserData*)Save::GetData())->m_now_select_diffculty = DIFF_ONI;
	//	USER_DATA->m_oni_unlock = false;
	//	((UserData*)Save::GetData())->m_panel_showing = false;
	//	((UserData*)Save::GetData())->m_player_amount = 1;


	//	for (int i = 0; i < MusicGame::MAX_PLAYER_AMOUNT; i++)
	//	{
	//		((UserData*)Save::GetData())->m_auto_play[i] = true;
	//	}

	//	Save::Open();
	//	init_flag = true;

	//}


	//Save::Seve();
	CObjSystem* system = new CObjSystem();
	Objs::InsertObj(system, OBJ_MAIN, PRIO_ENSO_ENSO);

	//list<string> fumen_path;
	//list<string> folder_path;
	//MusicGame::SongSelect::LoadDirectory(fumen_path, folder_path, "Fumen\\");


	//MusicGame::SongSelect::FumenListCreate(fumen_path);

	//for (int i = 0; i <= GENRE_Count; i++)
	//{
	//	wchar_t wcr[64];
	//	swprintf_s(wcr, L"Graphics/2_SongSelect/Bar_Box/Bar_Box_%d.png", i);
	//	Draw::LoadImageW(wcr, tex_BOX_NONE + i, TEX_SIZE_64);

	//	swprintf_s(wcr, L"Graphics/2_SongSelect/Difficulty_Box/Difficulty_Back_%d.png", i);
	//	Draw::LoadImageW(wcr, tex_DIFFCULTY_BOX_NONE + i, TEX_SIZE_64);

	//	swprintf_s(wcr, L"Graphics/2_SongSelect/Genre_Background/GenreBackground_%d.png", i);
	//	Draw::LoadImageW(wcr, tex_BACKGROUND_NONE + i, TEX_SIZE_64);

	//}

	//Draw::LoadImageW(L"Graphics/2_SongSelect/Bar_Box/Bar_Box_Close.png", tex_BOX_CLOSE, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/Bar_Box/Bar_Box_Close_Text.png", tex_BOX_CLOSE_TEXT, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/Bar_Box/Bar_Box_OverLay.png", tex_BOX_OVERLAY, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/Diffculty.png", tex_BOX_DIFFCULTY, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/Diffculty_Number.png", tex_BOX_DIFFCULTY_NUMBER, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Difficulty_Bar.png", tex_DIFFCULTY_BAR, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Small_Icon.png", tex_DIFFCULTY_ICON, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Cursor_1P.png", tex_DIFFCULTY_CURSOR, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/CourseSymbol.png", tex_DIFFCULTY_COURSESYMBOL, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/4_SongLoading/Fade.png", tex_LOADING_FADE, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/4_SongLoading/Bg.png", tex_LOADING_BG, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/4_SongLoading/Bg_wait.png", tex_LOADING_WAIT, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/4_SongLoading/Plate.png", tex_LOADING_PLATE, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/4_SongLoading/Chara.png", tex_LOADING_CHARA, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/Cursor_yellow.png", tex_SONGSELECT_CURSOR, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Cursor_Yellow.png", tex_DIFFCULTY_CURSOR2, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Oni_Appear.png", tex_DIFFCULTY_ONI_APPEAR, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Number.png", tex_DIFFCULTY_NUM, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Star.png", tex_DIFFCULTY_STAR, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Text.png", tex_DIFFCULTY_TEXT, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/Branch_Text.png", tex_DIFFCULTY_BRANCH, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/EnsoOption.png", tex_DIFFCULTY_OPTION, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/OptionArrow.png", tex_DIFFCULTY_OPTION_ARROW, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/EnsoOptionBar.png", tex_DIFFCULTY_OPTION_BAR, TEX_SIZE_64);
	//Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/EnsoOptionBarBack.png", tex_DIFFCULTY_OPTION_BAR_BACK, TEX_SIZE_64);

	//Audio::LoadAudio2(se_SKIP, "Sound/2_Songselect/Skip.ogg", SOUND_TYPE::EFFECT);
	//Audio::LoadAudio2(se_ONI_APPEAR, "Sound/2_Songselect/Oni_Appear.ogg", SOUND_TYPE::EFFECT);
	//Audio::LoadAudio2(se_ONI_SWITCHING, "Sound/2_Songselect/Switch.ogg", SOUND_TYPE::EFFECT);
	//Audio::LoadAudio2(bgm_IN, "Sound/2_Songselect/BGM_START.ogg", SOUND_TYPE::EFFECT);
	//Audio::LoadAudio2(bgm_SONGSELECT, "Sound/2_Songselect/BGM_LOOP.ogg", SOUND_TYPE::BACK_MUSIC);

	//Draw::InfoReset();


	//CObjSongSelect* lselect = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);

	////ステージセレクトが既に存在する場合生成しない
	//if (lselect != nullptr)
	//{
	//	lselect->ResultToSongSelect();
	//}
	//else
	//{
	//	CObjSongSelect* select = new CObjSongSelect();
	//	Objs::InsertObj(select, OBJ_SONGSELECT, PRIO_SONGSELECT_SONGSELECT);
	//}

	//CObjSongSelectBG* bg = new CObjSongSelectBG();
	//Objs::InsertObj(bg, OBJ_SONGSELECT_BG, PRIO_SONGSELECT_BG);
	//CObjNowSong* nowsong = new CObjNowSong(MusicGame::SONGSELECT_NOW_SONG);
	//Objs::InsertObj(nowsong, OBJ_NOWSONG, PRIO_SONGSELECT_NOWSONG);

	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Combo.png", tex_NUMBER, TEX_SIZE_64);
}
//実行中
void SceneSongSelect::Scene()
{
	CObjSongSelect* select = (CObjSongSelect*)Objs::GetObj(OBJ_SONGSELECT);
	CObjSongSelectBG* bg = (CObjSongSelectBG*)Objs::GetObj(OBJ_SONGSELECT_BG);	
	CObjDiffcultySelect* diffculty = (CObjDiffcultySelect*)Objs::GetObj(OBJ_DIFFCULTY_SELECT);
	CObjSongSelectCharacter* chara = (CObjSongSelectCharacter*)Objs::GetObj(OBJ_SONGSELECT_CHARA);

	if (select != nullptr)
	{
		m_debug_num.Draw(select->m_act_time, 64, 0 + 64, 40);
		m_debug_num.Draw(select->m_draw_time, 128, 0 + 64, 40);
	}

	if (bg != nullptr)
	{
		m_debug_num.Draw(bg->m_act_time, 64, 0 + 128, 40);
		m_debug_num.Draw(bg->m_draw_time, 128, 0 + 128, 40);
	}

	if (diffculty != nullptr)
	{
		m_debug_num.Draw(diffculty->m_act_time, 64, 0 + 192, 40);
		m_debug_num.Draw(diffculty->m_draw_time, 128, 0 + 192, 40);
	}
	if (chara != nullptr)
	{
		m_debug_num.Draw(chara->m_act_time, 64, 0 + 256, 40);
		m_debug_num.Draw(chara->m_draw_time, 128, 0 + 256, 40);
	}
}
//
//void SceneStageSelect::LoadDirectory(vector<MusicGame::ST_FUMEN_DATA>& vec_fumen, string path)
//{//"./"
//
//
//	DIR* dir;
//	struct dirent* dp;
//
//	dir = opendir(path.c_str());
//
//	for (dp = readdir(dir); dp != NULL; dp = readdir(dir))
//	{
//	//	ファイルを探す
//		string name = dp->d_name;
//		name = "Fumen/" + name;
//		
//		//テキストファイル
//		if (name.find(".txt") != -1)
//		{
//			string str_fumen_command;
//			list<string> str_split_fumen_command;
//
//			//ファイルを開く
//			ifstream ifs(name);
//			if (!ifs)
//			{
//				MessageBox(NULL, TEXT("やりなおしてください"),
//					TEXT("譜面ファイル読み込み失敗"), MB_OK);
//				ifs.close();
//			}
//
//			while (getline(ifs, str_fumen_command))
//			{
//				str_split_fumen_command.push_back(str_fumen_command);
//			}
//			MusicGame::ST_FUMEN_DATA fumen;
//
//			fumen.fumen_path = name;
//
//			//ヘッダの読み込み。
//			for (auto itr = str_split_fumen_command.begin(); itr != str_split_fumen_command.end(); itr++)
//			{
//				fumen.FumenHeaderLoad(*itr);
//			}
//
//			vec_fumen.push_back(fumen);
//
//		}
//	}
//
//	closedir(dir);
//}

