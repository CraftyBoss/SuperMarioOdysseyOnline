/**
 * @file GameDataFile.h
 * @brief Utilitis for agl namespace.
 */

#pragma once

#include "../types.h"
#include "DrawContext.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadMatrix.h"
#include "sead/gfx/seadColor.h"

namespace agl {
    namespace utl {
        class DevTools{
            public:
            void static beginDrawImm(agl::DrawContext *,sead::Matrix34<float> const&,sead::Matrix44<float> const&);
            void static drawTriangleImm(agl::DrawContext*, sead::Vector3<float> const&, sead::Vector3<float> const&, sead::Vector3<float> const&, sead::Color4f const&);
            void static drawLineImm(agl::DrawContext*, sead::Vector3<float> const&, sead::Vector3<float> const&, sead::Color4f const&, float);
        };
    };
};