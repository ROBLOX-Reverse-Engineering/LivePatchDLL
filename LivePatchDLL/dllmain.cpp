// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <iostream>
#include <string>
#include "watchdog.h"
#include "PatchHelper.h"

extern "C" __declspec(dllexport) int StartPatch(WatchDog* const watchdog);

int StartPatch(WatchDog* const watchdog)
{
#ifdef _DEBUG
	AllocConsole();
	FILE *ostream;
	FILE *istream;
	freopen_s(&ostream, "CONOUT$", "w", stdout);
	freopen_s(&istream, "CONIN$", "r", stdin);
	SetConsoleTitle("Debug Console");
	WatchDog::singleton()->print("Hello, world!");
	MessageBox(0, "Press OK to start patch & anti-cheat\nThis will automatically start in non-debug builds.", "Hello", MB_OK);

#endif
    PatchHelper::InitializeHooks();

    watchdog->startThreadIntegrity();
    
	return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule); // disables DLL_THREAD* calls which should boost performance
		StartPatch(WatchDog::singleton());
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        WatchDog::freeSingleton();
        break;
    }
    return TRUE;
}