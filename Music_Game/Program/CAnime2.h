#pragma once
//STLデバッグ機能をOFFにする
#define _HAS_ITERATOR_DEBUGGING	(0)

#include "CFileFormat.h"
#include "CTimeCounter.h"

class CAnime2 : CFileFormat
{
public:
	CAnime2();
	CAnime2(std::string entry_name);
	~CAnime2();
	void Init();
	void LoadData(std::string entry_name);

	//ST_ANIME_INFO Get() { return m_now_info; }
	void Action();
	void ActionLoop();

	void Start();
	void End();
	bool GetStart() { return m_flag_start; }

	struct ST_VALUE_TYPE
	{
		float x = 0.0f, y = 0.0f, scale_x = 1.0f, scale_y = 1.0f;
		float r = 1.0f, g = 1.0f, b = 1.0f, opacity = 1.0f;
		float rotate_z = 0.0f;
		float pattern = 0;
	};

	float GetNowFrame() { return (float)m_ct_time.NowValue / 1000.0f; }
	ST_VALUE_TYPE GetValue() { return m_value; }
	bool GetEnd() { return m_ct_time.GetEndValueReached(); }
	
	CAnime2& operator=(const CAnime2& rhs)
	{
		m_ct_time = rhs.m_ct_time;
		m_flag_start = rhs.m_flag_start;
		m_str_entry_name = rhs.m_str_entry_name;

		m_value =rhs.m_value;//現在の値を記憶するための変数
		

		m_vec_anime = rhs.m_vec_anime;

		return *this;
	}

private:
	//アニメーションタイプ
	enum E_MOVE_TYPE
	{
		POS_X,
		POS_Y,
		SCALE_X,
		SCALE_Y,
		COLOR_R,
		COLOR_G,
		COLOR_B,
		ROTATE_Z,
		OPACITY,
		PATTERN,

		AnimeTypeCounter,//タイプカウント用
	};

	const std::string STR_ANIME_TYPE[AnimeTypeCounter] =
	{
		"PosX",			//POS_X,
		"PosY",			//POS_Y,
		"ScaleX",		//SCALE_X,
		"ScaleY",		//SCALE_Y,
		"ColorR",		//COLOR_R,
		"ColorG",		//COLOR_G,
		"ColorB",		//COLOR_B,
		"RotateZ",		//ROTATE_Z,
		"Opacity",
		"Pattern",
	};

	enum E_ANIME_TYPE
	{
		MOVE_NORMAL,//直線
		MOVE_ACCELE,//加速
		MOVE_DECELE,//減速
		MOVE_ACC_DEC,//加減速
		MOVE_TELEPORT,

		MoveTypeCounter,//動き種類カウント用
	};

	const std::string STR_MOVE_TYPE[MoveTypeCounter] =
	{
		"Normal",	//直線
		"Accele",	//加速
		"Decele",	//減速
		"Acc_Dec",	//加減速
		"Teleport",
	};


	//vectorで管理される情報。
	struct ST_ANIME
	{
		ST_ANIME()
		{
			time = 0.0f;
			anime_type = MOVE_NORMAL;
			value = 0.0f;
		}
		float value;
		int time;
		E_ANIME_TYPE anime_type;
	};

	CTimeCounter m_ct_time;
	bool m_flag_start;
	std::string m_str_entry_name;

	ST_VALUE_TYPE m_value;//現在の値を記憶するための変数
	std::vector< std::vector<ST_ANIME>> m_vec_anime;//フレームごとの情報を入れるための変数

	void Update();
};