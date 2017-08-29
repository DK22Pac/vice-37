/***************************************************************************
 *                                                                         *
 * Module  : babinwor.h                                                    *
 *                                                                         *
 * Purpose : Binary world handling functions.                              *
 *                                                                         *
 **************************************************************************/

#ifndef RWBINWOR_H
#define RWBINWOR_H

/****************************************************************************
 Includes
 */

#include "../src/rwcore.h"
#include "baworld.h"

/****************************************************************************
 Defines
 */

/* RWPUBLIC */
/****************************************************************************
 Global types
 */

/* Binary Representation
 *
 */
typedef struct RpWorldChunkInfoSector RpWorldSectorChunkInfo;
typedef struct RpWorldChunkInfoSector _rpWorldSector;

#if (!defined(DOXYGEN))
struct RpWorldChunkInfoSector
{
    RwInt32 matListWindowBase;
    RwInt32 numTriangles;
    RwInt32 numVertices;
    RwV3d inf;
    RwV3d sup;
    RwBool collSectorPresent;   /* unused but retains same struct size */
    RwBool unused;
};


typedef struct RpPlaneSectorChunkInfo RpPlaneSectorChunkInfo;
typedef struct RpPlaneSectorChunkInfo _rpPlaneSector;

struct RpPlaneSectorChunkInfo
{
    RwInt32 type;
    RwReal value;    
    RwBool leftIsWorldSector;
    RwBool rightIsWorldSector;
    RwReal leftValue;
    RwReal rightValue;
};

typedef struct RpWorldChunkInfo RpWorldChunkInfo;
typedef struct RpWorldChunkInfo _rpWorld;

struct RpWorldChunkInfo
{
    RwBool rootIsWorldSector;

    RwV3d invWorldOrigin;

    RwInt32 numTriangles;
    RwInt32 numVertices;
    RwInt32 numPlaneSectors;
    RwInt32 numWorldSectors;
    RwInt32 colSectorSize;    

    RwInt32 format;  /* Flags about the world */

    /* Added in 34003 */
    RwBBox  boundingBox;
};

typedef struct rpWorldChunkInfo34000 rpWorldChunkInfo34000;

struct rpWorldChunkInfo34000
{
    RwBool rootIsWorldSector;

    RwV3d invWorldOrigin;

    RwSurfaceProperties surfaceProps;

    RwInt32 numTriangles;
    RwInt32 numVertices;
    RwInt32 numPlaneSectors;
    RwInt32 numWorldSectors;
    RwInt32 colSectorSize;    

    RwInt32 format;  /* Flags about the world */
};
#endif /* (!defined(DOXYGEN)) */

/* RWPUBLICEND */

/****************************************************************************
 Global Variables 
 */

/* RWPUBLIC */
/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* RWPUBLICEND */
/* Initialisation/termination */
RWEXPORT void* RWAPI _rpBinaryWorldOpen(void *instance,
                                RwInt32 offset,
                                RwInt32 size);
RWEXPORT void* RWAPI _rpBinaryWorldClose(void *instance,
                                 RwInt32 offset,
                                 RwInt32 size);

RWEXPORT RwStream* RWAPI _rpReadWorldRights(RwStream *s, RwInt32 len, void *obj,
                                    RwInt32 off, RwInt32 size);
RWEXPORT RwStream* RWAPI _rpWriteWorldRights(RwStream *s, RwInt32 len, const void *obj,
                                     RwInt32 off, RwInt32 size);
RWEXPORT RwInt32 RWAPI _rpSizeWorldRights(const void *obj, RwInt32 off, RwInt32 size);

RWEXPORT RwStream* RWAPI _rpReadSectRights(RwStream *s, RwInt32 len, void *obj,
                                   RwInt32 off, RwInt32 size);
RWEXPORT RwStream* RWAPI _rpWriteSectRights(RwStream *s, RwInt32 len, const void *obj,
                                    RwInt32 off, RwInt32 size);
RWEXPORT RwInt32 RWAPI _rpSizeSectRights(const void *obj, RwInt32 off, RwInt32 size);

/* RWPUBLIC */
/* Binary format */
RWEXPORT RwUInt32 RWAPI RpWorldStreamGetSize(const RpWorld *world);
RWEXPORT RpWorld* RWAPI RpWorldStreamRead(RwStream *stream);
RWEXPORT const RpWorld* RWAPI RpWorldStreamWrite(const RpWorld *world,
                                         RwStream *stream);
RWEXPORT RpWorldSectorChunkInfo* RWAPI
_rpWorldSectorChunkInfoRead(RwStream *stream,
                            RpWorldSectorChunkInfo *worldSectorChunkInfo,
                            RwInt32 *bytesRead);
RWEXPORT RpPlaneSectorChunkInfo* RWAPI
_rpPlaneSectorChunkInfoRead(RwStream *stream,
                            RpPlaneSectorChunkInfo *planeSectorChunkInfo,
                            RwInt32 *bytesRead);
RWEXPORT RpWorldChunkInfo* RWAPI
_rpWorldChunkInfoRead(RwStream *stream,
                      RpWorldChunkInfo *worldChunkInfo,
                      RwInt32 *bytesRead);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RpWorldSectorChunkInfoRead(stream, worldSectorChunkInfo, bytesRead) \
       _rpWorldSectorChunkInfoRead(stream, worldSectorChunkInfo, bytesRead)

#define RpPlaneSectorChunkInfoRead(stream, planeSectorChunkInfo, bytesRead) \
       _rpPlaneSectorChunkInfoRead(stream, planeSectorChunkInfo, bytesRead)

#define RpWorldChunkInfoRead(stream, worldChunkInfo, bytesRead) \
       _rpWorldChunkInfoRead(stream, worldChunkInfo, bytesRead)

/* RWPUBLICEND */

#endif /* RWBINWOR_H */
