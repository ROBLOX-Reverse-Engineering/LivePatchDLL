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
#include <mutex>

volatile int LoadCount = 0;

void watchdog::StartThreadIntegrity() {
    int TotalLoadCount = 0;
    // Run ProtectionModules on new thread.
	
    typedef void (*func)();
    func arr[]{NoDump::RunEngine, NoDump::RunEngine};
    for (auto* x : arr) {
        TotalLoadCount++;
        _InterlockedIncrement((long volatile*)&LoadCount);
        NEWTHREAD(x);
    }

	std::cout << "Loaded " << LoadCount << "/" << TotalLoadCount << " Modules" << std::endl;
}

void watchdog::HandleException() {
    try {
        throw;
    }
    catch (const std::runtime_error& e) {
        _InterlockedDecrement((long volatile*)&LoadCount);
        std::cout << ERRORMSG << "Runtime Exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        _InterlockedDecrement((long volatile*)&LoadCount);
        std::cout << ERRORMSG << "Exception: " << e.what() << std::endl;
    }
    catch (...) {
        _InterlockedDecrement((long volatile*)&LoadCount);
        std::cout << ERRORMSG << "Unknown Exception!" << std::endl;
    }
}