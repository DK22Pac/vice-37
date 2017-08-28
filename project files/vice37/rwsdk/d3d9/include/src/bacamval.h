/***************************************************************************
 * Module  : bacamval.h                                                    *
 *                                                                         *
 * Purpose : Camera functions                                              *
 *                                                                         *
 **************************************************************************/

#ifndef RWCAMVAL_H
#define RWCAMVAL_H

/****************************************************************************
 Includes
 */

#include "bacamera.h"

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

/* Open closing */
RWEXPORT void RWAPI _rwCameraValOpen(void);
RWEXPORT void RWAPI _rwCameraValClose(void);

/* Render */
RWEXPORT void RWAPI _rwCameraValRender(RwCamera * camera);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif                          /* RWCAMVAL_H */
