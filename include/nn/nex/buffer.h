/**
 * @file buffer.h
 * @brief NEX buffer implementation.
 */

#pragma once

#include "string.h"
#include "types.h"

namespace nn
{
    namespace nex
    {
        // todo
        class Buffer
        {
        public:
            Buffer(nn::nex::Buffer const &);
            Buffer(nn::nex::Buffer &&);
            Buffer(nn::nex::String const &);

            void FreeDataBuffer(u8 *, u64);

            virtual ~Buffer();
        };
    };
};