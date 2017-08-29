/***************************************************************************
 *                                                                         *
 * Module  : d3d9device.h                                                    *
 *                                                                         *
 * Purpose : d3d9 device header                                            *
 *                                                                         *
 **************************************************************************/

#ifndef D3D9DEVICE_H
#define D3D9DEVICE_H

/****************************************************************************
 Includes
 */

#include <d3d9.h>

/****************************************************************************
 Defines
 */

// OPT-IN for PERFHUD
//#define dNTL_OPTIN_FOR_PERFHUD

#define MINZBUFFERVALUE 0.0f
#define MAXZBUFFERVALUE 1.0f

#define RWD3D9_ALIGN16 __declspec(align(16))

/****************************************************************************
 Global Types
 */

typedef LPDIRECT3DVERTEXSHADER9 LPVERTEXSHADER;
typedef LPDIRECT3DPIXELSHADER9  LPPIXELSHADER;

typedef struct _rwD3D9AdapterInformation _rwD3D9AdapterInformation;
struct _rwD3D9AdapterInformation
{
    RwChar          name[MAX_DEVICE_IDENTIFIER_STRING];
    RwInt32         modeCount;
    D3DDISPLAYMODE  mode;
    RwInt32         displayDepth;
    RwInt32         flags;
};

RWEXPORT HWND                         WindowHandle;
RWEXPORT LPDIRECT3D9                  _RwDirect3DObject;
RWEXPORT RwUInt32                     _RwD3DAdapterIndex;
RWEXPORT RwUInt32                     _RwD3DAdapterType;
RWEXPORT LPDIRECT3DDEVICE9            _RwD3DDevice;
RWEXPORT D3DPRESENT_PARAMETERS        Present;
RWEXPORT _rwD3D9AdapterInformation    _RwD3D9AdapterInformation;
RWEXPORT LPDIRECT3DSURFACE9           _RwD3D9RenderSurface;
RWEXPORT LPDIRECT3DSURFACE9           _RwD3D9DepthStencilSurface;
RWEXPORT D3DCAPS9                     _RwD3D9DeviceCaps;
RWEXPORT RwInt32                      _RwD3D9ZBufferDepth;
RWEXPORT RwRGBAReal                   AmbientSaturated;

RWEXPORT RWD3D9_ALIGN16 D3DMATRIX     _RwD3D9D3D9ViewTransform;
RWEXPORT RWD3D9_ALIGN16 D3DMATRIX     _RwD3D9D3D9ProjTransform;
/* This pointer is set to NULL every time any of the previous matrix is changed */
RWEXPORT const D3DMATRIX*     _RwD3D9ActiveViewProjTransform;    


/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

#if defined(RWDEBUG)

RWEXPORT HRESULT RWAPI _rwD3D9CheckError(HRESULT hr, const RwChar *function, const RwChar *file, RwUInt32 line);

#define DXCHECK(fn) (_rwD3D9CheckError(fn, #fn, __FILE__, __LINE__))

#else
#define DXCHECK(fn) (fn)
#endif


RWEXPORT RwBool RWAPI
_rwD3D9BeginScene(void);

RWEXPORT RwBool RWAPI
_rwD3D9SetRenderTarget(RwUInt32 index,
                       LPDIRECT3DSURFACE9 rendertarget);

RWEXPORT void RWAPI
_rwD3D9SetDepthStencilSurface(LPDIRECT3DSURFACE9 depthStencilSurface);

RWEXPORT RwBool RWAPI _rwD3D9CameraClear(void *camera, void *color, RwInt32 clearFlags);
RWEXPORT RwBool RWAPI _rwD3D9CameraBeginUpdate(void *out, void *cameraIn, RwInt32 in);
RWEXPORT RwBool RWAPI _rwD3D9CameraEndUpdate(void *out, void *inOut, RwInt32 nIn);
RWEXPORT RwBool RWAPI _rwD3D9RasterShowRaster(void *out, void *inOut, RwInt32 flags);

RWEXPORT RwBool RWAPI _rwD3D9ForceLight(RwInt32 index, const void *light);

RWEXPORT RwBool RWAPI _rwD3D9LightsEqual(const D3DLIGHT9 *light0, const D3DLIGHT9 *light1);
RWEXPORT RwUInt32 RWAPI _rwD3D9FindSimilarLight(const void *light); /* returns 0xffffffff on failure */

RWEXPORT RwBool RWAPI _rwD3D9IndexBuffer32bitsCreate(RwUInt32 numIndices, void **indexBuffer);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* D3D9DEVICE_H */
