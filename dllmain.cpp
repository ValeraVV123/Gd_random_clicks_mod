#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

using namespace std;

void mouse_down();

void mouse_up();

DWORD WINAPI myThread(void* instance) {
    int chance = 120;

    MessageBoxA(NULL, "Injected has been success! right alt = on/off mod. Chance: 1/120 in frame.", "Inject info", MB_OK);

    bool run = false;
    int value = 0;

    srand(time(0));

    while (true) {
        if (GetAsyncKeyState(VK_RMENU) & 0x8000) {
            if (run == true) {
                run = false;
                printf("Mod: off.");
                Sleep(600);
                MessageBoxA(NULL, "Mod: off", "Mod status", MB_OK);
                continue;
            }
            else {
                run = true;
                printf("Mod: on.");
                Sleep(600);
                MessageBoxA(NULL, "Mod: on", "Mod status", MB_OK);
                continue;
            }
        }
        if (run == true) {
            srand(time(0));
            value = 1 + rand() % chance;
            if (value == 2) {
                mouse_down();
                Sleep(20);
                mouse_up();
                continue;
            }
        }
        

    }

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        auto handle = CreateThread(NULL, 0, &myThread, instance, 0, NULL);
        if (handle) CloseHandle(handle);
    }
    return TRUE;
}

void mouse_down() {
    POINT pos_mouse;

    GetCursorPos(&pos_mouse);

    mouse_event(MOUSEEVENTF_LEFTDOWN, pos_mouse.x, pos_mouse.y, 0, 0);
}

void mouse_up() {
    POINT pos_mouse;

    GetCursorPos(&pos_mouse);

    mouse_event(MOUSEEVENTF_LEFTUP, pos_mouse.x, pos_mouse.y, 0, 0);
}