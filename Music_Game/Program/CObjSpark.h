#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjSpark : public CObj
{
public:
	CObjSpark() {}
	~CObjSpark() {}
	void Init();
	void Action();
	void Draw();
	void SparkStart();
private:
	struct ST_SPARK
	{
		CCounter ct_pattern;
		Point pos;
	};
	
	const static int SPARK_AMOUNT = 6;
	const int SPARK_X[SPARK_AMOUNT] =
	{
	418,632,214,846,-10,1060
	};
	const static int SPARK_Y = 280;
	const static int SPARK_PATTERN = 30;
	const RECT_F RECT_SPARK = { 0.0f,0.0f,230.0f,460.0f };
	ST_SPARK m_spark[SPARK_AMOUNT];
	
};
