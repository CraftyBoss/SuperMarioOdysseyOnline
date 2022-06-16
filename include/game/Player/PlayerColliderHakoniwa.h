#pragma once

#include "types.h"
#include "PlayerCollider.h"
#include "game/Interfaces/IUsePlayerCollision.h"

class PlayerColliderHakoniwa : public IUsePlayerCollision {
    public:
        f32 getColliderRadius() const;
        f32 getColliderDiskHalfHeight() const;
        f32 getSafetyCeilSpace() const;
        f32 getCeilCheckHeight() const;
        f32 getGroundHeight() const;
        f32 getShadowDropHeight() const;
        f32 getFallDistance() const;

        PlayerCollider *getPlayerCollider() const;
};