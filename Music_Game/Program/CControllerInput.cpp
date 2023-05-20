#include "CControllerInput.h"
#include <Windows.h>
#include <stdlib.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")


bool CConInput::m_controller_used;

void CConInput::SetUsed()
{
    //コントローラー接続時はtrue
    //未接続時はfalseにしないと
    //処理落ちします
     m_controller_used = false;
}
bool CConInput::GetConInput(unsigned long button)
{
    if (m_controller_used == false)
        return false;

    JOYINFOEX JoyInfo;
    unsigned long input_state = 0;

    //XBox Controller
    /*if (joyGetPosEx(JOYSTICKID1, &JoyInfo) == JOYERR_NOERROR) {
        if (JoyInfo.dwXpos < INPUT_N)      input_state |= INPUT_LEFT;
        if (JoyInfo.dwXpos > INPUT_P)      input_state |= INPUT_RIGHT;
        if (JoyInfo.dwYpos < INPUT_N)      input_state |= INPUT_UP;
        if (JoyInfo.dwYpos > INPUT_P)      input_state |= INPUT_DOWN;
        if (JoyInfo.dwPOV == 0)      input_state |= INPUT_UP;
        if (JoyInfo.dwPOV == 9000)      input_state |= INPUT_RIGHT;
        if (JoyInfo.dwPOV == 18000)      input_state |= INPUT_DOWN;
        if (JoyInfo.dwPOV == 27000)      input_state |= INPUT_LEFT;
        if (JoyInfo.dwButtons & JOY_BUTTON1)  input_state |= INPUT_B_DOWN;
        if (JoyInfo.dwButtons & JOY_BUTTON2)  input_state |= INPUT_B_RIGHT;
        if (JoyInfo.dwButtons & JOY_BUTTON3)  input_state |= INPUT_B_LEFT;
        if (JoyInfo.dwButtons & JOY_BUTTON4)  input_state |= INPUT_B_UP;
    return CheckSync(input_state, button);
    }*/

    //DUALSHOCK 4
    if (joyGetPosEx(JOYSTICKID1, &JoyInfo) == JOYERR_NOERROR) {
        if (JoyInfo.dwXpos < INPUT_N)      input_state |= INPUT_LEFT;
        if (JoyInfo.dwXpos > INPUT_P)      input_state |= INPUT_RIGHT;
        if (JoyInfo.dwYpos < INPUT_N)      input_state |= INPUT_UP;
        if (JoyInfo.dwYpos > INPUT_P)      input_state |= INPUT_DOWN;
        if (JoyInfo.dwPOV == 0)      input_state |= INPUT_UP;
        if (JoyInfo.dwPOV == 9000)      input_state |= INPUT_RIGHT;
        if (JoyInfo.dwPOV == 18000)      input_state |= INPUT_DOWN;
        if (JoyInfo.dwPOV == 27000)      input_state |= INPUT_LEFT;
        if (JoyInfo.dwButtons & JOY_BUTTON1)  input_state |= INPUT_B_LEFT;
        if (JoyInfo.dwButtons & JOY_BUTTON2)  input_state |= INPUT_B_DOWN;
        if (JoyInfo.dwButtons & JOY_BUTTON3)  input_state |= INPUT_B_RIGHT;
        if (JoyInfo.dwButtons & JOY_BUTTON4)  input_state |= INPUT_B_UP;

        return CheckSync(input_state, button);
    }
    return false;
}
bool CConInput::CheckSync(unsigned long state, unsigned long button)
{
    for (int i = 2048; i >= 1; i >>= 1)
    {

        //しらべたい値まで来た！
        if (button == i)
        {
            //buttonからstateが引ける場合
            if (state >= button)
            {
                return true;
            }
            return false;
        }
        if (state >= i)
        {
            state -= i;
        }
    }
    return false;
}

//void CConInput::CmInput()
//{
//    static bool CmInput(unsigned long button)
//}