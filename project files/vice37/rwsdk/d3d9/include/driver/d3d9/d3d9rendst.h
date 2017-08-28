/***************************************************************************
 *                                                                         *
 * Module  : D3D9rendst.h                                                    *
 *                                                                         *
 * Purpose : Renderstates.                                                 *
 *                                                                         *
 **************************************************************************/

#ifndef D3D9RENDST_H
#define D3D9RENDST_H

#include "batypes.h"
#include "baimmedi.h"

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

RWEXPORT void RWAPI _rwD3D9RenderStateOpen(void);

RWEXPORT void RWAPI _rwD3D9RenderStateReset(void);

RWEXPORT void RWAPI _rwD3D9RenderStateFlushCache(void); /* need to be call before any Draw Primitive */

RWEXPORT RwBool RWAPI _rwD3D9RWSetRasterStage(RwRaster *raster, RwUInt32 stage);
RWEXPORT RwRaster* RWAPI _rwD3D9RWGetRasterStage(RwUInt32 stage);

RWEXPORT RwBool RWAPI _rwD3D9RWSetRenderState(RwRenderState nState, void *pParam);
RWEXPORT RwBool RWAPI _rwD3D9RWGetRenderState(RwRenderState nState, void *pParam);

RWEXPORT void RWAPI
_rwD3D9SetTextureAnisotropyOffset(RwInt32 anisotTextureOffset);

/* Fast Render State Set functions */
RWEXPORT RwBool RWAPI _rwD3D9RenderStateTextureFilter(RwTextureFilterMode filterMode);

RWEXPORT RwBool RWAPI _rwD3D9RenderStateTextureAddress(RwTextureAddressMode addressMode);
RWEXPORT RwBool RWAPI _rwD3D9RenderStateTextureAddressU(RwTextureAddressMode addressMode);
RWEXPORT RwBool RWAPI _rwD3D9RenderStateTextureAddressV(RwTextureAddressMode addressMode);

RWEXPORT RwBool RWAPI _rwD3D9RenderStateVertexAlphaEnable(RwBool enable);
RWEXPORT RwBool RWAPI _rwD3D9RenderStateIsVertexAlphaEnable(void);

RWEXPORT RwBool RWAPI _rwD3D9RenderStateSrcBlend(RwBlendFunction srcBlend);
RWEXPORT RwBool RWAPI _rwD3D9RenderStateDestBlend(RwBlendFunction dstBlend);

RWEXPORT RwBool RWAPI _rwD3D9RenderStateStencilEnable(RwBool enable);

RWEXPORT RwBool RWAPI _rwD3D9RenderStateStencilFail(RwStencilOperation operation);
RWEXPORT RwBool RWAPI _rwD3D9RenderStateStencilZFail(RwStencilOperation operation);
RWEXPORT RwBool RWAPI _rwD3D9RenderStateStencilPass(RwStencilOperation operation);

RWEXPORT RwBool RWAPI _rwD3D9RenderStateStencilFunction(RwStencilFunction function);
RWEXPORT RwBool RWAPI _rwD3D9RenderStateStencilFunctionRef(RwInt32 ref);
RWEXPORT RwBool RWAPI _rwD3D9RenderStateStencilFunctionMask(RwInt32 mask);
RWEXPORT RwBool RWAPI _rwD3D9RenderStateStencilFunctionWriteMask(RwInt32 writeMask);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* D3D9RENDST_H */



