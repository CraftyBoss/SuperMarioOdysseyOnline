/**
 * @file ResModel.h
 * @brief Resource model.
 */

#pragma once

#include "types.h"
#include "nn/gfx/api.h"
#include "nn/gfx/device.h"

namespace nn
{
    namespace g3d
    {
        class ResMaterial;
        
        typedef void* TextureRef;

        class ResModel
        {
        public:
            u64 BindTexture(nn::g3d::TextureRef (*)(char const *, void *), void *);
            void ForceBindTexture(nn::g3d::TextureRef const &, char const *);
            void ReleaseTexture();
            void Setup(nn::gfx::TDevice<nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>> *);
            void Cleanup(nn::gfx::TDevice<nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>> *);
            void Reset();
            void Reset(u32);
            nn::g3d::ResMaterial* FindMaterial(char const *materialName) const;

            u8 _0[0x70];
        };
    };
};