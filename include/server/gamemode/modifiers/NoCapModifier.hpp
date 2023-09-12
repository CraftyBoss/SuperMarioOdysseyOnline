#pragma once

#include "server/gamemode/modifiers/ModeModifierBase.hpp"

class NoCapModifier : public ModeModifierBase {
public:
    NoCapModifier(GameModeBase* modeInfo);
    
    void enable() override;
    void disable() override;
};