#pragma once
//STLデバッグ機能をOFFにする
#define _HAS_ITERATOR_DEBUGGING	(0)

#include "CFileFormat.h"
#include "GameL\DrawTexture.h"
#include "CLayout.h"
#include "CAnime2.h"
#include "Function.h"

class CLayoutGroup : CFileFormat
{
public:
	CLayoutGroup();
	~CLayoutGroup();
	void Init();
	void LoadData(std::string path);
	void Draw();
private:
	CLayout lyt;
	CAnime2 ani;
	CTexture tex;
};