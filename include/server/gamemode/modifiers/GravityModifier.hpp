#pragma once

#include "ModeModifierBase.hpp"
#include "game/StageScene/StageScene.h"

class GravityModifier : public ModeModifierBase {
public:
    GravityModifier(GameModeBase* modeInfo);
    
    void enable() override;
    void disable() override;
    void update() override;

    void setCamTicket(al::CameraTicket *ticket) {mTicket = ticket;};

private:
    al::CameraTicket *mTicket = nullptr;
};