/**
 * @file DrawContext.h
 * @brief Defines a draw context for textures in a GPU buffer.
 */

#pragma once

#include "types.h"
#include "DisplayList.h"

#include <sead/gfx/seadDrawContext.h>
#include <sead/thread/seadCriticalSection.h>

namespace agl
{
    class DrawContext : public sead::DrawContext
    {
    public:
        DrawContext();
        virtual ~DrawContext();

        void setCommandBuffer(agl::DisplayList *);
        void flushCommandBuffer();
        void setBoundRenderBuffer(u64 *);
        void barrierTexture(u32);
        void barrierShader(u32);
        bool isTextureDirty(u32, s32) const;
        void setTextureDirty(s32);
        void setCommandBufferTemporary();

        agl::DisplayList* mDisplayList; // _F0
        u64* _F8; // agl::RenderBuffer*
        u8 _100;
        u8 _101;
        u8 _102;
        u8 _103;
        u32 _104;
        u32 _10C;
        sead::CriticalSection mCriticalSection; // _110
    };
};