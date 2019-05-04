#pragma once
#include <src/rtfsyst.h>
#include "CPatch.h"

#define MAX_NB_FILES_PER_FS    20

struct FileFunctions {
    void *rwfexist;
    void *rwfopen;
    void *rwfclose;
    void *rwfread;
    void *rwfwrite;
    void *rwfgets;
    void *rwfputs;
    void *rwfeof;
    void *rwfseek;
    void *rwfflush;
    void *rwftell;
};

FileFunctions fileFunctions;

FileFunctions *RwOsGetFileInterface() {
    return &fileFunctions;
}

void MakeFileFunctionsHook() {
    fileFunctions.rwfexist = &RwFexist;
    fileFunctions.rwfopen = (void *)0x6526B0;
    fileFunctions.rwfclose = (void *)0x652540;
    fileFunctions.rwfread = (void *)0x652EC0;
    fileFunctions.rwfwrite = (void *)0x6531B0;
    fileFunctions.rwfgets = (void *)0x652A30;
    fileFunctions.rwfputs = (void *)0x652C20;
    fileFunctions.rwfeof = (void *)0x672EA0;
    fileFunctions.rwfseek = (void *)0x652E60;
    fileFunctions.rwfflush = (void *)0x6525D0;
    fileFunctions.rwftell = (void *)0x652D50;
    CPatch::RedirectJump(0x663580, RwOsGetFileInterface);
    CPatch::RedirectJump(0x663650, RwFexist);
}
