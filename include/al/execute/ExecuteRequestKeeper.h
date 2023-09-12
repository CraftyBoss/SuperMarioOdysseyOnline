#pragma once

#include "types.h"

namespace al {
  struct LiveActor;
}

namespace al {
class ExecuteRequestKeeper {
    public:
        ExecuteRequestKeeper(int);
        void executeRequestActorMovementAllOn();
        void executeRequestActorMovementAllOff();
        void executeRequestActorDrawAllOn();
        void executeRequestActorDrawAllOff();
        void request(al::LiveActor*, int);

        void *mActorMovementAllOn; // 0x0
        void *mActorMovementAllOff; // 0x8
        void *mActorDrawAllOn; // 0x10
        void *mActorDrawAllOff; // 0x18

   };
}