#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include "modules/Base/ModuleBase.h"


/// <summary>
/// Manages the DLL.
/// Currently the hub for all utility functions shared by the modules.
/// </summary>
class WatchDog
{	
private:
	std::vector<std::thread*> moduleThreads;
	std::vector<ModuleBase*> modules;
	std::mutex consoleMutex;
public:
	static WatchDog* const singleton();
	static void freeSingleton();

	WatchDog();
	~WatchDog();
	void startThreadIntegrity();
	void handleException(const char* moduleName, const char* methodName);

	void print(const char* const str);
	void print(std::string str);
	void vprintf(const char* const fmt, va_list argPtr);
	void printf(const char* const fmt, ...);

	static void startModule(WatchDog* const watchdog, ModuleBase* const module);
};