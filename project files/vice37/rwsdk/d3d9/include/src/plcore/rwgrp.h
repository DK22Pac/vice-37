/***************************************************************************
 *                                                                         *
 * Module  : rwgrp.h                                                       *
 *                                                                         *
 * Purpose : Binary file group handling                                    *
 *                                                                         *
 **************************************************************************/

#ifndef RWBRP_H
#define RWGRP_H

/****************************************************************************
 Includes
 */

#include "batypes.h"
#include "bastream.h"
#include "bamemory.h"

/* RWPUBLIC */

/****************************************************************************
 Defines
 */
#define rwCHUNKGROUPMAXNAME          32

#define rwCHUNKGROUPVERSION          0x01

/****************************************************************************
 Global Types
 */

typedef struct RwChunkGroup RwChunkGroup;

#ifndef RWADOXYGENEXTERNAL
/**
 * \ingroup rwchunkgroup
 * \struct RwChunkGroup
 * Holds the RenderWare stream group data.
 */
#endif /* RWADOXYGENEXTERNAL */
struct RwChunkGroup
{
    RwChar      name[rwCHUNKGROUPMAXNAME + 1];  /**< Name identifier for the group. */
};


/* RWPUBLICEND */

typedef struct rwChunkGroupGlobals rwChunkGroupGlobals;
struct rwChunkGroupGlobals
{
    RwFreeList         *groupFList;
};

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

/*
 * Internal functions.
 */

RWEXPORT void* RWAPI
_rwChunkGroupOpen(void *instance,
             RwInt32 __RWUNUSED__ offset ,
             RwInt32 __RWUNUSED__ size );

RWEXPORT void* RWAPI
_rwChunkGroupClose(void *instance,
             RwInt32 __RWUNUSED__ offset ,
             RwInt32 __RWUNUSED__ size );

/* RWPUBLIC */

/*
 * API Functions.
 */
RWEXPORT void RWAPI
RwChunkGroupSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

RWEXPORT RwChunkGroup* RWAPI
RwChunkGroupCreate( void );

RWEXPORT RwBool RWAPI
RwChunkGroupDestroy( RwChunkGroup *grp );

RWEXPORT RwChunkGroup* RWAPI
RwChunkGroupBeginStreamRead( RwStream *stream );

RWEXPORT RwChunkGroup* RWAPI
RwChunkGroupEndStreamRead( RwChunkGroup *grp,  RwStream *stream );

RWEXPORT const RwChunkGroup* RWAPI
RwChunkGroupBeginStreamWrite(const RwChunkGroup *grp, RwStream *stream );

RWEXPORT const RwChunkGroup* RWAPI
RwChunkGroupEndStreamWrite(const RwChunkGroup *grp, RwStream *stream);

RWEXPORT RwUInt32 RWAPI
RwChunkGroupStreamGetSize(const RwChunkGroup *grp);

RWEXPORT RwChunkGroup* RWAPI
RwChunkGroupSetName( RwChunkGroup *grp, const RwChar * name);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RWGRP_H */

