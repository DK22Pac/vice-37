#pragma once
#include "RwFunctionsList.h"
#include "CPatch.h"
#include "Debug.h"
#include <d3d9.h>
#include "FilePath.h"

bool gWindowedMode = false;

namespace os_types {
struct _PsGlobalType {
    HWND window;
    HINSTANCE instance;
    int fullscreen;
    DWORD lastMousePos_X;
    DWORD lastMousePos_Y;
    DWORD field_14;
    void *diInterface;
    void *diMouse;
    DWORD diDevice1;
    DWORD diDevice2;
};

struct _RsGlobalType {
    RwChar *appName;
    RwInt32 maximumWidth;
    RwInt32 maximumHeight;
    RwInt32 screenWidth;
    RwInt32 screenHeight;
    RwInt32 maxFPS;
    RwInt32 quit;
    _PsGlobalType *ps;
    //RsInputDevice keyboard;
    //RsInputDevice mouse;
    //RsInputDevice pad;
};
}

RwUInt32 &gEngineInitFailed = *(RwUInt32 *)0x783EF4;
RwInt32 &gAdapter = *(RwInt32 *)0x783EE8;
RwInt32 &gSelectedMode = *(RwInt32 *)0x783EEC;
RwInt32 &gVideoMemorySize = *(RwInt32 *)0x7F3C78;
os_types::_RsGlobalType &gRsGlobal = *(os_types::_RsGlobalType *)0x9B48D8;
RwInt32 &gMenuManager_f30 = *(RwInt32 *)(0x869630 + 0x30);
RwInt32 & gMenuManager_f5C = *(RwInt32 *)(0x869630 + 0x5C);
RwInt32 & gMenuManager_f60 = *(RwInt32 *)(0x869630 + 0x60);
RwUInt32 & g_6D59F8 = *(RwUInt32 *)0x6D59F8;
RwCamera *&gRwCamera = *(RwCamera **)0x8100BC;
char **&videoModeList = *(char ***)0x7839E0;

RwInt32 GetMaxRefreshRate(RwInt32 width, RwInt32 height, RwInt32 depth) {
    IDirect3D9 *d3d = Direct3DCreate9(31);
    RwInt32 maxRate = 0x7FFFFFFF;
    D3DFORMAT format = D3DFMT_R5G6B5;
    if (depth == 32)
        format = D3DFMT_A8B8G8R8;
    else if (depth == 24)
        format = D3DFMT_R8G8B8;
    UINT modeCount = d3d->GetAdapterModeCount(gAdapter, format);
    for (UINT i = 0; i < modeCount; i++) {
        D3DDISPLAYMODE mode;
        d3d->EnumAdapterModes(gAdapter, format, i, &mode);
        if (mode.Width == width && mode.Height == height) {
            if (!mode.RefreshRate) {
                d3d->Release();
                return 0;
            }
            if (mode.RefreshRate < maxRate && mode.RefreshRate >= 60)
                maxRate = mode.RefreshRate;
        }
    }
    d3d->Release();
    if (maxRate == 0x7FFFFFFF)
        return -1;
    return maxRate;
}

char **GetVideoModeList() {
    if (videoModeList)
        return videoModeList;
    RwInt32 numVideoModes = RwEngineGetNumVideoModes();
    videoModeList = ((char **(__cdecl *)(int, int))0x665B60)(numVideoModes, 4); // calloc
    for (RwInt32 i = 0; i < numVideoModes; i++) {
        RwVideoMode mode;
        RwEngineGetVideoModeInfo(&mode, i);
        if ((mode.width != 640 || mode.height != 480) && (gVideoMemorySize - mode.width * mode.height * mode.depth / 8) <= 0xC00000)
            videoModeList[i] = nullptr;
        else
        {
            videoModeList[i] = ((char *(__cdecl *)(int, int))0x665B60)(100, 1); // calloc
            if (mode.flags & rwVIDEOMODEEXCLUSIVE)
                sprintf(videoModeList[i], "%lu X %lu X %lu", mode.width, mode.height, mode.depth);
            else
                strcpy(videoModeList[i], "WINDOWED");
        }
    }
    return videoModeList;
}

RwBool RsSelectDevice() {
    if (!gEngineInitFailed) {
        RwUInt32 numSubsystems = RwEngineGetNumSubSystems();
        if (!numSubsystems)
            return FALSE;
        if (numSubsystems > 16)
            numSubsystems = 16;
        RwSubSystemInfo *info = (RwSubSystemInfo *)0x7839E4;
        for (RwInt32 i = 0; i < numSubsystems; i++)
            RwEngineGetSubSystemInfo(info++, i);
        gAdapter = RwEngineGetCurrentSubSystem();
    }
    if (!RwEngineSetSubSystem(gAdapter))
        return FALSE;
    RwVideoMode mode;
    if (!gEngineInitFailed) {
        if (gWindowedMode) {
            RwInt32 numModes = RwEngineGetNumVideoModes();
            for (RwInt32 i = 0; i < numModes; i++) {
                RwEngineGetVideoModeInfo(&mode, i);
                if ((mode.flags & rwVIDEOMODEEXCLUSIVE) == 0) {
                    gSelectedMode = i;
                    gMenuManager_f5C = i;
                    gMenuManager_f60 = i;
                    break;
                }
            }
        }
        else {
            if (GetVideoModeList()[gMenuManager_f60] && gMenuManager_f60) {
                gMenuManager_f5C = gMenuManager_f60;
                gSelectedMode = gMenuManager_f60;
            }
            else {
                RwBool defaultModeFound = false;
                while (!defaultModeFound && gSelectedMode < RwEngineGetNumVideoModes()) {
                    RwEngineGetVideoModeInfo(&mode, gSelectedMode);
                    if (!g_6D59F8 || mode.width == 800 && mode.height == 600 && mode.depth == 32 && mode.flags & rwVIDEOMODEEXCLUSIVE)
                        defaultModeFound = 1;
                    else
                        ++gSelectedMode;
                }
                if (!defaultModeFound) {
                    MessageBox(NULL, "Cannot find 800x600 video mode", "GTA: Vice City", MB_ICONERROR);
                    return FALSE;
                }
            }
        }
    }
    RwEngineGetVideoModeInfo(&mode, gSelectedMode);
    gMenuManager_f30 = 0;
    RwBool modeSet = RwEngineSetVideoMode(gSelectedMode);
    if (!modeSet)
        return FALSE;
    if (mode.flags & rwVIDEOMODEEXCLUSIVE) {
        DebugLine("%dx%dx%d", mode.width, mode.height, mode.depth);
        RwInt32 maxRefreshRate = GetMaxRefreshRate(mode.width, mode.height, mode.depth);
        if (maxRefreshRate != -1) {
            DebugLine("refresh %d", maxRefreshRate);
            RwD3D9EngineSetRefreshRate(maxRefreshRate);
        }
        gRsGlobal.maximumWidth = mode.width;
        gRsGlobal.maximumHeight = mode.height;
        gRsGlobal.screenWidth = mode.width;
        gRsGlobal.screenHeight = mode.height;
        gRsGlobal.ps->fullscreen = 1;
    }
    return TRUE;
}

void WINAPI OnSetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) {
    RECT rc;
    GetWindowRect(hWnd, &rc);
    int x = (GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 2;
    SetWindowPos(hWnd, hWndInsertAfter, x, y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
}

void SetVideoMode(RwInt32 mode) {
    RwTexDictionarySetCurrent(0);
    ((void(__thiscall *)(int))0x4A394D)(0x869630); // CMenuManager::UnloadTextures
    gAdapter = RwEngineGetCurrentSubSystem();
    gSelectedMode = mode;
    RwD3D9ChangeVideoMode(mode);
    gRsGlobal.maximumWidth = gRwCamera->frameBuffer->width;
    gRsGlobal.maximumHeight = gRwCamera->frameBuffer->height;
    if (gRsGlobal.ps && gRsGlobal.ps->window) {
        RwVideoMode info;
        RwEngineGetVideoModeInfo(&info, mode);
        if ((info.flags & rwVIDEOMODEEXCLUSIVE) == 0)
            OnSetWindowPos(gRsGlobal.ps->window, 0, 0, 0, 0, 0, 0);
    }
    ((void(__thiscall *)(int))0x4A3A13)(0x869630); // CMenuManager::LoadAllTextures
}

void MakeSelectDeviceHook() {
    CPatch::RedirectJump(0x600DA0, RsSelectDevice);
    CPatch::RedirectJump(0x601770, SetVideoMode);
    CPatch::RedirectJump(0x601880, GetVideoModeList);
    gWindowedMode = GetPrivateProfileIntW(L"MAIN", L"WINDOWED", 0, (GetModuleDir(NULL) + L"plugins\\vice37.ini").c_str()) == 1;
    if (gWindowedMode) {
        CPatch::Nop(0x5FFD78, 14);
        CPatch::Nop(0x5FFD9B, 1);
        CPatch::RedirectCall(0x5FFD9B + 1, OnSetWindowPos);
    }
    CPatch::Nop(0x6018DA, 6);
}
