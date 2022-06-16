#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/event/IEventFlowEventReceiver.h"
#include "IUseDemoSkip.h"

class ShineTowerRocket : public al::LiveActor, public al::IEventFlowEventReceiver, public IUseDemoSkip {
    // virtual void makeActorDead 0x30
};