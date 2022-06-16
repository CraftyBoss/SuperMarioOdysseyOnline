#pragma once

#include "game/Interfaces/IUseDimension.h"
#include "PlayerActorBase.h"
#include "PlayerPuppet.h"
#include "PlayerInput.h"
#include "PlayerAnimator.h"
#include "HackCap.h"
#include "PlayerModelKeeper.h"
#include "PlayerColliderHakoniwa.h"
#include "PlayerConst.h"
#include "PlayerHackKeeper.h"
#include "PlayerInfo.h"
#include "PlayerInitInfo.h"

class YukimaruRacePlayer : public PlayerActorBase , public IUseDimension {
    public:
        void initPlayer(al::ActorInitInfo const &, PlayerInitInfo const &);
        undefined size[0x1A8];
};