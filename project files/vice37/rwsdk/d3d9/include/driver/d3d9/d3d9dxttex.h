/***************************************************************************
 *                                                                         *
 * Module  : d3d9dxttex.h                                                  *
 *                                                                         *
 * Purpose : D3D9 DXT texture support                                      *
 *                                                                         *
 **************************************************************************/

#ifndef D3D9DXTTEX_H
#define D3D9DXTTEX_H

/****************************************************************************
 Includes
 */

#include "../../src/plcore/batypes.h"
#include "../../src/plcore/baimmedi.h"
#include "batextur.h"
#include "d3d9dxttex_add.h"

/****************************************************************************
 Defines
 */

/****************************************************************************
 Global Types
 */

/****************************************************************************
 Global variables (across program)
 */
/*
#ifdef    __cplusplus
extern "C"
{
#endif                           __cplusplus 

	RWEXPORT RwBool g_DXT1AlphaChecker;

#ifdef    __cplusplus
}
#endif                           __cplusplus 

*/
/****************************************************************************
 Function prototypes
 */

/* RWPUBLIC */
#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

RWEXPORT RwRaster* RWAPI
RwD3D9RasterStreamReadDDS(RwStream *stream);

RWEXPORT RwTexture* RWAPI
RwD3D9DDSTextureRead(const RwChar *name, const RwChar *maskname);

RWEXPORT RwBool RWAPI
RwD3D9RasterIsCompressed(const RwRaster *raster);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */
/* RWPUBLICEND */


#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

RWEXPORT RwBool RWAPI
_rwD3D9DecompressDXT1(RwInt32 width, RwInt32 height, RwUInt32 *destPixels, const RwUInt16 *srcPixels);

RWEXPORT void RWAPI
_rwD3D9DecompressDXT3(RwInt32 width, RwInt32 height, RwUInt32 *destPixels, const RwUInt16 *srcPixels);

RWEXPORT void RWAPI
_rwD3D9DecompressDXT5(RwInt32 width, RwInt32 height, RwUInt32 *destPixels, const RwUInt16 *srcPixels);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


#endif /* D3D9DXTTEX_H */
