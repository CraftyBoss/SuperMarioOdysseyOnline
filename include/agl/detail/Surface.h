/**
 * @file Surface.h
 * @brief Defines classes to setup NVN textures on a surface.
 */

#pragma once

#include "types.h"
#include "agl/util.h"

class NVNtextureBuilder;
class NVNtexture;

namespace agl
{
    namespace detail
    {
        struct SurfaceBase;

        class Surface
        {
        public:
            Surface();
            void initialize(agl::TextureType, agl::TextureFormat, u32, agl::TextureAttribute, agl::MultiSampleType);
            void initializeSize(u32, u32, u32);
            void copyFrom(agl::detail::SurfaceBase const &);
            void calcSizeAndAlignment();
            void setupNVNtextureBuilder(NVNtextureBuilder *) const;
            void printInfo() const;
            void copyFrom(NVNtexture const &);

            u16 _0;
            u16 _2;
            u16 _4;
            u16 _6;
            u8 _8;
            u8 _9;
            u16 _A;
            u8 C[0x1A-0xC];
            u8 _1A;
            u8 _1B;
            u32 _1C;
            u8 _20;
            u8 _21;
            u8 _22;
            u8 _23;
        };

        struct SurfaceBase
        {
            u64 _0;
            u64 _8;
            u64 _10;
        };
    };
};