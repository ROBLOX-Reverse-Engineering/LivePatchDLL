#include "watchdog.h"
#include <future>
#include <thread>
#include <chrono>
#include <iostream>

void watchdog::StartThreadIntegrity() {
    using namespace std::chrono_literals;

    // Create a packaged_task using some task and get its future.
    std::packaged_task<void()> task([] {
        // Start protections (preferably as seperate threads)
        });
    auto future = task.get_future();

    // Run task on new thread.
    std::thread t(std::move(task));

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