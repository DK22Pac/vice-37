/***************************************************************************
 *                                                                         *
 * Purpose : SSE Matrix Multiply                                           *
 *                                                                         *
 **************************************************************************/

#ifndef SSEMATML_H
#define SSEMATML_H

/****************************************************************************
 Includes
 */

#include "bamatrix.h"

/****************************************************************************
 Defines
 */

/****************************************************************************
 Global Types
 */


/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

RWEXPORT void RWAPI
_rwIntelSSEMatrixMultiply( RwMatrix *dstMat,
                           const RwMatrix *matA,
                           const RwMatrix *matB );

RWEXPORT void RWAPI
_rwIntelSSEAlignedMatrixMultiply( RwMatrix *dstMat,
                                  const RwMatrix *matA,
                                  const RwMatrix *matB );

RWEXPORT RwV3d* RWAPI
_rwIntelSSEV3dTransformPoints( RwV3d          *pointsOut,
                               const RwV3d    *pointsIn,  
                               RwInt32        numPoints,  
                               const RwMatrix *matrix );

RWEXPORT RwV3d* RWAPI
_rwIntelSSEV3dTransformPointsAlignedMatrix( RwV3d          *pointsOut,
                                            const RwV3d    *pointsIn,  
                                            RwInt32        numPoints,  
                                            const RwMatrix *matrix );

RWEXPORT RwV3d* RWAPI
_rwIntelSSEV3dTransformVectors( RwV3d          *vectorsOut,
                                const RwV3d    *vectorsIn,  
                                RwInt32        numVectors,  
                                const RwMatrix *matrix );

RWEXPORT RwV3d* RWAPI
_rwIntelSSEV3dTransformVectorsAlignedMatrix( RwV3d          *vectorsOut,
                                             const RwV3d    *vectorsIn,  
                                             RwInt32        numVectors,  
                                             const RwMatrix *matrix );


RWEXPORT RwV3d* RWAPI
_rwIntelSSEV3dTransformPoint( RwV3d          *pointOut,
                              const RwV3d    *pointIn,  
                              const RwMatrix *matrix );

RWEXPORT RwV3d* RWAPI
_rwIntelSSEV3dTransformPointAlignedMatrix( RwV3d          *pointOut,
                                           const RwV3d    *pointIn,  
                                           const RwMatrix *matrix );

RWEXPORT RwV3d* RWAPI
_rwIntelSSEV3dTransformVector( RwV3d          *vectorOut,
                               const RwV3d    *vectorIn,  
                               const RwMatrix *matrix );

RWEXPORT RwV3d* RWAPI
_rwIntelSSEV3dTransformVectorAlignedMatrix( RwV3d          *vectorOut,
                                            const RwV3d    *vectorIn,  
                                            const RwMatrix *matrix );

/* Pentium 4 specific versions */
RWEXPORT RwV3d* RWAPI
_rwIntelSSEP4V3dTransformPoints(RwV3d          *pointsOut,
                                const RwV3d    *pointsIn,  
                                RwInt32        numPoints,  
                                const RwMatrix *matrix );

RWEXPORT RwV3d* RWAPI
_rwIntelSSEP4V3dTransformVectors(RwV3d          *vectorsOut,
                                 const RwV3d    *vectorsIn,  
                                 RwInt32        numVectors,  
                                 const RwMatrix *matrix );

RWEXPORT RwV3d* RWAPI
_rwIntelSSEP4V3dTransformPoint(RwV3d          *pointOut,
                               const RwV3d    *pointIn,  
                               const RwMatrix *matrix );


RWEXPORT RwV3d* RWAPI
_rwIntelSSEP4V3dTransformVector(RwV3d          *vectorOut,
                                const RwV3d    *vectorIn,  
                                const RwMatrix *matrix );

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* SSEMATML_H */
