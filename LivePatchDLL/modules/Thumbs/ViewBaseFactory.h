#pragma once
#include "Addresses.h"
#include "RenderSettings.h"

struct OSContext
{
	void* hWnd;
	int width;
	int height;
    
	//insert OS specific stuff here.
	OSContext()
		: hWnd(0)
		, width(640)
		, height(480)
	{
	}

};

class ViewBaseFactory
{
public:
	FUNC(void*, CreateView, ARGS(CRenderSettings::GraphicsMode mode,
								OSContext* context,
								void* renderSettings
		),
		VERSION_ADDR(132, 0xA0CE50)
		0x0
	)
};