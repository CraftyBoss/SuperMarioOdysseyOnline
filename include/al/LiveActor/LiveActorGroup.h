#pragma once

#include "al/hio/HioNode.h"

namespace al
{
    class LiveActor;

    class LiveActorGroup : public al::HioNode
    {
    public:
        LiveActorGroup(const char *, int);

        virtual void registerActor(al::LiveActor *);

        const char* mGroupName; // _8
        int mMaxActorCount; // _10
        int mActorCount; // _14
        al::LiveActor** mActors; // _18
    };
};