#pragma once 

//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"
#include "MusicGame.h"
#include "Gamehead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[�����C��
class SceneSongSelect :public CScene
{
public:
	SceneSongSelect();
	~SceneSongSelect();
	void InitScene();//������
	void Scene();//���s��
private:
	CNumTexSource m_debug_num;
	const RECT_F RECT_NUM = { 0.0f,0.0f,40.0f,49.0f };
};