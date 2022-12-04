#pragma once
#include "modules/Base/ModuleBase.h"

/// <summary>
/// An example ProtectionModule.
/// </summary>
class NoDump : public ModuleBase
{
public:
	NoDump();
	void startModule();
};

