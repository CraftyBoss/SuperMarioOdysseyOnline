/**
 * @file viewport.h
 * @brief Basic Viewport class.
 */

#pragma once

#include <types.h>
#include <sead/math/seadVector.h>
#include <sead/gfx/seadDrawContext.h>
#include <sead/gfx/seadFrameBuffer.h>

namespace sead
{
    class Viewport
    {
    public:
        Viewport();
        Viewport(f32 left, f32 top, f32 right, f32 bottom);
        Viewport(sead::LogicalFrameBuffer const&);

        void project(sead::Vector2<f32> *, sead::Vector3<f32> const &) const;
        // void project(sead::Vector2<f32> *, sead::Vector3<f32> const &) const;

        void apply(sead::DrawContext *, sead::LogicalFrameBuffer const &) const;

        f32 _8;
        f32 Viewport_xC;
        f32 _10;
        f32 _14;
    };
};