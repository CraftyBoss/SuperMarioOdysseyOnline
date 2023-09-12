#pragma once

#include "al/actor/ActorInitInfo.h"
#include "container/seadPtrArray.h"

namespace al {
    struct SubActorInfo {
        struct LiveActor* mActor;
        void* unkPtr;
        int unkInt;
    };

    class SubActorKeeper {
    public:
        SubActorKeeper(al::LiveActor*);
        static SubActorKeeper *tryCreate(al::LiveActor*, char const*, int);
        static SubActorKeeper *create(al::LiveActor*);
        void registerSubActor(al::LiveActor*, unsigned int);
        void init(al::ActorInitInfo const&, char const*, int);

        al::LiveActor* mRootActor;
        sead::PtrArray<SubActorInfo> mArray;
    };
}