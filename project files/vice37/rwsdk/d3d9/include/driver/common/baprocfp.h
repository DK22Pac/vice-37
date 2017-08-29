/***************************************************************************
 *                                                                         *
 * Module  : baprocfp.h                                                    *
 *                                                                         *
 * Purpose : Processor floating point mode stuff                           *
 *                                                                         *
 **************************************************************************/

#ifndef RWPROCFP_H
#define RWPROCFP_H

/****************************************************************************
 Includes
 */

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

RWEXPORT void RWAPI _rwProcessorInitialize(void);
RWEXPORT void RWAPI _rwProcessorRelease(void);
RWEXPORT void RWAPI _rwProcessorForceSinglePrecision(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RWPROCFP_H */
