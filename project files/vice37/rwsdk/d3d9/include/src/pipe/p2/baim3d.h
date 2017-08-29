/***************************************************************************
 *                                                                         *
 *  IM3DH                                                                  *
 *                                                                         *
 * Module  : baim3d.h                                                      *
 *                                                                         *
 * Purpose : See baim3d.c                                                  *
 *                                                                         *
 **************************************************************************/

#ifndef BAIM3D_H
#define BAIM3D_H

/****************************************************************************
 Includes
 */

#include "../../plcore/batypes.h"
#include "../../plcore/baimmedi.h"
#include "../../plcore/bamatrix.h"
#include "../../../driver/d3d9/drvmodel.h"

#include "p2core.h"
#include "d3d9/pip2model.h"
#include "p2stdcls.h"
#include "p2renderstate.h"

/****************************************************************************
 Global Defines
 */

/* RWPUBLIC */

/**
 * \ingroup rwim3d
 * RwIm3DTransformFlags
 *  The bit-field type  RwIm3DTransformFlags
 * specifies options available for controlling execution of the 3D immediate
 * mode pipeline (see API function \ref RwIm3DTransform):*/
enum RwIm3DTransformFlags
{
    rwIM3D_VERTEXUV      = 1,   /**<Texture coordinates in source vertices should be used */
    rwIM3D_ALLOPAQUE     = 2,   /**<All source vertices are opaque (alpha is 255) */
    rwIM3D_NOCLIP        = 4,   /**<No clipping should be performed on the geometry (the
                                 * app may know it is all onscreen or within the guard band clipping
                                 * region for the current hardware, so clipping can be skipped) */
    rwIM3D_VERTEXXYZ     = 8,   /**<Vertex positions */
    rwIM3D_VERTEXRGBA    = 16,  /**<Vertex color */

    rwIM3DTRANSFORMFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwIm3DTransformFlags RwIm3DTransformFlags;


/* RWPUBLICEND */

/****************************************************************************
 Global Types
 */

/* MODULE REGISTRATION */

/* RWPUBLIC */

typedef struct rwIm3DPool            rwIm3DPool;
typedef struct rwImmediGlobals       rwImmediGlobals;
typedef struct rwIm3DRenderPipelines rwIm3DRenderPipelines;
typedef struct _rwIm3DPoolStash       _rwIm3DPoolStash;

#if (0 && defined(SKY2))
typedef struct rwIm3DVertexCache     RwIm3DVertexCache;
#endif /* (0&& defined(SKY2)) */

/* complete information to reconstruct post-transform Im3D "mesh" packet */

#if (!defined(DOXYGEN))
struct _rwIm3DPoolStash
{
    RwUInt32                 flags;    /* rwIM3D_VERTEXUV, rwIM3D_ALLOPAQUE, rwIM3D_NOCLIP etc */
    RwMatrix                *ltm;      /* world-space frame of the vertices, if they have one */
    RwUInt32                 numVerts;
    RxObjSpace3DVertex      *objVerts;
    RxCamSpace3DVertex      *camVerts;
    RxScrSpace2DVertex      *devVerts;
    RxMeshStateVector       *meshState;
    RxRenderStateVector     *renderState;
    RxPipeline              *pipeline;
    RwPrimitiveType          primType;
    RxVertexIndex           *indices;
    RwUInt32                 numIndices;
};

/* Used as a cache of transformed vertices */
struct rwIm3DPool
{
    RwUInt16         numElements; /* could become RwUInt32 nowadays */
    RwUInt16         pad;         /* alignment padding */
    void            *elements;    /* the original array of verts (or whatever...) - referenced not copied */
    RwInt32          stride;      /* the stride of the element */
    _rwIm3DPoolStash  stash;
};

struct rwIm3DRenderPipelines
{
    /* One Im3D render pipeline pointer per rwPRIMTYPE
     * (several pointers may point to the same pipeline though) */
    RxPipeline *triList;
    RxPipeline *triFan;
    RxPipeline *triStrip;
    RxPipeline *lineList;
    RxPipeline *polyLine;
    RxPipeline *pointList;
};

struct rwImmediGlobals
{
    RxPipeline           *im3DTransformPipeline;
    rwIm3DRenderPipelines im3DRenderPipelines;

    /* Platforms that have their own non-generic pipelines
     * (OPENGL, D3D8, SKY2, KAMUI2, DOLPHIN) put them here: */
    RxPipeline           *platformIm3DTransformPipeline;
    rwIm3DRenderPipelines platformIm3DRenderPipelines;

#if (defined(SKY2_DRVMODEL_H))
    /* The triangle PS2All render pipe automatically
     * calls this PS2AllMat pipeline: */
    RxPipeline           *ps2AllMatIm3DTrianglePipeline;
    /* The line PS2All render pipe automatically
     * calls this PS2AllMat pipeline: */
    RxPipeline           *ps2AllMatIm3DLinePipeline;
#endif /* (defined(SKY2_DRVMODEL_H)) */

    rwIm3DPool   curPool;              /* The current cache of transformed vertices */
};
#endif /* (!defined(DOXYGEN)) */

/* RWPUBLICEND */

/****************************************************************************
 Function prototypes
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

RWEXPORT void* RWAPI _rwIm3DOpen( void *instance, RwInt32 offset, RwInt32 size);
RWEXPORT void* RWAPI _rwIm3DClose(void *instance, RwInt32 offset, RwInt32 size);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/* RWPUBLIC */

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

RWEXPORT rwIm3DPool* RWAPI _rwIm3DGetPool( void );

RWEXPORT void* RWAPI RwIm3DTransform(RwIm3DVertex *pVerts, RwUInt32 numVerts,
                              RwMatrix *ltm, RwUInt32 flags);
RWEXPORT RwBool RWAPI RwIm3DEnd(void);

RWEXPORT RwBool RWAPI RwIm3DRenderLine(RwInt32 vert1, RwInt32 vert2);
RWEXPORT RwBool RWAPI RwIm3DRenderTriangle(RwInt32 vert1, RwInt32 vert2,
                                   RwInt32 vert3);
RWEXPORT RwBool RWAPI RwIm3DRenderIndexedPrimitive(RwPrimitiveType primType,
                                           RwImVertexIndex *indices,
                                           RwInt32 numIndices);
RWEXPORT RwBool RWAPI RwIm3DRenderPrimitive(RwPrimitiveType primType);

RWEXPORT RxPipeline* RWAPI RwIm3DGetTransformPipeline(void);
RWEXPORT RxPipeline* RWAPI RwIm3DGetRenderPipeline(   RwPrimitiveType  primType);
RWEXPORT RxPipeline* RWAPI RwIm3DSetTransformPipeline(RxPipeline *pipeline);
RWEXPORT RxPipeline* RWAPI RwIm3DSetRenderPipeline(   RxPipeline *pipeline,
                                              RwPrimitiveType primType);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/* RWPUBLICEND */

#endif /* BAIM3D_H */

