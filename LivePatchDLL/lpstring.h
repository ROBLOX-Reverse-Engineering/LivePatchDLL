#pragma once
#include <string>
#include "old_string.h"
#include "Globals.h"

#define LPSTRING(name) std::string(((string*)&name)->c_str())

class string :
#ifdef VS2008
	public old::string
#else
	public std::string
#endif
{
#ifdef VS2008
	using old::string::string;
#else
	using std::string::basic_string;
#endif
};