#include "CObjSpark.h"
#include "GameHead.h"
//‰Šú‰»
void CObjSpark::Init()
{
	for (int i = 0; i < SPARK_AMOUNT; i++)
	{
		m_spark[i].pos.x = SPARK_X[i];
		m_spark[i].pos.y = SPARK_Y;
		m_spark[i].ct_pattern = { CCounter(-(i / 2),0.0f,SPARK_PATTERN,STOP) };

		m_spark[i].ct_pattern.NowValue = m_spark[i].ct_pattern.MaxValue;
	}
}
//is
void CObjSpark::Action()
{
	for (int i = 0; i < SPARK_AMOUNT; i++)
	{
		m_spark[i].ct_pattern.Add(1);
	}
}
void CObjSpark::Draw()
{
	for (int i = 0; i < SPARK_AMOUNT; i++)
	{
		Draw::SetBlend(tex_SPARK, ADDITIONALPHA);
		RECT_F rect_spark = RECT_SPARK;
		rect_spark.m_x = m_spark[i].ct_pattern.NowValue * RECT_SPARK.m_width;

		if (m_spark[i].ct_pattern.NowValue >= 0 && !m_spark[i].ct_pattern.GetMaxReached())
			Draw::Draw(tex_SPARK, m_spark[i].pos.x, m_spark[i].pos.y, rect_spark);
	}
}

void CObjSpark::SparkStart()
{
	for (int i = 0; i < SPARK_AMOUNT; i++)
	{
		m_spark[i].ct_pattern.Reset();
	}
}