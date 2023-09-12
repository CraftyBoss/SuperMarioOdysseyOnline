#pragma once

#include "al/LiveActor/LiveActor.h"

namespace rs {
    void createPlayerSklRetargettingInfo(al::LiveActor *,sead::Vector3f const&);
    void initItemByPlacementInfo(al::LiveActor *, al::ActorInitInfo const &, bool);
    float setShadowDropLength(al::LiveActor *,al::ActorInitInfo const&,char const*);
} // namespace rs
