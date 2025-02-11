# KeyBoardMonitor
A module that helps you to monitor keyboard actions.

### Descriptions
KeyBoardMonitor is written by C. It allows you to monitor Keyboard actions in another thread.
This programm can only be used on Window, because it based on api that support by Windows.

### API

##### MonitorStart()

```C
void MonitorSTart(void);
```
Create a new thread to update the key's actions.

##### MonitorEnd()

```C
void MonitorEnd(void);
```
End up the thread.

##### KBM_KEYS_STATE[256]

```C
uint8_t KBM_KEYS_STATE[256];
```
This is a global property. The type is bool, 1 means the key is on pressed and 0 means the key is not on pressed.
For each key on the keyboard, it has a virtual code which ranged between 0 to 196, but **it is noncontinuous**.
But you can access the array by macro definitions. You can see all of it in **KBM.h** file. What you have to be carefull
is that not all of keys' state in the array will be update. The programm only focuses on common keys. If you need more 
keys, edit the source code yourself. The function you need to perfect is `DWORD WINAPI KeyStateUpdate(LPVOID lpParam);`.
You can find it in `KBM.h` and `KeyBoardMonitor.c`. What really needs to mention is that this array is been protected by 
the mutex, which means it can only be access by one thread. So if you get more than on thread that is associated with this
array, you have to consider race condition, i.e. deadlock. Don't try to set a new array to detect changes of `KBM_KEYS_STATE`.

##### KBM_MONITOR_THREAD_HANDLE
```
HANDLE KBM_MONITOR_THREAD_HANDLE;
```
This is the thread handle where you can use Windows api to control the thread.

##### KBM_MONITOR_THREAD_ID
```
DWORD KBM_MONITOR_THREAD_ID;
```
This is the thread handle.

### Example
```C
// ./test_file.c
#include <stdio.h>
#include "KBM.h"

void main()
{
    MonitorStart();
    while (1)
    {  
        printf("%d\n", KBM_KEYS_STATE[VK_A]);
        // YourFunction();  // Complete with you functions
    }
    MonitorEnd();
}
```
Then put all of the files, i.e. test_file.c KBM.h kbm.dll together in your project folder.

```bash
gcc -o test test_file.c -L./ -lkbm
```
Then run the order. It will generate a test.exe file in project folder. Dubble tap to run.

### Statement
The programm should not be used as any illegal purposes. Including but not limited to monitoring users privacy.
Any consequences resulting from improper purposes will be considered as personal behavior.


