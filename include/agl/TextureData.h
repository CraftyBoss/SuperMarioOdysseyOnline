/**
 * @file TextureData.h
 * @brief Defines a class that implements a texture compressor, and a texture data storage container.
 */

#pragma once

#include "detail/Surface.h"
#include "driver/NVNtexture.h"

#include "sead/prim/seadSafeString.h"

namespace agl
{
    class TextureData
    {
    public:
        class CompressToWork
        {
        public:
            CompressToWork(agl::TextureData const &);

            u64 _0;
            u64 _8;
            u64 _10;
            u64 _18;
            u32 _20;
            u64 _28;
            u64 _30;
            u32 _38;
            u64 _40;
            agl::detail::Surface mSurface; // _48
            agl::driver::NVNtexture_ mTexture; // _70
        };

        TextureData();

        void setMipLevelNum_(s32, bool);
        u16 getMinSlice_() const;
        void getTextureFormatName() const;
        u32 calcMipByteSize(u32) const;
        bool isCompressedFormat() const;
        bool isRenderTargetCompressAvailable() const;
        bool isDepthFormat() const;
        bool hasStencil() const;
        void invalidateCPUCache();
        void flushCPUCache() const;
        void setDebugLabel(sead::SafeStringBase<char> const &);
        void getDebugLabel() const;

        u64 _0;
        u32 _8;
        u32 C;
        u64 _10;
        u64 _18;
        u64 _20;
        u64 _28;
        agl::detail::Surface mSurface; // _30
        agl::TextureFormat mTextureFormat; // _54
        u8 _58[0x120-0x58];
        char* _120; // "agl::TextureData string"
    };
};