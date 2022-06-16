#pragma once

#include "PlayerActorBase.h"
#include "PlayerActorHakoniwa.h"
#include "YukimaruRacePlayer.h"
#include "al/factory/Factory.h"

template <class T>
PlayerActorBase* createPlayerFunction(const char *name);

typedef PlayerActorBase* (*CreateHakoniwa)(const char* name);

static al::NameToCreator<CreateHakoniwa> playerEntries[] = {
    {"PlayerActorHakoniwa", &createPlayerFunction<PlayerActorHakoniwa>},
    {"YukimaruRacePlayer", &createPlayerFunction<YukimaruRacePlayer>}
};

class PlayerFactory : public al::Factory<CreateHakoniwa> {
    public:
        PlayerFactory() {
            this->factoryName = "プレイヤー生成";
            this->actorTable = playerEntries;
            this->factoryCount = sizeof(playerEntries)/sizeof(playerEntries[0]);
        };
};
