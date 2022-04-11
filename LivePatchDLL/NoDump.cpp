#include <iostream>
#include "NoDump.h"
#include "watchdog.h"

void NoDump::RunEngine() {
	try {
		std::cout << "NoDump Module loaded!" << std::endl;
	}
	catch (...) {
		watchdog::HandleException();
	}
}

// create event when handle creation, loop through child-windows and if it contains process name, code red.