/***************************************************************************
 *                                                                         *
 * Module  : batkbin.h                                                     *
 *                                                                         *
 * Purpose : Binary tk module handling functions.                          *
 *                                                                         *
 **************************************************************************/

#ifndef RWTKBIN_H
#define RWTKBIN_H

/****************************************************************************
 Includes
 */

#include "batkreg.h"
#include "bastream.h"

/****************************************************************************
 Defines
 */

/****************************************************************************
 Global types
 */

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

/* Plugin binary stream stuff */
RWEXPORT RwInt32 RWAPI _rwPluginRegistryAddPluginStream(
                   RwPluginRegistry *reg,
                   RwUInt32 pluginID,
                   RwPluginDataChunkReadCallBack readCB,
                   RwPluginDataChunkWriteCallBack writeCB,
                   RwPluginDataChunkGetSizeCallBack getSizeCB);
RWEXPORT RwInt32 RWAPI _rwPluginRegistryAddPlgnStrmlwysCB(
                   RwPluginRegistry *reg,
                   RwUInt32 pluginID,
                   RwPluginDataChunkAlwaysCallBack alwaysCB);
RWEXPORT RwInt32 RWAPI _rwPluginRegistryAddPlgnStrmRightsCB(
                   RwPluginRegistry *reg,
                   RwUInt32 pluginID,
                   RwPluginDataChunkRightsCallBack rightsCB);
RWEXPORT const RwPluginRegistry* RWAPI _rwPluginRegistryReadDataChunks(const RwPluginRegistry *reg,
                                                              RwStream *stream,
                                                              void *object);
RWEXPORT const RwPluginRegistry* RWAPI _rwPluginRegistryWriteDataChunks(const RwPluginRegistry *reg,
                                                               RwStream *stream,
                                                               const void *object);
RWEXPORT const RwPluginRegistry* RWAPI _rwPluginRegistrySkipDataChunks(const RwPluginRegistry * reg,
                                                              RwStream * stream);
RWEXPORT RwInt32 RWAPI _rwPluginRegistryGetSize(const RwPluginRegistry *reg, const void *object);
RWEXPORT const RwPluginRegistry* RWAPI _rwPluginRegistryInvokeRights(const RwPluginRegistry *reg,
                                                             RwUInt32 id,
                                                             void *obj,
                                                             RwUInt32 extraData);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* Compatibility macros */

#define rwPluginRegistryAddPluginStream(reg, pluginID, readCB, writeCB, getSizeCB) \
       _rwPluginRegistryAddPluginStream(reg, pluginID, readCB, writeCB, getSizeCB)
#define rwPluginRegistryAddPluginStreamAlwaysCB(reg, pluginID, alwaysCB) \
       _rwPluginRegistryAddPlgnStrmlwysCB(reg, pluginID, alwaysCB)
#define rwPluginRegistryReadDataChunks(reg, stream, object) \
       _rwPluginRegistryReadDataChunks(reg, stream, object)
#define rwPluginRegistryWriteDataChunks(reg, stream, object) \
       _rwPluginRegistryWriteDataChunks(reg, stream, object)
#define rwPluginRegistrySkipDataChunks(reg, stream) \
       _rwPluginRegistrySkipDataChunks(reg, stream)
#define rwPluginRegistryGetSize(reg, object) \
       _rwPluginRegistryGetSize(reg, object)


/* RWPUBLICEND */

#endif /* RWTKBIN_H */
