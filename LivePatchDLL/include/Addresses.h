#pragma once

#include "Globals.h"

#define IMAGE_BASE 0x400000

// Version-Based Address
#define VERSION_ADDR(ver, addr) ver == APP_VERSION ? addr : 
// Defines an address with the given name and value
#define ADDR(name, contents) static const unsigned int name = contents;
// Captures a set of arguments (for ignoring commas)
#define ARGS(...) __VA_ARGS__
// Defines a function using the given return type, name, arguments, and address contents
//// Defines a function, but allows for trampolining. Sets the base class's function once hooked.
#define FUNC(type, name, args, contents) private: typedef type(* name ## _ptr)(args); \
public: static inline name ## _ptr name = ( name ## _ptr)(contents);
// Converts an address in memory to a Relative Virtual Address
#define RVA(addr) (addr - IMAGE_BASE) + (DWORD)GetModuleHandle(NULL)

class SavedAddr
{
public:
	/*
		Define addresses for strings and functions here:
		Example:
			static const unsigned int isTrustedContent = 0x000000;
	*/

	// Content Patches (RVAs)

	// Hooks (Addresses)
};