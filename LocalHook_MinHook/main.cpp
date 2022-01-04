#include <Windows.h>
#include <iostream>
#include "MinHook.h"

#pragma comment(lib, "libMinHook.x86.lib")



typedef int (WINAPI* OldMessageBox)(HWND, LPCSTR, LPCSTR, UINT);

OldMessageBox fpMessageBoxA = NULL;

int WINAPI MyMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
    int ret = fpMessageBoxA(hWnd, "Hook Inject", lpCaption, uType);
    return ret;
}

void SetHook()
{
    if (MH_Initialize() == MB_OK)
    {
        MH_CreateHook(&MessageBoxA, &MyMessageBoxA, reinterpret_cast<void**>(&fpMessageBoxA));
        MH_EnableHook(&MessageBoxA);
    }
    else {
        std::cout << "Can not install hppk" << std::endl;
    }
}

void UnHook()
{
    if (MH_DisableHook(&MessageBoxA) == MB_OK)
    {
        MH_Uninitialize();
    }
}


int main()
{
    int key = 0;
    std::cout << "input key to starthook" << std::endl;
    std::cin >> key;
    //Install Hook function
    SetHook();
    //Call the normal MessageBoxA function
    MessageBoxA(NULL, "Orgin MessageBox", "tip", NULL);
    std::cout << "input key to UnHook" << std::endl;
    std::cin >> key;
    //Unload Hook function
    UnHook();
    MessageBoxA(NULL, "After Hook MessageBox", "tip", NULL);
    getchar();
    return 0;
}