#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjBalloon : public CObj
{
public:
	CObjBalloon() {}
	~CObjBalloon() {}
	void Init();
	void Action();
	void Draw();
	void Start(int max,int player);
	void Set(int num, int player);
	void End(int player);
	void Break(int player);
private:

	const float BALLOON_NUM_PADDING = 49.0f;
	const float BALLOON_NUM_SCALE = 0.8f;
	CAnime m_ani_number_scale = { "Animation/BallonNumScale" };
	CNumTexSource m_num_roll;
	const RECT_F RECT_ROLL_NUMBER = { 0.0f,0.0f,64.0f,73.0f };

	CCounter m_ct_break_opacity;
	float OPACITY_SPEED = 0.167f;
	bool m_reset_flag;
	bool m_show_flag[MusicGame::MAX_PLAYER_AMOUNT];
	int m_roll_remain[MusicGame::MAX_PLAYER_AMOUNT];
	int m_max_val[MusicGame::MAX_PLAYER_AMOUNT];
	//íËêî
	CLayout m_lyt_balloon[MusicGame::MAX_PLAYER_AMOUNT];
	CLayout m_lyt_fukidashi[MusicGame::MAX_PLAYER_AMOUNT];
	CLayout m_lyt_number[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime3 m_ani_balloon_fadeout[MusicGame::MAX_PLAYER_AMOUNT];
};
