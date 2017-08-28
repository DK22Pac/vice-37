/***************************************************************************
 * Module  : baframe.h                                                     *
 *                                                                         *
 * Purpose : frame handling for engine                                     *
 *                                                                         *
 **************************************************************************/

#ifndef RWFRAME_H
#define RWFRAME_H

/****************************************************************************
 Includes
 */

#include "plcore/batype.h"
#include "plcore/bamemory.h"
#include "plcore/bamatrix.h"
#include "plcore/batkreg.h"

/* RWPUBLIC */

/****************************************************************************
 Defines
 */

#if (!defined(RWFRAMESTATICPLUGINSSIZE))
#define RWFRAMESTATICPLUGINSSIZE 0
#endif

#define RWFRAMEALIGNMENT(_frame) \
   (! (((rwFRAMEALIGNMENT)-1) & ((RwUInt32)(_frame))))

/* Type ID */
#define rwFRAME 0

/* dirty flag bits */
#define rwFRAMEPRIVATEHIERARCHYSYNCLTM  0x01
#define rwFRAMEPRIVATEHIERARCHYSYNCOBJ  0x02
#define rwFRAMEPRIVATESUBTREESYNCLTM    0x04
#define rwFRAMEPRIVATESUBTREESYNCOBJ    0x08
#define rwFRAMEPRIVATESTATIC            0x10

/****************************************************************************
 Global Types
 */

#if (!defined(DOXYGEN))
struct RwFrame
{
    RwObject            object;

    RwLLLink            inDirtyListLink;

    /* Put embedded matrices here to ensure they remain 16-byte aligned */
    RwMatrix            modelling;
    RwMatrix            ltm;

    RwLinkList          objectList; /* List of objects connected to a frame */

    struct RwFrame      *child;
    struct RwFrame      *next;
    struct RwFrame      *root;   /* Root of the tree */

#if (RWFRAMESTATICPLUGINSSIZE)
    RWALIGN(RwUInt8             pluginData[RWFRAMESTATICPLUGINSSIZE], rwFRAMEALIGNMENT);
#endif /* defined(RWFRAMESTATICPLUGINSIZE)) */
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rwframe
 * \struct RwFrame 
 * Frame for defining object position and orientation. 
 * This should be considered an opaque type.
 * Use the RwFrame API functions to access.
 */
typedef struct RwFrame RWALIGN(RwFrame, rwFRAMEALIGNMENT);

/**
 * \ingroup rwframe
 * \ref RwFrameCallBack type represents the function 
 * called from \ref RwFrameForAllChildren for all child frames linked to a given frame.  
 * This function should return a pointer to the current frame to indicate success.  
 * The callback may return NULL to terminate further callbacks on the child frames.
 * 
 * \param  frame   Pointer to the current frame, supplied by
 * iterator.
 * \param  data  Pointer to developer-defined data structure.
 *
 * \return Pointer to the current frame, or NULL If not found.
 *
 * \see RwFrameForAllChildren
 *
 */
typedef RwFrame *(*RwFrameCallBack)(RwFrame *frame, void *data);


#define RwFrameGetParentMacro(_f)   ((RwFrame *)rwObjectGetParent(_f))
#if (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ))
#define RwFrameGetParent(_f)    RwFrameGetParentMacro(_f)
#endif

#define RwFrameGetMatrixMacro(_f)   (&(_f)->modelling)
#if (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ))
#define RwFrameGetMatrix(_f)    RwFrameGetMatrixMacro(_f)
#endif


/* RWPUBLICEND */


typedef struct rwFrameGlobals rwFrameGlobals;
struct rwFrameGlobals
{
    RwFreeList         *frames;
};

/****************************************************************************
 Globals (across program)
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

RWEXPORT RwPluginRegistry frameTKList;

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLIC */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */


/* Finding what is attached to a frame */
RWEXPORT RwFrame* RWAPI
RwFrameForAllObjects(RwFrame * frame,
                     RwObjectCallBack callBack,
                     void *data);

/* Matrix operations */
RWEXPORT RwFrame* RWAPI
RwFrameTranslate(RwFrame * frame,
                 const RwV3d * v,
                 RwOpCombineType combine);

RWEXPORT RwFrame* RWAPI
RwFrameRotate(RwFrame * frame,
              const RwV3d * axis,
              RwReal angle,
              RwOpCombineType combine);

RWEXPORT RwFrame* RWAPI
RwFrameScale(RwFrame * frame,
             const RwV3d * v,
             RwOpCombineType combine);

RWEXPORT RwFrame* RWAPI
RwFrameTransform(RwFrame * frame,
                 const RwMatrix * m,
                 RwOpCombineType combine);

RWEXPORT RwFrame* RWAPI
RwFrameOrthoNormalize(RwFrame * frame);

RWEXPORT RwFrame* RWAPI
RwFrameSetIdentity(RwFrame * frame);

/* Cloning */
RWEXPORT RwFrame* RWAPI
RwFrameCloneHierarchy(RwFrame * root);

/* Destruction */
RWEXPORT RwBool RWAPI
RwFrameDestroyHierarchy(RwFrame * frame);

/* Building a frame */
RWEXPORT RwFrame* RWAPI
RwFrameForAllChildren(RwFrame * frame,
                      RwFrameCallBack callBack,
                      void *data);

RWEXPORT RwFrame* RWAPI
RwFrameRemoveChild(RwFrame * child);

RWEXPORT RwFrame* RWAPI
RwFrameAddChild(RwFrame * parent, RwFrame * child);

RWEXPORT RwFrame* RWAPI
RwFrameAddChildNoUpdate(RwFrame *parent, RwFrame *child);

#if ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )
RWEXPORT RwFrame* RWAPI
RwFrameGetParent(const RwFrame * frame);
#endif

/* Getting the root */
RWEXPORT RwFrame* RWAPI
RwFrameGetRoot(const RwFrame * frame);

/* Getting Matrices */
RWEXPORT RwMatrix* RWAPI
RwFrameGetLTM(RwFrame * frame);

#if ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )
RWEXPORT RwMatrix* RWAPI
RwFrameGetMatrix(RwFrame * frame);
#endif

/* Elements */
RWEXPORT RwFrame* RWAPI
RwFrameUpdateObjects(RwFrame * frame);

/* Creating destroying frames */
RWEXPORT void RWAPI
RwFrameSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

RWEXPORT RwFrame* RWAPI
RwFrameCreate(void);

RWEXPORT RwBool RWAPI
RwFrameDestroy(RwFrame * frame);

/* Finding a frames state */
RWEXPORT RwBool RWAPI
RwFrameDirty(const RwFrame * frame);

/* Find the amount of frames in a hierarchy */
RWEXPORT RwInt32 RWAPI
RwFrameCount(RwFrame * frame);

/* static frame functions */
RWEXPORT RwBool RWAPI
_rwFrameSetStaticPluginsSize(RwInt32 size);

RWEXPORT RwBool RWAPI
_rwFrameInit(RwFrame *frame);

RWEXPORT RwBool RWAPI
_rwFrameDeInit(RwFrame *frame);

/* Plugins */
RWEXPORT RwInt32 RWAPI
RwFrameRegisterPlugin(RwInt32 size,
                      RwUInt32 pluginID,
                      RwPluginObjectConstructor constructCB,
                      RwPluginObjectDestructor destructCB,
                      RwPluginObjectCopy copyCB);

RWEXPORT RwInt32 RWAPI
RwFrameGetPluginOffset(RwUInt32 pluginID);

RWEXPORT RwBool RWAPI
RwFrameValidatePlugins(const RwFrame * frame);

/* Cloning */
RWEXPORT RwFrame* RWAPI
_rwFrameCloneAndLinkClones(RwFrame * root);

RWEXPORT
RwFrame* RWAPI
_rwFramePurgeClone(RwFrame *root);

/* RWPUBLICEND */

/* Opening and closing */
RWEXPORT void* RWAPI
_rwFrameClose(void *instance,
              RwInt32 offset,
              RwInt32 size);

RWEXPORT void* RWAPI
_rwFrameOpen(void *instance,
             RwInt32 offset,
                RwInt32 size);

    /* Getting Matrices */
#define _rwFrameGetLTM(f) (&(f)->ltm)

/* RWPUBLIC */
#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif                          /* RWFRAME_H */

