#pragma once
#include "ThumbnailModuleBase.h"
#include "Addresses.h"
#include "lpstring.h"

#include "ViewBaseFactory.h"

/// <summary>
/// A general client-management module.
/// </summary>
class ThumbnailModule : public ThumbnailModuleBase
{
private:
	static inline void* viewSingleton = nullptr;

public:
	static void* getViewSingleton() { return viewSingleton; }
	static void thumbRenderWorker();
	static void* CreateView(CRenderSettings::GraphicsMode mode,
		OSContext* context,
		void* renderSettings);
	static void renderThumb(unsigned char* data, int width, int height, bool crop, bool allowDolly);
public:
	void startModule();

public:
	
};

