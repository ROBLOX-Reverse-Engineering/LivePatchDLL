#pragma once
class PatchHelper
{
#define FixAddress(addr) (addr - 0x00400000) + (DWORD)GetModuleHandle(NULL)

public:
	static void patchString(const int address, const char stringBuffer[]);
	static void patchFunction(const int adr, const int func);
};	