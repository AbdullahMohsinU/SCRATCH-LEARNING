#include "cook.h"

bool _cond_result = false;

void cook(const char* str) {
    DWORD written;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleA(hOut, str, strlen(str), &written, NULL);
}

void dash() {
    if (!_cond_result)
        cook("DASH: Else block executed.\n");
}

