#pragma once
#include <Windows.h>
#include <stdio.h>
#include "FilePath.h"

bool gDebug = false;

bool DebugMsg(char *message, ...) {
    if (gDebug) {
        char text[512];
        va_list ap;
        va_start(ap, message);
        vsnprintf(text, 512, message, ap);
        va_end(ap);
        MessageBoxA(NULL, text, "Debug message", 0);
    }
    return false;
}

bool DebugLine(char *line, ...) {
    if (gDebug) {
        char text[1024];
        va_list ap;
        va_start(ap, line);
        vsnprintf(text, 1024, line, ap);
        va_end(ap);
        FILE *f = _wfopen((GetModuleDir(NULL) + L"plugins\\debug37.txt").c_str(), L"at");
        if (f) {
            fputs(text, f);
            fputs("\n", f);
            fclose(f);
        }
    }
    return false;
}
