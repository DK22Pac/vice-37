/***************************************************************************
 *                                                                         *
 * Module  : balist.h                                                      *
 *                                                                         *
 * Purpose : list handling for engine                                      *
 *                                                                         *
 **************************************************************************/

#ifndef RWLIST_H
#define RWLIST_H

/****************************************************************************
 Includes
 */

#include "batypes.h"

/****************************************************************************
 Defines
 */

#define SLIST_STARTSIZE 20

/* RWPUBLIC */
/****************************************************************************
 Global Types
 */

typedef struct RwSList RwSList;

#if (!defined(DOXYGEN))
struct RwSList
{
    RwUInt8    *listElements;
    RwInt32     numElementsFilled;
    RwInt32     numElementsAlloced;
    RwInt32     entrySize;
};
#endif /* (!defined(DOXYGEN) */


/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* SList functions */
RWEXPORT RwSList* RWAPI _rwSListCreate(RwInt32 size, RwUInt32 hint);
RWEXPORT RwBool RWAPI _rwSListDestroy(RwSList *sList);
RWEXPORT RwBool RWAPI _rwSListDestroyArray(RwUInt8 *array);
RWEXPORT void RWAPI _rwSListDestroyEndEntries(RwSList *sList, RwInt32 amount);
RWEXPORT RwBool RWAPI _rwSListDestroyEntry(RwSList *sList, RwInt32 entry);
RWEXPORT void RWAPI _rwSListEmpty(RwSList *sList);
RWEXPORT void* RWAPI _rwSListGetArray(RwSList *sList);
RWEXPORT void* RWAPI _rwSListGetEntry(RwSList *sList, RwInt32 entry);
RWEXPORT void* RWAPI _rwSListGetNewEntry(RwSList *sList, RwUInt32 hint);
RWEXPORT void* RWAPI _rwSListGetNewEntries(RwSList *sList, RwInt32 entry,
                                          RwUInt32 hint);
RWEXPORT RwInt32 RWAPI _rwSListGetNumEntries(const RwSList *sList);
RWEXPORT RwBool RWAPI _rwSListReleaseArray(RwSList *sList);
RWEXPORT void* RWAPI _rwSListToArray(RwSList *sList);
RWEXPORT void* RWAPI _rwSListGetBegin(RwSList *sList);
RWEXPORT void* RWAPI _rwSListGetEnd(RwSList *sList);


#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* Comparibility macros */

#define rwSListCreate(size, hint) \
       _rwSListCreate(size, hint)
#define rwSListDestroy(sList) \
       _rwSListDestroy(sList)
#define rwSListDestroyArray(array) \
       _rwSListDestroyArray(array)
#define rwSListDestroyEndEntries(sList, amount) \
       _rwSListDestroyEndEntries(sList, amount)
#define rwSListDestroyEntry(sList, entry) \
       _rwSListDestroyEntry(sList, entry)
#define rwSListEmpty(sList) \
       _rwSListEmpty(sList)
#define rwSListGetArray(sList) \
       _rwSListGetArray(sList)
#define rwSListGetEntry(sList, entry) \
       _rwSListGetEntry(sList, entry)
#define rwSListGetNewEntry(sList, hint) \
       _rwSListGetNewEntry(sList, hint)
#define rwSListGetNewEntries(sList, entry, hint) \
       _rwSListGetNewEntries(sList, entry, hint)
#define rwSListGetNumEntries(sList) \
       _rwSListGetNumEntries(sList)
#define rwSListReleaseArray(sList) \
       _rwSListReleaseArray(sList)
#define rwSListToArray(sList) \
       _rwSListToArray(sList)
#define rwSListGetBegin(sList) \
       _rwSListGetBegin(sList)
#define rwSListGetEnd(sList) \
       _rwSListGetEnd(sList)

/* RWPUBLICEND */

#endif /* RWLIST_H */
