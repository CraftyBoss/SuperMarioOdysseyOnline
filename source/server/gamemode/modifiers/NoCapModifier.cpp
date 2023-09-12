#include "server/gamemode/modifiers/NoCapModifier.hpp"
#include "game/GameData/GameDataFunction.h"
#include "server/gamemode/GameModeBase.hpp"
#include "game/GameData/GameDataHolderAccessor.h"
#include "helpers.hpp"
#include "math/seadVector.h"
#include "rs/util.hpp"
#include "server/gamemode/GameModeManager.hpp"

NoCapModifier::NoCapModifier(GameModeBase* mode) : ModeModifierBase(mode) {}

void NoCapModifier::enable() {
    ModeModifierBase::enable();
}

void NoCapModifier::disable() {
    ModeModifierBase::disable();
}