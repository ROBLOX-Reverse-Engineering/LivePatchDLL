#include "NoDump.h"

NoDump::NoDump()
	: ModuleBase(
		"NoDump", // Module Name
		true	  // Enabled
	)
{
}


void NoDump::startModule()
{
	ModuleBase::startModule();

	print("Welcome to the NoDump module!\nThis is just an example module.");

	initEndEvent();
}

// create event when handle creation, loop through child-windows and if it contains process name, code red.