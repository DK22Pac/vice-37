/***************************************************************************
 *                                                                         *
 * Module  : baworobj.h                                                    *
 *                                                                         *
 * Purpose : World object handling functions.                              *
 *                                                                         *
 **************************************************************************/

#ifndef RWWOROBJ_H
#define RWWOROBJ_H

/****************************************************************************
 Includes
 */

#include "../src/rwcore.h"
#include "basector.h"
#include "baclump.h"
#include "balight.h"
#include "baworld.h"

/****************************************************************************
 Defines
 */

#if (!defined(RWDEBUG))
/* Called from RpWorldRender() */
#define _rwCameraAssertWorld(camera, world) /* No op */
#endif /* (!defined(RWDEBUG)) */

/* RWPUBLIC */
/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

RWEXPORT void RWAPI RpTieSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );
RWEXPORT void RWAPI RpLightTieSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

/* Adding and removing cameras to/from the world */
RWEXPORT RpWorld* RWAPI RpWorldRemoveCamera(RpWorld *world, RwCamera *camera);
RWEXPORT RpWorld* RWAPI RpWorldAddCamera(RpWorld *world, RwCamera *camera);
RWEXPORT RpWorld* RWAPI RwCameraGetWorld(const RwCamera *camera);

/* Adding and removing atomics to/from the world */
RWEXPORT RpWorld* RWAPI RpWorldRemoveAtomic(RpWorld *world, RpAtomic *atomic);
RWEXPORT RpWorld* RWAPI RpWorldAddAtomic(RpWorld *world, RpAtomic *atomic);
RWEXPORT RpWorld* RWAPI RpAtomicGetWorld(const RpAtomic *atomic);

/* Adding and removing clumps to/from the world */
RWEXPORT RpWorld* RWAPI RpWorldAddClump(RpWorld *world, RpClump *clump);
RWEXPORT RpWorld* RWAPI RpWorldRemoveClump(RpWorld *world, RpClump *clump);
RWEXPORT RpWorld* RWAPI RpClumpGetWorld(const RpClump *clump);

/* Adding and removing lights to/from the world */
RWEXPORT RpWorld* RWAPI RpWorldAddLight(RpWorld *world, RpLight *light);
RWEXPORT RpWorld* RWAPI RpWorldRemoveLight(RpWorld *world, RpLight *light);
RWEXPORT RpWorld* RWAPI RpLightGetWorld(const RpLight *light);

/* Finding whats in the view frustum */
RWEXPORT RwCamera* RWAPI RwCameraForAllClumpsInFrustum(RwCamera *camera, void *data);
RWEXPORT RwCamera* RWAPI RwCameraForAllAtomicsInFrustum(RwCamera *camera, 
                                                RpAtomicCallBack callback,
                                                void *data);
RWEXPORT RwCamera* RWAPI RwCameraForAllSectorsInFrustum(RwCamera *camera,
                                                RpWorldSectorCallBack callBack,
                                                void *pData);

/* Enumeration involving the world sectors */
RWEXPORT RpLight* RWAPI RpLightForAllWorldSectors(RpLight *light,
                                          RpWorldSectorCallBack callback,
                                          void *data);
RWEXPORT RpAtomic* RWAPI RpAtomicForAllWorldSectors(RpAtomic *atomic,
                                            RpWorldSectorCallBack callback,
                                            void *data);
RWEXPORT RpWorldSector* RWAPI RpWorldSectorForAllAtomics(RpWorldSector *sector,
                                                 RpAtomicCallBack callback,
                                                 void *data);
RWEXPORT RpWorldSector* RWAPI RpWorldSectorForAllCollisionAtomics(RpWorldSector *sector,
                                                 RpAtomicCallBack callback,
                                                 void *data);
RWEXPORT RpWorldSector* RWAPI RpWorldSectorForAllLights(RpWorldSector *sector,
                                                RpLightCallBack callback,
                                                void *data);

/* RWPUBLICEND */

/* Registering toolkits to attach objects into worlds */
RWEXPORT RwBool RWAPI _rpWorldObjRegisterExtensions(void);
RWEXPORT RwBool RWAPI _rpTieDestroy(RpTie *tie);
RWEXPORT RwBool RWAPI _rpLightTieDestroy(RpLightTie *tie);

#if (defined(RWDEBUG))
/* Called from RpWorldRender() */
RWEXPORT void RWAPI _rwCameraAssertWorld(RwCamera *camera, RpWorld *world);
#endif /* (defined(RWDEBUG)) */

/* RWPUBLIC */
#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RWWOROBJ_H */
