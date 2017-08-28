#ifndef BAPIPEW_H
#define BAPIPEW_H

#include "../../../src/rwcore.h"

#include "baworld.h"
#include "basector.h"
#include "baclump.h"
#include "bamateri.h"

/* API */

RWEXPORT RwBool RWAPI _rpWorldPipeAttach(void);
RWEXPORT RwBool RWAPI _rpWorldPipelineOpen( void);
RWEXPORT void RWAPI _rpWorldPipelineClose(void);

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */
RWEXPORT RwBool RWAPI _rxWorldDevicePluginAttach(void);
#ifdef    __cplusplus
}
#endif /* __cplusplus */

/****************************************************************************
 <macro/inline functionality
 */

/* RWPUBLIC */

#define RpWorldGetDefaultSectorPipelineMacro() \
    (RXPIPELINEGLOBAL(currentWorldSectorPipeline))

#define RpWorldSetSectorPipelineMacro(_world, _pipeline) \
    ( ((_world)->pipeline = _pipeline), _world )

#define RpWorldGetSectorPipelineMacro(_world, _pipeline) \
    ( (*(_pipeline) = (_world)->pipeline), _world )

#define RpWorldSectorSetPipelineMacro(_sector, _pipeline) \
    ( ((_sector)->pipeline = _pipeline), _sector )

#define RpWorldSectorGetPipelineMacro(_sector, _pipeline) \
    ( (*(_pipeline) = (_sector)->pipeline), _sector )

#define RpAtomicGetDefaultPipelineMacro() \
    (RXPIPELINEGLOBAL(currentAtomicPipeline))

#define RpAtomicSetPipelineMacro(_atomic, _pipeline) \
    ( ((_atomic)->pipeline = _pipeline), _atomic )

#define RpAtomicGetPipelineMacro(_atomic, _pipeline) \
    ( (*(_pipeline) = (_atomic)->pipeline), _atomic )

#define RpMaterialGetDefaultPipelineMacro() \
    (RXPIPELINEGLOBAL(currentMaterialPipeline))

#define RpMaterialSetPipelineMacro(_material, _pipeline) \
    ( ((_material)->pipeline = _pipeline), _material )

#define RpMaterialGetPipelineMacro(_material, _pipeline) \
    ( (*(_pipeline) = (_material)->pipeline), _material )


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RpWorldGetDefaultSectorPipeline RpWorldGetDefaultSectorPipelineMacro
#define RpWorldSetSectorPipeline        RpWorldSetSectorPipelineMacro
#define RpWorldGetSectorPipeline        RpWorldGetSectorPipelineMacro
#define RpWorldSectorSetPipeline        RpWorldSectorSetPipelineMacro
#define RpWorldSectorGetPipeline        RpWorldSectorGetPipelineMacro

#define RpAtomicGetDefaultPipeline      RpAtomicGetDefaultPipelineMacro
#define RpAtomicSetPipeline             RpAtomicSetPipelineMacro
#define RpAtomicGetPipeline             RpAtomicGetPipelineMacro

#define RpMaterialGetDefaultPipeline    RpMaterialGetDefaultPipelineMacro
#define RpMaterialSetPipeline           RpMaterialSetPipelineMacro
#define RpMaterialGetPipeline           RpMaterialGetPipelineMacro

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/* RWPUBLICEND */

/****************************************************************************
 Function prototypes
 */

/* RWPUBLIC */

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

RWEXPORT RxPipeline* RWAPI RpWorldSetDefaultSectorPipeline(RxPipeline *pipeline);
RWEXPORT RxPipeline* RWAPI RpAtomicSetDefaultPipeline(RxPipeline *pipeline);
RWEXPORT RxPipeline* RWAPI RpMaterialSetDefaultPipeline(RxPipeline *pipeline);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

RWEXPORT RxPipeline* RWAPI RpWorldGetGenericSectorPipeline(void);
RWEXPORT RxPipeline* RWAPI RpWorldGetDefaultSectorPipeline(void);
RWEXPORT RpWorld* RWAPI RpWorldSetSectorPipeline(RpWorld       *world,
                                                  RxPipeline    *pipeline);
RWEXPORT RpWorld* RWAPI RpWorldGetSectorPipeline(RpWorld       *world,
                                                  RxPipeline   **pipeline);
RWEXPORT RpWorldSector* RWAPI RpWorldSectorSetPipeline(RpWorldSector *sector,
                                                  RxPipeline    *pipeline);
RWEXPORT RpWorldSector* RWAPI RpWorldSectorGetPipeline(RpWorldSector *sector,
                                                  RxPipeline   **pipeline);

RWEXPORT RxPipeline* RWAPI RpAtomicGetGenericPipeline(void);
RWEXPORT RxPipeline* RWAPI RpAtomicGetDefaultPipeline(void);
RWEXPORT RpAtomic* RWAPI RpAtomicSetPipeline(RpAtomic             *atomic,
                                             RxPipeline           *pipeline);
extern const RpAtomic* RWAPI RpAtomicGetPipeline(const RpAtomic *const atomic, 
                                             RxPipeline          **pipeline);

RWEXPORT RxPipeline* RWAPI RpMaterialGetGenericPipeline(void);
RWEXPORT RxPipeline* RWAPI RpMaterialGetDefaultPipeline(void);
RWEXPORT RpMaterial* RWAPI RpMaterialSetPipeline(RpMaterial  *material,
                                               RxPipeline  *pipeline);
RWEXPORT RpMaterial* RWAPI RpMaterialGetPipeline(RpMaterial  *material,
                                               RxPipeline **pipeline);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

RWEXPORT const RpGeometry* RWAPI RpGeometryIsCorrectlySorted(const RpGeometry * geometry,
                                                     RwBool * result);
RWEXPORT RpGeometry* RWAPI RpGeometrySortByMaterial(const RpGeometry * geometry,
                                                  RpGeometrySortByMaterialCallBack  callback);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/* LEGACY-SUPPORT macros */
#define RpWorldSetDefaultSectorInstancePipeline RpWorldSetDefaultSectorPipeline
#define RpWorldGetDefaultSectorInstancePipeline RpWorldGetDefaultSectorPipeline
#define RpWorldSetSectorInstancePipeline        RpWorldSetSectorPipeline
#define RpWorldGetSectorInstancePipeline        RpWorldGetSectorPipeline
#define RpWorldSectorSetInstancePipeline        RpWorldSectorSetPipeline
#define RpWorldSectorGetInstancePipeline        RpWorldSectorGetPipeline

#define RpAtomicGetDefaultInstancePipeline      RpAtomicGetDefaultPipeline
#define RpAtomicSetDefaultInstancePipeline      RpAtomicSetDefaultPipeline
#define RpAtomicSetInstancePipeline             RpAtomicSetPipeline
#define RpAtomicGetInstancePipeline             RpAtomicGetPipeline

#define RpMaterialSetDefaultRenderPipeline      RpMaterialSetDefaultPipeline
#define RpMaterialGetDefaultRenderPipeline      RpMaterialGetDefaultPipeline
#define RpMaterialSetRenderPipeline             RpMaterialSetPipeline
#define RpMaterialGetRenderPipeline             RpMaterialGetPipeline

/* RWPUBLICEND */

#endif /* BAPIPEW_H */
