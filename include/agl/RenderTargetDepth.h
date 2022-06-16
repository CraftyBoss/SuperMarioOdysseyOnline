/**
 * @file RenderTargetDepth.h
 * @brief Defines a class to represent a render target depth.
 */

#pragma once

#include "TextureData.h"

namespace agl
{
    class RenderTargetDepth : public agl::TextureData
    {
    public:
        RenderTargetDepth();
        RenderTargetDepth(agl::TextureData const &, u32, u32);

        void onApplyTextureData_();
        void initRegs_(u32) const;

        s32 _128;
        u32 _12C;
        u64 _130;
        u64 _138;
        u64 _140;
        u64 _148;
        u8 _150[0x178-0x150];
    };
};