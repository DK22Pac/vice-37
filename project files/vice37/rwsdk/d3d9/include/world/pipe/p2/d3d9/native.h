/****************************************************************************
 *                                                                          *
 * module : native.h                                                        *
 *                                                                          *
 * purpose: see native.c                                                    *
 *                                                                          *
 ****************************************************************************/

#ifndef NATIVE_H
#define NATIVE_H

#include "rwcore.h"

/****************************************************************************
 global prototypes
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Geometry */
RWEXPORT RwStream* RWAPI _rpGeometryNativeWrite(RwStream *stream,
                                        const RpGeometry *geometry);
RWEXPORT RpGeometry* RWAPI _rpGeometryNativeRead(RwStream *stream,
                                         RpGeometry *geometry);
RWEXPORT RwInt32 RWAPI _rpGeometryNativeSize(const RpGeometry *geometry);

/* World sectors */
RWEXPORT RwStream* RWAPI _rpWorldSectorNativeWrite(RwStream *stream,
                                           const RpWorldSector *sector);
RWEXPORT RpWorldSector* RWAPI _rpWorldSectorNativeRead(RwStream *stream,
                                               RpWorldSector *sector);
RWEXPORT RwInt32 RWAPI _rpWorldSectorNativeSize(const RpWorldSector *sector);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


#endif /* NATIVE_H */
