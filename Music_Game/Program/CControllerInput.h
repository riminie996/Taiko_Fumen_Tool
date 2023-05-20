#pragma once
#include <Windows.h>
#include <stdlib.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")


enum Controller_Input_Xbox
{
	INPUT_UP =		0x00000001,
	INPUT_DOWN =	0x00000002,
	INPUT_LEFT =	0x00000004,
	INPUT_RIGHT =	0x00000008,
	INPUT_B_DOWN =		0x00000100,
	INPUT_B_RIGHT =		0x00000200,
	INPUT_B_LEFT =		0x00000400,
	INPUT_B_UP =		0x00000800,
	INPUT_P =		0xBFFF,  //�A�i���O�p�b�h��臒l�B�K��
	INPUT_N =		0x3FFF,  //�A�i���O�p�b�h��臒l�B�K��
};


typedef class CConInput
{
public:
	CConInput();
	static void SetUsed();
	static bool GetConInput(unsigned long button);

private:
	static bool CheckSync(unsigned long state, unsigned long button);
	static bool m_controller_used;
}InputC;

//
// �R���g���[���[���͂ɂ���
// A 1
// B 2
// C 4
// D 8
// RIGHT 256
// UP 512
// DOWN 1024
// LEFT 2048
// ���Ƃ�����
// 
//
