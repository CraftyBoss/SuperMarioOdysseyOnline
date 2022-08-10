#pragma once

#include "al/factory/Factory.h"
#include "server/hns/HideAndSeekConfigMenu.hpp"
#include "server/gamemode/GameModeConfigMenu.hpp"

typedef GameModeConfigMenu* (*createMenu)(const char* name);

template <class T>
GameModeConfigMenu* createGameModeConfigMenu(const char* name) {
    return new T();
};

__attribute((used)) constexpr al::NameToCreator<createMenu> menuTable[] = {
    {"HideAndSeek", &createGameModeConfigMenu<HideAndSeekConfigMenu>},
};

class GameModeConfigMenuFactory : public al::Factory<createMenu> {
public:
    GameModeConfigMenuFactory(const char* fName) {
        this->factoryName = fName;
        this->actorTable = menuTable;
        this->factoryCount = sizeof(menuTable) / sizeof(menuTable[0]);
    };

    constexpr static const char* getMenuName(int idx);
    constexpr static int getMenuCount();
};

constexpr const char* GameModeConfigMenuFactory::getMenuName(int idx) {
    if (idx >= 0 && idx < sizeof(menuTable) / sizeof(menuTable[0]))
        return menuTable[idx].creatorName;
    return nullptr;
}

constexpr int GameModeConfigMenuFactory::getMenuCount() {
    return sizeof(menuTable) / sizeof(menuTable[0]);
}