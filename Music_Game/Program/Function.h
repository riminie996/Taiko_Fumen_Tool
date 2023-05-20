#pragma once
#include <vector>
#include <string>
#include "GameL\DrawTexture.h"
using namespace GameL;

//�֗��Ȋ֐��u����
struct Point
{
	int x;
	int y;
};
struct PointF
{
	float x;
	float y;
};

//����
enum DIRECTION
{
	Left,
	Right,
	Up,
	Down,
};
//---�ǂ̃Q�[���ł��g����֐�----------------------------

//�^����ꂽ���l�̌����𒲂ׂ�֐�
int numOfDigit(int num);

//���߂�ꂽ�����甲���Ă��܂����ꍇ�A�����I�ɂ����Ŏ~�߂�
int Min_Max(int position, int min, int max);
float Min_Max(float position, float min, float max);

float DistanceToRotate(float rvx, float rvy);

//��ʊO���������B
//��ɕ`�揈�����X�L�b�v����Ƃ��Ɏg���B ��{�e�N�X�`���T�C�Y:64
bool IntheScreen(float x, float y, float sizeX = 64, float sizeY = 64);

//��_�ԋ��������߂�
float DistanceF(float fx, float fy, float sx, float sy);

//�����_���ʂ���l�̌ܓ����܂��B
int RoundingFirstDecimal(float num);

int RoundingFirstDigit(float num);

std::vector<std::string> split(std::string& input, char delimiter);

void DrawFill(int tex, RECT_F rectangle);

const float PI = 3.141592f;

bool stob(std::string str);