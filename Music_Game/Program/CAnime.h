#pragma once
//STL�f�o�b�O�@�\��OFF�ɂ���
#define _HAS_ITERATOR_DEBUGGING	(0)

#include "CFileFormat.h"

//struct ST_ANIME_INFO
//{
//	//�ʒu
//	float pos_x;
//	float pos_y;
//	//�X�P�[��
//	float scale_x;
//	float scale_y;
//	//�F�Ɠ����x
//	float color_r;
//	float color_g;
//	float color_b;
//	float color_a;
//	//��]��
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
		MOVE_NORMAL,//����
		MOVE_ACCELE,//����
		MOVE_DECELE,//����
		MOVE_ACC_DEC,//������

		MoveTypeCounter,//������ރJ�E���g�p
	};

	const std::string STR_MOVE_TYPE[MoveTypeCounter] =
	{
		"Normal",	//����
		"Accele",	//����
		"Decele",	//����
		"Acc_Dec",	//������
	};


	//vector�ŊǗ��������B
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
	float m_now_frame;	//�A�j���[�V�������̌��݂̃t���[��
	float m_max_frame;	//�A�j���[�V�����̍ŏI�t���[��
	bool m_flag_start;
	std::string m_str_entry_name;

	std::vector<ST_ANIME> m_vec_anime;
	//ST_ANIME_INFO m_now_info;

};