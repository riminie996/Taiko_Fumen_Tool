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
#include "SceneMain.h"
#include "GameHead.h"


//デストラクタ
SceneMain::~SceneMain()
{

}
//初期化
void SceneMain::InitScene()
{
	//セーブデータ
	static bool init_flag = false;

	if (init_flag == false)
	{

		((UserData*)Save::GetData())->m_default_option = ST_ENSO_OPTION().GetDefaultOption();
		((UserData*)Save::GetData())->m_default_diffculty = DIFF_ONI;
		((UserData*)Save::GetData())->m_max_song = 0;
		((UserData*)Save::GetData())->m_now_select_diffculty[0] = DIFF_ONI;
		USER_DATA->m_oni_unlock = false;
		((UserData*)Save::GetData())->m_panel_showing = false;
		((UserData*)Save::GetData())->m_player_amount = 1;
		((UserData*)Save::GetData())->m_judge_showing = false;
		((UserData*)Save::GetData())->m_judge_sec_showimg = false;
		USER_DATA->m_save_score = true;
		USER_DATA->m_bgm_demo_play = true;
		USER_DATA->m_auto_play_roll = 17;

		for (int i = 0; i < MusicGame::MAX_PLAYER_AMOUNT; i++)
		{
			((UserData*)Save::GetData())->m_auto_play[i] = true;
		}
		for (int i = 0; i < MusicGame::bp_Count; i++)
		{
			((UserData*)Save::GetData())->m_better_performance[i] = true;
		}

		Save::Open();
		init_flag = true;

	}
	((UserData*)Save::GetData())->m_better_performance[MusicGame::bp_CHARA] = false;
	Save::Seve();
	CObjSystem* system = new CObjSystem();
	Objs::InsertObj(system, OBJ_MAIN, 0);

	//仮に設定
//	EnsoStart();

}
//実行中
void SceneMain::Scene()
{
	static bool init_flag = false;

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
	//	for (int i = 0; i < MusicGame::bp_Count; i++)
	//	{
	//		((UserData*)Save::GetData())->m_better_performance[i] = true;
	//	}

	//	Save::Open();
	//	init_flag = true;

	//}
}

