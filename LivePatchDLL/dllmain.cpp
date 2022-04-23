// dllmain.cpp : Defines the entry point for the DLL application.
typedef struct IUnknown IUnknown;
#include <windows.h>
#include <iostream>
#include <string>
#include "watchdog.h"
#include "PatchHelper.h"
#include "Addresses.h"

extern "C" __declspec(dllexport) int StartPatch();

FILE* ostream;
FILE* istream;

// thread starts work after unpacking seemingly every time. lucky? windows dll loader quirk?
int StartPatch()
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s(&ostream, "CONOUT$", "w", stdout);
	freopen_s(&istream, "CONIN$", "r", stdin);
	SetConsoleTitle("Debug Console");
	std::cout << "Hello, world!" << std::endl;
	MessageBox(0, "Press OK to start patch & anti-cheat\nThis will automatically start in non-debug builds.", "Hello", MB_OK);

#endif
    PatchHelper::InitializeHooks();
    /*
        Insert PatchHelper calls here
    */
    watchdog::StartThreadIntegrity();
    
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
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(StartPatch), nullptr, 0, nullptr);

        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        // close I/O handles to avoid issues
        CloseHandle(istream);
        CloseHandle(ostream);

        break;
    }
    return TRUE;
}