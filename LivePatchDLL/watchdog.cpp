typedef struct IUnknown IUnknown;
#include <future>
#include <thread>
#include <iostream>
#include <windows.h>
#include "WatchDog.h"
#include "format_string.h"
// Start Protections
#include "modules/NoDump/NoDump.h"
#include "modules/ClientManager/ClientManager.h"
// End Protections


WatchDog* const WatchDog::singleton()
{
    static WatchDog* watchDog(new WatchDog());
    return watchDog;
}


void WatchDog::freeSingleton()
{
    delete WatchDog::singleton();
}


WatchDog::WatchDog()
{
    moduleThreads = std::vector<std::thread*>();
    modules = std::vector<ModuleBase*>();
    modules.push_back(new NoDump());
    //modules.push_back(new ClientManager());
}


WatchDog::~WatchDog()
{
    // Terminate all existing threads for the modules
    for (int i = moduleThreads.size() - 1; i >= 0; i--)
    {
        if (moduleThreads.at(i) != nullptr)
            delete moduleThreads.at(i);
    }
    // Deallocate modules
    for (int i = modules.size() - 1; i >= 0; i--)
    {
        if (modules.at(i) != nullptr)
            delete modules.at(i);
    }
}


void WatchDog::startThreadIntegrity()
{
    // Run ProtectionModules on new thread.
    const int totalModulesCount = modules.size();
    auto asyncTasks = std::vector<std::future<void>>();

    printf("Initializing %d modules...", totalModulesCount);
    for (int i = 0; i < totalModulesCount; i++)
    {
        ModuleBase* const module = modules[i];
        startModule(this, module);
        /*asyncTasks.push_back(std::async(
            [this, i, totalModulesCount](ModuleBase* const module)
            {
                printf("Initializing %d/%d modules", i + 1, totalModulesCount);
                startModule(this, module);
                printf("Initialized %d/%d modules", i + 1, totalModulesCount);
            },
            module
        ));*/
        //std::thread* const moduleThread = new std::thread(startModule, this, module);
        //moduleThreads.push_back(moduleThread);
    }
    asyncTasks.~vector();
    printf("Finished initializing %d modules!", totalModulesCount);
}


void WatchDog::handleException(const char* moduleName, const char* methodName)
{
    try {
        throw;
    }
    catch (const std::runtime_error& e) {
        printf("[%s] %s() Runtime Exception: %s", moduleName, methodName, e.what());
    }
    catch (const std::exception& e) {
        printf("[%s] %s() Exception: %s", moduleName, methodName, e.what());
    }
    catch (...) {
        printf("[%s] %s() Unknown Exception!", moduleName, methodName);
    }
}


/// <summary>
/// Prints in a (hopefully) thread-safe way
/// </summary>
/// <param name="str">The string to print</param>
void WatchDog::print(const char* const str)
{
    std::lock_guard<std::mutex> guard(consoleMutex);
    std::cout << str << std::endl;
}


void WatchDog::print(std::string str)
{
    print(str.c_str());
}


void WatchDog::vprintf(const char* const fmt, va_list argPtr)
{
    print(vformat(fmt, argPtr));
}


void WatchDog::printf(const char* const fmt, ...)
{
    va_list argList;
    va_start(argList, fmt);

    vprintf(fmt, argList);

    va_end(argList);
}


void WatchDog::startModule(WatchDog* const watchdog, ModuleBase* const module)
{
    try
    {
        module->startModule();
    }
    catch (...)
    {
        watchdog->handleException(module->getModuleName(), __FUNCTION__);
    }
}