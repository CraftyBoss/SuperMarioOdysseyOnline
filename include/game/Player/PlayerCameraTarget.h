#pragma once

#include "al/actor/ActorCameraTarget.h"

class PlayerCameraTarget : public al::ActorCameraTarget 
{
    public:
        PlayerCameraTarget(al::LiveActor const *player);

        float unk1;
        float unk2;
};