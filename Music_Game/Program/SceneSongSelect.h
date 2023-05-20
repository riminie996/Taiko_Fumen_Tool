#pragma once 

//使用するヘッダーファイル
#include "GameL\SceneManager.h"
#include "MusicGame.h"
#include "Gamehead.h"

//使用するネームスペース
using namespace GameL;

//シーンメイン
class SceneSongSelect :public CScene
{
public:
	SceneSongSelect();
	~SceneSongSelect();
	void InitScene();//初期化
	void Scene();//実行中
private:
	CNumTexSource m_debug_num;
	const RECT_F RECT_NUM = { 0.0f,0.0f,40.0f,49.0f };
};