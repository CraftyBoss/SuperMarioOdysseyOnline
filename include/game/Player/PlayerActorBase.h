#pragma once
/**
 * @file PlayerActorBase.h
 * @brief base class for PlayerActor
* Vtable loc: 1D77980
*/

#include "PlayerHackKeeper.h"
#include "al/LiveActor/LiveActor.h"
#include "game/Interfaces/IUsePlayerHack.h"

class PlayerActorBase : public al::LiveActor , public IUsePlayerHack {
    public: 
        PlayerHackKeeper *getPlayerHackKeeper() const; 
        void movement(void);
        int getPortNo();
};