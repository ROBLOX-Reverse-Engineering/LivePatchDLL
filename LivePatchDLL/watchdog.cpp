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

void watchdog::StartThreadIntegrity() {
    // Run ProtectionModules on new thread.
	
    typedef void (*func)();
    func arr[]{NoDump::RunEngine, NoDump::RunEngine};
    for (auto* x : arr) {
        NEWTHREAD(x);
    }
}

void watchdog::HandleException() {
    try {
        throw;
    }
    catch (const std::runtime_error& e) {
        std::cout << ERRORMSG << "Runtime Exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << ERRORMSG << "Exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << ERRORMSG << "Unknown Exception!" << std::endl;
    }
}