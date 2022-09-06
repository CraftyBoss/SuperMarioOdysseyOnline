#pragma once

#include "Resource.h"
#include "types.h"

namespace al {
    class ActorResourceHolder {

        ActorResourceHolder(int);
        ~ActorResourceHolder();

        void tryFindActorResource(sead::SafeString const&);
        void findActorResourceImpl(sead::SafeString const&);
        void createActorResource(sead::SafeString const&, al::Resource*, al::Resource*);
        void removeAll();
        void eraseResourceUser(al::Resource*);
        void freeErasedActorResource();

    };
}