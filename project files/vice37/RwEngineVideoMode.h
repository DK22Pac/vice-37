#pragma once
#include <src/rwcore.h>
#include <Windows.h>
#include "CPatch.h"

struct MyRwVideoMode {
    RwInt32 width;
    RwInt32 height;
    RwInt32 depth;
    RwVideoModeFlag flags;
};

MyRwVideoMode *MyRwEngineGetVideoModeInfo(MyRwVideoMode *modeinfo, RwInt32 modeIndex) {
    RwVideoMode mode;
    RwEngineGetVideoModeInfo(&mode, modeIndex);
    memcpy(modeinfo, &mode, 16);
    return modeinfo;
}

void MakeRwEngineVideoModeHook() {
    CPatch::RedirectJump(0x642B70, MyRwEngineGetVideoModeInfo);
}
