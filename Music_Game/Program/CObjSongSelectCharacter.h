#pragma once
#include "MusicGame.h"
#include "GameHead.h"
#include "GameL\SceneObjManager.h"
using namespace GameL;


class CObjSongSelectCharacter : public CObj
{
public:
	CObjSongSelectCharacter() {}
	~CObjSongSelectCharacter() {}
	void Init();
	void Action();
	void Draw();
	void Select();
	void SongStart();
private:
	const Point CHARACTER_POS = { 0,329 };
	static const int CHARA_LOOP_FRAME = 60;
	static const int CHARA_SELECT_FRAME = 66;
	static const int CHARA_START_FRAME = 24;
	CCounter m_ct_chara_loop;
	CCounter m_ct_chara_select;
	CCounter m_ct_chara_start;
	bool m_song_start;
};
