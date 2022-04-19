typedef struct IUnknown IUnknown;
#include "watchdog.h"
// Start Protections
#include "NoDump.h"
// End Protections
#include <future>
#include <thread>
#include <chrono>
#include <iostream>
#include <Windows.h>
#include "atomic.h"

static atomic<int> LoadCount = 0;

void watchdog::StartThreadIntegrity() {
    // Run ProtectionModules on new thread.
	
    typedef void (*func)();
    func arr[]{NoDump::RunEngine, NoDump::RunEngine};

    int const TotalLoadCount = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Starting to load " << TotalLoadCount << " modules..." << std::endl;
    for (auto* x : arr) {
        NEWTHREAD(x);
    }

	std::cout << "Loaded " << TotalLoadCount - LoadCount << "/" << TotalLoadCount << " Modules" << std::endl;
}

void watchdog::HandleException(const char* Module, const char* Function) {
    LoadCount++;
    try {
        throw;
    }
    catch (const std::runtime_error& e) {
        std::cout << "[" << Module << "] " << Function << "() Runtime Exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "[" << Module << "] " << Function << "() Exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "[" << Module << "] " << Function << "() Unknown Exception!" << std::endl;
    }
}