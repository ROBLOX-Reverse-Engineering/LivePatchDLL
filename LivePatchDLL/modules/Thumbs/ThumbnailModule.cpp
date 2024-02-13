#include <fstream>
#include "ThumbnailModule.h"
#include "PatchHelper.h"
#include "WatchDog.h"

void ThumbnailModule::startModule()
{
	ModuleBase::startModule();

	// Do startup stuff
	HOOK_FUNCT(ViewBaseFactory::CreateView, CreateView);
	//thumbRenderWorker();

	initEndEvent();
}

void ThumbnailModule::thumbRenderWorker()
{
	unsigned char data[1000000];

	renderThumb(data, 420, 420, false, false);
	std::ofstream myfile;
	myfile.open("test.png");
	myfile << data;
	myfile.close();
}

void* ThumbnailModule::CreateView(CRenderSettings::GraphicsMode mode,
	OSContext* context,
	void* renderSettings)
{
	// Yoink the view pointer
	viewSingleton = ViewBaseFactory::CreateView(mode, context, renderSettings);
	WatchDog::singleton()->printf("ViewBase: \"%x\"", viewSingleton);
	return viewSingleton;
}

void ThumbnailModule::renderThumb(unsigned char* data, int width, int height, bool crop, bool allowDolly)
{
	ThumbnailModuleBase::renderThumb(getViewSingleton(), getViewSingleton(), data, width, height);
}