/**
 * @file ShaderHolder.h
 * @brief Defines classes for shader storage.
 */

#pragma once

#include "sead/heap.h"

namespace agl
{
    namespace detail
    {
        class ShaderHolder
        {
        public:

            class SingletonDisposer_
            {
            public:
                virtual ~SingletonDisposer_();

                static SingletonDisposer_ sStaticDisposer;
            };

            ShaderHolder();

            static agl::detail::ShaderHolder* createInstance(sead::Heap *);
            static void deleteInstance();
        };
    };
};