/***************************************************************************
 *                                                                         *
 * Module  : palquant.h                                                        *
 *                                                                         *
 * Purpose :                                                               *
 *                                                                         *
 **************************************************************************/

#ifndef PALQUANT_H
#define PALQUANT_H

/****************************************************************************
 Includes
 */
#include "baimage.h"

/* RWPUBLIC */

/****************************************************************************
 Defines
 */

#define RWPALQUANT_MAXDEPTH 8
#define RWPALQUANT_MAXCOLOR (1<<RWPALQUANT_MAXDEPTH)

/****************************************************************************
 Global Types
 */

/**
 * \ingroup rwpalquant
 * \struct RwPalQuant
 * This opaque type is a structure that stores working data for the palette
 * quantization functions. This contains the color quantization tree, which
 * has a maximum depth set globally by \ref RwPalQuantSetMaxDepth.
 *
 * \see RwPalQuantInit
 * \see RwPalQuantAddImage
 * \see RwPalQuantResolvePalette
 * \see RwPalQuantMatchImage
 * \see RwPalQuantTerm
 */
typedef struct RwPalQuant RwPalQuant;

#if (!defined(DOXYGEN))

typedef struct _rwPalQuantRGBABox _rwPalQuantRGBABox;
typedef struct _rwPalQuantOctNode _rwPalQuantOctNode;
typedef struct _rwPalQuantLeafNode _rwPalQuantLeafNode;
typedef struct _rwPalQuantBranchNode _rwPalQuantBranchNode;

struct _rwPalQuantRGBABox
{
    RwInt32 col0[4];    /* min value, inclusive */
    RwInt32 col1[4];    /* max value, exclusive */
};

struct _rwPalQuantLeafNode
{
    /* Represents stats for both true leaf nodes and also branch nodes */
    RwReal      weight;     /* Accumulated weight */
    RwRGBAReal  ac;         /* Accumulated (weight * color) */
    RwReal      var;        /* Weight * variance */
    RwUInt8     palIndex;
};

struct _rwPalQuantBranchNode
{
    _rwPalQuantOctNode *dir[16];
};

struct _rwPalQuantOctNode
{
    _rwPalQuantLeafNode   Leaf;
    _rwPalQuantBranchNode Branch;
};

struct RwPalQuant
{
    _rwPalQuantRGBABox  Mcube[RWPALQUANT_MAXCOLOR];
    RwReal              Mvv[RWPALQUANT_MAXCOLOR];
    _rwPalQuantLeafNode Mvol[RWPALQUANT_MAXCOLOR];
    _rwPalQuantOctNode  *root;                    
    RwFreeList          *cubefreelist;            
};

#endif /* (!defined(DOXYGEN)) */

/****************************************************************************
 Function prototypes
 */


#ifdef    __cplusplus
extern          "C"
{
#endif         /* __cplusplus */

RWEXPORT void RWAPI
RwPalQuantSetMaxDepth(RwUInt32 depth);

RWEXPORT RwUInt32 RWAPI
RwPalQuantGetMaxDepth(void);

RWEXPORT RwBool RWAPI
RwPalQuantInit(RwPalQuant *pq);

RWEXPORT void RWAPI
RwPalQuantTerm(RwPalQuant *pq);


RWEXPORT void RWAPI
RwPalQuantAddImage(RwPalQuant *pq, RwImage *img, RwReal weight);


RWEXPORT RwInt32 RWAPI
RwPalQuantResolvePalette(RwRGBA *palette, RwInt32 maxcols, RwPalQuant *pq);


RWEXPORT void RWAPI
RwPalQuantMatchImage(RwUInt8 *dstpixels, RwInt32 dststride, RwInt32 dstdepth,
                      RwBool dstPacked, RwPalQuant *pq, RwImage *img);

#ifdef    __cplusplus
}
#endif         /* __cplusplus */

/* RWPUBLICEND */

#endif /* PALQUANT_H */
