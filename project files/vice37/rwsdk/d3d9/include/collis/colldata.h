/*
 *  RenderWare Graphics Collision Plugin
 *
 *  File:    colldata.h
 *  Purpose: Collision data management
 */

#ifndef COLLDATA_H
#define COLLDATA_H

/******************************************************************************
 *  Global Types
 */

/******************************************************************************
 *  Internal globals/macros
 */

RWEXPORT RwInt32 _rpCollisionNumInstances;
RWEXPORT RwInt32 _rpCollisionGlobalRefOffset;
RWEXPORT RwInt32 _rpCollisionAtomicRefOffset;


#define _rpCollisionGlobalRefMacro() \
    (*RWPLUGINOFFSET(RwUInt32, RwEngineInstance, _rpCollisionGlobalRefOffset))

#define _rpCollisionAtomicRefMacro(_atomic) \
    (*RWPLUGINOFFSET(RwUInt32, _atomic, _rpCollisionAtomicRefOffset))


/* RWPUBLIC */

/******************************************************************************
 *  API types/globals/macros
 */

#if !defined(DOXYGEN)
typedef struct RpCollisionData RpCollisionData;
struct RpCollisionData
{
    RpCollTree  *tree;
};
#endif /* !defined(DOXYGEN) */

#define _rpCollisionGeometryGetDataMacro(_geometry) \
    RWPLUGINOFFSET(RpCollisionData, _geometry, _rpCollisionGeometryDataOffset)

#define _rpCollisionWorldSectorGetDataMacro(_sector) \
    RWPLUGINOFFSET(RpCollisionData, _sector, _rpCollisionWorldSectorDataOffset)


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RpCollisionGeometryGetCollTree(_geometry) \
    (_rpCollisionGeometryGetDataMacro(_geometry)->tree)

#define RpCollisionWorldSectorGetCollTree(_sector) \
    (_rpCollisionWorldSectorGetDataMacro(_sector)->tree)

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


/******************************************************************************
 *  Functions
 */

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

RWEXPORT RwInt32 _rpCollisionGeometryDataOffset;
RWEXPORT RwInt32 _rpCollisionWorldSectorDataOffset;

/*
 *  Collision data
 */

RWEXPORT RwBool RWAPI
RpCollisionPluginAttach(void);

/* 
 *  Worlds
 */
RWEXPORT RwBool RWAPI
RpCollisionWorldQueryData(RpWorld *world);

RWEXPORT RpWorld* RWAPI
RpCollisionWorldDestroyData(RpWorld *world);

/*
 *  World Sectors  
 */

RWEXPORT RpWorldSector* RWAPI
RpCollisionWorldSectorDestroyData(RpWorldSector *worldSector);

RWEXPORT RwBool RWAPI
RpCollisionWorldSectorQueryData(RpWorldSector *worldSector);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
RWEXPORT RpCollTree *
RpCollisionWorldSectorGetCollTree(RpWorldSector *worldSector);
#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

RWEXPORT RpWorldSector* RWAPI
_rpCollisionWorldSectorSetCollTree(RpWorldSector *worldSector, 
                                   RpCollTree *collTree);
/*
 *  Geometries
 */

RWEXPORT RpGeometry* RWAPI
RpCollisionGeometryDestroyData(RpGeometry *geometry);

RWEXPORT RwBool RWAPI
RpCollisionGeometryQueryData(RpGeometry *geometry);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
RWEXPORT RpCollTree* RWAPI
RpCollisionGeometryGetCollTree(RpGeometry *geometry);
#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

RWEXPORT RpGeometry* RWAPI
_rpCollisionGeometrySetCollTree(RpGeometry *geometry, 
                                RpCollTree *collTree);


#ifdef    __cplusplus
}
#endif /* __cplusplus */

/* RWPUBLICEND */

#endif /* COLLDATA_H */
