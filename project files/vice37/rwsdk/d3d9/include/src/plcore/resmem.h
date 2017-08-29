/***************************************************************************
 *                                                                         *
 * Module  : resmem.h                                                      *
 *                                                                         *
 * Purpose : Resource memory heap allocator                                *
 *                                                                         *
 **************************************************************************/

#ifndef RESMEM_H
#define RESMEM_H

/****************************************************************************
 Includes
 */

#include "batypes.h"

/****************************************************************************
 Defines
 */

/****************************************************************************
 Global Types
 */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

/* Init and de-init */
RWEXPORT RwBool RWAPI _rwResHeapInit(void *resHeap, RwUInt32 size);
RWEXPORT RwBool RWAPI _rwResHeapClose(void *resHeap);

/* Allocating and freeing memory */
RWEXPORT void* RWAPI _rwResHeapAlloc(void *resHeap, RwUInt32 size);
RWEXPORT void* RWAPI _rwResHeapCalloc(void *resHeap, RwUInt32 num, RwUInt32 size);
RWEXPORT void* RWAPI _rwResHeapRealloc(void *memory, RwUInt32 size);
RWEXPORT void RWAPI _rwResHeapFree(void *memory);

/* Usage statistics */
RWEXPORT RwBool RWAPI _rwResHeapGetStats(void     *resHeap,
                                   RwUInt32 *totalAllocated, 
                                   RwUInt32 *totalFree,
                                   RwUInt32 *largestAllocated,
                                   RwUInt32 *largestFree,
                                   RwUInt32 *smallestAllocated,
                                   RwUInt32 *smallestFree); 

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RESMEM_H */
