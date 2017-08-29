/***************************************************************************
 *                                                                         *
 * Module  : D3D9raster.h                                                    *
 *                                                                         *
 * Purpose : D3D9 raster header                                            *
 *                                                                         *
 **************************************************************************/

#ifndef D3D9RASTER_H
#define D3D9RASTER_H

/****************************************************************************
 Includes
 */

#include <d3d9.h>

#include "batypes.h"
#include "baimmedi.h"

/****************************************************************************
 Global Types
 */
typedef struct _rwD3D9Palette _rwD3D9Palette;
struct _rwD3D9Palette
{
    PALETTEENTRY    entries[256];
    RwInt32     globalindex;
};

typedef LPDIRECT3DSURFACE9 LPSURFACE;
typedef LPDIRECT3DTEXTURE9 LPTEXTURE;

typedef struct _rwD3D9RasterExt _rwD3D9RasterExt;
struct _rwD3D9RasterExt
{
    LPTEXTURE               texture;
    _rwD3D9Palette          *palette;
    RwUInt8                 alpha;              /* This texture has alpha */
    RwUInt8                 cube : 4;           /* This texture is a cube texture */
    RwUInt8                 face : 4;           /* The active face of a cube texture */
    RwUInt8                 automipmapgen : 4;  /* This texture uses automipmap generation */
    RwUInt8                 compressed : 4;     /* This texture is compressed */
    RwUInt8                 lockedMipLevel;
    LPSURFACE               lockedSurface;
    D3DLOCKED_RECT          lockedRect;
    D3DFORMAT               d3dFormat;          /* D3D format */
    LPDIRECT3DSWAPCHAIN9    swapChain;
    HWND                    window;
};

typedef struct _rwD3D9RasterConvData _rwD3D9RasterConvData;
struct _rwD3D9RasterConvData
{
    D3DFORMAT   format;
    RwUInt8     depth;
    RwUInt8     alpha;
};

typedef struct _rwD3D9FormatInfo _rwD3D9FormatInfo;
struct _rwD3D9FormatInfo
{
    RwUInt8 alpha;
    RwUInt8 depth;
    RwUInt16 rwFormat;
};

/****************************************************************************
 Defines
 */
#define RASTEREXTFROMRASTER(raster) \
    ((_rwD3D9RasterExt *)(((RwUInt8 *)(raster)) + _RwD3D9RasterExtOffset))

#define RASTEREXTFROMCONSTRASTER(raster)                        \
    ((const _rwD3D9RasterExt *)                                 \
     (((const RwUInt8 *)(raster)) + _RwD3D9RasterExtOffset))

#define FMT2TBL(_p) (((_p) & rwRASTERFORMATPIXELFORMATMASK) >> 8)

/****************************************************************************
 Global variables (across program)
 */

RWEXPORT RwInt32 _RwD3D9RasterExtOffset;    /* Raster extension offset */

RWEXPORT const _rwD3D9RasterConvData _rwRasterConvTable[];

RWEXPORT _rwD3D9FormatInfo _rwD3D9PixelFormatInfo[];

#if defined(RWDEBUG)
RWEXPORT RwUInt32  NumVideoMemoryRasters;
RWEXPORT RwUInt32  NumNormalRasters;
RWEXPORT RwUInt32  NumTextureRasters;
RWEXPORT RwUInt32  NumCameraTextureRasters;
RWEXPORT RwUInt32  NumCameraRasters;
RWEXPORT RwUInt32  NumZBufferRasters;
#endif /* defined(RWDEBUG) */

/****************************************************************************
 Function prototypes
 */
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Plugin Attach */
RWEXPORT RwBool RWAPI _rwD3D9RasterPluginAttach(void);

/* Open/Close */
RWEXPORT void RWAPI _rwD3D9RasterOpen(void);
RWEXPORT void RWAPI _rwD3D9RasterClose(void);

RWEXPORT void RWAPI _rxD3D9VideoMemoryRasterListRelease(void);
RWEXPORT RwBool RWAPI _rxD3D9VideoMemoryRasterListRestore(void);

RWEXPORT RwBool RWAPI _rwD3D9RasterHasAlpha(const RwRaster *raster);
RWEXPORT RwBool RWAPI _rwD3D9TextureHasAlpha(const RwTexture *texture);
RWEXPORT void RWAPI _rwD3D9RasterRemoveAlphaFlag(RwRaster *raster);

RWEXPORT RwBool RWAPI _rwD3D9CubeRasterCreate(RwRaster *raster, RwUInt32 d3dformat, RwInt32 mipmapLevels);
RWEXPORT void RWAPI _rwD3D9CubeRasterSelectFace(RwRaster *raster, RwUInt32 face);
RWEXPORT RwBool RWAPI _rwD3D9RasterIsCubeRaster(const RwRaster *raster);

/* Locking and unlocking */
RWEXPORT RwBool RWAPI _rwD3D9RasterLock(void *pixelsIn, void *rasterIn, RwInt32 accessMode);
RWEXPORT RwBool RWAPI _rwD3D9RasterUnlock(void *unused1, void *rasterIn, RwInt32 unused3);
RWEXPORT RwBool RWAPI _rwD3D9RasterLockPalette(void *paletteInOut, void *rasterIn, RwInt32 accessMode);
RWEXPORT RwBool RWAPI _rwD3D9RasterUnlockPalette(void *unused1, void *rasterIn, RwInt32 unused3);

/* Raster operations */
RWEXPORT RwBool RWAPI _rwD3D9RasterClear(void *unused1, void *unused2, RwInt32 packedColor);
RWEXPORT RwBool RWAPI _rwD3D9RasterClearRect(void *unused1, void *rectIn, RwInt32 packedColor);
RWEXPORT RwBool RWAPI _rwD3D9RasterRender(void *rasterIn, void *rectIn, RwInt32 unused3);
RWEXPORT RwBool RWAPI _rwD3D9RasterRenderScaled(void *rasterIn, void *rectIn, RwInt32 flags);
RWEXPORT RwBool RWAPI _rwD3D9RasterRenderFast(void *rasterIn, void *rectIn,  RwInt32 flags);

/* Setting the context */
RWEXPORT RwBool RWAPI _rwD3D9SetRasterContext(void *unused1, void *rasIn, RwInt32 unused3);

/* Finding formats */
RWEXPORT RwInt32 RWAPI _rwD3D9FindCorrectRasterFormat(RwRasterType type, RwInt32 flags);

RWEXPORT RwBool RWAPI _rwD3D9CheckRasterFormat(void *rasterIn, RwInt32 flags);

/* Creating and destroying */
RWEXPORT RwBool RWAPI _rwD3D9RasterCreate(void *unused1, void *rasterIn, RwInt32 flags);
RWEXPORT RwBool RWAPI _rwD3D9RasterDestroy(void *unused1, void *raster, RwInt32 unused3);

/* Getting a rasters mip levels */
RWEXPORT RwBool RWAPI _rwD3D9RasterGetMipLevels(void *mipLevels, void *ras, RwInt32 unused3);

RWEXPORT RwBool RWAPI _rwD3D9TextureSetRaster(void *unused1, void *unused2, RwInt32 unused3);
RWEXPORT RwBool RWAPI _rwD3D9RasterSubRaster(void *rasterIn, void *parentRasterIn, RwInt32 unused3);

/* Checking functions */
RWEXPORT RwBool RWAPI _rwD3D9CheckValidZBufferFormat(RwInt32 format);
RWEXPORT RwBool RWAPI _rwD3D9CheckValidTextureFormat(RwInt32 format);
RWEXPORT RwBool RWAPI _rwD3D9CheckValidCameraTextureFormat(RwInt32 format);
RWEXPORT RwBool RWAPI _rwD3D9CheckValidZBufferTextureFormat(RwInt32 format);
RWEXPORT RwBool RWAPI _rwD3D9CheckValidCubeTextureFormat(RwInt32 format);
RWEXPORT RwBool RWAPI _rwD3D9CheckValidCameraCubeTextureFormat(RwInt32 format);

RWEXPORT RwBool RWAPI _rwD3D9CheckAutoMipmapGenTextureFormat(RwInt32 format);
RWEXPORT RwBool RWAPI _rwD3D9CheckAutoMipmapGenCameraTextureFormat(RwInt32 format);
RWEXPORT RwBool RWAPI _rwD3D9CheckAutoMipmapGenCubeTextureFormat(RwInt32 format);
RWEXPORT RwBool RWAPI _rwD3D9CheckAutoMipmapGenCameraCubeTextureFormat(RwInt32 format);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* D3D9RASTER_H */
