#ifndef COOK_H
#define COOK_H

#include <iostream>
#include <windows.h>
#include <cstring>

extern bool _cond_result;

void cook(const char* str);
void dash();

// Your custom syntax macros
#define check(condition) \
    _cond_result = (condition); \
    if (_cond_result)

#define run for
#define to =
#define until <
#endif

