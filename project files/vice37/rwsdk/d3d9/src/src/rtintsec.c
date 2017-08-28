/*
 *
 * Intersection logic.
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 */
 
#include <rwcore.h>
#include "rtintsec.h"

// We do not implement these things for now.
/* Line intersections */
RwBool
RtIntersectionLineTriangle(const RwV3d *lineStart, 
                           const RwV3d *lineDelta,
                           const RwV3d *v0, 
                           const RwV3d *v1, 
                           const RwV3d *v2, 
                           RwReal *distance)
{
    RWFUNCTION(RWSTRING(__FUNCTION__));

    RwBool result;

    RtIntersectionLineTriangleMacro( result, lineStart, lineDelta, v0, v1, v2, distance );

    RWRETURN(result);
}

/* Sphere intersections */
RwBool
RtIntersectionSphereTriangle(const RwSphere *sphere, 
                             const RwV3d  *v0, 
                             const RwV3d *v1, 
                             const RwV3d *v2,
                             RwV3d  *normal,
                             RwReal *distance)
{
    RWFUNCTION(RWSTRING(__FUNCTION__));

    RWRETURN( 0 );
}

/* BBox intersections */
RwBool
RtIntersectionBBoxTriangle(const RwBBox *bbox, 
                           const RwV3d *v0, 
                           const RwV3d *v1, 
                           const RwV3d *v2)
{
    RWFUNCTION(RWSTRING(__FUNCTION__));

    RWRETURN( 0 );
}