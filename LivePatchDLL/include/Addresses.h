#pragma once

#include "Globals.h"

// Version-Based Address
#define VERSION_ADDR(ver, addr) ver == APP_VERSION ? addr : 
// Defines an address with the given name and value
#define ADDR(name, contents) static const unsigned int name = contents;
// Captures a set of arguments (for ignoring commas)
#define ARGS(...) __VA_ARGS__
// Defines a function using the given return type, name, arguments, and address contents
#define FUNC(type, name, args, contents) typedef type(* name ## _ptr)(args); \
const name ## _ptr name = ( name ## _ptr)(contents);

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