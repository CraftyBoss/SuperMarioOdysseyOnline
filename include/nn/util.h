#pragma once

#include "../types.h"

namespace nn { namespace util {

s32 SNPrintf(char* s, ulong n, const char* format, ...);
s32 VSNPrintf(char* s, ulong n, const char* format, va_list arg);

} }
