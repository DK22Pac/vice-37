/***************************************************************************
 *                                                                         *
 * Module  : D3D92drend.h                                                    *
 *                                                                         *
 * Purpose : 2D primitive rendering functions.                             *
 *                                                                         *
 **************************************************************************/

#ifndef D3D92DREND_H
#define D3D92DREND_H

RWEXPORT RwBool RWAPI _rwD3D9Im2DRenderOpen(void);

RWEXPORT RwBool RWAPI _rwD3D9Im2DRenderLine(RwIm2DVertex *verts, RwInt32 numVerts,
                                  RwInt32 vert1, RwInt32 vert2);
RWEXPORT RwBool RWAPI _rwD3D9Im2DRenderTriangle(RwIm2DVertex *verts, RwInt32 numVerts,
                               RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
RWEXPORT RwBool RWAPI _rwD3D9Im2DRenderPrimitive(RwPrimitiveType primType,
                                       RwIm2DVertex *verts,
                                       RwInt32 numVerts);
RWEXPORT RwBool RWAPI _rwD3D9Im2DRenderIndexedPrimitive(RwPrimitiveType primType,
                                              RwIm2DVertex *verts,
                                              RwInt32 numVerts,
                                              RwImVertexIndex *indices,
                                              RwInt32 numIndices);

RWEXPORT void RWAPI _rwD3D9Im2DRenderClose(void);

#endif /* D3D92DREND_H */
