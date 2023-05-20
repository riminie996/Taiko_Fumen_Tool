
//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)  

//�֗��Ȋ֐��u����
#include "Function.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameHead.h"
#include "main.h"
#include <math.h>
#include "GameL\UserData.h"
#include <sstream>

using namespace GameL;

//�n���ꂽ�l�̌�����Ԃ��֐�
int numOfDigit(int num)
{
	int digit = 1;
	//�ꌅ����X�^�[�g�B
	//num��10�ȏ�̏ꍇ�J�E���g�𑝂₷���A
	//9�̏ꍇ��for����ʂ�Ȃ�1���Ȃ̂ŁB
	while ( num >= 10 )
	{
		//1, �l��10�Ŋ��� ��̈ʂ͐؂�̂� 
		//2, ������1���₷ 

		num /= 10;
		digit++;
	}
	return digit;
}

//���߂�ꂽ�����甲���Ă��܂����ꍇ�A�����I�ɂ����Ŏ~�߂�
//��Ƀ��j���[�̃J�[�\���ȂǂŎg������...
//min�͍ŏ��������A�ꉞmax��min���ׂĂ����B

//�Ԃ�l�@�������ꂽ�l
float Min_Max(float position, float min, float max)
{
	if (min > max)
	{
		float a = min;
		min = max;
		max = a;
	}
	
	if (position < min) return min;
	if (position > max) return max;

	return position;
}
int Min_Max(int position, int min, int max)
{
	if (min > max)
	{
		int a = min;
		min = max;
		max = a;
	}

	if (position < min) return min;
	if (position > max) return max;

	return position;
}

//��ʊO������s��
//��ʓ��̏ꍇ�Atrue��Ԃ��B
bool IntheScreen(float x, float y, float sizeX, float sizeY)
{
	//0�ȉ��̏ꍇ���Ƃ��܂������Ȃ��̂ŁA�O�̂���
	//�e�N�X�`���T�C�Y�~2�̒l�ȉ��ɂȂ����Ƃ�
	if (x > -(sizeX * 2) && x < WINDOW_SIZE_W + sizeX &&
		y > -(sizeY * 2) && y < WINDOW_SIZE_H + sizeY)
	{
		return true;
	}
	return false;
}

//��_�ԋ���
//���W�@X Y ����X ����Y
float DistanceF(float fx, float fy, float sx, float sy)
{
	return sqrtf((fx - sx) * (fx - sx) + (fy - sy) * (fy - sy));
}
//�����_���ʂ���l�̌ܓ����܂��B
int RoundingFirstDecimal(float num)
{
	int inte = (int)num;

	//1.57 - 1 = 0.57
	if (num - inte < 0.5f)
	{
		//�؂�̂�
		return inte;
	}
	else
	{
		//�J��グ
		return inte + 1;
	}
}
//�ꌅ�ڂ��l�̌ܓ�
int RoundingFirstDigit(float num)
{
	int inte = (int)num;
	if (inte % 10 < 5)
	{
		return inte - inte % 10;
	}
	else
	{
		return inte - inte % 10 + 10;
	}
}

//��������p�x�ɕϊ�
float DistanceToRotate(float rvx, float rvy)
{
	float r = atan2(rvy, rvx) * 180.0f / 3.14f;

	if (r < 0.0f)
		r = abs(r);
	else
		r = 360.0f - abs(r);

	return r;
}


std::vector<std::string> split(std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string field;
	std::vector<std::string> result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}

void DrawFill(int tex, RECT_F rectangle)
{
	for (float y = 0.0f; y < WINDOW_SIZE_H; y += rectangle.m_height)
	{
		for (float x = 0.0f; x < WINDOW_SIZE_W; x += rectangle.m_width)
		{
			Draw::Draw(tex, x, y, rectangle);
		}
	}
}

bool stob(std::string str)
{
	if (str == "true")return true;
	if (str == "1")return true;
	return false;
}