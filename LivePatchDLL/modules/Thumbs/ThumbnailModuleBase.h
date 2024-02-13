#pragma once
#include "modules/Base/ModuleBase.h"
#include "Addresses.h"

/// <summary>
/// The base class for the Thumbnail module.
/// Includes original hooked functions needed for the module.
/// </summary>
class ThumbnailModuleBase : public ModuleBase
{
public:
	ThumbnailModuleBase()
		: ModuleBase(
			"ThumbnailModule", // Module Name
			true			   // Enabled
		)
	{}

	FUNC(void, renderThumb, ARGS(void* view, void* view2, unsigned char* data, int width, int height),
		VERSION_ADDR(132, 0x48D7F0)
		0x0
	)
};