/**
 * @file RootObject.h
 * @brief RootObject for NEX.
 */

#pragma once

#include "types.h"

namespace nn
{
    namespace nex
    {
        class RootObject
        {
        public:
            enum TargetPool;

            virtual ~RootObject();

            void* operator new(std::u64);
            void operator delete(void *);
            void* operator new(std::u64, char const *, u32);
            void* operator new[](std::u64);
            void* operator new[](std::u64,  char const *, u32);
            void operator delete[](void *);
            void operator delete(void *,char const *, u32);
            void operator delete[](void *,char const *, u32);
            void* operator new(std::u64, nn::nex::RootObject::TargetPool);
            void* operator new(std::u64, nn::nex::RootObject::TargetPool, char const *, u32);
        };
    };
};