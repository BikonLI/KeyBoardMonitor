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
unsigned short KBM_KEYS_STATE[256];
```
This is a global property. The type is bool, 1 means the key is on pressed and 0 means the key is not on pressed.
For each key on the keyboard, it has a virtual code which ranged between 0 to 196, but **it is noncontinuous**.
But you can access the array by macro definitions. You can see all of it in **KBM.h** file. What you have to be carefull
is that not all of keys' state in the array will be update. The programm only focuses on common keys. If you need more 
keys, edit the source code yourself. The function you need to perfect is `DWORD WINAPI KeyStateUpdate(LPVOID lpParam);`.
You can find it in `KBM.h` and `KeyBoardMonitor.c`. 

### Example


