#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjFooter : public CObj
{
public:
	CObjFooter() { m_skin_name = "Common"; }
	CObjFooter(string name) { m_skin_name = name; }
	~CObjFooter() {}
	void Init();
	void Action();
	void Draw();
private:

	const Point BG_FOOTER_POS = { 0,676 };
	string m_skin_name;
};
