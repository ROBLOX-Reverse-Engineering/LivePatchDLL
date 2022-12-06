#pragma once
#include <mutex>

#define IMAGE_BASE 0x00400000

class PatchHelper
{
#define FixAddress(addr) (addr - IMAGE_BASE) + (DWORD)GetModuleHandle(NULL)
#define FixHook(addr) addr + (DWORD)GetModuleHandle(NULL)

public:
	// Requires that every thread waits their turn in order to write to the heap
	static std::mutex heapMutex;

	static void PatchBytes(const unsigned int address, const char bytesBuffer[]);
	static void InitializeHooks();
	static void HookFunction(const unsigned int adr, const unsigned int func, const unsigned int& orig = NULL);
	static void DisableHook(const unsigned int adr);
	static void EnableHook(const unsigned int adr);
};