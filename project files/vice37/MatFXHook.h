#pragma once
#include "CPatch.h"
#include <src/rwcore.h>
//#include <rpmatfx.h>

unsigned int &MyMatFXMaterialDataOffset = *(unsigned int *)0x7876CC;

RwBool MyRpMatFXPluginAttach()
{
	RwBool result = RpMatFXPluginAttach();
	MyMatFXMaterialDataOffset = RpMaterialGetPluginOffset(0x120);
	return result;
}

void MakeMatFxHook()
{
    MessageBox( NULL, "the init", "the blowa", MB_OK );

	CPatch::RedirectJump(0x655EB0, MyRpMatFXPluginAttach);
}