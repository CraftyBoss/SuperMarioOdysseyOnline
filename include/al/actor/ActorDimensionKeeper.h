#pragma once

#include "al/LiveActor/LiveActor.h"

class ActorDimensionKeeper {
    public:
        ActorDimensionKeeper(al::LiveActor const *);
        void validate(void);
        void invalidate(void);
        void forceChange2DKeep(void);
        void forceEndChange2DKeep(void);
        void update(void);
        
        al::LiveActor *curActor; // 0x0
        bool is2D; // 0x8
        bool is2DModel; // 0x9
        bool unk2; // 0x10
        bool unk3; // 0xA
        bool unk4; // 0xB
        struct In2DAreaMoveControl *mMoveControl; // 0x10
};