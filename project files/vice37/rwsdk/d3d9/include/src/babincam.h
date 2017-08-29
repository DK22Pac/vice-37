/***************************************************************************
 *                                                                         *
 * Module  : babincam.h                                                    *
 *                                                                         *
 * Purpose : Binary camera handling functions.                             *
 *                                                                         *
 **************************************************************************/

#ifndef RWBINCAM_H
#define RWBINCAM_H

/****************************************************************************
 Includes
 */

#include "bacamera.h"
#include "plcore/bastream.h"

/* A nice high point in the core to make sure these files are parsed by incgen
 * for rwcore.h (found by looking at a generated rwcore.h to see what the last
 * file was - no dependants)
 */
#include "../driver/d3d9/drvmodel.h"
#include "../driver/d3d9/drvfns.h"

/****************************************************************************
 Defines
 */

/* RWPUBLIC */
/****************************************************************************
 Global types
 */

/* Camera stream format */

/**
 * \ingroup rwcamera
 * \ref RwCameraChunkInfo is typedef'd to a structure that holds camera
 * data. This should be considered an opaque type. Use the RwCamera
 * API functions to access it.
 */

typedef struct rwStreamCamera RwCameraChunkInfo;
typedef struct rwStreamCamera rwStreamCamera;

#if (!defined(DOXYGEN))
struct rwStreamCamera
{
    RwV2d viewWindow;
    RwV2d viewOffset;
    RwReal nearPlane, farPlane;
    RwReal fogPlane;
    RwUInt32 projection;
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

/* Camera binary format */
RWEXPORT RwInt32 RWAPI RwCameraRegisterPluginStream(RwUInt32 pluginID,
                                            RwPluginDataChunkReadCallBack readCB,
                                            RwPluginDataChunkWriteCallBack writeCB,
                                            RwPluginDataChunkGetSizeCallBack getSizeCB);
RWEXPORT RwInt32 RWAPI RwCameraSetStreamAlwaysCallBack(
                   RwUInt32 pluginID,
                   RwPluginDataChunkAlwaysCallBack alwaysCB);
RWEXPORT RwUInt32 RWAPI RwCameraStreamGetSize(const RwCamera *camera);
RWEXPORT RwCamera* RWAPI RwCameraStreamRead(RwStream *stream);
extern const RwCamera* RWAPI RwCameraStreamWrite(const RwCamera *camera,
                                           RwStream *stream);
RWEXPORT RwCameraChunkInfo* RWAPI RwCameraChunkInfoRead(RwStream *stream,
                                                 RwCameraChunkInfo *cameraChunkInfo,
                                                 RwInt32 *bytesRead);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */
#endif /* RWBINCAM_H */
