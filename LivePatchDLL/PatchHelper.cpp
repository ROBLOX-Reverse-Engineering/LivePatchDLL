typedef struct IUnknown IUnknown;
#include <iostream>
#include <windows.h>
#include "PatchHelper.h"
#include "minhook\include\MinHook.h"

void PatchHelper::patchString(const int address, const char stringBuffer[])
{
	char* buffer = reinterpret_cast<char*>(FixAddress(address));
#if _DEBUG
	std::cout << "Address: " << std::hex << address << std::endl;
	std::cout << "Buffer: " << std::hex << buffer << std::endl;
#endif
	const size_t length = strlen(buffer) + 1;
	DWORD oldProtect;

	VirtualProtect(buffer, length, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(buffer, stringBuffer, length);
	VirtualProtect(buffer, length, oldProtect, nullptr);

#if _DEBUG
	std::cout << "New Buffer: " << std::hex << (int)reinterpret_cast<char*>(FixAddress(address)) << std::endl;
#endif
}

void PatchHelper::patchFunction(const int adr, const int func)
{
	MH_CreateHook((LPVOID)(FixAddress(adr)), (LPVOID)func, NULL);
	MH_EnableHook((LPVOID)adr);
}