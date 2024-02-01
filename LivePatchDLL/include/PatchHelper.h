#pragma once
#include <mutex>

class PatchHelper
{
#define PATCH_BYTES(addr, buffer) PatchHelper::PatchBytes(addr, buffer)
#define HOOK_FUNC(addr, func) PatchHelper::HookFunction((unsigned int)addr, (unsigned int)&func)
#define HOOK_FUNCT(baseFunc, func) PatchHelper::HookFunction((unsigned int)baseFunc, (unsigned int)&func, (unsigned int)&baseFunc)
public:
	// Requires that every thread waits their turn in order to write to the heap
	static std::mutex heapMutex;

	static void PatchBytes(const unsigned int address, const char *bytesBuffer);
	static void InitializeHooks();
	static void HookFunction(const unsigned int adr, const unsigned int func, const unsigned int& orig = NULL);
	static void DisableHook(const unsigned int adr);
	static void EnableHook(const unsigned int adr);
};