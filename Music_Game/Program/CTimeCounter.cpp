//�g�p����w�b�_�[�t�@�C��
#include "CTimeCounter.h"

//�g�p����l�[���X�y�[�X

CTimeCounter::CTimeCounter()
{
	isStoped = true;
	isProgress = false;
	isUnused = true;
}
//�R���X�g���N�^
CTimeCounter::CTimeCounter(int start, int end, int msInterval)
{
	//ms���Z�B300ms��0.3�b
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
//�J�n
void CTimeCounter::Start(int start, int end, int msInterval)
{
	//ms���Z�B300ms��0.3�b
	NowValue = start;
	StartValue = start;
	EndValue = end;
	msInterval_Value = msInterval;
	ckStart = clock();
	ckLast = clock();
	isUnused = false;
	isProgress = true;
}
//��~
void CTimeCounter::Stop()
{
	isStoped = true;
	isProgress = false;
	isUnused = true;
}

//�i�s
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

	//����
	//�O�� 3300
	//���� 3500
	//�Ԋu 100
	//�O��̎��Ԃ���ǂꂮ�炢�o�߂��Ă��邩���v�Z����
	//�l�ɉ��Z����A�ł����񂶂��...?
	//���_:�_���B�Ԋu�l�������ł��傫���Ɠ����Ȃ��B

	ckNow = clock() - ckStart - (NowValue - StartValue) * msInterval_Value;


	while (msInterval_Value <= ckNow)
	{
		//ckNow���Am_msInterval���傫���Ȃ����ꍇ�A�������Ȃ�܂ň���
		if (EndValue > NowValue)
		{
			NowValue++;
		}
		ckNow -= msInterval_Value;
	}
	//�O��̋L�^����
	ckLast = clock();
}

//�i�sLoop
void CTimeCounter::ActionLoop()
{
	if (isUnused == true)
	{
		isStoped = true;
		return;
	}

	isStoped = false;
	isProgress = true;

	//		�����[�Ƃ��Ă���̒l�̍�	
	ckNow = (clock() - ckStart) - NowValue * msInterval_Value;

	while (msInterval_Value <= (int)ckNow)
	{
		//ckNow���Am_msInterval���傫���Ȃ����ꍇ�A�������Ȃ�܂ň���
		if (EndValue > NowValue)
		{
			NowValue++;
		}
		if (EndValue <= NowValue)
		{
			//�^�C�}�[�����Z�b�g
			ckStart += NowValue * msInterval_Value;
			NowValue -= EndValue - StartValue;
		}

		ckNow -= msInterval_Value;
	}
}
//	//		�����[�Ƃ��Ă���̒l�̍�	
//	ckNow = (clock() - ckStart);
//
//	while ((long)((NowValue - StartValue) * msInterval_Value) <= ckNow)
//	{
//		//ckNow���Am_msInterval���傫���Ȃ����ꍇ�A�������Ȃ�܂ň���
//
//		NowValue++;
//
//	}
//	while (EndValue <= NowValue)
//	{
//		//�^�C�}�[�����Z�b�g
//		ckStart += (EndValue - StartValue) * msInterval_Value;
//		NowValue -= EndValue - StartValue;
//	}
//}

//�I���l�ɒB���Ă��邩�ǂ����Ԃ��B
bool CTimeCounter::GetEndValueReached()
{
	if (NowValue == EndValue)
	{
		return true;
	}
	return false;
}