#pragma once
class PatchHelper
{
#define FixAddress(addr) (addr - 0x00400000) + (DWORD)GetModuleHandle(NULL)

public:
	static void PatchString(const int address, const char stringBuffer[]);
	static void PatchFunction(const int adr, const int func);
	static void DisableHook(const int adr);
	static void EnableHook(const int adr);
};	