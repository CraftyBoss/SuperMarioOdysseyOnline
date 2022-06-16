#pragma once

#include "sead/prim/seadSafeString.h"
#include "sead/heap/seadHeap.h"
#include "sead/math/seadVector.h"
#include "sead/thread/seadThread.h"
#include "sead/prim/seadRuntimeTypeInfo.h"

struct NVNcommandBuffer;
struct NVNcommandBufferMemoryEvent;

namespace sead
{
    class GameFrameworkNx {
        public:
            struct CreateArg;

            GameFrameworkNx(sead::GameFrameworkNx::CreateArg const&);
            ~GameFrameworkNx();
            void initializeGraphicsSystem(sead::Heap *,sead::Vector2<float> const&);
            void outOfMemoryCallback_(NVNcommandBuffer *,NVNcommandBufferMemoryEvent,ulong,void *);
            void presentAsync_(sead::Thread *,long);
            void getAcquiredDisplayBufferTexture(void);
            void setVBlankWaitInterval(uint);
            void requestChangeUseGPU(bool);
            void getGraphicsDevToolsAllocatorTotalFreeSize(void);
            void initRun_(sead::Heap *);
            void runImpl_(void);
            void createMethodTreeMgr_(sead::Heap *);
            void mainLoop_(void);
            void procFrame_(void);
            void procDraw_(void);
            void procCalc_(void);
            void present_(void);
            void waitVsyncEvent_(void);
            void swapBuffer_(void);
            void clearFrameBuffers_(int);
            void waitForGpuDone_(void);
            void setGpuTimeStamp_(void);
            void getMethodFrameBuffer(int);
            void getMethodLogicalFrameBuffer(int);
            void checkDerivedRuntimeTypeInfo(sead::RuntimeTypeInfo::Interface const*);
            void getRuntimeTypeInfo(void);
            float calcFps(void);
            void setCaption(sead::SafeStringBase<char> const&);
    };
} // namespace sead
