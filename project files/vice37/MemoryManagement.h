#pragma once
#include "CPatch.h"
#include "Debug.h"

struct MemoryFunctions {
    char _pad[0x130];
    void *rwmalloc;
    void *rwfree;
    void *rwrealloc;
    void *rwcalloc;
};

MemoryFunctions memoryFunctions;
MemoryFunctions *pMemFunctions = &memoryFunctions;

void MakeMemoryManagementHook() {
    memoryFunctions.rwmalloc = (void *)0x661870;
    memoryFunctions.rwfree = (void *)0x6618A0;
    memoryFunctions.rwrealloc = (void *)0x6618D0;
    memoryFunctions.rwcalloc = (void *)0x665B60;

    CPatch::SetPointer(0x615CB6 + 2, &pMemFunctions); // CBike::CBike malloc
    CPatch::SetPointer(0x6018A7 + 2, &pMemFunctions);
    CPatch::SetPointer(0x601936 + 2, &pMemFunctions);
    CPatch::SetPointer(0x6005F6 + 2, &pMemFunctions); // WinMain free
    CPatch::SetPointer(0x600611 + 2, &pMemFunctions); // WinMain free
    CPatch::SetPointer(0x59EF2B + 2, &pMemFunctions); // CAutomobile::CAutomobile malloc
    CPatch::SetPointer(0x57EE54 + 2, &pMemFunctions); // geometry list malloc
    CPatch::SetPointer(0x57E9C8 + 2, &pMemFunctions);	// RpClumpGtaStreamRead2 free
    CPatch::SetPointer(0x57EA64 + 2, &pMemFunctions);	// RpClumpGtaStreamRead2 free
    CPatch::SetPointer(0x57EAE4 + 2, &pMemFunctions);	// RpClumpGtaStreamRead2 free
    CPatch::SetPointer(0x57EB61 + 2, &pMemFunctions);	// RpClumpGtaStreamRead2 free
    CPatch::SetPointer(0x57E8D1 + 2, &pMemFunctions); // RpClumpGtaCancelStream malloc
    CPatch::SetPointer(0x566335 + 2, &pMemFunctions); // CPedModelInfo::CreateHitColModelSkinned malloc
    CPatch::SetPointer(0x48A41A + 2, &pMemFunctions);	// CFileLoader::LoadCollisionModel malloc
    CPatch::SetPointer(0x48A4D8 + 2, &pMemFunctions);	// CFileLoader::LoadCollisionModel malloc
    CPatch::SetPointer(0x48A537 + 2, &pMemFunctions);	// CFileLoader::LoadCollisionModel malloc
    CPatch::SetPointer(0x48A73D + 2, &pMemFunctions);	// CFileLoader::LoadCollisionModel malloc
    CPatch::SetPointer(0x416B80 + 0x5D + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x85 + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x97 + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x105 + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x12F + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x141 + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x1BE + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x1E6 + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x1F8 + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x24C + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x268 + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x2CA + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x2E6 + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x4DB + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416B80 + 0x4ED + 2, &pMemFunctions);	// CColModel::operator=
    CPatch::SetPointer(0x416AE9 + 2, &pMemFunctions); // CColModel::CalculateTrianglePlanes malloc
    CPatch::SetPointer(0x416ABB + 2, &pMemFunctions); // CColModel::RemoveTrianglePlanes free
    CPatch::SetPointer(0x4169B0 + 0x11 + 2, &pMemFunctions); //  CColModel::RemoveCollisionVolumes
    CPatch::SetPointer(0x4169B0 + 0x26 + 2, &pMemFunctions); //  CColModel::RemoveCollisionVolumes
    CPatch::SetPointer(0x4169B0 + 0x3B + 2, &pMemFunctions); //  CColModel::RemoveCollisionVolumes
    CPatch::SetPointer(0x4169B0 + 0x50 + 2, &pMemFunctions); //  CColModel::RemoveCollisionVolumes
    CPatch::SetPointer(0x4169B0 + 0x65 + 2, &pMemFunctions); //  CColModel::RemoveCollisionVolumes
    CPatch::SetPointer(0x402C4F + 2, &pMemFunctions);	// CAnimBlendSequence::~CAnimBlendSequence free
    CPatch::SetPointer(0x402C64 + 2, &pMemFunctions);	// CAnimBlendSequence::~CAnimBlendSequence free
    CPatch::SetPointer(0x402BC1 + 2, &pMemFunctions);	// CAnimBlendSequence::~CAnimBlendSequence free
    CPatch::SetPointer(0x402BD6 + 2, &pMemFunctions);	// CAnimBlendSequence::~CAnimBlendSequence free
    CPatch::SetPointer(0x402B0E + 2, &pMemFunctions);	// CAnimBlendSequence::SetNumFrames malloc
    CPatch::SetPointer(0x402B3A + 2, &pMemFunctions);	// CAnimBlendSequence::SetNumFrames malloc
    CPatch::SetPointer(0x402B63 + 2, &pMemFunctions);	// CAnimBlendSequence::SetNumFrames malloc
}
