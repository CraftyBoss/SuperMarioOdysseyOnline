/**
 * @file audio.h
 * @brief Audio implementation.
 */

#pragma once

#include "types.h"

namespace nn
{
    namespace audio
    {
        struct AudioRendererConfig
        {
            u64* _0;
            u64* _8;
            u64* _10;
            u64* _18;
            u64* _20;
            u64* _28;
            u64* _30;
            u64* _38;
            u64* _40;
            u64* _48;
            u64* _50;
        };

        struct DelayType
        {
            u64* _0;
        };

        struct FinalMixType
        {
            u64* _0;
        };
        
        struct SubMixType
        {
            u64* _0;
        };

        void SetDelayInputOutput(nn::audio::DelayType *, s8 const *, s8 const *, s32);
        void* RemoveDelay(nn::audio::AudioRendererConfig *, nn::audio::DelayType *, nn::audio::FinalMixType *);
        void* RemoveDelay(nn::audio::AudioRendererConfig *, nn::audio::DelayType *, nn::audio::SubMixType *);
        bool IsDelayRemoveable(nn::audio::DelayType *);
    };
};