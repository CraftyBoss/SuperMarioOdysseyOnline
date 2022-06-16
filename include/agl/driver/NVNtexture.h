/**
 * @file device.h
 * @brief Defines a class to represent a NVN texture.
 */

#pragma once

#include "types.h"

class NVNtextureView;
class NVNtexture;

namespace agl
{
    namespace driver
    {
        class NVNtexture_
        {
        public:
            NVNtexture_();
            NVNtexture_(agl::driver::NVNtexture_ const &);
            ~NVNtexture_();

            void releaseTexture();
            void updateTexId_(s32 newID);
            //agl::driver:NVNtexture_ operator=(agl::driver::NVNtexture_ const &);
            bool registerTexture(NVNtexture const *, NVNtextureView const *, char const *, bool);

            void setReference_() const;

            u8 _0[0xC0]; // NVNtexture
            s32 mTextureID; // _C0
            u8 _C4;
            u8 _C5;
            u8 _C6;
            u8 _C7;
        };
    };
};