#pragma once

#include "al/factory/Factory.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/hns/HideAndSeekMode.hpp"

typedef GameModeBase* (*createMode)(const char* name);

template <class T>
GameModeBase* createGameMode(const char* name)
{
    return new T(name);
};

__attribute((used)) constexpr al::NameToCreator<createMode> modeTable[] = {
    {"HideAndSeek", &createGameMode<HideAndSeekMode>}
};

constexpr const char* modeNames[] = {
    "Hide and Seek"
};

class GameModeFactory : public al::Factory<createMode> {
    public:
        GameModeFactory(const char *fName) {
            this->factoryName = fName;
            this->actorTable = modeTable;
            this->factoryCount = sizeof(modeTable)/sizeof(modeTable[0]);
        };

        constexpr static const char* getModeString(GameMode mode);
        constexpr static const char* getModeName(GameMode mode);
        constexpr static const char* getModeName(int idx);
        constexpr static int getModeCount();
};

// TODO: possibly use shadows' crc32 hash algorithm for this
constexpr const char* GameModeFactory::getModeString(GameMode mode) {
    if(mode >= 0 && (size_t)mode < sizeof(modeTable)/sizeof(modeTable[0]))
        return modeTable[mode].creatorName;
    return nullptr;
}

constexpr const char* GameModeFactory::getModeName(GameMode mode) {
    if(mode >= 0 && (size_t)mode < sizeof(modeNames)/sizeof(modeNames[0]))
        return modeNames[mode];
    return nullptr;
}

constexpr const char* GameModeFactory::getModeName(int idx) {
    if(idx >= 0 && (size_t)idx < sizeof(modeNames)/sizeof(modeNames[0]))
        return modeNames[idx];
    return nullptr;
}

constexpr int GameModeFactory::getModeCount() {
    return sizeof(modeTable)/sizeof(modeTable[0]);
}