#pragma once
#include <windows.h>

class DummyWindow
{
public:
	HWND handle;
	DummyWindow(int width, int height);
	~DummyWindow(void);
};
