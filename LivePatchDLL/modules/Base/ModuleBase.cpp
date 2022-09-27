#include <windows.h>
#include "ModuleBase.h"
#include "WatchDog.h"
#include "format_string.h"

void ModuleBase::initBeginEvent()
{
	printf("Loading module...", moduleName.c_str());
}


void ModuleBase::initEndEvent()
{
	printf("Module has loaded!", moduleName.c_str());
}


ModuleBase::ModuleBase(
	const char* const moduleName,
	bool moduleEnabled)
	:moduleName(moduleName)
	, moduleEnabled(moduleEnabled)
{
}


// Getters and setters
const char* const ModuleBase::getModuleName()
{
	return moduleName.c_str();
}


void ModuleBase::startModule()
{
	initBeginEvent();
}


void ModuleBase::print(const char* const str)
{
	// TODO: Improve
	std::string prefix(format_string(
		"[%s] ", getModuleName()
	));


	WatchDog::singleton()->print(prefix.append(str).c_str());
}


void ModuleBase::printf(const char* const fmt, ...)
{
	va_list argList;
	va_start(argList, fmt);

	// TODO: Improve
	std::string prefix(format_string(
		"[%s] ", getModuleName()
	));


	WatchDog::singleton()->vprintf(prefix.append(fmt).c_str(), argList);

	va_end(argList);
}
