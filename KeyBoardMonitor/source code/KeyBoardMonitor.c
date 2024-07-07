#include "KBM.h"

int KBM_QUIT = 0;

unsigned short KBM_KEYS_STATE[0x100] = {0};
HANDLE KBM_MONITOR_THREAD;

void is_down(int key, unsigned short *p);

DWORD WINAPI KeyStateUpdate(LPVOID lpParam)
{
    int i;
    while (!KBM_QUIT)
    {
        for (i = 0x41; i <= 0x5A; i++)
            is_down(i, &KBM_KEYS_STATE[i]);

        for (i = 0x30; i <= 0x39; i++)
            is_down(i, &KBM_KEYS_STATE[i]);
        
        is_down(VK_SPACE, &KBM_KEYS_STATE[VK_SPACE]);
        is_down(VK_TAB, &KBM_KEYS_STATE[VK_TAB]);
        is_down(VK_LSHIFT, &KBM_KEYS_STATE[VK_LSHIFT]);
        is_down(VK_LCONTROL, &KBM_KEYS_STATE[VK_LCONTROL]);
        is_down(VK_ESCAPE, &KBM_KEYS_STATE[VK_ESCAPE]);
        is_down(VK_BACK, &KBM_KEYS_STATE[VK_BACK]);
        is_down(VK_RETURN, &KBM_KEYS_STATE[VK_RETURN]);
        is_down(VK_RSHIFT, &KBM_KEYS_STATE[VK_RSHIFT]);
        is_down(VK_RCONTROL, &KBM_KEYS_STATE[VK_RCONTROL]);
        is_down(VK_UP, &KBM_KEYS_STATE[VK_UP]);
        is_down(VK_DOWN, &KBM_KEYS_STATE[VK_DOWN]);
        is_down(VK_LEFT, &KBM_KEYS_STATE[VK_LEFT]);
        is_down(VK_RIGHT, &KBM_KEYS_STATE[VK_RIGHT]);
    }
}

void MonitorStart(void)
{
    KBM_MONITOR_THREAD = CreateThread(  
        NULL,                   // 默认安全属性  
        0,                      // 使用默认堆栈大小  
        KeyStateUpdate,         // 线程函数  
        NULL,                   // 不传递任何参数给线程函数  
        0,                      // 默认创建标志  
        NULL);           // 接收新线程的标识符  
}

void MonitorEnd(void)
{
    KBM_QUIT = 1;
}

void is_down(int key, unsigned short *p)
{
    if (GetAsyncKeyState(key) && 0x8000)
        *p = KBM_KEY_DOWN;
    else 
        *p = KBM_KEY_UP;
}
