#pragma once
#include "modules/Base/ModuleBase.h"
#include "Addresses.h"

/// <summary>
/// The base class for the ApplicationManager module.
/// Includes original hooked functions needed for the module.
/// </summary>
class ApplicationManagerBase : public ModuleBase
{
public:
	ApplicationManagerBase()
		: ModuleBase(
			"ApplicationManager", // Module Name
			true				  // Enabled
		)
	{}

	FUNC(bool, Initialize, ARGS(void* app, void* hWnd, void* hInstance),
		VERSION_ADDR(132, 0x4045D0)
		0x0
	)

	FUNC(void, initializeView, ARGS(),
		VERSION_ADDR(132, 0x468810)
		0x0
	)

	FUNC(void, UploadSessionLogs, ARGS(),
		VERSION_ADDR(132, 0x404340)
		0x0
	)
};