/****************************************************************************
 *                                                                          *
 * module : nodeD3D9AtomicAllInOne.h                                        *
 *                                                                          *
 * purpose: see nodeD3D9AtomicAllInOne.c                                    *
 *                                                                          *
 ****************************************************************************/

#ifndef NODED3D9ATOMICALLINONE_H
#define NODED3D9ATOMICALLINONE_H

#include "rwcore.h"


/****************************************************************************
 global prototypes
 */

/* RWPUBLIC */
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

RWEXPORT RxNodeDefinition* RWAPI
RxNodeDefinitionGetD3D9AtomicAllInOne(void);

#ifdef RWD3D9_USE_VERTEXSHADER_PIPELINE
RWEXPORT RxNodeDefinition* RWAPI
RxNodeDefinitionGetD3D9VertexShaderAtomicAllInOne(void);
#endif

/* RWPUBLICEND */

RWEXPORT D3DCAPS9 _RwD3D9DeviceCaps;

RWEXPORT void RWAPI
_rwD3D9AtomicDefaultLightingCallback(void *object);

/* RWPUBLIC */
#ifdef    __cplusplus
}
#endif /* __cplusplus */
/* RWPUBLICEND */


#endif /* NODED3D9ATOMICALLINONE_H */
