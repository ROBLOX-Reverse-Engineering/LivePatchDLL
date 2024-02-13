#pragma once
#include "Addresses.h"

class CRenderSettings
{
public:
	typedef enum
	{
		UnknownGraphicsMode = 0,
		AutoGraphicsMode = 1,
		Direct3D11 = 2, // Doesn't exist in 2013, causes a close
		Direct3D9 = 3,
		OpenGL,
		NoGraphics
	} GraphicsMode;

	// Needs to not be an RVA if we wanna call it
	FUNC(void*, singleton, ARGS(),
		VERSION_ADDR(132, 0x4078B0)
		0x0
	)
};