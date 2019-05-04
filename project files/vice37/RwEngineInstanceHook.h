#pragma once
#include "CPatch.h"
#include <src/rwcore.h>

#define OFFSET_VECSPRINTF 0xC4  // 0xF0 - 0x2C
#define OFFSET_VECSTRLEN 0xF4   // 0x11C - 0x2C + 4

void MakeRwEngineInstanceHooks() {
    CPatch::SetPointer(0x61E7DF + 2, &RwEngineInstance); // txd stream read
    CPatch::SetPointer(0x61E5D6 + 2, &RwEngineInstance); // txd stream read
    CPatch::SetPointer(0x61E3CF + 2, &RwEngineInstance); // txd stream read
    CPatch::SetPointer(0x601969 + 2, &RwEngineInstance); // vecSprintf
    CPatch::SetInt(0x601975 + 2, OFFSET_VECSPRINTF);     // vecSprintf
    CPatch::SetPointer(0x5C1534 + 2, &RwEngineInstance); // curCamera
    CPatch::SetPointer(0x58067F + 2, &RwEngineInstance); // vecStrlen
    CPatch::SetInt(0x580686 + 2, OFFSET_VECSTRLEN);      // vecStrlen
    CPatch::SetPointer(0x6405AD, &RwEngineInstance);     // AtomicDefaultRenderCallback
    CPatch::SetPointer(0x6405B3, &_rxPipelineGlobalsOffset);// AtomicDefaultRenderCallback
}
