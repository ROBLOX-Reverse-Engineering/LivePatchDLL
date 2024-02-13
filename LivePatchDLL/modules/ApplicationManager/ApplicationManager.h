#pragma once
#include "modules/Base/ModuleBase.h"
#include "Addresses.h"
#include "ApplicationManagerBase.h"

class ApplicationManager : public ApplicationManagerBase
{
private:
	void hookFunctions();

	static bool Initialize(void* app, void* hWnd, void* hInstance);
	static void initializeView();
	/// <summary>
	/// Triggers when SHIFT + F8 is pressed
	/// </summary>
	static void UploadSessionLogs();
public:
	void startModule();
};

