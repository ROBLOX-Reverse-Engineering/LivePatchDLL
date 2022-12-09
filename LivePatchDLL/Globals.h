#pragma once

#define APP_VERSION 132

// Version-Based Address
#define VERSION_ADDR(ver, addr) ver == APP_VERSION ? addr : 
// Defines an address with the given name and value
#define ADDR(name, contents) static const unsigned int name = contents;
// Captures a set of arguments (for ignoring commas)
#define ARGS(...) __VA_ARGS__
// Defines a function using the given return type, name, arguments, and address contents
#define FUNC(type, name, args, contents) typedef type(* name ## _ptr)(args); \
const name ## _ptr name = ( name ## _ptr)(contents);

#if APP_VERSION <= 146
	#define VS2008
#endif