/***************************************************************************
 *                                                                         *
 * Module  : basync.h                                                      *
 *                                                                         *
 * Purpose : Lighting a world                                              *
 *                                                                         *
 **************************************************************************/

#ifndef RWSYNC_H
#define RWSYNC_H

/****************************************************************************
 Includes
 */

#include "baframe.h"

/****************************************************************************
 Defines
 */

/****************************************************************************
 Global Types
 */

/****************************************************************************
 Function prototypes
 */

/* RWPUBLIC */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */
    
/* Sync all the dirty frames */
RWEXPORT RwBool RWAPI _rwFrameSyncDirty(void);

/* Syncing the LTMs in a hierarchy */
RWEXPORT void RWAPI _rwFrameSyncHierarchyLTM(RwFrame *frame);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RWSYNC_H */
