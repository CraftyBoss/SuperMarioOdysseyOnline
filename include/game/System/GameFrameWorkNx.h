#pragma once

#include "al/debug/GpuPerf.h"
#include "agl/DrawContext.h"
#include "agl/RenderBuffer.h"
#include "sead/framework/seadGameFramework.h"
#include "al/hio/HioNode.h"

namespace al
{
    class GameFrameworkNx : public sead::GameFrameworkNx, public al::HioNode {
        public:
            unsigned char padding_198[0x198];
            agl::RenderBuffer *mCurRenderBuffer; // 0x198
            unsigned char padding_210[0x208 - 0x198];
            agl::DrawContext *mDrawContext; // 0x210
            agl::RenderBuffer *mFirstRenderBuffer; // 0x218
            void *unkPtr1; // 0x220
            agl::RenderBuffer *mSecondRenderBuffer; // 0x228
            unsigned char padding_248[0x18];
            al::GpuPerf *mGpuPerf; // 0x248
            unsigned char padding_268[0x18];
            bool unkBool; // 0x268 
            bool unkBool2; // 0x269
    };
} // namespace al
