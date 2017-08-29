/***************************************************************************
 *                                                                         *
 * Module  : wrldpipe.h                                                    *
 *                                                                         *
 * Purpose : See wrldpipe.c                                                *
 *                                                                         *
 **************************************************************************/

#ifndef WRLDPIPE_H
#define WRLDPIPE_H

/****************************************************************************
 Includes
 */

#include "rwcore.h"

/****************************************************************************
 Global Defines
 */

#define RWD3D9_USE_VERTEXSHADER_PIPELINEx

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

RWEXPORT RwBool RWAPI _rpCreatePlatformMaterialPipelines(void);
RWEXPORT RwBool RWAPI _rpCreatePlatformWorldSectorPipelines(void);
RWEXPORT RwBool RWAPI _rpCreatePlatformAtomicPipelines(void);

RWEXPORT void RWAPI _rpDestroyPlatformMaterialPipelines(void);
RWEXPORT void RWAPI _rpDestroyPlatformAtomicPipelines(void);
RWEXPORT void RWAPI _rpDestroyPlatformWorldSectorPipelines(void);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* WRLDPIPE_H */
