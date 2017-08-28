/***************************************************************************
 *                                                                         *
 * Module  : im3dpipe.h                                                    *
 *                                                                         *
 * Purpose : See im3dpipe.c                                                *
 *                                                                         *
 **************************************************************************/

#ifndef IM3DPIPE_H
#define IM3DPIPE_H

/****************************************************************************
 Includes
 */

#include "batypes.h"
#include "baimmedi.h"
#include "bamatrix.h"
#include "p2core.h"

/* Next line is a sneaky way to get the contents of pip2model.h into rwcore.h */
#include "pip2model.h"

/* We need this to get the structure passed in */
#include "baim3d.h"

/****************************************************************************
 Global Defines
 */

/****************************************************************************
 Global Types
 */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

RWEXPORT RwBool RWAPI _rwIm3DCreatePlatformTransformPipeline(RxPipeline **globalPipe);
RWEXPORT RwBool RWAPI _rwIm3DCreatePlatformRenderPipelines(rwIm3DRenderPipelines *globalPipes);
RWEXPORT void RWAPI _rwIm3DDestroyPlatformTransformPipeline(RxPipeline **globalPipe);
RWEXPORT void RWAPI _rwIm3DDestroyPlatformRenderPipelines(rwIm3DRenderPipelines *globalPipes);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* IM3DPIPE_H */

