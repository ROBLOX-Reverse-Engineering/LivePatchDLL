#include "ApplicationManager.h"
#include "PatchHelper.h"
#include "WatchDog.h"
#include "modules/Thumbs/ThumbnailModule.h"

void ApplicationManager::startModule()
{
	ModuleBase::startModule();

	// Do startup stuff
	hookFunctions();

	initEndEvent();
}

void ApplicationManager::hookFunctions()
{
	//HOOK_FUNCT(ApplicationManagerBase::Initialize, Initialize);
	//HOOK_FUNCT(ApplicationManagerBase::initializeView, initializeView);
	HOOK_FUNCT(ApplicationManagerBase::UploadSessionLogs, UploadSessionLogs);
}

bool ApplicationManager::Initialize(void* app, void* hWnd, void* hInstance)
{
	return ApplicationManagerBase::Initialize(app, hWnd, hInstance);
	//return true;
}

void ApplicationManager::initializeView()
{
	return ApplicationManagerBase::initializeView();
}

void ApplicationManager::UploadSessionLogs()
{
	//ApplicationManagerBase::UploadSessionLogs();
	ThumbnailModule::thumbRenderWorker();
	WatchDog::singleton()->printf("SHIFT + F8 pressed!");
}