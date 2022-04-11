#pragma once
class watchdog
{
#define NEWTHREAD(x) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)x, NULL, NULL, NULL)

public:
	static void StartThreadIntegrity();
};

