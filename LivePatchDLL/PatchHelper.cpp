typedef struct IUnknown IUnknown;
#include <iostream>
#include <windows.h>
#include "PatchHelper.h"
#include "minhook\include\MinHook.h"

[[deprecated("PatchString is deprecated, use PatchBytes instead. This function will be removed in future builds")]] 
__inline void PatchHelper::PatchString(const int address, const char stringBuffer[])
{
	PatchBytes(address, stringBuffer);
}

void PatchHelper::PatchBytes(const int address, const char bytesBuffer[])
{
	char* buffer = reinterpret_cast<char*>(FixAddress(address));
#ifdef _DEBUG
	std::cout << "[" << __FUNCTION__ << "] Address: " << std::hex << address << std::endl;
	std::cout << "[" << __FUNCTION__ << "] Buffer: " << std::hex << buffer << std::endl;
#endif
	const size_t length = strlen(buffer) + 1;
	DWORD oldProtect;

	VirtualProtect(buffer, length, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(buffer, bytesBuffer, length);
	VirtualProtect(buffer, length, oldProtect, nullptr);

#ifdef _DEBUG 
	std::cout << "[" << __FUNCTION__ << "] New Buffer: " << std::hex << (int)reinterpret_cast<char*>(FixAddress(address)) << std::endl;
#endif
}

void PatchHelper::PatchByte(const int address, const char byte)
{
	char* buffer = reinterpret_cast<char*>(FixAddress(address));
#ifdef _DEBUG
	std::cout << "[" << __FUNCTION__ << "] Address: " << std::hex << address << std::endl;
	std::cout << "[" << __FUNCTION__ << "] Buffer: " << std::hex << buffer << std::endl;
#endif
	const size_t length = sizeof(byte);
	DWORD oldProtect;

	VirtualProtect(buffer, length, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(BYTE*)(buffer) = byte;
	VirtualProtect(buffer, length, oldProtect, nullptr);

#ifdef _DEBUG 
	std::cout << "[" << __FUNCTION__ << "] New Buffer: " << std::hex << (int)reinterpret_cast<char*>(FixAddress(address)) << std::endl;
#endif
}

void PatchHelper::InitializeHooks() {
	MH_Initialize();
}

void PatchHelper::HookFunction(const int adr, const int func)
{
	MH_CreateHook((LPVOID)(FixAddress(adr)), (LPVOID)func, NULL);
	MH_EnableHook((LPVOID)(FixAddress(adr)));
}

void PatchHelper::DisableHook(const int adr)
{
	MH_DisableHook((LPVOID)adr);
}

void PatchHelper::EnableHook(const int adr)
{
	MH_EnableHook((LPVOID)adr);
}
