#pragma once

#include "al/actor/ActorInitInfo.h"

namespace alPlacementFunction {
    void getModelName(char const**,al::ActorInitInfo const&);
    void getModelName(char const**,al::PlacementInfo const&);
    bool tryGetModelName(char const**,al::PlacementInfo const&);
    bool tryGetModelName(char const**, al::ActorInitInfo const&);

}