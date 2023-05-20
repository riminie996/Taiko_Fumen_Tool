#pragma once
#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjTitle : public CObj
{
public:
	CObjTitle() { }
	~CObjTitle() {}
	void Init();
	void Action();
	void Draw();
private:
	CFIFO m_fadein;
	CFIFO m_fadeout;

	const RECT_N RECT_BACKGROUND =	{ 0,0,1280,720 };
	const RECT_N RECT_HIYOKO1 =		{ 0,720,57,48 };
	const RECT_N RECT_HIYOKO2 =		{ 57,720,53,45 };
	const RECT_N RECT_DARUMA =		{ 0,768,64,64 };
	const RECT_N RECT_SUZU =		{ 0,832,116,90 };
	const RECT_N RECT_TETSUO =		{ 0,922,279,315 };
	const RECT_N RECT_HANAKO =		{ 279,720,278,328 };
	const RECT_N RECT_BACHIO =		{ 116,720,140,202 };
	const RECT_N RECT_DONKO =		{ 557,720,544,267 };
	const RECT_N RECT_KAMEN =		{ 279,1048,425,232 };
	const RECT_N RECT_TAIKO =		{ 704,987,324,340 };
	const RECT_N RECT_LOGO =		{ 0,1280,620,229 };
	const RECT_N RECT_DONCHAN =			{ 0,1509,612,541 };
	const RECT_N RECT_KACCHAN =		{ 620,1327,577,514 };

	const Point BACKGROUND_POS	= { 0,0 };
	const Point HIYOKO1_POS		= { 1203,63 };
	const Point HIYOKO2_POS		= { 11,221 };
	const Point DARUMA_POS		= { 1205,240 };
	const Point SUZU_POS		= { 414,43 };
	const Point TETSUO_POS		= { 997,481 };
	const Point HANAKO_POS		= { -2,430 };
	const Point BACHIO_POS		= { 627,41 };
	const Point DONKO_POS		= { -63,535 };
	const Point KAMEN_POS		= { 861,544 };
	const Point TAIKO_POS		= { 640,540 };
	const Point LOGO_POS		= { 640,492 };
	const Point DONCHAN_POS		= { 23,-14 };
	const Point KACCHAN_POS		= { 703,11 };

	CAnime3 m_ani_appear;
	CAnime3 m_ani_logo_effect;
};
