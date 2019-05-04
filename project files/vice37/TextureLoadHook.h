#pragma once
#include "CPatch.h"
#include <src/rwcore.h>

extern "C" RwBool _rwD3D9CheckValidTextureFormat(RwUInt32 format);

RwUInt32 RwStreamReadTextureCount(RwStream *stream, RwUInt32 *buffer, RwUInt32 length) {
    RwUInt32 bytesRead = RwStreamRead(stream, buffer, length);
    *buffer &= 0xFFFF;
    return bytesRead;
}

void MakeTextureLoadHook() {
    CPatch::RedirectCall(0x61E74B, RwStreamReadTextureCount);
    CPatch::RedirectCall(0x61E521, RwStreamReadTextureCount);
    CPatch::RedirectJump(0x65FA80, _rwD3D9CheckValidTextureFormat);
}
