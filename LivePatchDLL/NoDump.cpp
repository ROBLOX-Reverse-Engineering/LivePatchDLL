#include <iostream>
#include "NoDump.h"
#include "watchdog.h"

void NoDump::RunEngine() {
	const char* ModuleName = "NoDump";

	try {
		std::cout << "[" << ModuleName << "] Module has loaded!" << std::endl;
	}
	catch (...) {
		watchdog::HandleException(ModuleName, __FUNCTION__);
	}
}

// create event when handle creation, loop through child-windows and if it contains process name, code red.