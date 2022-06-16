/**
 * @file RenderTargetColor.h
 * @brief Defines classes implement a rendering target color.
 */

#pragma once

#include "TextureData.h"

namespace agl
{
    class RenderTargetColor : agl::TextureData
    {
    public:
        RenderTargetColor();
        RenderTargetColor(agl::TextureData const &, u32, u32);

        void onApplyTextureData_();
        void initRegs_(u32) const;

        s32 _128;
        u32 _12C;
        u32 _130;
        u32 _134;
        u64 _138;
        u64 _140;
        u64 _148;
        u64 _150;
        u64 _158;
        u64 _160;
        u64 _168;
        u64 _170;
    };
};