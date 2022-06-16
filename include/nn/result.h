#pragma once

#include "types.h"

namespace nn {

struct Result
{
    Result(u32 value = 0) : value(value) { }

    inline bool isSuccess()
    {
        return value == 0;
    }

    inline bool isFailure()
    {
        return !isSuccess();
    }

    u32 value;
};

}
