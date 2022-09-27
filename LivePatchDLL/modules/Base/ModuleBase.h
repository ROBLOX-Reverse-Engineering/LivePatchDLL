#pragma once
#include <string>

class ModuleBase
{
private:
	bool moduleEnabled;
	const std::string moduleName;
protected:
	void initBeginEvent();
	void initEndEvent();
public:
	ModuleBase(const char* const moduleName, bool moduleEnabled);

	// Getters and setters
	const char* const getModuleName();

	virtual void startModule();
	void print(const char* const str);
	void printf(const char* const fmt, ...);

};

