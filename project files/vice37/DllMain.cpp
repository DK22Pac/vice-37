#include "RwFunctionsHook.h"
#include "SelectDevice.h"
#include "FileSystem.h"
#include "RwEngineInstanceHook.h"
#include "MemoryManagement.h"
#include "TextureLoadHook.h"
#include "RwEngineVideoMode.h"
#include "MatFXHook.h"
#include "HAnimHook.h"

RwBool MyRwEngineInit(const RwMemoryFunctions *memFuncs, RwUInt32 initFlags, RwUInt32 resArenaSize) {
    return RwEngineInit(memFuncs, initFlags, resArenaSize);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        gDebug = GetPrivateProfileIntW(L"MAIN", L"DEBUG", 0, (GetModuleDir(NULL) + L"plugins\\vice37.ini").c_str()) == 1;
        if (gDebug) {
            FILE *f = fopen("plugins\\debug37.txt", "wt");
            if (f)
                fclose(f);
            CPatch::RedirectJump(0x401000, DebugLine);
        }
        CPatch::RedirectCall(0x602DF5, MyRwEngineInit);
        MakeRwFunctionsHook();
        MakeMemoryManagementHook();
        MakeFileFunctionsHook();
        MakeRwEngineVideoModeHook();
        MakeRwEngineInstanceHooks();
        MakeSelectDeviceHook();
        MakeMatFxHook();
        MakeHAnimHook();
        MakeTextureLoadHook();
    }
    return TRUE;
}
