/****************************************************************************
 *                                                                          *
 * Module  : d3d9vertexbuffer.h                                             *
 *                                                                          *
 * Purpose : See d3d9vertexbuffer.c                                         *
 *                                                                          *
 ****************************************************************************/

#ifndef D3D9VERTEXBUFFER_H
#define D3D9VERTEXBUFFER_H

/****************************************************************************
 Includes
 */

/****************************************************************************
 Global Defines
 */
#define LPVERTEXBUFFER LPDIRECT3DVERTEXBUFFER9

/****************************************************************************
 Global Types
 */

/****************************************************************************
 Global Variables
 */

/****************************************************************************
 Function prototypes
 */

/* RWPUBLIC */
#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */
/* RWPUBLICEND */

RWEXPORT RwBool RWAPI
_rwD3D9VertexBufferManagerOpen(void);

RWEXPORT void RWAPI
_rwD3D9VertexBufferManagerClose(void);

RWEXPORT void RWAPI
_rwD3D9DynamicVertexBufferRelease(void);

RWEXPORT RwBool RWAPI
_rwD3D9DynamicVertexBufferRestore(void);

RWEXPORT void RWAPI
_rwD3D9DynamicVertexBufferManagerForceDiscard(void);

/* RWPUBLIC */

RWEXPORT void RWAPI
RwD3D9VertexBufferManagerChangeDefaultSize(RwUInt32 defaultSize);

/*
 * To get a pointer to a static vertex buffer
 * Use both functions, Create and Destroy, not only Create
 */
RWEXPORT RwBool RWAPI
RwD3D9CreateVertexBuffer(RwUInt32 stride,
                         RwUInt32 size,
                         void **vertexBuffer,
                         RwUInt32 *offset);

RWEXPORT void RWAPI
RwD3D9DestroyVertexBuffer(RwUInt32 stride,
                          RwUInt32 size,
                          void *vertexBuffer,
                          RwUInt32 offset);

/*
 * To get a pointer to a Dynamic vertex buffer
 * Use both functions, Create and Destroy, not only Create
 */
RWEXPORT RwBool RWAPI RwD3D9DynamicVertexBufferCreate(RwUInt32 size,
                                              void **vertexBuffer);

RWEXPORT void RWAPI RwD3D9DynamicVertexBufferDestroy(void *vertexBuffer);

/*
 * To get a temporary pointer to a Dynamic vertex buffer memory
 * Don't use with the previous functions because
 * it mantains an internal list of dinamic vertex buffers
 */
RWEXPORT RwBool RWAPI RwD3D9DynamicVertexBufferLock(RwUInt32 vertexSize,
                                            RwUInt32 numVertex,
                                            void **vertexBufferOut,
                                            void **vertexDataOut,
                                            RwUInt32 *baseIndexOut);

RWEXPORT RwBool RWAPI RwD3D9DynamicVertexBufferUnlock(void *vertexBuffer);

#ifdef    __cplusplus
}
#endif /* __cplusplus */
/* RWPUBLICEND */

#endif /* D3D9VERTEXBUFFER_H */
