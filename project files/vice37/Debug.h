#pragma once
#include <Windows.h>
#include <stdio.h>

bool DebugMsg(char *message, ...)
{
	char text[512];
	va_list ap;
	va_start(ap, message);
	vsnprintf(text, 512, message, ap);
	va_end(ap);
	MessageBoxA(NULL, text, "Debug message", 0);
	return false;
}

bool DebugLine(char *line, ...)
{
	char text[1024];
	va_list ap;
	va_start(ap, line);
	vsnprintf(text, 1024, line, ap);
	va_end(ap);
	FILE *f = fopen("debug37.txt", "at");
	fputs(text, f);
	fputs("\n", f);
	fclose(f);
	return false;
}