/****************************************************************************
 *                                                                          *
 *  Module  :   p2define.h                                                  *
 *                                                                          *
 *  Purpose :   See p2define.c                                              *
 *                                                                          *
 ****************************************************************************/

#ifndef DEFINEPIPE_H
#define DEFINEPIPE_H

/****************************************************************************
 Includes
 */

#include "p2core.h"

/****************************************************************************
 Global Types
 */

/* RWPUBLIC */

/**
 * \ingroup rwcoregeneric
 * \ref RxNodeOutput 
 * typedef for a reference to an output of a pipeline node */
typedef RwUInt32       *RxNodeOutput;

/**
 * \ingroup rwcoregeneric
 * \ref RxNodeInput 
 *  typedef for a reference to the input of a pipeline node */
typedef RxPipelineNode *RxNodeInput;

/**
 * \ingroup rwcoregeneric
 * \ref RxLockedPipe
 * typedef for a reference to a locked pipeline 
 */
typedef RxPipeline      RxLockedPipe;

/* RWPUBLICEND */

/****************************************************************************
 Global Prototypes
 */

/* RWPUBLIC */

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* RWPUBLICEND */

/* Used in _PropagateDependenciesAndKillDeadPaths() -> _ReqCreate() */

RWEXPORT RwUInt32 RWAPI
PipelineCalcNumUniqueClusters(RxPipeline *pipe);

/* Used in p2dep.c */

RWEXPORT void* RWAPI
StalacTiteAlloc(RwUInt32 size);

RWEXPORT void* RWAPI
StalacMiteAlloc(RwUInt32 size);

/* RWPUBLIC */

/* PIPELINENODE API */

RWEXPORT RxNodeOutput RWAPI
RxPipelineNodeFindOutputByName(RxPipelineNode *node,
                               const RwChar *outputname);

RWEXPORT RxNodeOutput RWAPI
RxPipelineNodeFindOutputByIndex(RxPipelineNode *node,
                                RwUInt32 outputindex);

RWEXPORT RxNodeInput RWAPI
RxPipelineNodeFindInput(RxPipelineNode *node);

RWEXPORT RxNodeDefinition* RWAPI
RxPipelineNodeCloneDefinition(RxPipelineNode *node,
                              RxClusterDefinition *cluster2add);

RWEXPORT RxPipeline* RWAPI
RxPipelineNodeRequestCluster(RxPipeline *pipeline,
                             RxPipelineNode *node,
                             RxClusterDefinition *clusterDef);

RWEXPORT RxPipeline* RWAPI
RxPipelineNodeReplaceCluster(RxPipeline *pipeline,
                             RxPipelineNode *node,
                             RxClusterDefinition *oldClusterDef,
                             RxClusterDefinition *newClusterDef);

RWEXPORT void* RWAPI
RxPipelineNodeGetInitData(RxPipelineNode *node);

RWEXPORT void* RWAPI
RxPipelineNodeCreateInitData(RxPipelineNode *node,
                             RwUInt32 size);

/* PIPELINE MANIPULATION API */

RWEXPORT RxPipeline* RWAPI
RxPipelineClone(RxPipeline *pipeline);

RWEXPORT RxPipelineNode* RWAPI
RxPipelineFindNodeByName(RxPipeline *pipeline,
                         const RwChar *name,
                         RxPipelineNode *start,
                         RwInt32 *nodeIndex);

RWEXPORT RxPipelineNode* RWAPI
RxPipelineFindNodeByIndex(RxPipeline *pipeline,
                          RwUInt32 nodeindex);

RWEXPORT RxLockedPipe* RWAPI
RxPipelineLock(RxPipeline *pipeline);

RWEXPORT RxPipeline* RWAPI
RxLockedPipeUnlock(RxLockedPipe *pipeline);


RWEXPORT RxLockedPipe* RWAPI
RxLockedPipeAddFragment(RxLockedPipe *pipeline,
                        RwUInt32 *firstIndex,
                        RxNodeDefinition *nodeDef0,
                        ...);


RWEXPORT RxPipeline* RWAPI
RxLockedPipeReplaceNode(RxLockedPipe *pipeline,
                        RxPipelineNode *node,
                        RxNodeDefinition *nodeDef);

RWEXPORT RxPipeline* RWAPI
RxLockedPipeDeleteNode(RxLockedPipe *pipeline,
                       RxPipelineNode *node);


RWEXPORT RxPipeline* RWAPI
RxLockedPipeSetEntryPoint(RxLockedPipe *pipeline,
                          RxNodeInput in);


RWEXPORT RxPipelineNode* RWAPI
RxLockedPipeGetEntryPoint(RxLockedPipe *pipeline);


RWEXPORT RxPipeline* RWAPI
RxLockedPipeAddPath(RxLockedPipe *pipeline,
                    RxNodeOutput out,
                    RxNodeInput in);

RWEXPORT RxPipeline* RWAPI
RxLockedPipeDeletePath(RxLockedPipe *pipeline,
                       RxNodeOutput out,
                       RxNodeInput in);


RWEXPORT RxPipeline* RWAPI
RxPipelineInsertDebugNode(RxPipeline *pipeline,
                          RxPipelineNode *before,
                          RxPipelineNode *after,
                          RxNodeDefinition *debugNode);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/* RWPUBLICEND */

#endif /* DEFINEPIPE_H */
