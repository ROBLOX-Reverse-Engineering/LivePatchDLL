#include "watchdog.h"
// Start Protections
#include "NoDump.h"
// End Protections
#include <future>
#include <thread>
#include <chrono>
#include <iostream>

void watchdog::StartThreadIntegrity() {
    // Run task on new thread.
    std::thread t(NoDump::RunEngine);

    // Get thread status using wait_for as before.
    //auto status = future.wait_for(0ms);

    // Print status.
    //if (status == std::future_status::ready) {
        //std::cout << "this is a test";
    //}

    //system("pause");
    //t.join(); // Join thread.
    //system("pause");
}