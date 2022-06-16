#pragma once

#include "types.h"

namespace nn { namespace atk { 

class SoundArchive
{
public:
    const char* GetItemLabel(u32 id) const;
    u32 GetItemId(char const* label) const;
};

class SoundActor    // Inherits SoundStartable, size: 0x7C
{
public:
    virtual ~SoundActor();
    u8 data[0x7C-0x4];
};

} }
