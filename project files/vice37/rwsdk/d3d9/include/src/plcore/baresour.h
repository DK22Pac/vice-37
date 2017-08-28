/***************************************************************************
 *                                                                         *
 * Module  : baresour.h                                                    *
 *                                                                         *
 * Purpose : Resource handling                                             *
 *                                                                         *
 **************************************************************************/

#ifndef RWRESOUR_H
#define RWRESOUR_H

/****************************************************************************
 Includes
 */

#include "balibtyp.h"
#include "batypes.h"

/****************************************************************************
 Defines
 */

/* RWPUBLIC */

#define RWRESOURCESGLOBAL(var) (RWPLUGINOFFSET(rwResourcesGlobals,  \
    RwEngineInstance, resourcesModule.globalsOffset)->var)
/* RWPUBLICEND */

/****************************************************************************
 Global Types
 */

/* RWPUBLIC */
#ifndef RWADOXYGENEXTERNAL
/**
 * \ingroup rwresources
 * \struct RwResEntry
 * RwResEntry object. Instanced data block in resources arena.
 * This should be considered an opaque
 * type. Use the RwResEntry API functions to access.
 */
#endif /* RWADOXYGENEXTERNAL */
typedef struct RwResEntry RwResEntry;

#ifndef RWADOXYGENEXTERNAL
/**
 * \ingroup rwresources
 * \ref RwResEntryDestroyNotify type represents the function
 * called from \ref RwResourcesFreeResEntry (and indirectly from
 * \ref RwResourcesEmptyArena) immediately before the memory used by the
 * specified resources entry is released.
 *
 * \param  resEntry   Pointer to the instanced data.
 */
#endif /* RWADOXYGENEXTERNAL */
typedef void        (*RwResEntryDestroyNotify) (RwResEntry * resEntry);

#if (!defined(DOXYGEN))
struct RwResEntry
{
    RwLLLink            link;   /* Node in the list of resource elements */
    RwInt32             size;   /* Size of this node */
    void               *owner;  /* Owner of this node */
    RwResEntry        **ownerRef; /* Pointer to pointer to this (enables de-alloc) */
    RwResEntryDestroyNotify destroyNotify; /* This is called right before destruction */
};
#endif /* (!defined(DOXYGEN)) */

typedef struct rwResources rwResources;

#if (!defined(DOXYGEN))
struct rwResources
{
    RwInt32             maxSize;
    RwInt32             currentSize;
    RwInt32             reusageSize;

    void               *memHeap;

    RwLinkList          entriesA;
    RwLinkList          entriesB;

    RwLinkList         *freeEntries;
    RwLinkList         *usedEntries;
};


typedef struct rwResourcesGlobals rwResourcesGlobals;
struct rwResourcesGlobals
{
    rwResources         res;
};
#endif /* (!defined(DOXYGEN)) */

/* RWPUBLICEND */

/****************************************************************************
 Function prototypes
 */

/* RWPUBLIC */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

/* Setting the resources arena size */
RWEXPORT RwBool RWAPI RwResourcesSetArenaSize(RwUInt32 size);
RWEXPORT RwInt32 RWAPI RwResourcesGetArenaSize(void);
RWEXPORT RwInt32 RWAPI RwResourcesGetArenaUsage(void);
RWEXPORT RwBool RWAPI RwResourcesEmptyArena(void);

/* Allocate */
RWEXPORT RwResEntry* RWAPI RwResourcesAllocateResEntry(void *owner,
                                                RwResEntry **ownerRef,
                                                RwInt32 size,
                                                RwResEntryDestroyNotify
                                                destroyNotify);
/* Deallocate */
RWEXPORT RwBool RWAPI RwResourcesFreeResEntry(RwResEntry * entry);
/* Mark all as unused */
RWEXPORT void RWAPI _rwResourcesPurge(void);
#if ((defined(RWDEBUG)) || (defined(RWSUPPRESSINLINE)))
/* Mark as used */
RWEXPORT RwResEntry* RWAPI RwResourcesUseResEntry(RwResEntry * entry);
#endif /* ((defined(RWDEBUG)) || (defined(RWSUPPRESSINLINE))) */

RWEXPORT RwModuleInfo resourcesModule;

/* RWPUBLICEND */

/* Opening and closing */
RWEXPORT void* RWAPI _rwResourcesOpen(void *instance, RwInt32 offset,
                                     RwInt32 size);
RWEXPORT void* RWAPI _rwResourcesClose(void *instance,
                                      RwInt32 offset, RwInt32 size);

/* RWPUBLIC */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#if ((!defined(RWDEBUG)) && (!defined(RWSUPPRESSINLINE)))
#define RwResourcesUseResEntry(_ntry)                               \
    ((((_ntry)->link.next)?                                         \
          (rwLinkListRemoveLLLink(&((_ntry)->link)),                \
           rwLinkListAddLLLink(RWRESOURCESGLOBAL(res.usedEntries),  \
                               &((_ntry)->link))):                  \
          NULL),                                                    \
     (_ntry))
#endif /* ((!defined(RWDEBUG)) && (!defined(RWSUPPRESSINLINE))) */

/* RWPUBLICEND */

#endif                          /* RWRESOUR_H */
