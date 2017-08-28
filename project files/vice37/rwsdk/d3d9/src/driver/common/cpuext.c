/* 
 * Querying processor features
 *
 * Copyright (c) 2001 Criterion Software Ltd.
 */

#include <string.h>

#include "batypes.h"
#include "barwtyp.h"
#include "badebug.h"

#include "cpuext.h"

#ifdef _WIN32
#include <windows.h>
#include <intrin.h>
#endif

#define CPUID_MMX   (1 << 23)
#define CPUID_SSE   (1 << 25)
#define CPUID_SSE2  (1 << 26)

#define CPUID_EXT_3DNOW (1 << 31)

/**************************************************************************
 CPUHaveCPUID

 Does the processor support the CPUID function?

 On entry   : Nothing
 On exit    : TRUE if processor supports CPUID, FALSE otherwise
 */
static RwBool
CPUHaveCPUID(void)
{
    RWFUNCTION( RWSTRING( "CPUHaveCPUID" ) );

#ifdef _WIN32
    // We assume the CPUID instruction is always available.
    RWRETURN( 1 );
#else
    // Not implemented.
    RWRETURN( 0 );
#endif
}

/**
 * CPUGetFeatures Get CPU features flags
 *
 * Returns value of EDX
 */
static RwUInt32
CPUGetFeatures(void)
{
    RwUInt32    result = 0;

    RWFUNCTION(RWSTRING("CPUGetFeatures"));

#if (!defined(__GNUC__))
    unsigned int cpu_features[4];

    __cpuid( (int*)cpu_features, 0x00000001 );

    result = cpu_features[3];
#endif /* (!defined(__GNUC__)) */

    RWRETURN(result);
}

/**
 * CPUHaveExtFeatures Does the CPU support extended features
 *
 * Returns true if it makes sense to fetch extended features
 */
#ifdef _WIN32
static inline unsigned int _CPUGetExtFeatureCount( void )
{
    unsigned int cpu_features[4];

    __cpuid( (int*)cpu_features, 0x80000000 );

    return ( cpu_features[4] - 0x80000000 );
}
#endif

static RwBool
CPUHaveExtFeatures(void)
{
    RwBool  extFeaturesOkay = FALSE;

    RWFUNCTION(RWSTRING("CPUHaveExtFeatures"));

#if (!defined(__GNUC__))
    extFeaturesOkay = ( _CPUGetExtFeatureCount() >= 1 );
#endif /* (!defined(__GNUC__)) */

    RWRETURN(extFeaturesOkay);
}

/**
 * CPUGetExtFeatures Get CPU extended features flags
 *
 * Returns value of EDX
 */
static RwUInt32
CPUGetExtFeatures(void)
{
    RwUInt32    result = 0;

    RWFUNCTION(RWSTRING("CPUGetExtFeatures"));

#if (!defined(__GNUC__))
    unsigned int cpu_features[4];

    __cpuid( (int*)cpu_features, 0x80000001 );

    result = cpu_features[3];
#endif /* (!defined(__GNUC__)) */

    RWRETURN(result);
}

#if (!defined(__GNUC__))
/**
 * CPUGetProcessorFamilyModel Get CPU processor flags
 *
 * Returns value of EDX
 */
static void
CPUGetProcessorFamilyModel(RwUInt32 *family, RwUInt32 *model)
{
    RWFUNCTION(RWSTRING("CPUGetProcessorFamilyModel"));

    *family = 0;
    *model = 0;

    if (CPUHaveCPUID())
    {
#if (!defined(__GNUC__))
        unsigned int cpuFlags = 0;

        if ( _CPUGetExtFeatureCount() >= 1 )
        {
            unsigned int cpu_features[4];

            __cpuid( (int*)cpu_features, 0x80000001 );

            cpuFlags = cpu_features[0];
        }

        if ( cpuFlags == 0 )
        {
            unsigned int cpu_features[4];

            __cpuid( (int*)cpu_features, 0x00000001 );

            cpuFlags = cpu_features[0];
        }

        *family = ( ( cpuFlags << 8 ) & 0xF );
        *model = ( ( cpuFlags << 4 ) & 0xF );
#endif /* (!defined(__GNUC__)) */
    }

    RWRETURNVOID();
}
#endif /* (!defined(__GNUC__)) */

static inline void _SkipWhiteSpaceMax(
    const char *input, size_t maxLen,
    const char **skippedOut, size_t *remMaxOut
)
{
    size_t iter = 0;

    const char *inputPtr = input;

    for (;;)
    {
        if ( iter >= maxLen )
        {
            break;
        }

        char c = *inputPtr;

        if ( c == 0 )
        {
            break;
        }

        if ( c != ' ' )
        {
            break;
        }

        iter++;
        inputPtr++;
    }

    *skippedOut = inputPtr;
    *remMaxOut = ( maxLen - iter );
}

/*
 * _rwCPUGetCPUName_sized copies the cpu name to the buffer
 */
#pragma warning(push)
#pragma warning(disable: 4996)
void
_rwCPUGetCPUName_sized(RwChar *cpuName, size_t cpuNameSize)
{
    RWFUNCTION(RWSTRING("_rwCPUGetCPUName"));

    cpuName[0] = 0;

    if (CPUHaveCPUID())
    {
#if (!defined(__GNUC__))
        char cpuNameDecay[sizeof(unsigned int) * 12 + 1];

        if ( _CPUGetExtFeatureCount() >= 4 )
        {
            char cpuBrandString[sizeof(unsigned int) * 12];

            __cpuid( (int*)cpuBrandString + 0, 0x80000001 );
            __cpuid( (int*)cpuBrandString + 4, 0x80000002 );
            __cpuid( (int*)cpuBrandString + 8, 0x80000003 );

            // Skip spaces and copy into final destination buffer.
            size_t newMaxString;
            const char *cpuBrandStart;

            _SkipWhiteSpaceMax( cpuBrandString, sizeof(cpuBrandString), &cpuBrandStart, &newMaxString );

            size_t strLength = strnlen( cpuBrandStart, newMaxString );

            memcpy( cpuNameDecay, cpuBrandStart, strLength );

            cpuNameDecay[strLength] = 0;
        }
        else
        {
            unsigned int cpu_features[4];

            __cpuid( (int*)cpu_features, 0x00000000 );

            char fakeCPUName[12];

            *( (unsigned int*)fakeCPUName + 0 ) = cpu_features[0];
            *( (unsigned int*)fakeCPUName + 1 ) = cpu_features[2];
            *( (unsigned int*)fakeCPUName + 2 ) = cpu_features[1];

            RwUInt32 family;
            RwUInt32 model;

            CPUGetProcessorFamilyModel(&family, &model);

            RwBool requiresCopyFromFakeBuffer = 0;

            if (strncmp(fakeCPUName, "GenuineIntel", sizeof(fakeCPUName)) == 0)
            {
                switch (family)
                {
                case 4:
                    strncpy(cpuNameDecay, "Intel 486", sizeof(cpuNameDecay));
                    break;

                case 5:
                    switch (model)
                    {
                    case 4:
                    case 8:
                        strncpy(cpuNameDecay, "Intel Pentium MMX", sizeof(cpuNameDecay));
                        break;

                    default:
                        strncpy(cpuNameDecay, "Intel Pentium", sizeof(cpuNameDecay));
                        break;
                    }
                    break;

                case 6:
                    switch (model)
                    {
                    case 0:
                    case 1:
                        strncpy(cpuNameDecay, "Intel Pentium Pro", sizeof(cpuNameDecay));
                        break;

                    case 3:
                    case 5:
                        strncpy(cpuNameDecay, "Intel Pentium II", sizeof(cpuNameDecay));
                        break;

                    case 6:
                        strncpy(cpuNameDecay, "Intel Celeron", sizeof(cpuNameDecay));
                        break;

                    case 7:
                    case 8:
                        strncpy(cpuNameDecay, "Intel Pentium III", sizeof(cpuNameDecay));
                        break;

                    case 0xa:
                        strncpy(cpuNameDecay, "Intel Pentium III Xeon", sizeof(cpuNameDecay));
                        break;

                    default:
                        requiresCopyFromFakeBuffer = 1;
                        break;
                    }
                    break;

                case 0xf:
                    strncpy(cpuNameDecay, "Intel Pentium 4", sizeof(cpuNameDecay));
                    break;

                default:
                    requiresCopyFromFakeBuffer = 1;
                    break;
                }
            }
            else if (strncmp(fakeCPUName, "AuthenticAMD", sizeof(fakeCPUName)) == 0 ||
                     strncmp(fakeCPUName, "AMD ISBETTER", sizeof(fakeCPUName)) == 0 )
            {
                switch (family)
                {
                case 4:
                    strncpy(cpuNameDecay, "AMD 486", sizeof(cpuNameDecay));
                    break;

                case 5:
                    switch (model)
                    {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        strncpy(cpuNameDecay, "AMD K5", sizeof(cpuNameDecay));
                        break;

                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        strncpy(cpuNameDecay, "AMD K6", sizeof(cpuNameDecay));
                        break;

                    case 8:
                        strncpy(cpuNameDecay, "AMD K6 2", sizeof(cpuNameDecay));
                        break;

                    case 9:
                    case 0xd:
                        strncpy(cpuNameDecay, "AMD K6 III", sizeof(cpuNameDecay));
                        break;

                    default:
                        requiresCopyFromFakeBuffer = 1;
                        break;
                    }
                    break;

                case 6: /* K7 Athlon */
                    switch (model)
                    {
                    case 1:
                    case 2:
                        strncpy(cpuNameDecay, "AMD Athlon", sizeof(cpuNameDecay));
                        break;

                    case 3:
                        strncpy(cpuNameDecay, "AMD Duron", sizeof(cpuNameDecay));
                        break;

                    case 4:
                        strncpy(cpuNameDecay, "AMD Athlon", sizeof(cpuNameDecay));
                        break;

                    default:
                        strncpy(cpuNameDecay, "AMD Athlon", sizeof(cpuNameDecay));
                        break;
                    }
                    break;

                default:
                    requiresCopyFromFakeBuffer = 1;
                    break;
                }
            }
            else
            {
                requiresCopyFromFakeBuffer = 1;
            }

            size_t copyMax;
            const char *copySource;

            if ( requiresCopyFromFakeBuffer )
            {
                copyMax = sizeof(fakeCPUName);
                copySource = fakeCPUName;
            }
            else
            {
                copyMax = sizeof(cpuNameDecay);
                copySource = cpuNameDecay;
            }

            size_t maxCopySize = ( copyMax > cpuNameSize ? cpuNameSize : copyMax );

            memcpy( cpuName, copySource, maxCopySize );

            if ( maxCopySize < cpuNameSize )
            {
                cpuName[ maxCopySize ] = 0;
            }
        }
#endif /* (!defined(__GNUC__)) */
    }

    RWRETURNVOID();
}
#pragma warning(pop)

/*
 * _rwCPUHaveMMX checks whether CPU supports MMX functions
 */
RwBool
_rwCPUHaveMMX(void)
{
    RwBool  result = FALSE;

    RWFUNCTION(RWSTRING("_rwCPUHaveMMX"));

    if (CPUHaveCPUID())
    {
        result = CPUGetFeatures();

        result = ((result & CPUID_MMX) != 0);
    }

    RWRETURN(result);
}

/*
 * _rwCPUHaveSSE checks whether CPU supports SSE functions
 */
RwBool
_rwCPUHaveSSE(void)
{
    RwBool  result = FALSE;

    RWFUNCTION(RWSTRING("_rwCPUHaveSSE"));

    if (CPUHaveCPUID())
    {
        result = CPUGetFeatures();

        result = ((result & (CPUID_SSE | CPUID_SSE2)) != 0);
    }

    RWRETURN(result);
}

/*
 * _rwCPUHaveSSE2 checks whether CPU supports SSE functions
 */
RwBool
_rwCPUHaveSSE2(void)
{
    RwBool  result = FALSE;

    RWFUNCTION(RWSTRING("_rwCPUHaveSSE2"));

    if (CPUHaveCPUID())
    {
        result = CPUGetFeatures();

        result = ((result & CPUID_SSE2) != 0);
    }

    RWRETURN(result);
}

/*
 * _rwCPUHave3DNow checks whether CPU supports 3DNow functions
 */
RwBool
_rwCPUHave3DNow(void)
{
    RwBool  result = FALSE;

    RWFUNCTION(RWSTRING("_rwCPUHave3DNow"));

    if (CPUHaveCPUID())
    {
        if (CPUHaveExtFeatures())
        {
            result = CPUGetExtFeatures();

            result = ((result & CPUID_EXT_3DNOW) != 0);
        }
    }

    RWRETURN(result);
}

/*
 * _rwGetWindowsVersion copies the operating system version name to the buffer
 */
#if defined(WIN32)
RwBool
_rwCPUGetOSName(RwChar *osName)
{
    OSVERSIONINFOEX osvi;
    RwBool osVersionInfoEx;

    RWFUNCTION(RWSTRING("_rwCPUGetWindowsVersion"));

    osName[0] = 0;

    /* Try calling GetVersionEx using the OSVERSIONINFOEX structure.
       If that fails, try using the OSVERSIONINFO structure. */

    memset(&osvi, 0, sizeof(OSVERSIONINFOEX));

    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    osVersionInfoEx = GetVersionEx((OSVERSIONINFO *)&osvi);
    if (osVersionInfoEx == FALSE)
    {
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if (GetVersionEx((OSVERSIONINFO *)&osvi) == FALSE)
        {
            RWRETURN(FALSE);
        }
    }

    switch (osvi.dwPlatformId)
    {
        /* Test for the Windows NT product family. */
        case VER_PLATFORM_WIN32_NT:
            /* Test for the specific product family. */
            if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
            {
                osName += rwsprintf(osName, "Microsoft Windows .NET Server 2003 family, ");
            }
            else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
            {
                osName += rwsprintf(osName, "Microsoft Windows XP ");
            }
            else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
            {
                osName += rwsprintf(osName, "Microsoft Windows 2000 ");
            }
            else if ( osvi.dwMajorVersion <= 4 )
            {
                osName += rwsprintf(osName, "Microsoft Windows NT ");
            }

            /* Test for specific product on Windows NT 4.0 SP6 and later. */
            #if defined(VER_NT_WORKSTATION) && defined(VER_NT_SERVER)
            if (osVersionInfoEx)
            {
                /* Test for the workstation type. */
                if ( osvi.wProductType == VER_NT_WORKSTATION )
                {
                    if ( osvi.dwMajorVersion == 4 )
                    {
                        osName += rwsprintf(osName, "Workstation 4.0 " );
                    }
                    else if ( osvi.wSuiteMask & VER_SUITE_PERSONAL )
                    {
                        osName += rwsprintf(osName, "Home Edition " );
                    }
                    else
                    {
                        osName += rwsprintf(osName, "Professional " );
                    }
                }
                /* Test for the server type. */
                else if ( osvi.wProductType == VER_NT_SERVER )
                {
                    if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
                    {
                        if ( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                        {
                            osName += rwsprintf(osName, "Datacenter Edition " );
                        }
                        else if ( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                        {
                            osName += rwsprintf(osName, "Enterprise Edition " );
                        }
#if (!defined(__GNUC__))       
                        else if ( osvi.wSuiteMask == VER_SUITE_BLADE )
                        {
                            osName += rwsprintf(osName, "Web Edition " );
                        }
#endif /* (!defined(__GNUC__)) */
                        else
                        {
                            osName += rwsprintf(osName, "Standard Edition " );
                        }
                    }
                    else if( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
                    {
                        if ( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                        {
                            osName += rwsprintf(osName, "Datacenter Server " );
                        }
                        else if ( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                        {
                            osName += rwsprintf(osName, "Advanced Server " );
                        }
                        else
                        {
                            osName += rwsprintf(osName, "Server " );
                        }
                    }
                    else  /* Windows NT 4.0 */
                    {
                        if ( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                        {
                            osName += rwsprintf(osName, "Server 4.0, Enterprise Edition " );
                        }
                        else
                        {
                            osName += rwsprintf(osName, "Server 4.0 " );
                        }
                    }
                }
            }
            else
            #endif /* defined(VER_NT_WORKSTATION) && defined(VER_NT_SERVER) */
            {
                if ( osvi.dwMajorVersion <= 4 )
                {
                    osName += rwsprintf(osName, "%d.%d ", osvi.dwMajorVersion, osvi.dwMinorVersion);
                }
            }

            /* Test Service Pack info. */
            if (osVersionInfoEx)
            {
                if (osvi.wServicePackMajor)
                {
                    if (osvi.wServicePackMinor)
                    {
                        osName += rwsprintf(osName, "Service Pack %d.%d", osvi.wServicePackMajor, osvi.wServicePackMinor);
                    }
                    else
                    {
                        osName += rwsprintf(osName, "Service Pack %d", osvi.wServicePackMajor);
                    }
                }
            }
            break;

        /* Test for the Windows 9x product family. */
        case VER_PLATFORM_WIN32_WINDOWS:
            if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
            {
                osName += rwsprintf(osName, "Microsoft Windows 95 ");
                if ( osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B' )
                {
                    osName += rwsprintf(osName, "OSR2 " );
                }
            }
            else if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
            {
                osName += rwsprintf(osName, "Microsoft Windows 98 ");
                if ( osvi.szCSDVersion[1] == 'A' )
                {
                    osName += rwsprintf(osName, "SE " );
                }
            }
            else if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
            {
                osName += rwsprintf(osName, "Microsoft Windows Millennium Edition");
            } 
            break;
    }

    RWRETURN(TRUE);
}
#endif /* defined(WIN32) */
