/***************************************************************************
 *                                                                         *
 * Module  : baimage.h                                                     *
 *                                                                         *
 * Purpose : Handling bitmap images                                        *
 *                                                                         *
 **************************************************************************/

#ifndef RWIMAGE_H
#define RWIMAGE_H

/****************************************************************************
 Includes
 */

#include "plcore/bamemory.h"
#include "plcore/bastream.h"
#include "plcore/bacolor.h"
#include "plcore/batkreg.h"

/* RWPUBLIC */

/****************************************************************************
 Defines
 */

/* If this bit is set then the image has been allocated by the user */

enum RwImageFlag
{
    rwNAIMAGEFLAG = 0x00,
    rwIMAGEALLOCATED = 0x1,
    rwIMAGEGAMMACORRECTED = 0x2,
    rwIMAGEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwImageFlag RwImageFlag;

/****************************************************************************
 Global Types
 */

/**
 * \ingroup rwimage
 * \struct RwImage 
 * Image containing device-independent pixels. 
 * This should be considered an opaque type.
 * Use the RwImage API functions to access.
 */
typedef struct RwImage RwImage;

#if (!defined(DOXYGEN))
struct RwImage
{
        RwInt32             flags;

        RwInt32             width;  /* Device may have different ideas */
        RwInt32             height; /* internally !! */

        RwInt32             depth;  /* Of referenced image */
        RwInt32             stride;

        RwUInt8            *cpPixels;
        RwRGBA             *palette;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rwimage
 * \ref RwImageCallBackRead 
 * is the function registered with \ref RwImageRegisterImageFormat that is used,
 * for example by \ref RwImageRead and \ref RwImageReadMaskedImage,
 * to read images of a specific format from a disk file.
 * 
 * \param  imageName   Pointer to a string containing the file name of the image.
 *
 * \return Returns a pointer to the image read.
 *
 * \see RwImageRegisterImageFormat
 *
 */
typedef RwImage *(*RwImageCallBackRead)(const RwChar * imageName);

/**
 * \ingroup rwimage
 * \ref RwImageCallBackWrite 
 * is the function registered with \ref RwImageRegisterImageFormat that is used,
 * for example by \ref RwImageWrite, 
 * to write images of a specific format to a disk file.
 * 
 * \param  image   Pointer to the image.
 *
 * \param  imageName   Pointer to a string containing the file name
 * of the image.
 *
 *
 * \return Pointer to the written image.
 *
 * \see RwImageRegisterImageFormat
 *
 */
typedef RwImage *(*RwImageCallBackWrite)(RwImage *image, const RwChar *imageName);

/* RWPUBLICEND */

typedef struct rwImageFormat rwImageFormat;
struct rwImageFormat
{
        RwChar              lcExtension[20]; /* Lower case version */
        RwChar              ucExtension[20]; /* Upper case version */
        RwImageCallBackRead readImage;
        RwImageCallBackWrite writeImage;
        rwImageFormat      *nextFormat;
};

typedef struct rwImageGlobals rwImageGlobals;
struct rwImageGlobals
{
        RwFreeList         *imageFreeList;
        RwChar             *imagePath;
        RwInt32             imagePathSize;

        RwUInt8             gammaTable[256];
        RwUInt8             invGammaTable[256];
        RwReal              gammaVal;

        RwUInt8            *scratchMem;
        RwInt32             scratchMemSize;

        RwFreeList         *imageFormatFreeList;
        rwImageFormat      *imageFormats;
};

/* RWPUBLIC */

/****************************************************************************
 <macro/inline functionality
 */

#define RwImageSetStrideMacro(_image, _stride)      \
    (((_image)->stride = (_stride)), (_image))

#define RwImageSetPixelsMacro(_image, _pixels)      \
    (((_image)->cpPixels = (_pixels)), (_image))

#define RwImageSetPaletteMacro(_image, _palette)    \
    (((_image)->palette = (_palette)), (_image))

#define RwImageGetWidthMacro(_image)                \
    ((_image)->width)

#define RwImageGetHeightMacro(_image)               \
    ((_image)->height)

#define RwImageGetDepthMacro(_image)                \
    ((_image)->depth)

#define RwImageGetStrideMacro(_image)               \
    ((_image)->stride)

#define RwImageGetPixelsMacro(_image)               \
    ((_image)->cpPixels)

#define RwImageGetPaletteMacro(_image)              \
    ((_image)->palette)


#if !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE))

#define RwImageSetStride(_image, _stride)           \
    RwImageSetStrideMacro(_image, _stride)

#define RwImageSetPixels(_image, _pixels)           \
    RwImageSetPixelsMacro(_image, _pixels)

#define RwImageSetPalette(_image, _palette)         \
    RwImageSetPaletteMacro(_image, _palette)

#define RwImageGetWidth(_image)                     \
    RwImageGetWidthMacro(_image)

#define RwImageGetHeight(_image)                    \
    RwImageGetHeightMacro(_image)

#define RwImageGetDepth(_image)                     \
    RwImageGetDepthMacro(_image)

#define RwImageGetStride(_image)                    \
    RwImageGetStrideMacro(_image)

#define RwImageGetPixels(_image)                    \
    RwImageGetPixelsMacro(_image)

#define RwImageGetPalette(_image)                   \
    RwImageGetPaletteMacro(_image)

#endif /* !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

    /* Creating and destroying */

RWEXPORT void RWAPI RwImageSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

RWEXPORT void RWAPI RwImageFormatSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

RWEXPORT RwImage* RWAPI RwImageCreate(RwInt32 width, RwInt32 height,
                                  RwInt32 depth);
RWEXPORT RwBool RWAPI RwImageDestroy(RwImage * image);

    /* Allocating */
RWEXPORT RwImage* RWAPI RwImageAllocatePixels(RwImage * image);
RWEXPORT RwImage* RWAPI RwImageFreePixels(RwImage * image);

    /* Converting images */
RWEXPORT RwImage* RWAPI RwImageCopy(RwImage * destImage,
                                const RwImage * sourceImage);

    /* Resizing images */
RWEXPORT RwImage* RWAPI RwImageResize(RwImage * image, RwInt32 width,
                                  RwInt32 height);

    /* Producing masks ! */
RWEXPORT RwImage* RWAPI RwImageApplyMask(RwImage * image,
                                     const RwImage * mask);
RWEXPORT RwImage* RWAPI RwImageMakeMask(RwImage * image);

    /* Helper functions */
RWEXPORT RwImage* RWAPI RwImageReadMaskedImage(const RwChar * imageName,
                                           const RwChar * maskname);
RWEXPORT RwImage* RWAPI RwImageRead(const RwChar * imageName);
RWEXPORT RwImage* RWAPI RwImageWrite(RwImage * image,
                                 const RwChar * imageName);

    /* Setting and getting the default path for images */
RWEXPORT RwChar* RWAPI RwImageGetPath(void);
RWEXPORT const RwChar* RWAPI RwImageSetPath(const RwChar * path);
    /* Fast image path change */
RWEXPORT void RWAPI _rwImageSwapPath(RwChar **path, RwInt32 *size);

    /* Setting */
#if (defined(RWDEBUG) || defined(RWSUPPRESSINLINE))
RWEXPORT RwImage* RWAPI RwImageSetStride(RwImage * image, RwInt32 stride);
RWEXPORT RwImage* RWAPI RwImageSetPixels(RwImage * image, RwUInt8 * pixels);
RWEXPORT RwImage* RWAPI RwImageSetPalette(RwImage * image, RwRGBA * palette);

    /* Getting */
RWEXPORT RwInt32 RWAPI RwImageGetWidth(const RwImage * image);
RWEXPORT RwInt32 RWAPI RwImageGetHeight(const RwImage * image);
RWEXPORT RwInt32 RWAPI RwImageGetDepth(const RwImage * image);
RWEXPORT RwInt32 RWAPI RwImageGetStride(const RwImage * image);
RWEXPORT RwUInt8* RWAPI RwImageGetPixels(const RwImage * image);
RWEXPORT RwRGBA* RWAPI RwImageGetPalette(const RwImage * image);
#endif /* (defined(RWDEBUG) || defined(RWSUPPRESSINLINE)) */

    /* Get device dependent pixel value */
RWEXPORT RwUInt32 RWAPI RwRGBAToPixel(RwRGBA * rgbIn, RwInt32 rasterFormat);
RWEXPORT RwRGBA* RWAPI RwRGBASetFromPixel(RwRGBA * rgbOut,
                                       RwUInt32 pixelValue,
                                       RwInt32 rasterFormat);

    /* Gamma correction */
RWEXPORT RwBool RWAPI RwImageSetGamma(RwReal gammaValue);
RWEXPORT RwReal RWAPI RwImageGetGamma(void);
RWEXPORT RwImage* RWAPI RwImageGammaCorrect(RwImage * image);

    /* Adding and removing gamma correction */
RWEXPORT RwRGBA* RWAPI RwRGBAGammaCorrect(RwRGBA * rgb);

    /* Attaching toolkits */
RWEXPORT RwInt32 RWAPI RwImageRegisterPlugin(RwInt32 size, RwUInt32 pluginID,
                                          RwPluginObjectConstructor
                                          constructCB,
                                          RwPluginObjectDestructor
                                          destructCB,
                                          RwPluginObjectCopy copyCB);
RWEXPORT RwInt32 RWAPI RwImageGetPluginOffset(RwUInt32 pluginID);
RWEXPORT RwBool RWAPI  RwImageValidatePlugins(const RwImage * image);

RWEXPORT RwBool RWAPI RwImageRegisterImageFormat(const RwChar * extension,
                                               RwImageCallBackRead
                                               imageRead,
                                               RwImageCallBackWrite
                                               imageWrite);

    /* Finding an extension for an image to load */
RWEXPORT const RwChar* RWAPI RwImageFindFileType(const RwChar * imageName);

    /* Reading and writing images to streams */
RWEXPORT RwInt32 RWAPI RwImageStreamGetSize(const RwImage * image);
RWEXPORT RwImage* RWAPI RwImageStreamRead(RwStream * stream);
RWEXPORT const RwImage* RWAPI RwImageStreamWrite(const RwImage * image,
                                         RwStream * stream);

    /* RWPUBLICEND */

    /* Gamma correction */
RWEXPORT void RWAPI _rwImageGammaCorrectArrayOfRGBA(RwRGBA * rgbaOut,
                                                    RwRGBA * rgbaIn,
                                                    RwInt32 numEls);
RWEXPORT void RWAPI _rwImageGammaUnCorrectArrayOfRGBA(RwRGBA * rgbaOut,
                                                      RwRGBA * rgbaIn,
                                                      RwInt32 numEls);

    /* Opening and closing libraries */
RWEXPORT void* RWAPI _rwImageOpen(void *instance, RwInt32 offset,
                                 RwInt32 size);
RWEXPORT void* RWAPI _rwImageClose(void *instance, RwInt32 offset,
                                  RwInt32 size);

    /* RWPUBLIC */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */
/* RWPUBLICEND */

#endif                          /* RWIMAGE_H */

