#ifdef WIN32
#include <windows.h>
#endif
#include "format_string.h"

std::string vformat(const char *fmt, va_list argPtr) {
    // We draw the line at a 1MB string.
    const int maxSize = 1000000;

    // If the string is less than 161 characters,
    // allocate it on the stack because this saves
    // the malloc/free time.
    const int bufSize = 161;
	char stackBuffer[bufSize];

    int actualSize = _vscprintf(fmt, argPtr) + 1;

    if (actualSize > bufSize) {

        // Now use the heap.
        char* heapBuffer = NULL;

        if (actualSize < maxSize) {

            heapBuffer = (char*)malloc(maxSize + 1);
			if (!heapBuffer)
				throw std::bad_alloc();
            vsnprintf_s(heapBuffer, maxSize, _TRUNCATE, fmt, argPtr);
            heapBuffer[maxSize] = '\0';
        } else {
            heapBuffer = (char*)malloc(actualSize);
			vsnprintf_s(heapBuffer, actualSize-1, _TRUNCATE, fmt, argPtr);
			heapBuffer[actualSize-1] = '\0';
        }

        std::string formattedString(heapBuffer);
        free(heapBuffer);
        return formattedString;
    } else {
		vsnprintf_s(stackBuffer, bufSize-1, _TRUNCATE, fmt, argPtr);
		stackBuffer[bufSize-1] = '\0';
        return std::string(stackBuffer);
    }
}

std::string format_string(const char* fmt,...) {
    va_list argList;
    va_start(argList,fmt);
    std::string result = vformat(fmt, argList);
    va_end(argList);
	
    return result;
}
