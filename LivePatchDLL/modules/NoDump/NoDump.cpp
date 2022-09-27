#include <iostream>
#include "NoDump.h"

NoDump::NoDump()
	: ModuleBase(
		"NoDump", // Module Name
		true	  // Enabled
	)
{
}

void NoDump::StartModule()
{
	ModuleBase::startModule();



	initEndEvent();
}

// create event when handle creation, loop through child-windows and if it contains process name, code red.