/**
 * @file hid.h
 * @brief Functions that help process gamepad inputs.
 */

#pragma once

#include "types.h"
#include "util.h"

namespace nn
{
    namespace hid
    {
        struct NpadHandheldState;
        struct NpadStyleTag;

        void InitializeNpad();
        void SetSupportedNpadIdType(u32 const* , u64);
        void SetSupportedNpadStyleSet(nn::util::BitFlagSet<32, nn::hid::NpadStyleTag>);
        void GetNpadStyleSet(u32 const &);
        void GetNpadStates(nn::hid::NpadHandheldState *, s32, u32 const &);
    };
};