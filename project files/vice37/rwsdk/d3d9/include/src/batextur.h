/*
 * Types for textures
 * Copyright (c) Criterion Software Limited
 */

/***************************************************************************
 *                                                                         *
 * Module  : batextur.h                                                    *
 *                                                                         *
 * Purpose : Texture map handling                                          *
 *                                                                         *
 **************************************************************************/

#ifndef RWTEXTUR_H
#define RWTEXTUR_H

/****************************************************************************
 Includes
 */

#include "plcore/batype.h"
#include "plcore/bamemory.h"
#include "baraster.h"
#include "plcore/baimmedi.h"
#include "baimage.h"

/* RWPUBLIC */

/****************************************************************************
 Defines
 */

/* Type ID */
#define rwTEXDICTIONARY 6

/* Mipmap Name generation - maximum number of RwChar characters which can
 * be appended to the root name.
 */
#define rwTEXTUREMIPMAPNAMECHARS    16

/* We define texture names to be a maximum of 16 ISO chars */
#define rwTEXTUREBASENAMELENGTH     32

#define rwTEXTUREFILTERMODEMASK     0x000000FF
#define rwTEXTUREADDRESSINGUMASK    0x00000F00
#define rwTEXTUREADDRESSINGVMASK    0x0000F000
#define rwTEXTUREADDRESSINGMASK     (rwTEXTUREADDRESSINGUMASK |  \
                                     rwTEXTUREADDRESSINGVMASK)

/****************************************************************************
 Global Types
 */

/**
 * \ingroup rwtexdict
 * \struct RwTexDictionary 
 * is a texture dictionary containing textures. 
 * This should be considered an opaque type.
 * Use the RwTexDictionary API functions to access.
 */
typedef struct RwTexDictionary RwTexDictionary;

#if (!defined(DOXYGEN))
struct RwTexDictionary
{
    RwObject            object; /* Homogeneous type */
    RwLinkList          texturesInDict; /* List of textures in dictionary */
    RwLLLink            lInInstance; /* Link list of all dicts in system */
};
/* Information is entirely device dependent */
#endif /* (!defined(DOXYGEN)) */


/* Parent is the dictionary */

/**
 * \ingroup rwtexture
 * \struct  RwTexture 
 * is a texture object. 
 * This should be considered an opaque type.
 * Use the RwTexture API functions to access.
 */
typedef struct RwTexture RwTexture;

#if (!defined(DOXYGEN))
struct RwTexture
{
    RwRaster           *raster; /** pointer to RwRaster with data */
    RwTexDictionary    *dict;   /* Dictionary this texture is in */
    RwLLLink            lInDictionary; /* List of textures in this dictionary */

    RwChar              name[rwTEXTUREBASENAMELENGTH];  /* Name of the texture */
    RwChar              mask[rwTEXTUREBASENAMELENGTH];  /* Name of the textures mask */

    /* 31 [xxxxxxxx xxxxxxxx vvvvuuuu ffffffff] 0 */
    RwUInt32            filterAddressing; /* Filtering & addressing mode flags */

    RwInt32             refCount; /* Reference count, surprisingly enough */
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rwtexture
 * \ref RwTextureCallBackRead 
 * represents the function used by \ref RwTextureRead to read the specified
 * texture from a disk file. This function should return a pointer to the
 * texture to indicate success.
 * 
 * \param  name   Pointer to a string containing the name of
 * the texture to read.
 *
 * \param  maskName   Pointer to a string containing the name
 * of the mask to read and apply to the texture.
 *
 * \return Pointer to the texture
 *
 * \see RwTextureSetReadCallBack
 * \see RwTextureGetReadCallBack
 */
typedef RwTexture *(*RwTextureCallBackRead)(const RwChar *name,
                                            const RwChar *maskName);

/**
 * \ingroup rwtexture
 * \ref RwTextureCallBackFind
 * represents the function used by \ref RwTextureRead to search for a 
 * texture in memory before attempting to read one from disk. This
 * may involve searching previously loaded texture dictionaries.
 *
 * \param  name   Pointer to a string containing the name of
 * the texture to find.
 *
 * \return Pointer to the texture, or NULL if not found.
 *
 * \see RwTextureSetFindCallBack
 * \see RwTextureGetFindCallBack
 */
typedef RwTexture *(*RwTextureCallBackFind)(const RwChar *name);

/**
 * \ingroup rwtexture
 * \ref RwTextureCallBack
 * represents the function called from \ref RwTexDictionaryForAllTextures
 * for all textures in a given texture dictionary. This function should
 * return the current texture to indicate success. The callback may return
 * NULL to terminate further callbacks on the texture dictionary.
 * 
 * \param  texture   Pointer to the current texture.
 *
 * \param  pData   User-defined data pointer.
 *
 * \return Pointer to the current texture
 *
 * \see RwTexDictionaryForAllTextures
 */
typedef RwTexture *(*RwTextureCallBack)(RwTexture *texture, void *pData);


/**
 * \ingroup rwtexdict
 * \ref RwTexDictionaryCallBack
 * represents the function called from \ref RwTexDictionaryForAllTexDictionaries
 * for all texture dictionaries that currently exist. This function should
 * return the current texture dictionary to indicate success. The callback may
 * return NULL to terminate further callbacks on the texture dictionary. It may
 * safely destroy the current texture dictionary without adversely affecting
 * the iteration process.
 * 
 * \param  dict   Pointer to the current texture dictionary.
 *
 * \param  pData   User-defined data pointer.
 *
 * \return Pointer to the current texture dictionary
 *
 * \see RwTexDictionaryForAllTexDictionaries
 */
typedef RwTexDictionary *(*RwTexDictionaryCallBack)(RwTexDictionary *dict, void *data);


/**
 * \ingroup rwtexture
 * \ref RwTextureCallBackMipmapGeneration 
 * is the callback function supplied to \ref RwTextureSetMipmapGenerationCallBack 
 * and returned from \ref RwTextureGetMipmapGenerationCallBack.
 *
 * The supplied function will be passed a pointer to a raster and an image.
 * The raster is the target for the generated mipmap levels and the image 
 * provides the base for their generation.
 * 
 * \param  raster   Pointer to raster, the target for generated mipmap levels
 * \param  image    Pointer to image, used to generate mipmap levels.
 * 
 * \return
 * Returns a pointer to the raster if successful or NULL if an error occurred.
 * 
 * \see RwTextureSetMipmapGenerationCallBack
 * \see RwTextureGetMipmapGenerationCallBack
 * \see RwTextureSetAutoMipmapping
 * \see RwTextureGetAutoMipmapping
 */
typedef RwRaster *(*RwTextureCallBackMipmapGeneration)(RwRaster * raster,
                                                       RwImage * image);

/**
 * \ingroup rwtexture
 * \ref RwTextureCallBackMipmapName
 * is the callback function supplied to \ref RwTextureSetMipmapNameCallBack and
 * returned from \ref RwTextureGetMipmapNameCallBack.
 *
 * The supplied function will be passed a pointer to a root name, a maskName, a mipmap
 * level and a format. The function returns TRUE if successful and the root name will have been 
 * modified to equal the mipmap name.
 * 
 * \param  name       Pointer to a string containing the root name of the texture. The 
 * mipmap level name is put here.
 * \param  maskName   Pointer to a string containing the root mask name of the texture or
 * NULL if no mask name is required.
 * \param  mipLevel   A value equal to the mipmap level for which the name is required.
 * \param  format     A value describing the mipmapping mode. A combination of the bit
 * flags rwRASTERFORMATMIPMAP and rwRASTERFORMATAUTOMIPMAP.
 * 
 * \return
 * Returns TRUE if the name is generated successfully or FALSE if an error occurred.
 * 
 * \see RwTextureGenerateMipmapName
 * \see RwTextureSetMipmapNameCallBack
 * \see RwTextureGetMipmapNameCallBack
 * \see RwTextureSetAutoMipmapping
 * \see RwTextureGetAutoMipmapping
 */
typedef RwBool (*RwTextureCallBackMipmapName)(RwChar *name,
                                              RwChar *maskName,
                                              RwUInt8 mipLevel,
                                              RwInt32 format);

/****************************************************************************
 <macro/inline functionality
 */

#define RwTextureGetRasterMacro(_tex)                       \
    ((_tex)->raster)

#define RwTextureAddRefMacro(_tex)                          \
    (((_tex)->refCount++), (_tex))

#define RwTextureAddRefVoidMacro(_tex)                      \
MACRO_START                                                 \
{                                                           \
    (_tex)->refCount++;                                     \
}                                                           \
MACRO_STOP

#define RwTextureGetNameMacro(_tex)                         \
    ((_tex)->name)

#define RwTextureGetMaskNameMacro(_tex)                     \
    ((_tex)->mask)

#define RwTextureGetDictionaryMacro(_tex)                   \
    ((_tex)->dict)

#define RwTextureSetFilterModeMacro(_tex, _filtering)                       \
    (((_tex)->filterAddressing =                                            \
      ((_tex)->filterAddressing & ~rwTEXTUREFILTERMODEMASK) |               \
      (((RwUInt32)(_filtering)) &  rwTEXTUREFILTERMODEMASK)),               \
     (_tex))

#define RwTextureGetFilterModeMacro(_tex)                                   \
    ((RwTextureFilterMode)((_tex)->filterAddressing &                       \
                           rwTEXTUREFILTERMODEMASK))

#define RwTextureSetAddressingMacro(_tex, _addressing)                      \
    (((_tex)->filterAddressing =                                            \
      ((_tex)->filterAddressing & ~rwTEXTUREADDRESSINGMASK) |               \
      (((((RwUInt32)(_addressing)) <<  8) & rwTEXTUREADDRESSINGUMASK) |     \
       ((((RwUInt32)(_addressing)) << 12) & rwTEXTUREADDRESSINGVMASK))),    \
     (_tex))

#define RwTextureSetAddressingUMacro(_tex, _addressing)                     \
    (((_tex)->filterAddressing =                                            \
      ((_tex)->filterAddressing & ~rwTEXTUREADDRESSINGUMASK) |              \
      (((RwUInt32)(_addressing) << 8) & rwTEXTUREADDRESSINGUMASK)),         \
     (_tex))

#define RwTextureSetAddressingVMacro(_tex, _addressing)                     \
    (((_tex)->filterAddressing =                                            \
      ((_tex)->filterAddressing & ~rwTEXTUREADDRESSINGVMASK) |              \
      (((RwUInt32)(_addressing) << 12) & rwTEXTUREADDRESSINGVMASK)),        \
     (_tex))

#define RwTextureGetAddressingMacro(_tex)                                   \
    (((((_tex)->filterAddressing & rwTEXTUREADDRESSINGUMASK) >>  8) ==      \
      (((_tex)->filterAddressing & rwTEXTUREADDRESSINGVMASK) >> 12)) ?      \
     ((RwTextureAddressMode)(((_tex)->filterAddressing &                    \
                              rwTEXTUREADDRESSINGVMASK) >> 12)) :           \
     rwTEXTUREADDRESSNATEXTUREADDRESS)

#define RwTextureGetAddressingUMacro(_tex)                                  \
    ((RwTextureAddressMode)(((_tex)->filterAddressing &                     \
                             rwTEXTUREADDRESSINGUMASK) >> 8))

#define RwTextureGetAddressingVMacro(_tex)                                  \
    ((RwTextureAddressMode)(((_tex)->filterAddressing &                     \
                             rwTEXTUREADDRESSINGVMASK) >> 12))


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RwTextureGetRaster(_tex)                            \
    RwTextureGetRasterMacro(_tex)

#define RwTextureAddRef(_tex)                               \
    RwTextureAddRefMacro(_tex)

#define RwTextureGetName(_tex)                              \
    RwTextureGetNameMacro(_tex)

#define RwTextureGetMaskName(_tex)                          \
    RwTextureGetMaskNameMacro(_tex)

#define RwTextureGetDictionary(_tex)                        \
    RwTextureGetDictionaryMacro(_tex)

#define RwTextureSetFilterMode(_tex, _filtering)            \
    RwTextureSetFilterModeMacro(_tex, _filtering)

#define RwTextureGetFilterMode(_tex)                        \
    RwTextureGetFilterModeMacro(_tex)

#define RwTextureSetAddressing(_tex, _addressing)           \
    RwTextureSetAddressingMacro(_tex, _addressing)

#define RwTextureSetAddressingU(_tex, _addressing)          \
    RwTextureSetAddressingUMacro(_tex, _addressing)

#define RwTextureSetAddressingV(_tex, _addressing)          \
    RwTextureSetAddressingVMacro(_tex, _addressing)

#define RwTextureGetAddressing(_tex)                        \
    RwTextureGetAddressingMacro(_tex)

#define RwTextureGetAddressingU(_tex)                       \
    RwTextureGetAddressingUMacro(_tex)

#define RwTextureGetAddressingV(_tex)                       \
    RwTextureGetAddressingVMacro(_tex)

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


/* RWPUBLICEND */
typedef struct rwTextureGlobals rwTextureGlobals;
struct rwTextureGlobals
{
        RwLinkList          texDictList;
        RwFreeList         *textureFreeList;
        RwFreeList         *texDictFreeList;
        RwTexDictionary    *currentTexDict;
        RwTextureCallBackRead textureReadFunc;
        RwTextureCallBackFind textureFindFunc;
        RwBool              haveTexMipmaps;
        RwBool              generateTexMipmaps;
        RwUInt8            *scratchMem;
        RwInt16             scratchMemSize;
        RwInt16             pad;
        RwTextureCallBackMipmapGeneration mipmapCallback;
        RwTextureCallBackMipmapName mipmapNameCallback;
};

/****************************************************************************
 Globals (across program)
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

RWEXPORT RwPluginRegistry textureTKList;
RWEXPORT RwPluginRegistry texDictTKList;

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

    /* Reading mip maps */

    /* Setting mip mapping states */
RWEXPORT RwBool RWAPI RwTextureSetMipmapping(RwBool enable);
RWEXPORT RwBool RWAPI RwTextureGetMipmapping(void);
RWEXPORT RwBool RWAPI RwTextureSetAutoMipmapping(RwBool enable);
RWEXPORT RwBool RWAPI RwTextureGetAutoMipmapping(void);

    /* Setting and getting the mipmap generation function */
RWEXPORT RwBool RWAPI
RwTextureSetMipmapGenerationCallBack(RwTextureCallBackMipmapGeneration
                                     callback);
RWEXPORT RwTextureCallBackMipmapGeneration RWAPI
RwTextureGetMipmapGenerationCallBack(void);

    /* Setting and getting the mipmap file name generation function */
RWEXPORT RwBool RWAPI
RwTextureSetMipmapNameCallBack(RwTextureCallBackMipmapName callback);
RWEXPORT RwTextureCallBackMipmapName RwTextureGetMipmapNameCallBack(void);

    /* Generating mipmaps for a raster */
RWEXPORT RwBool RWAPI RwTextureGenerateMipmapName(RwChar * name,
                                                RwChar * maskName,
                                                RwUInt8 mipLevel,
                                                RwInt32 format);
RWEXPORT RwBool RWAPI RwTextureRasterGenerateMipmaps(RwRaster * raster,
                                                   RwImage * image);

    /* LEGACY-SUPPORT mip mapping */
RWEXPORT RwBool RWAPI _rwTextureSetAutoMipMapState(RwBool enable);
RWEXPORT RwBool RWAPI _rwTextureGetAutoMipMapState(void);

    /* Setting and getting the callback function */
RWEXPORT RwTextureCallBackRead RWAPI RwTextureGetReadCallBack(void);
RWEXPORT RwBool RWAPI RwTextureSetReadCallBack(RwTextureCallBackRead callBack);

RWEXPORT RwTextureCallBackFind RWAPI RwTextureGetFindCallBack(void);
RWEXPORT RwBool RWAPI RwTextureSetFindCallBack(RwTextureCallBackFind callBack);

    /* Texture and mask names */
RWEXPORT RwTexture* RWAPI RwTextureSetName(RwTexture * texture,
                                     const RwChar * name);
RWEXPORT RwTexture* RWAPI RwTextureSetMaskName(RwTexture * texture,
                                         const RwChar * maskName);

    /* Creating/destroying dictionaries */
RWEXPORT void RWAPI RwTexDictionarySetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

RWEXPORT RwTexDictionary* RWAPI RwTexDictionaryCreate(void);
RWEXPORT RwBool RWAPI RwTexDictionaryDestroy(RwTexDictionary * dict);

    /* Textures */
void RWAPI RwTextureSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

RWEXPORT RwTexture* RWAPI RwTextureCreate(RwRaster * raster);
RWEXPORT RwBool RWAPI RwTextureDestroy(RwTexture * texture);

    /* Setting and getting texture map rasters */
RWEXPORT RwTexture* RWAPI RwTextureSetRaster(RwTexture * texture,
                                       RwRaster * raster);

    /* Dictionary access */
RWEXPORT RwTexture* RWAPI RwTexDictionaryAddTexture(RwTexDictionary * dict,
                                              RwTexture * texture);
RWEXPORT RwTexture* RWAPI RwTexDictionaryRemoveTexture(RwTexture * texture);
RWEXPORT RwTexture* RWAPI RwTexDictionaryFindNamedTexture(RwTexDictionary *
                                                    dict,
                                                    const RwChar * name);

    /* Reading a texture */
RWEXPORT RwTexture* RWAPI RwTextureRead(const RwChar * name,
                                  const RwChar * maskName);

    /* Setting the current dictionary */
RWEXPORT RwTexDictionary* RWAPI RwTexDictionaryGetCurrent(void);
RWEXPORT RwTexDictionary* RWAPI RwTexDictionarySetCurrent(RwTexDictionary * dict);

    /* Enumerating textures */
RWEXPORT const RwTexDictionary* RWAPI RwTexDictionaryForAllTextures(const
                                                            RwTexDictionary
                                                            * dict,
                                                            RwTextureCallBack
                                                            fpCallBack,
                                                            void *pData);

    /* Enumerating the texture dictionaries currently in the system */
RWEXPORT RwBool RWAPI RwTexDictionaryForAllTexDictionaries(
    RwTexDictionaryCallBack fpCallBack, void *pData);


    /* Attaching toolkits */
RWEXPORT RwInt32 RWAPI RwTextureRegisterPlugin(RwInt32 size,
                                            RwUInt32 pluginID,
                                            RwPluginObjectConstructor
                                            constructCB,
                                            RwPluginObjectDestructor
                                            destructCB,
                                            RwPluginObjectCopy copyCB);
RWEXPORT RwInt32 RWAPI RwTexDictionaryRegisterPlugin(RwInt32 size,
                                                  RwUInt32 pluginID,
                                                  RwPluginObjectConstructor
                                                  constructCB,
                                                  RwPluginObjectDestructor
                                                  destructCB,
                                                  RwPluginObjectCopy
                                                  copyCB);
RWEXPORT RwInt32 RWAPI RwTextureGetPluginOffset(RwUInt32 pluginID);
RWEXPORT RwInt32 RWAPI RwTexDictionaryGetPluginOffset(RwUInt32 pluginID);
RWEXPORT RwBool RWAPI RwTextureValidatePlugins(const RwTexture * texture);
RWEXPORT RwBool RWAPI RwTexDictionaryValidatePlugins(const RwTexDictionary *
                                                   dict);

#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
/* Textures */
RWEXPORT RwRaster* RWAPI RwTextureGetRaster(const RwTexture *texture);
RWEXPORT RwTexture* RWAPI RwTextureAddRef(RwTexture *texture);

/* Texture and mask names */
RWEXPORT RwChar* RWAPI RwTextureGetName(RwTexture *texture);
RWEXPORT RwChar* RWAPI RwTextureGetMaskName(RwTexture *texture);

/* Get owner dictionary */
RWEXPORT RwTexDictionary* RWAPI RwTextureGetDictionary(RwTexture *texture);

/* Filtering */
RWEXPORT RwTexture* RWAPI RwTextureSetFilterMode(RwTexture *texture,
                                         RwTextureFilterMode filtering);

RWEXPORT RwTextureFilterMode RWAPI RwTextureGetFilterMode(const RwTexture *texture);

/* Addressing */
RWEXPORT RwTexture* RWAPI RwTextureSetAddressing(RwTexture *texture,
                                         RwTextureAddressMode addressing);
RWEXPORT RwTexture* RWAPI RwTextureSetAddressingU(RwTexture *texture,
                                          RwTextureAddressMode addressing);
RWEXPORT RwTexture* RWAPI RwTextureSetAddressingV(RwTexture *texture,
                                          RwTextureAddressMode addressing);

RWEXPORT RwTextureAddressMode RWAPI RwTextureGetAddressing(const RwTexture *texture);
RWEXPORT RwTextureAddressMode RWAPI RwTextureGetAddressingU(const RwTexture *texture);
RWEXPORT RwTextureAddressMode RWAPI RwTextureGetAddressingV(const RwTexture *texture);

#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */


    /* RWPUBLICEND */

    /* Opening and closing */
RWEXPORT void* RWAPI _rwTextureOpen(void *instance, RwInt32 offset,
                                   RwInt32 size);
RWEXPORT void* RWAPI _rwTextureClose(void *instance, RwInt32 offset,
                                    RwInt32 size);

    /* RWPUBLIC */
#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RwTextureSetAutoMipMapState(_enable) \
    _rwTextureSetAutoMipMapState(_enable)

#define RwTextureGetAutoMipMapState() \
    _rwTextureGetAutoMipMapState()

/* RWPUBLICEND */

#endif                          /* RWTEXTUR_H */

