/***************************************************************************
 *                                                                         *
 * Module  : babintex.h                                                    *
 *                                                                         *
 * Purpose : Binary texture handling functions.                            *
 *                                                                         *
 **************************************************************************/

#ifndef RWBINTEX_H
#define RWBINTEX_H

/****************************************************************************
 Includes
 */

#include "batextur.h"
#include "plcore/bastream.h"

/****************************************************************************
 Defines
 */

/* RWPUBLIC */
/****************************************************************************
 Global types
 */
typedef struct rpTextureChunkInfo RwTextureChunkInfo;

#if (!defined(DOXYGEN))
struct rpTextureChunkInfo
{
    RwTextureFilterMode filtering;
    RwTextureAddressMode addressingU;
    RwTextureAddressMode addressingV;
};
#endif /* (!defined(DOXYGEN)) */

/* Bit flags defining properties of textures when stream */
enum RwTextureStreamFlags
{
    rwNATEXTURESTREAMFLAG = 0x00,
    rwTEXTURESTREAMFLAGSUSERMIPMAPS = 0x01,
    rwTEXTURESTREAMFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwTextureStreamFlags RwTextureStreamFlags;
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

/* RWPUBLIC */
/* Texture binary format */
RWEXPORT RwInt32 RWAPI
RwTextureRegisterPluginStream(RwUInt32 pluginID,
                              RwPluginDataChunkReadCallBack readCB,
                              RwPluginDataChunkWriteCallBack writeCB,
                              RwPluginDataChunkGetSizeCallBack getSizeCB);

RWEXPORT RwInt32 RWAPI
RwTextureSetStreamAlwaysCallBack(RwUInt32 pluginID,
                                 RwPluginDataChunkAlwaysCallBack alwaysCB);

RWEXPORT RwUInt32 RWAPI
RwTextureStreamGetSize(const RwTexture *texture);

RWEXPORT RwTexture* RWAPI
RwTextureStreamRead(RwStream *stream);

RWEXPORT const RwTexture* RWAPI
RwTextureStreamWrite(const RwTexture *texture,
                     RwStream *stream);

/* Texture dictionary binary format */
RWEXPORT RwInt32 RWAPI
RwTexDictionaryRegisterPluginStream(RwUInt32 pluginID,
                                    RwPluginDataChunkReadCallBack readCB,
                                    RwPluginDataChunkWriteCallBack writeCB,
                                    RwPluginDataChunkGetSizeCallBack getSizeCB);

RWEXPORT RwInt32 RWAPI
RwTexDictionarySetStreamAlwaysCallBack(RwUInt32 pluginID,
                                       RwPluginDataChunkAlwaysCallBack alwaysCB);

RWEXPORT RwUInt32 RWAPI
RwTexDictionaryStreamGetSize(const RwTexDictionary *texDict);

RWEXPORT RwTexDictionary* RWAPI
RwTexDictionaryStreamRead(RwStream *stream);

RWEXPORT const RwTexDictionary* RWAPI
RwTexDictionaryStreamWrite(const RwTexDictionary *texDict,
                           RwStream *stream);

RWEXPORT RwTextureChunkInfo* RWAPI
_rwTextureChunkInfoRead(RwStream *stream,
                        RwTextureChunkInfo *textureChunkInfo,
                        RwInt32 *bytesRead);

/* Compatibility macro */

#define  RwTextureChunkInfoRead(_stream, _textureChunkInfo, _bytesRead) \
        _rwTextureChunkInfoRead(_stream, _textureChunkInfo, _bytesRead) 

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif /* RWBINTEX_H */
