#pragma once

#include "al/factory/Factory.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/modifiers/GravityModifier.hpp"
#include "server/gamemode/modifiers/ModeModifierBase.hpp"
#include "server/gamemode/modifiers/NoCapModifier.hpp"

typedef ModeModifierBase* (*createMod)(GameModeBase* mode);

template <class T>
ModeModifierBase* createModifier(GameModeBase* mode)
{
    return new T(mode);
};

__attribute((used)) constexpr al::NameToCreator<createMod> modifierTable[] = {
    {"Gravity", &createModifier<GravityModifier>},
    {"NoCap", &createModifier<NoCapModifier>}
};

constexpr const char* modifierNames[] = {
    "Sticky Gravity",
    "Cappy-Less"
};

class ModifierFactory : public al::Factory<createMod> {
    public:
        ModifierFactory(const char *fName) {
            this->factoryName = fName;
            this->actorTable = modifierTable;
            this->factoryCount = sizeof(modifierTable)/sizeof(modifierTable[0]);
        };
};