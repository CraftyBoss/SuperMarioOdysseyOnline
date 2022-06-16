#pragma once

#include "al/LiveActor/LiveActor.h"

namespace al
{
    template<typename T>
    al::LiveActor *createActorFunction(const char *actorName);

} // namespace al

