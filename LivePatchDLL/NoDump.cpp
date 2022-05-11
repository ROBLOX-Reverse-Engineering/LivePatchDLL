#define EnabledModule true
#include <iostream>
#include "NoDump.h"
#include "watchdog.h"

void NoDump::RunEngine() {
	const char* ModuleName = "NoDump";
	START_MODULE;
	
	END_MODULE;
}

// create event when handle creation, loop through child-windows and if it contains process name, code red.