#pragma once
//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)

//���������[�N���o�p
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include "Function.h"//Point
#include "CCounter.h"
#include "CTimeCounter.h"
#include "GameL\UserData.h"

#include <string>
#include <list>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#define new DBG_NEW
#endif  // _DEBUG
using namespace std;
using namespace GameL;

/*
string��wstring�֕ϊ�����
*/

#define SONG_HISTORY_PATH ("Config/History")
#define SONG_FAVOLITE_PATH ("Config/Favolite")
#define ARRAY_LENGTH(ar) (sizeof(ar) / sizeof(ar[0]))
#define SCOREFILE_STR ("score")

enum class E_GAME_MODE
{
	ENSO,
	ENSO_DAN,
	ENSO_BATTLE,
};

//��Փx�ꗗ
enum E_DIFFCULTY
{
	DIFF_EASY,
	DIFF_NORMAL,
	DIFF_HARD,
	DIFF_ONI,
	DIFF_EDIT,
	DIFF_TOWER,
	DIFF_DAN,
	DIFF_Count,
};
enum E_GENRE
{
	GENRE_NONE,
	GENRE_POPS,
	GENRE_ANIME,
	GENRE_VOCALOID,
	GENRE_GAMEMUSIC,
	GENRE_VARIETY,
	GENRE_CLASSIC,
	GENRE_NAMCOORIGINAL,
	GENRE_KIDS,
	GENRE_DAN,
	GENRE_HISTORY,
	GENRE_FAVOLITE,
	GENRE_Count,
};
//����ꗗ
enum E_JUDGE
{
	JUST,
	HIT,
	MISS,
	ROLL,
	JUDGE_COUNT,//����̐�������
};
enum E_NOTES_TYPE :unsigned short
{
	//�m�[�c�ꗗ
	NOTES_BAR_LINE,
	NOTES_DON =			1,	
	NOTES_KA =			2,
	NOTES_BIG_DON =		3,
	NOTES_BIG_KA =		4,
	NOTES_ROLL =		5,
	NOTES_BIG_ROLL =	6,
	NOTES_BALLOON =		7,
	NOTES_ROLLEND =		8,
	NOTES_KUSUDAMA =	9,
	NOTES_BOMB_DON,
	NOTES_BOMB_KA,
	NOTES_Count,
	NOTES_BIG_ROLLEND,
	NOTES_BALLOON_ROLLEND,
	NOTES_KUSUDAMA_ROLLEND,
	//���߈ꗗ
	ORDER_BPM_CHANGE = 0x80,
	ORDER_GOGOSTART,
	ORDER_GOGOEND,
	ORDER_END,
	ORDER_SCROLL,
	ORDER_BRANCHSTART,
	ORDER_BRANCHEND,
	ORDER_SECTION,
	ORDER_LEVELHOLD,
	ORDER_NEXTSONG,
	ORDER_EFFECT1,
	ORDER_EFFECTEND,
};
enum class E_SCORE_RANK
{
	RANK_NONE = -1,
	RANK_IKI_WHITE,
	RANK_IKI_BRONZE,
	RANK_IKI_SILVER,
	RANK_MIYABI_YELLOW,
	RANK_MIYABI_PINK,
	RANK_MIYABI_PURPLE,
	RANK_KIWAMI,
	RANK_Count,
};
enum class E_CROWN
{
	CROWN_NONE = -1,
	CROWN_CLEAR,
	CROWN_FULLCOMBO,
	CROWN_DONDAFULLCOMBO,
	CROWN_Count,
};



struct ST_ENSO_OPTION
{
	ST_ENSO_OPTION()
	{
		scroll_speed = 1.0f;
		doron = false;
		abekobe = false;
		random = RANDOM_OFF;
		skip = false;
		offset = 0;
		b_offset = false;
		voice = true;
		neiro = 0;
	}

	ST_ENSO_OPTION GetDefaultOption()
	{
		return ST_ENSO_OPTION();
	}

	enum E_RANDOM
	{
		RANDOM_OFF,
		RANDOM_KIMAGURE,
		RANDOM_DETARAME,
	};

	float scroll_speed;
	bool doron;
	bool abekobe;
	int random;
	bool skip;
	int offset;
	bool b_offset;
	bool voice;
	int neiro;
};

struct ST_SCORE_DATA
{
	ST_SCORE_DATA()
	{
		for (int i = 0; i < JUDGE_COUNT; i++)
		{
			judge[i] = 0;
		}
		score = 0;
		combo = 0;
		max_combo = 0;

		for (int i = 0; i < (int)E_SCORE_RANK::RANK_Count; i++)
		{
			score_rank_norma[i] = 0;
		}
		ct_gauge = { CCounter(0.0f,0.0f,100.0f,STOP) };
		score_rank = (E_SCORE_RANK)-1;
		crown = (E_CROWN)-1;
		playcount = 0;
	}

	int judge[E_JUDGE::JUDGE_COUNT];//����L�^��� + �A�Ő�
	int score;				//���݂̃X�R�A
	int combo;				//���݂̃R���{
	int max_combo;			//�ő�̃R���{
	int score_rank_norma[(int)E_SCORE_RANK::RANK_Count];
	int playcount;
	CCounter ct_gauge;
	E_SCORE_RANK score_rank;
	E_CROWN crown;
	ST_ENSO_OPTION st_option;
};

enum E_BRANCH
{
	BRANCH_NONE,
	BRANCH_NORMAL,
	BRANCH_KUROTO,
	BRANCH_TATSUJIN,
	BRANCH_Count,
};
enum E_BRANCH_TYPE
{
	BRANCH_ROLL,
	BRANCH_PERFECT,
	BRANCH_SCORE,
};
enum E_DAN_TYPE
{
	TYPE_GAUGE,
	TYPE_GREAT,
	TYPE_GOOD,
	TYPE_MISS,
	TYPE_SCORE,
	TYPE_ROLL,
	TYPE_HIT,
	TYPE_COMBO,
};


enum E_TAIKO_FLUSH
{
	LEFT_DON,
	RIGHT_DON,
	LEFT_KA,
	RIGHT_KA,
	TAIKO_FLUSH_Count,
};

enum E_SE_NOTES
{
	MOJI_�h��,
	MOJI_�h,
	MOJI_�R,
	MOJI_�J�b,
	MOJI_�J,
	MOJI_�h����,
	MOJI_�J�b��,
	MOJI_�A��,
	MOJI_�[,
	MOJI_���I,
	MOJI_�A�ő�,
	MOJI_�ӂ�����,
	MOJI_��������,
};

//�m�[�c���̍\����
struct ST_NOTES
{
	E_NOTES_TYPE notes_type;		//�m�[�c���
	float judge_time;	//������s������	
	int measure;		//���ߐ�
//	int lane;			//���Ԗڂ̃��[���H
	bool judge;			//������I���H
	float scroll_speed;
	float roll_time;		//�ʒu
	int roll_info;	//�A�ŗp�@�ԐF�ɕω�
	E_BRANCH branch;
	E_SE_NOTES moji;
};
struct ST_NOTES_BRANCH
{
	float norma[2];//���l���ʁA�B�l����		
	E_BRANCH_TYPE type;
	float judge_time;	//������s������	
	int measure;		//���ߐ�
//	int lane;			//���Ԗڂ̃��[���H
	bool judge;			//������I���H
};
enum E_DANRESULT_STATUS
{
	RESULT_FAILURE,
	RESULT_CLEARED,
	RESULT_GOLDCLEARED,
};


namespace MusicGame
{
	enum E_BETTER_PERFORMANCE
	{
		bp_JUDGE,
		bp_MTAIKO,
		bp_CHARA,
		bp_FLYINGNOTES,
		bp_BG,
		bp_COMBOBALLOON,
		bp_SPARK,
		bp_DANCER,
		bp_FOOTER,
		bp_Count,
	};

	E_DIFFCULTY StrToDiffculty(string str);
	E_GENRE StrToGenre(string str);
	wchar_t* StrToWcr(string str);


	//���ʏ��̍\����
	struct ST_FUMEN_DATA
	{
		ST_FUMEN_DATA()
		{
			title = "";
			sub_title = "";
			bpm = 120.0f;
			demo_start = 0.0f;
			diffculty = E_DIFFCULTY::DIFF_ONI;
			offset = 0.0f;
			wave_file = "";
			measure_count = 1;
			for (int i = 0; i < BRANCH_Count; i++)
				notes_count[i] = 0;
			score_add = 0;
			roll_remain = 0;

			for (int i = 0; i < DIFF_Count; i++)
			{
				diff_fumen_use[i] = false;
				level[i] = 0;
				is_branch[i] = false;
			}
			genre = GENRE_NONE;

		}

		void FumenHeaderLoad(string command_param)
		{
			//find�֐��́A�����񂪌�����Ȃ����
			//npos(-1)��Ԃ����߁A-1�o�Ȃ����m�F���邱�ƂƂ���

			//SUBTITLE�ɂ�TITLE�Ƃ��������񂪊܂܂�Ă��邽�߁A���SUBTITLE����`�F�b�N���A
			//�^�C�g���ɃT�u�^�C�g��������Ȃ��悤�ɂ���B
			if (command_param.find("SUBTITLE:") != -1)
			{
				sub_title = command_param.substr(9);
			}
			else if (command_param.find("TITLE:") != -1)
			{
				title = command_param.substr(6);
			}
			else if (command_param.find("GENRE:") != -1)
			{
				string genre_str = command_param.substr(6);
				genre = MusicGame::StrToGenre(genre_str);
			}

			//���̑��w�b�_�̓ǂݍ��݁B
			if (command_param.find("BPM:") != -1)
			{
				command_param = command_param.substr(4);
				bpm = atof(command_param.c_str());
			}
			else if (command_param.find("OFFSET:") != -1)
			{
				command_param = command_param.substr(7);
				offset = atof(command_param.c_str());
			}
			else if (command_param.find("DEMOSTART:") != -1)
			{
				command_param = command_param.substr(10);
				demo_start = atof(command_param.c_str());
			}
			else if (command_param.find("WAVE:") != -1)
			{
				command_param = command_param.substr(5);
				wave_file = fumen_path + "/../" + command_param;
			}
			else if (command_param.find("COURSE:") != -1)
			{
				command_param = command_param.substr(7);
				diffculty = MusicGame::StrToDiffculty(command_param);
				diff_fumen_use[diffculty] = true;
			}
			else if (command_param.find("LEVEL:") != -1)
			{
				command_param = command_param.substr(6);
				level[diffculty] = atoi(command_param.c_str());
			}
			else if (command_param.find("#BRANCHSTART") != -1)
			{
				is_branch[diffculty] = true;
			}

		}

		string fumen_path;		//���ʃt�@�C���̃p�X
		string title;			//�Ȗ�
		string sub_title;		//�T�u�^�C�g��
		float bpm;				//�Ȃ̃e���|
		float offset;			//�Ȃ̊J�n�ʒu
		float demo_start;				//�f���̊J�n�ʒu
		E_DIFFCULTY diffculty;	//���ʂ̓�Փx
		E_GENRE genre;
		string wave_file;		//�����t�@�C���̃p�X

		//���t���Ɏg�����
		int measure_count;
		int notes_count[BRANCH_Count];
		int roll_remain;
		int score_add;
		list<ST_NOTES> list_notes;
		list<ST_NOTES_BRANCH> list_branch;
		list<int> list_balloon;
		float end_time;

		bool is_branch[DIFF_Count];
		bool diff_fumen_use[DIFF_Count];
		int level[DIFF_Count];
	};
	struct ST_ENSO_BATTLE
	{

	};

	const RECT_F RECT_TILE_BLACK = { 64.0f,0.0f,64.0f,64.0f };

	//4/4���q���Ƃ��A1/4�����Ƃ��A�Ƃ肠���������������萔��p�ӂ��Ă݂�B
	//���q�ύX���߂Ƃ��������ł���΂��̒萔���g�����Ƃ͂Ȃ����낤�B
	//�Ƃ���ŁA�ǂ�����4���������Ƃ��A4��������4��1���߂��Ƃ��A
	//����4�͂ǂ����痈���̂��낤�B
	const int MEASURE_LENGTH = 4;
	const float JUDGE_OFFSET = 0.016f;
	const float JUDGE_OUT_TIME = 5.0f;//������s���Ȃ������ꍇ���b��ɍ폜���邩�B

	const float JUDGE_RANGE[JUDGE_COUNT] =
	{
		0.03333f,//JUST
		0.06668f,//HIT
		0.100f,//MISS
		0.0f,//ROLL
	};

	const float SCORE_RANK_NORMA_PERCENTAGE[(int)E_SCORE_RANK::RANK_Count] =
	{
		0.5f,//��
		0.6f,
		0.7f,
		0.8f,//��
		0.9f,
		0.95f,
		1.0f,//��
	};

	//�I���܂ł̒x��
	const int TIME_START_DELAY = 2000;
	const int TIME_END_DELAY = 500;

	//2P
	const Point NOTES_JUDGE_LINE[2] = { { 350,192 },{350,368} };
	const static float SE_NOTES_OFFSET_Y = 131;

	const RECT_F RECT_OPTION_DORON = { 0.0f,0.0f,32.0f,32.0f };
	const RECT_F RECT_OPTION_ABEKOBE = { 0.0f,32.0f,32.0f,32.0f };
	const RECT_F RECT_OPTION_KIMAGURE = { 0.0f,64.0f,32.0f,32.0f };
	const RECT_F RECT_OPTION_DETARAME = { 0.0f,96.0f,32.0f,32.0f };
	const RECT_F RECT_OPTION_OFFSET = { 0.0f,128.0f,32.0f,32.0f };
	const RECT_F RECT_OPTION_SPEED = { 0.0f,160.0f,32.0f,32.0f };


	const RECT_F RECT_TITLE_SONG = { 0.0f,0.0f,384.0f,64.0f };

	const int TAIKO_FLUSH_TYPE = 4;

	std::wstring StringToWString
	(
		std::string oString
	);

	const int SONGSELECT_BAR_AMOUNT = 13;

	const int DAN_NEXTSONG_TIME = 7700;
	const int DAN_MAX_SONG = 3;
	const RECT_F RECT_NOWSONG_NUMBER = { 0.0f,0.0f,27.0f,29.0f };
	const Point SONGSELECT_NOW_SONG = { 1073,149 };
	const static int MAX_PLAYER_AMOUNT = 4;
	const static float P2_HEIGHT = 176.0f;
	const static int HISTORY_MAX = 30;
	const static int CLOSE_BOX_INTERVAL = 7;

	class DanC
	{
	public:
		enum E_DAN_STATUS
		{
			DANC_FAILED,
			DANC_PINCH,
			DANC_REACH,
			DANC_CLEAR,
			DANC_GOLD,
		};
		enum E_DAN_RANGE
		{
			RANGE_MORE,
			RANGE_LESS,
		};

		DanC();
		~DanC() {}
		void SetDanC(E_DAN_TYPE type,int red, int gold);
		int GetValue();
		bool Update(int value,int song_num);
		void SetStatus(E_DAN_STATUS status,int song);
		E_DAN_STATUS GetStatus(int song);
		void Start();
		void SongEndCheck();
		bool GetCommonCondition() { return m_common; }
		bool GetReached();
		float GetValueToPercent(int song);
		E_DAN_TYPE m_type;
		E_DAN_RANGE m_range;
		int m_value[DAN_MAX_SONG];
		int m_norma[DAN_MAX_SONG][2];//�ԍ��i�A�����i
		bool m_common;

	private:

		E_DAN_STATUS m_status[DAN_MAX_SONG];
		int m_song_count;
		bool m_failed;
		void SetCleared(int song);
		void SetReached(int song);//�B���̌����݂����邩�ǂ������肷��B
	};

	struct ST_STATUS_PANEL
	{
		ST_STATUS_PANEL()
		{
			for (int i = 0; i < (int)E_DIFFCULTY::DIFF_Count; i++)
			{
				for (int j = 0; j < (int)E_CROWN::CROWN_Count; j++)
				{
					crown_count[i][j] = 0;
				}
				for (int j = 0; j < (int)E_SCORE_RANK::RANK_Count; j++)
				{
					rank_count[i][j] = 0;
				}
			}
		}

		int crown_count[(int)E_DIFFCULTY::DIFF_Count][(int)E_CROWN::CROWN_Count];
		int rank_count[(int)E_DIFFCULTY::DIFF_Count][(int)E_SCORE_RANK::RANK_Count];
	};

	//�L�����N�^�[�e�N�X�`��
	extern vector<CTexture> g_tex_normal;
	extern vector<CTexture> g_tex_10combo;
	extern vector<CTexture> g_tex_10combo_max;
	extern vector<CTexture> g_tex_clear;
	extern vector<CTexture> g_tex_clear_in;
	extern vector<CTexture> g_tex_gogostart;
	extern vector<CTexture> g_tex_gogo;
	extern vector<CTexture> g_tex_soulin;
	extern vector<CTexture> g_tex_balloon_broke;
	extern vector<CTexture> g_tex_balloon_miss;
	extern vector<CTexture> g_tex_balloon_break;
	extern CTexture g_tex_title;
	extern CTexture g_tex_controll_guide;
	extern CTexture g_tex_lane;
	extern CTexture g_tex_taiko;
	extern CTexture g_tex_lane_left;
	extern CTexture g_tex_score_bg;
	extern CTexture g_tex_gauge_base;
	extern CTexture g_tex_gauge_line;
	extern CTexture g_tex_gauge_rainbow;
	extern CTexture g_tex_gauge_base_dan;
	extern CTexture g_tex_gauge_line_dan;
	extern CTexture g_tex_gauge_rainbow_dan;
	extern CTexture g_tex_soul;
	extern CTexture g_tex_soul_fire;
	extern CTexture g_tex_balloon;
	extern CTexture g_tex_balloon_fukidashi;
	extern CTexture g_tex_balloon_number;
	extern CTexture g_tex_kusudama;
	extern CTexture g_tex_concentration_line;
	extern CTexture g_tex_kusudama_renda;
	extern string g_now_select_songtitle;
	extern int g_confirm_song_id;
	extern E_GAME_MODE g_mode;
	extern ST_STATUS_PANEL g_player_status;
	
	namespace SongSelect
	{
		enum E_BAR_TYPE
		{
			BAR_FOLDER,
			BAR_FUMEN,
			BAR_CLOSE,
			BAR_RANDOM,
		};
		struct ST_BAR_INFO
		{
			struct ST_BAR_SCORE
			{
				E_DIFFCULTY crown_diff;
				E_DIFFCULTY rank_diff;
				E_CROWN crown_color;
				E_SCORE_RANK rank_color;
				
			};

			void ScoreSet(ST_SCORE_DATA score,E_DIFFCULTY diffculty);

			E_BAR_TYPE bar_type;
			E_GENRE genre;
			string title;
			string subtitle;
			string folder_path;
			string wave_file;
			float demo_start;
			int level[DIFF_Count];
			bool branch[DIFF_Count];
			ST_BAR_SCORE show_score;
			int bestscore[DIFF_Count];
			E_CROWN crown[DIFF_Count];
			E_SCORE_RANK rank[DIFF_Count];
			int id;
		};

		extern vector<ST_BAR_INFO> g_vec_all_fumen_bar;
		extern 	vector<ST_BAR_INFO> g_vec_folder_bar;
		extern vector<vector<int>> g_vec_folder_fumen;

		extern vector<CTexture> g_tex_chara_start;
		extern vector<CTexture> g_tex_chara_select;
		extern vector<CTexture> g_tex_chara_loop;
		extern CTexture g_tex_box_overlay;

		void LoadDirectory(list<string>& path_list, list<string>& folder_path_list, string path);
		void SongBarCreate();
		void SongBarDelete();
		ST_BAR_INFO FumenBarCreate(ST_FUMEN_DATA fumen);
		void FumenListCreate(list<string> fumen_path_list);
		void CloseBoxInsert(vector<int>& folder_fumen);

		extern int g_close_id;
	}

	void CommonTextureLoader();
	int TextureAmountCount(string path, string find_str);

	void ScoreDataImport(ST_SCORE_DATA score[DIFF_Count],string file_path);
}






struct ST_DAN_SONG
{
	ST_DAN_SONG()
	{
		title = "";
		sub_title = "";
		diffculty = E_DIFFCULTY::DIFF_ONI;
		wave_file = "";
		measure_count = 1;
		for (int i = 0; i < BRANCH_Count; i++)
			notes_count[i] = 0;
		score_add = 0;
		roll_remain = 0;

		diff_fumen_use = false;
		level = 0;
		is_branch = false;
		roll_time = 0.0f;
		music_start_time = 0.0f;
		genre = GENRE_NONE;
	}

	string title;			//�Ȗ�
	string sub_title;		//�T�u�^�C�g��
	E_DIFFCULTY diffculty;	//���ʂ̓�Փx
	E_GENRE genre;
	string wave_file;		//�����t�@�C���̃p�X

	//���t���Ɏg�����
	int measure_count;
	int notes_count[BRANCH_Count];
	int roll_remain;
	int score_add;
	list<ST_NOTES_BRANCH> list_branch;
	float roll_time;
	float music_start_time;

	bool is_branch;
	bool diff_fumen_use;
	int level;
};