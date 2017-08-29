/****************************************************************************
 *                                                                          *
 * module : nodeD3D9oxSubmitNoLight.h                                         *
 *                                                                          *
 * purpose: see nodeD3D9oxSubmitNoLight.c                                     *
 *                                                                          *
 ****************************************************************************/

#ifndef NODED3D9SUBMITNOLIGHT_H
#define NODED3D9SUBMITNOLIGHT_H

#include "../p2core.h"
 
/****************************************************************************
 global prototypes
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

RWEXPORT RwBool RWAPI _rwD3D9Im3DRenderOpen(void);

RWEXPORT RxNodeDefinition* RWAPI RxNodeDefinitionGetD3D9ImmInstance(void);
RWEXPORT RxNodeDefinition* RWAPI RxNodeDefinitionGetD3D9SubmitNoLight(void);

RWEXPORT void RWAPI _rwD3D9Im3DRenderClose(void);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* NODED3D9SUBMITNOLIGHT_H */
