// RenderWare filesystem functions.

#include <rwcore.h>
#include "rtfsyst.h"

#include <stdio.h>
#include <sys/stat.h>

#pragma warning(push)
#pragma warning(disable: 4996)

void* RwFopen( const RwChar *path, const RwChar *mode )
{
    return fopen( path, mode );
}

#pragma warning(pop)

RwInt32 RwFclose( void *handle )
{
    return fclose( (FILE*)handle );
}

size_t RwFread( void *addr, size_t size, size_t count, void *fptr )
{
    return fread( addr, size, count, (FILE*)fptr );
}

size_t RwFwrite( const void *addr, size_t size, size_t count, void *fptr )
{
    return fwrite( addr, size, count, (FILE*)fptr );
}

RwInt32 RwFseek( void *fptr, long offset, RwInt32  origin )
{
    return fseek( (FILE*)fptr, offset, origin );
}

RwChar* RwFgets( RwChar *buffer, RwInt32 maxLen, void *fptr )
{
    return fgets( buffer, maxLen, (FILE*)fptr );
}

RwInt32 RwFputs( const RwChar *buffer, void *fptr )
{
    return fputs( buffer, (FILE*)fptr );
}

RwInt32 RwFeof( void *fptr )
{
    return feof( (FILE*)fptr );
}

RwBool RwFexist( const RwChar *name )
{
    struct stat st;
    
    int result = stat( name, &st );

    return ( result == 0 );
}

RwInt32 RwFtell( void *fptr )
{
    return ftell( (FILE*)fptr );
}