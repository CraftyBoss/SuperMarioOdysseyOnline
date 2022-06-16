#pragma once

#include "NerveStateBase.h"
#include "al/LiveActor/LiveActor.h"

namespace al {
    class ActorStateBase : public al::NerveStateBase {
    public:
        ActorStateBase(const char*, al::LiveActor*);

    protected:
        LiveActor* mLiveActor;
    };
}