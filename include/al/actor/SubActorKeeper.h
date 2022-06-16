#pragma once


#include "container/seadPtrArray.h"
namespace al {
    struct SubActorInfo {
        struct LiveActor* mActor;
        void* unkPtr;
        int unkInt;
    };

    class SubActorKeeper {
        al::LiveActor* mRootActor;
        sead::PtrArray<SubActorInfo> mArray;
    };
}