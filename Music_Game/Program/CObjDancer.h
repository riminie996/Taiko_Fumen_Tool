#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjDancer : public CObj
{
public:
	CObjDancer() { m_dancer_name = "Common"; }
	CObjDancer(string name) { m_dancer_name = name; }
	~CObjDancer() {}
	void Init();
	void Action();
	void Draw();
private:
	struct ST_DANCER
	{
		vector<CTexture> texture;
		vector<CTexture> wait_texture;
		CLayout lyt;
		CAnime3 ani;
		CAnime3 ani_loop;
	};

	static const int DANCER_AMOUNT = 5;
	vector<ST_DANCER>m_dancer;
	string m_dancer_name;
};
