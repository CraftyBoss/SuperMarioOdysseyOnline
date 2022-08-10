#pragma once

#include "server/gamemode/GameModeBase.hpp"
#include <heap/seadHeap.h>

// base struct containing info about the current gamemode
struct GameModeInfoBase {
    GameMode mMode;
};

#include "server/gamemode/GameModeManager.hpp"