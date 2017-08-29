/***************************************************************************
 *                                                                         *
 * Module  : d3d9metric.h                                                    *
 *                                                                         *
 * Purpose : D3D9 metrics                                                  *
 *                                                                         *
 **************************************************************************/

#ifndef D3D9METRIC_H
#define D3D9METRIC_H

/****************************************************************************
 Includes
 */

#include "batypes.h"

/****************************************************************************
 Defines
 */

/****************************************************************************
 Global Types
 */

/****************************************************************************
 Global variables (across program)
 */

/****************************************************************************
 Function prototypes
 */
#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

RWEXPORT void RWAPI _rwD3D9MetricsReset(void);
RWEXPORT RwD3D9Metrics* RWAPI _rwD3D9MetricsGet(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* D3D9METRIC_H */
