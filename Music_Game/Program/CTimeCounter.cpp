//使用するヘッダーファイル
#include "CTimeCounter.h"

//使用するネームスペース

CTimeCounter::CTimeCounter()
{
	isStoped = true;
	isProgress = false;
	isUnused = true;
}
//コンストラクタ
CTimeCounter::CTimeCounter(int start, int end, int msInterval)
{
	//ms換算。300msが0.3秒
	NowValue = start;
	StartValue = start;
	EndValue = end;
	msInterval_Value = msInterval;
	ckStart = clock();
	ckLast = clock();
	isStoped = true;
	isProgress = false;
	isUnused = false;
}
//開始
void CTimeCounter::Start(int start, int end, int msInterval)
{
	//ms換算。300msが0.3秒
	NowValue = start;
	StartValue = start;
	EndValue = end;
	msInterval_Value = msInterval;
	ckStart = clock();
	ckLast = clock();
	isUnused = false;
	isProgress = true;
}
//停止
void CTimeCounter::Stop()
{
	isStoped = true;
	isProgress = false;
	isUnused = true;
}

//進行
void CTimeCounter::Action()
{
	if (EndValue <= NowValue || isUnused == true)
	{
		isStoped = true;
		return;
	}
	isStoped = false;

	if (isPause == true)
	{

	}

	//メモ
	//前回 3300
	//今回 3500
	//間隔 100
	//前回の時間からどれぐらい経過しているかを計算して
	//値に加算する、でいいんじゃね...?
	//結論:ダメ。間隔値が少しでも大きいと動かない。

	ckNow = clock() - ckStart - (NowValue - StartValue) * msInterval_Value;


	while (msInterval_Value <= ckNow)
	{
		//ckNowが、m_msIntervalより大きくなった場合、小さくなるまで引く
		if (EndValue > NowValue)
		{
			NowValue++;
		}
		ckNow -= msInterval_Value;
	}
	//前回の記録時間
	ckLast = clock();
}

//進行Loop
void CTimeCounter::ActionLoop()
{
	if (isUnused == true)
	{
		isStoped = true;
		return;
	}

	isStoped = false;
	isProgress = true;

	//		すたーとしてからの値の差	
	ckNow = (clock() - ckStart) - NowValue * msInterval_Value;

	while (msInterval_Value <= (int)ckNow)
	{
		//ckNowが、m_msIntervalより大きくなった場合、小さくなるまで引く
		if (EndValue > NowValue)
		{
			NowValue++;
		}
		if (EndValue <= NowValue)
		{
			//タイマーをリセット
			ckStart += NowValue * msInterval_Value;
			NowValue -= EndValue - StartValue;
		}

		ckNow -= msInterval_Value;
	}
}
//	//		すたーとしてからの値の差	
//	ckNow = (clock() - ckStart);
//
//	while ((long)((NowValue - StartValue) * msInterval_Value) <= ckNow)
//	{
//		//ckNowが、m_msIntervalより大きくなった場合、小さくなるまで引く
//
//		NowValue++;
//
//	}
//	while (EndValue <= NowValue)
//	{
//		//タイマーをリセット
//		ckStart += (EndValue - StartValue) * msInterval_Value;
//		NowValue -= EndValue - StartValue;
//	}
//}

//終了値に達しているかどうか返す。
bool CTimeCounter::GetEndValueReached()
{
	if (NowValue == EndValue)
	{
		return true;
	}
	return false;
}