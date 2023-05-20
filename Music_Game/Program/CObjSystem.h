#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
#include <thread>
using namespace GameL;

class CObjSystem : public CObj
{
public:
	CObjSystem() {}
	~CObjSystem();
	void Init();
	void Action();
	void Draw();
	void Delete();

	void SongSelectStart();
	void SongSelectEnd();
	void EnsoStart(string fumen_path, ST_ENSO_OPTION option);
	void EnsoEnd();
	void ResultStart(ST_SCORE_DATA score_data);
	void ResultEnd();
	void DanResultStart(ST_SCORE_DATA score_data);
	void DanResultEnd();
	void DanSelectStart();
	void DanSelectEnd();
	void EntryStart();
	void EntryEnd();
	void GameEnd();
	void HeyaStart();
	void HeyaEnd();
	void EnsoBattleStart(string fumen_path, ST_ENSO_OPTION option);
	void EnsoBattleEnd();
	void TitleStart();
	void TitleEnd();

	bool GetInput(E_TAIKO_FLUSH taiko,int player);

	void AddSongNumber() { m_song_number++; }
	int GetNowSongNumber() { return m_song_number; }

	list<string> m_list_favolite_fumen_path;
	list<string> m_list_history_fumen_path;
private:
	bool m_key_flag[TAIKO_FLUSH_Count * MusicGame::MAX_PLAYER_AMOUNT];
	bool m_key[TAIKO_FLUSH_Count * MusicGame::MAX_PLAYER_AMOUNT];
//	string m_fumen_file_path;

	RECT_F rect_title;

//	vector<MusicGame::ST_FUMEN_DATA> m_vec_fumen;
//	vector<string> m_vec_fumen_path;

	void LoadDirectory(vector<MusicGame::ST_FUMEN_DATA>& vec_fumen, string path);
	void CharacterTexLoad();

	int m_song_number;
	int m_max_song;
	int m_player_count;

	void FirstAction();
	bool m_first_action;

	void SubThrActionDraw();

	bool m_load_fumen;
	bool m_load_tex;
	bool m_load_sound;
	bool m_load_game;

	std::thread* thr_loading;
};
