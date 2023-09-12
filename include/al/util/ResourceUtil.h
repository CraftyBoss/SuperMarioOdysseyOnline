#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/resource/ActorResourceHolder.h"
#include "al/resource/ActorResource.h"

namespace al {

    al::ActorResource *findOrCreateActorResource(al::ActorResourceHolder *,char const*,char const*);
    al::ActorResource* findOrCreateActorResourceWithAnimResource(al::ActorResourceHolder*,
                                                                 char const*, char const*,
                                                                 char const*, bool);

    al::Resource *getModelResource(al::LiveActor const*);
    al::Resource *getModelResourceYaml(al::LiveActor const*,char const*,char const*);

}