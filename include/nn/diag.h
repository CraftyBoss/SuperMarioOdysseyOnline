#pragma once

#include "types.h"

namespace nn { namespace diag {

struct ModuleInfo
{
    const char* path;
    u32 base;
    u32 size;
};

u32 GetAllModuleInfo(ModuleInfo** outModuleInfos, void* buffer, u32 bufferLen);
u32 GetRequiredBufferSizeForGetAllModuleInfo();
u32 GetModulePath(char* outName, u32 nameLenMax, u32 address);

} }
