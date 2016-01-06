#pragma once
#include "CPatch.h"
#include "Debug.h"
#include <d3d9.h>

#define gdwAdapter (*(UINT *)0x783EE8)

int GetMaxRefreshRate(int width, int height, int depth)
{
	IDirect3D9 *d3d = Direct3DCreate9(31);
	INT maxRate = 0x7FFFFFFF;
	D3DFORMAT format = D3DFMT_R5G6B5;
	if(depth == 32)
		format = D3DFMT_A8B8G8R8;
	else if(depth == 24)
		format = D3DFMT_R8G8B8;
	UINT modeCount = d3d->GetAdapterModeCount(gdwAdapter, format);
	for(UINT i = 0; i < modeCount; i++)
	{
		D3DDISPLAYMODE mode;
		d3d->EnumAdapterModes(gdwAdapter, format, i, &mode);
		if(mode.Width == width && mode.Height == height)
		{
			if(!mode.RefreshRate)
			{
				d3d->Release();
				return 0;
			}
			if(mode.RefreshRate < maxRate && mode.RefreshRate >= 60)
				maxRate = mode.RefreshRate;
		}
	}
	d3d->Release();
    if (maxRate == 0x7FFFFFFF) {
        return -1;
    }
	return maxRate;
}

void MakeAdapterRefreshRateHook()
{
	CPatch::RedirectJump(0x600FB0, GetMaxRefreshRate);
}