#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

enum E_LANE_FLUSH_COLOR
{
	Red,
	Blue,
	Yellow,
};


class CObjLane : public CObj
{
public:
	CObjLane(){}
	~CObjLane() {}
	void Init();
	void Action();
	void Draw();
	void HitEffectStart(E_JUDGE judge,bool big,int player);
	void LaneFlushStart(E_LANE_FLUSH_COLOR color, int player);
	void GogoStart(int player);
	void BranchChange(E_BRANCH branch, int player);
	int GetJudgePosX(int player) {return m_lyt_judge_pos[player].GetPos().x; }
	int GetJudgePosY(int player) {return m_lyt_judge_pos[player].GetPos().y; }
private:

	//íËêî
	const RECT_F RECT_NOTES_JUDGE_LINE = { 0.0f,0.0f,128.0f,128.0f };
	const RECT_F RECT_NOTES_JUDGE_LINE_GOGO = { 0.0f,128.0f,128.0f,128.0f };
	const RECT_F RECT_FIRE = { 0.0f,0.0f,360.0f,360.0f };
	const RECT_F RECT_HIT_EFFECT = { 0.0f,0.0f,128.0f,128.0f };
	const RECT_F RECT_LANE_FLUSH[3] = 
	{ 
		{ 0.0f,0.0f,1280.0f,134.0f },
		{ 0.0f,134.0f,1280.0f,134.0f },
		{ 0.0f,268.0f,1280.0f,134.0f },
	};
	const RECT_F RECT_LANE_NORMAL = { 0.0f,0.0f,1280.0f,130.0f };
	const RECT_F RECT_LANE_KUROTO = { 0.0f,130.0f,1280.0f,130.0f };
	const RECT_F RECT_LANE_TATSUJIN = { 0.0f,260.0f,1280.0f,130.0f };

	const Point P1_FLAME_POS = { 329,184 };
	const int LANE_FLUSH_OFFSET = 8 ;
	CTimeCounter m_ct_fire_rect;

	int m_hit_effect_type[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_hit_opacity[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_lane_flush[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_lane_flush_yellow[MusicGame::MAX_PLAYER_AMOUNT];

	CAnime2 m_ani_lane_gogo[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_lane_gogo_scale[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_fire_scale[MusicGame::MAX_PLAYER_AMOUNT];
	E_LANE_FLUSH_COLOR m_lane_color[MusicGame::MAX_PLAYER_AMOUNT];
	E_BRANCH m_branch[MusicGame::MAX_PLAYER_AMOUNT];
	E_BRANCH m_branch_before[MusicGame::MAX_PLAYER_AMOUNT];

	CAnime2 m_ani_branch_text_before[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_branch_text_after[MusicGame::MAX_PLAYER_AMOUNT];
	CAnime2 m_ani_branch_lane_after[MusicGame::MAX_PLAYER_AMOUNT];
	int m_branch_anime_dir[MusicGame::MAX_PLAYER_AMOUNT];

	CLayout m_lyt_fire;
	CTexture g_tex_gogo_fire;


	CLayout m_lyt_lane[MusicGame::MAX_PLAYER_AMOUNT];
	CLayout m_lyt_judge_pos[MusicGame::MAX_PLAYER_AMOUNT];
};
