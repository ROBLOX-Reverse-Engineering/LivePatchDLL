#pragma once

#include <string>

std::string vformat(const char *fmt, va_list argPtr);

std::string format_string(const char* fmt,...);