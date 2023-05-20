#pragma once
//STLデバッグ機能をOFFにする
#define _HAS_ITERATOR_DEBUGGING	(0)

#include "CFileFormat.h"

//struct ST_ANIME_INFO
//{
//	//位置
//	float pos_x;
//	float pos_y;
//	//スケール
//	float scale_x;
//	float scale_y;
//	//色と透明度
//	float color_r;
//	float color_g;
//	float color_b;
//	float color_a;
//	//回転率
//	float rotate_z;
//};

class CAnime : CFileFormat
{
public:
	CAnime();
	CAnime(std::string entry_name);
	~CAnime();
	void Init();

	//ST_ANIME_INFO Get() { return m_now_info; }
	void Action();
	void ActionLoop();

	void Start();
	void End();

	float GetNowFrame() { return m_now_frame; }
	float GetValue() { return m_value; }
	bool GetEnd() { return m_now_frame == m_max_frame; }
	bool GetStart() { return m_flag_start; }
private:

	enum E_ANIME_TYPE
	{
		MOVE_NORMAL,//直線
		MOVE_ACCELE,//加速
		MOVE_DECELE,//減速
		MOVE_ACC_DEC,//加減速

		MoveTypeCounter,//動き種類カウント用
	};

	const std::string STR_MOVE_TYPE[MoveTypeCounter] =
	{
		"Normal",	//直線
		"Accele",	//加速
		"Decele",	//減速
		"Acc_Dec",	//加減速
	};


	//vectorで管理される情報。
	struct ST_ANIME
	{
		ST_ANIME()
		{
			frame = 0.0f;
			value = 0.0f;
			anime_type = MOVE_NORMAL;
		}

		float frame;
		float value;
		E_ANIME_TYPE anime_type;
	};

	float m_value;
	float m_now_frame;	//アニメーション中の現在のフレーム
	float m_max_frame;	//アニメーションの最終フレーム
	bool m_flag_start;
	std::string m_str_entry_name;

	std::vector<ST_ANIME> m_vec_anime;
	//ST_ANIME_INFO m_now_info;

};