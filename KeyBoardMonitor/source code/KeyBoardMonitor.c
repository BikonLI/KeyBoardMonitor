#include "KBM.h"

int KBM_QUIT = 0;

HANDLE KBM_MONITOR_THREAD_HANDLE = NULL;
DWORD KBM_MONITOR_THREAD_ID = 0;

uint8_t KBM_KEYS_STATE[0x100] = {0};
uint8_t ks_previous[0x100] = {0};
uint8_t ks_current[0x100] = {0};

HANDLE Mutex = NULL;

void is_down(int key, uint8_t *p);
void flash_ks(void);
int is_change(void);

uint8_t KBM_KEYS_STATE[0x100];
uint8_t ks_previous[0x100];
uint8_t ks_current[0x100];

DWORD WINAPI KeyStateUpdate(LPVOID lpParam)
{
    int i;
    while (!KBM_QUIT)
    {
        for (i = 0x41; i <= 0x5A; i++)
            is_down(i, &ks_current[i]);

        for (i = 0x30; i <= 0x39; i++)
            is_down(i, &ks_current[i]);

        is_down(VK_SPACE, &ks_current[VK_SPACE]);
        is_down(VK_TAB, &ks_current[VK_TAB]);
        is_down(VK_LSHIFT, &ks_current[VK_LSHIFT]);
        is_down(VK_LCONTROL, &ks_current[VK_LCONTROL]);
        is_down(VK_ESCAPE, &ks_current[VK_ESCAPE]);
        is_down(VK_BACK, &ks_current[VK_BACK]);
        is_down(VK_RETURN, &ks_current[VK_RETURN]);
        is_down(VK_RSHIFT, &ks_current[VK_RSHIFT]);
        is_down(VK_RCONTROL, &ks_current[VK_RCONTROL]);
        is_down(VK_UP, &ks_current[VK_UP]);
        is_down(VK_DOWN, &ks_current[VK_DOWN]);
        is_down(VK_LEFT, &ks_current[VK_LEFT]);
        is_down(VK_RIGHT, &ks_current[VK_RIGHT]);

        if (is_change())
        {
            flash_ks();
        }
    }
}

void MonitorStart(void)
{
    Mutex = CreateMutex(NULL, FALSE, NULL);

    KBM_MONITOR_THREAD_HANDLE = CreateThread(
        NULL,
        0,
        KeyStateUpdate,
        NULL,
        0,
        &KBM_MONITOR_THREAD_ID);
}

void MonitorEnd(void)
{
    KBM_QUIT = 1;
    CloseHandle(KBM_MONITOR_THREAD_HANDLE);
}

void is_down(int key, uint8_t *p)
{
    if (GetAsyncKeyState(key) && 0x8000)
        *p = KBM_KEY_DOWN;
    else
        *p = KBM_KEY_UP;
}

int is_change(void)
{
    int i, result = 0;
    for (i = 0; i < 0x100; i++)
    {
        if (ks_previous[i] != ks_current[i])
        {
            result = 1;
            break;
        }
        else
        {
            result = 0;
        }
    }
    return result;
}

void flash_ks(void)
{
    int i;
    for (i = 0; i < 0x100; i++)
    {
        WaitForSingleObject(Mutex, INFINITE);
        KBM_KEYS_STATE[i] = ks_current[i]; // Flash ks
        ReleaseMutex(Mutex);

        ks_previous[i] = ks_current[i];
    }
}
