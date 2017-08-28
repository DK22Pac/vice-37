/***************************************************************************
 *                                                                         *
 * Module  : baresamp.h                                                    *
 *                                                                         *
 * Purpose : Re-sampling images                                             *
 *                                                                         *
 **************************************************************************/

#ifndef RWRESAMP_H
#define RWRESAMP_H

/****************************************************************************
 Includes
 */

#include "baimage.h"

/****************************************************************************
 Defines
 */


/****************************************************************************
 Global Types
 */


/* RWPUBLIC */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

RWEXPORT RwImage* RWAPI RwImageResample(RwImage *dstImage, const RwImage *srcImage);
RWEXPORT RwImage* RWAPI RwImageCreateResample(const RwImage *srcImage, RwInt32 width,
                                                               RwInt32 height);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RWRESAMP_H */

