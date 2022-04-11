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

#define ERRORMSG "Error: " << __FUNCTION__ << "() "

void watchdog::StartThreadIntegrity() {
    // Run task on new thread.
#ifdef _DEBUG
    try {
#endif
        NEWTHREAD(NoDump::RunEngine);
		
#ifdef _DEBUG
    }
    catch (const std::runtime_error& e) {
        std::cout << ERRORMSG << "Runtime Exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e){
		std::cout << ERRORMSG << "Exception: " << e.what() << std::endl;
	}
    catch (...) {
		std::cout << ERRORMSG << "Unknown Exception!" << std::endl;
    }
#endif


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