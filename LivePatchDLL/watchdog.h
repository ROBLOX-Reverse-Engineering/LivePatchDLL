#pragma once
class watchdog
{
	
public:
	static void StartThreadIntegrity();
	static void HandleException(const char* Module, const char* Function);
};

