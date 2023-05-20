#pragma once
//STLデバッグ機能をOFFにする
#define _HAS_ITERATOR_DEBUGGING	(0)

#include "CFileFormat.h"
#include "CTimeCounter.h"
#include "Function.h"
#include "GameL\DrawTexture.h"

class CLayout2 : CFileFormat
{
public:
	CLayout2();
	~CLayout2();
	void Init();
	void LoadData(std::string file_name);
	void Draw();
	ST_LAYOUT GetData(int num) { return  m_lyt[num]; }
	vector<ST_LAYOUT>  GetData() { return  m_lyt; }
	std::string GetTexName() { return m_str_tex; }
private:
	std::string m_str_tex;
	vector<ST_LAYOUT> m_lyt;
	bool m_load_layout;

};