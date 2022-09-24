#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <cstdio>
//#include <string> Я забыл убрать это.

//Include libs (all libraries need for my programm)

void mouse_down();

void mouse_up();

//Function prototypes


//Thread function

DWORD WINAPI myThread(void* instance) {
    int chance = 120;
    int Input_delay = 600;
    int Click_delay = 20;
    int value = 0;
    bool run = false;
    
    // Define variables

    MessageBoxA(NULL, 
        "Injected has been success! right alt = on/off mod. Chance: 1/120 in frame.", 
        "Inject info", MB_OK);

    srand(time(0)); // Seed

    while (true) {
        if (GetAsyncKeyState(VK_RMENU) & 0x8000) {
            if (run) {
                run = false;

                printf("Mod: off.");
                Sleep(Input_delay);
                MessageBoxA(NULL, 
                    "Mod: off", 
                    "Mod status", 
                    MB_OK);

                continue;
            }
            else {
                run = true;

                printf("Mod: on.");
                Sleep(Input_delay);
                MessageBoxA(NULL, 
                    "Mod: on", 
                    "Mod status", 
                    MB_OK);
                
                continue;
            } // Mod: on/off
        }
        if (run) {
            srand(time(0));
            value = 1 + rand() % chance;
            if (value == 2) {
                mouse_down();
                Sleep(Click_delay);
                mouse_up();

                //Random click

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

    //Main function (run thread)

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

//Functions for mouse press/release
