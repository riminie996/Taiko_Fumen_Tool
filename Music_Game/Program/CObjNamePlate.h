#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjNamePlate : public CObj
{
public:
	CObjNamePlate() {}
	~CObjNamePlate() {}
	void Init();
	void Action();
	void Draw();
private:


};