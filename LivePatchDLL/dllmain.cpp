// dllmain.cpp : Defines the entry point for the DLL application.
typedef struct IUnknown IUnknown;
#include <windows.h>
#include <iostream>
#include <string>
#include "watchdog.h"

#define NEWTHREAD(x) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)x, NULL, NULL, NULL)
extern "C" __declspec(dllexport) int StartPatch();
using namespace std;

int StartPatch()
{
#ifdef _DEBUG
	AllocConsole();
	FILE *ostream;
	FILE *istream;
	freopen_s(&ostream, "CONOUT$", "w", stdout);
	freopen_s(&istream, "CONIN$", "r", stdin);
	SetConsoleTitle("Debug Console");
	std::cout << "Hello, world!" << std::endl;
	MessageBox(0, "Press OK to start anti-cheat\nThis will automatically start in non-debug builds.", "Hello", MB_OK);

#endif
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
		StartPatch(); //   <-- Use this if you want to run this on the UI thread (not recommended) (edit: using it on UI thread as it is it going to start dedicated threads)
		//NEWTHREAD(StartPatch);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}