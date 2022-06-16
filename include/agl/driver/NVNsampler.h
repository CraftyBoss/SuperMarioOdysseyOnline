/**
 * @file NVNsampler.h
 * @brief Defines a sampler for NVN images.
 */

#pragma once

#include "types.h"

class NVNsampler;

namespace agl
{
    namespace driver
    {
        class NVNsampler_
        {
        public:
            NVNsampler_();
            NVNsampler_(agl::driver::NVNsampler_ const &);
            ~NVNsampler_();

            void releaseSampler();
            bool registerSampler(NVNsampler const &, char const *);
            void updateTextureId(s32);

            u64 _0;
            s16 _8;
        };
    };
};