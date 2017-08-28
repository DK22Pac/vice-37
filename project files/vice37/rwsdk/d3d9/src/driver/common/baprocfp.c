
/***************************************************************************
 *                                                                         *
 * Module  : baprocfp.c                                                    *
 *                                                                         *
 * Purpose : Processor specific functions                                  *
 *                                                                         *
 **************************************************************************/

#ifdef _WIN32

#include <intrin.h>
#include <float.h>

#pragma warning(push)
#pragma warning(disable: 4996)

unsigned int _rwFPUCtrl = 0;
unsigned int _rwFPUSaveState = 0;

static inline unsigned int __rwProcessorOptimizeFPUControlWord( unsigned int control_word )
{
    return ( ( control_word & ~0x300 ) | 0x3F );
}

void _rwProcessorInitialize( void )
{
    // Get the current control word.
    _rwFPUCtrl = _controlfp( 0, 0 );
    
    // Disable all exceptions and enable single precision.
    {
        unsigned int control_word = _rwFPUCtrl;

        _rwFPUSaveState = control_word;

        _rwFPUCtrl = __rwProcessorOptimizeFPUControlWord( control_word );
    }

    // Load the new control word.
    _controlfp( _rwFPUCtrl, _rwFPUCtrl );
}

void _rwProcessorRelease( void )
{
    // Restore old control word.
    _controlfp( _rwFPUSaveState, _rwFPUSaveState );
}

void _rwProcessorForceSinglePrecision( void )
{
    // Store old control word.
    _rwFPUCtrl = _controlfp( 0, 0 );

    // Optimize it.
    _rwFPUCtrl = __rwProcessorOptimizeFPUControlWord( _rwFPUCtrl );

    // Load the new.
    _controlfp( _rwFPUCtrl, _rwFPUCtrl );
}

#pragma warning(pop)

#endif //_WIN32