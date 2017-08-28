/**
 *
 * RenderStateVectors in custom pipelines
 * 
 * Copyright (c) Criterion Software Limited
 */
/****************************************************************************
 *                                                                          *
 *  Module  :   p2renderstate.h                                             *
 *                                                                          *
 *  Purpose :   See p2renderstate.c                                         *
 *                                                                          *
 ****************************************************************************/

#ifndef P2RENDERSTATE_H
#define P2RENDERSTATE_H

#include "../../plcore/bacolor.h"
#include "../../baraster.h" /* For RwRaster */
#include "../../plcore/baimmedi.h" /* For renderstates */
#include "../../../driver/d3d9/drvmodel.h"

/****************************************************************************
 Global Types
 */

/* RWPUBLIC */

/**
 * \ingroup rwcoregeneric
 *  RxRenderStateFlag 
 *  Flags used in the \ref RxRenderStateVector structure */
enum RxRenderStateFlag
{
    rxRENDERSTATEFLAG_TEXTUREPERSPECTIVE   = 0x00000001, /**<Perspective texturing is to be enabled */
    rxRENDERSTATEFLAG_ZTESTENABLE          = 0x00000002, /**<Z-Buffer testing is to be performed */
    rxRENDERSTATEFLAG_ZWRITEENABLE         = 0x00000004, /**<Z-Buffer writing is to be enabled */
    rxRENDERSTATEFLAG_VERTEXALPHAENABLE    = 0x00000008, /**<Vertex alpha is to be enabled */
    rxRENDERSTATEFLAG_FOGENABLE            = 0x00000010, /**<Fog is to be enabled */
    rxRENDERSTATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RxRenderStateFlag RxRenderStateFlag;

typedef struct RxRenderStateVector RxRenderStateVector;
/**
 * \ingroup rwcoregeneric
 * \struct RxRenderStateVector
 * Structure describing a render-state vector,
 * used by the RxClRenderState cluster */
struct RxRenderStateVector
{
    RwUInt32             Flags;         /**< A load of the boolean renderstate options */
    RwShadeMode          ShadeMode;     /**< Flat or Gouraud currently */
    RwBlendFunction      SrcBlend;      /**< Src  alpha, 1-src  alpha, etc */
    RwBlendFunction      DestBlend;     /**< Dest alpha, 1-dest alpha, etc */
    RwRaster            *TextureRaster; /**< texture raster */
    RwTextureAddressMode AddressModeU;  /**< U addressing mode - WRAP, MIRROR, CLAMP, BORDER */
    RwTextureAddressMode AddressModeV;  /**< V addressing mode - WRAP, MIRROR, CLAMP, BORDER */
    RwTextureFilterMode  FilterMode;    /**< filtering mode - combos of NEAREST LINEAR MIP */
    RwRGBA               BorderColor;   /**< Border color for texturing address mode border */
    RwFogType            FogType;       /**< Select the type of fogging to use */
    RwRGBA               FogColor;      /**< Color used for fogging */
};

#if (!defined(RxRenderStateVectorAssign))
#define RxRenderStateVectorAssign(_target, _source)            \
    ( *(_target) = *(_source) )
#endif /* (!defined(RxRenderStateVectorAssign)) */


/* RWPUBLICEND */

/****************************************************************************
 Global Prototypes
 */

/* RWPUBLIC */

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

RWEXPORT RxRenderStateVector* RWAPI RxRenderStateVectorSetDefaultRenderStateVector(RxRenderStateVector *rsvp);
RWEXPORT const RxRenderStateVector* RWAPI RxRenderStateVectorGetDefaultRenderStateVector(void);
RWEXPORT RxRenderStateVector* RWAPI RxRenderStateVectorCreate(RwBool current);
RWEXPORT void RWAPI RxRenderStateVectorDestroy(RxRenderStateVector *rsvp);
RWEXPORT RxRenderStateVector* RWAPI RxRenderStateVectorLoadDriverState(RxRenderStateVector *rsvp);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

/* RWPUBLICEND */

#endif /* RWPIP2_H */


