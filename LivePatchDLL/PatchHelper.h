#pragma once
class PatchHelper
{
#define FixAddress(addr) (addr - 0x00400000) + (DWORD)GetModuleHandle(NULL)

public:
	static void PatchString(const int address, const char stringBuffer[]);
	static void PatchBytes(const int address, const char bytesBuffer[]);
	static void PatchByte(const int address, const char byte);
	static void InitializeHooks();
	static void HookFunction(const int adr, const int func);
	static void DisableHook(const int adr);
	static void EnableHook(const int adr);
};