#include <windows.h>
#include "PatchHelper.h"
#include "minhook\include\MinHook.h"
#include "WatchDog.h"

std::mutex PatchHelper::heapMutex;


void PatchHelper::PatchBytes(const unsigned int address, const char bytesBuffer[])
{
	char* const buffer = (char* const)FixAddress(address);
#ifdef _DEBUG
	WatchDog::singleton()->printf("[%s] Address: %x", __FUNCTION__, (unsigned int)address);
	WatchDog::singleton()->printf("[%s] Buffer: \"%s\"", __FUNCTION__, buffer);
#endif
	const size_t length = strlen(buffer) + 1;
	DWORD oldProtect;

	std::lock_guard<std::mutex> guard(PatchHelper::heapMutex);

	// TODO: This might have to be called if we want to destruct std::strings given to us on our end
	VirtualProtect(buffer, length, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(buffer, bytesBuffer, length);
	VirtualProtect(buffer, length, oldProtect, nullptr);

#ifdef _DEBUG 
	WatchDog::singleton()->printf("[%s] New Buffer: \"%s\"", __FUNCTION__, buffer);
#endif
}


void PatchHelper::InitializeHooks() {
	MH_Initialize();
}


void PatchHelper::HookFunction(const unsigned int adr, const unsigned int func, const unsigned int& orig)
{
	std::lock_guard<std::mutex> guard(PatchHelper::heapMutex);

	MH_CreateHook((LPVOID)(FixHook(adr)), (LPVOID)func, (LPVOID*)orig);
	MH_EnableHook((LPVOID)(FixHook(adr)));
}


void PatchHelper::DisableHook(const unsigned int adr)
{
	MH_DisableHook((LPVOID)adr);
}


void PatchHelper::EnableHook(const unsigned int adr)
{
	MH_EnableHook((LPVOID)adr);
}
