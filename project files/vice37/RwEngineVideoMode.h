#pragma once

#include <src/rwcore.h>
#include <Windows.h>
#include "CPatch.h"

struct MyRwVideoMode
{
	RwInt32 width;
	RwInt32 height;
	RwInt32 depth;
	RwVideoModeFlag flags;
};

MyRwVideoMode *MyRwEngineGetVideoModeInfo(MyRwVideoMode *modeinfo, RwInt32 modeIndex)
{
	RwVideoMode mode;
	RwEngineGetVideoModeInfo(&mode, modeIndex);
	memcpy(modeinfo, &mode, 16);
	return modeinfo;
}

RwBool MyRwEngineSetVideoMode(RwInt32 modeIndex) {
    RwEngineSetVideoMode(modeIndex);
    RwD3D9EngineSetMultiSamplingLevels(RwD3D9EngineGetMaxMultiSamplingLevels());
    return true;
}

void MakeRwEngineVideoModeHook()
{
	CPatch::RedirectJump(0x642B70, MyRwEngineGetVideoModeInfo);
    CPatch::RedirectJump(0x642BD0, MyRwEngineSetVideoMode);
}