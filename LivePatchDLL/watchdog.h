#pragma once
class watchdog
{
#define NEWTHREAD(x) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)x, NULL, NULL, NULL)
#if EnabledModule
#define START_MODULE try { \
	std::cout << "[" << ModuleName << "] Module has loaded!" << std::endl;
#define END_MODULE } \
	catch (...) { \
		watchdog::HandleException(ModuleName, __FUNCTION__); \
}
#else
#define START_MODULE if (0) {
#define END_MODULE }
#endif
	
public:
	static void StartThreadIntegrity();
	static void HandleException(const char* Module, const char* Function);
};

