/***************************************************************************
 *                                                                         *
 * Purpose : CPU extensions                                                *
 *                                                                         *
 **************************************************************************/

#ifndef CPUEXT_H
#define CPUEXT_H

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

/*
 * The CPU name length could be up to 48 bytes (49 with the '\0').
 */
RWEXPORT void RWAPI _rwCPUGetCPUName_sized(RwChar *cpuName, size_t cpuNameSize);

RWEXPORT RwBool RWAPI _rwCPUHaveMMX(void);

RWEXPORT RwBool RWAPI _rwCPUHaveSSE(void);

RWEXPORT RwBool RWAPI _rwCPUHaveSSE2(void);

RWEXPORT RwBool RWAPI _rwCPUHave3DNow(void);

/*
 * The OS version name length could be up to 127 bytes (128 with the '\0').
 */
RWEXPORT RwBool RWAPI
_rwCPUGetOSName(RwChar *osName);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* CPUEXT_H */
