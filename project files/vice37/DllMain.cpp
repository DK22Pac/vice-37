#include "RwFunctionsHook.h"
#include "AdapterRefreshRate.h"
#include "FileSystem.h"
#include "RwEngineInstanceHook.h"
#include "MemoryManagement.h"
#include "TextureLoadHook.h"
#include "RwEngineVideoMode.h"
#include "MatFXHook.h"
#include "HAnimHook.h"

RwBool MyRwEngineInit(const RwMemoryFunctions *memFuncs, RwUInt32 initFlags, RwUInt32 resArenaSize)
{
	RwBool result = RwEngineInit(memFuncs, initFlags, resArenaSize);
#if 0
	if(RtFSManagerOpen(RTFSMAN_UNLIMITED_NUM_FS) != FALSE)
		psInstallFileSystem();
#endif
	return result;
};

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if(reason == DLL_PROCESS_ATTACH)
	{
#ifndef _DISABLE_DEBUG_
		FILE *f = fopen("debug37.txt", "wt");
		fclose(f);
		CPatch::RedirectJump(0x401000, DebugLine);
#endif
		CPatch::RedirectCall(0x602DF5, MyRwEngineInit);
		MakeRwFunctionsHook();
		MakeMemoryManagementHook();
		MakeFileFunctionsHook();
		MakeRwEngineVideoModeHook();
		MakeRwEngineInstanceHooks();
		MakeAdapterRefreshRateHook();
		MakeMatFxHook();
		MakeHAnimHook();
		MakeTextureLoadHook();
	}
    return TRUE;
}