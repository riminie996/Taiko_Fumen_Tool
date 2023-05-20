
//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)  

//便利な関数置き場
#include "Function.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameHead.h"
#include "main.h"
#include <math.h>
#include "GameL\UserData.h"
#include <sstream>

using namespace GameL;

//渡された値の桁数を返す関数
int numOfDigit(int num)
{
	int digit = 1;
	//一桁からスタート。
	//numが10以上の場合カウントを増やすが、
	//9の場合はfor文を通らなく1桁なので。
	while ( num >= 10 )
	{
		//1, 値を10で割る 一の位は切り捨て 
		//2, 桁数を1つ増やす 

		num /= 10;
		digit++;
	}
	return digit;
}

//決められた幅から抜けてしまった場合、強制的にそこで止める
//主にメニューのカーソルなどで使うかな...
//minは最少数だが、一応maxとminを比べておく。

//返り値　調整された値
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

//画面外判定を行う
//画面内の場合、trueを返す。
bool IntheScreen(float x, float y, float sizeX, float sizeY)
{
	//0以下の場合だとうまくいかないので、念のため
	//テクスチャサイズ×2の値以下になったとき
	if (x > -(sizeX * 2) && x < WINDOW_SIZE_W + sizeX &&
		y > -(sizeY * 2) && y < WINDOW_SIZE_H + sizeY)
	{
		return true;
	}
	return false;
}

//二点間距離
//座標　X Y 距離X 距離Y
float DistanceF(float fx, float fy, float sx, float sy)
{
	return sqrtf((fx - sx) * (fx - sx) + (fy - sy) * (fy - sy));
}
//小数点第一位から四捨五入します。
int RoundingFirstDecimal(float num)
{
	int inte = (int)num;

	//1.57 - 1 = 0.57
	if (num - inte < 0.5f)
	{
		//切り捨て
		return inte;
	}
	else
	{
		//繰り上げ
		return inte + 1;
	}
}
//一桁目を四捨五入
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

//距離から角度に変換
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