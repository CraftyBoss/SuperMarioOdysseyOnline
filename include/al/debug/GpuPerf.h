#pragma once

#include "agl/DrawContext.h"
#include "sead/gfx/seadFrameBuffer.h"

// seems to be a static class for managing agl::fctr::GPUStressChecker
namespace al
{
    class GpuPerf {
        public:
            GpuPerf(void);
            void beginPerf(agl::DrawContext *);
            void endPerf(agl::DrawContext *);
            void update(void);
            void drawResult(agl::DrawContext *,sead::FrameBuffer const*) const;

            // this class has no members
    };
} // namespace al
