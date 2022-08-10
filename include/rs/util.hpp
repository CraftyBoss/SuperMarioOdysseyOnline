#pragma once

#include "game/GameData/GameDataFile.h"
#include "game/Info/QuestInfoHolder.h"
#include "game/Player/PlayerActorBase.h"
#include "sead/math/seadVector.h"
#include "al/util.hpp"
#include "al/sensor/SensorMsg.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "al/area/ChangeStageInfo.h"

namespace rs {

    bool isModeE3Rom(void);

    bool isModeE3LiveRom(void);

    bool tryCalcMapNorthDir(sead::Vector3f *, al::IUseSceneObjHolder const*);

    void invalidateQuest(QuestInfo const *info);

    QuestInfoHolder *getQuestInfoHolder(al::IUseSceneObjHolder const*);

    char16_t* getWorldCoinCollectPictureFont(al::LayoutActor const*);

    bool calcOnGroundNormalOrGravityDir(sead::Vector3f*, al::LiveActor const*, IUsePlayerCollision const*);

    void buyCap(al::IUseSceneObjHolder const *, char const*);
    void buyCloth(al::IUseSceneObjHolder const *, char const*);

    ChangeStageInfo *createChangeStageInfo(al::LiveActor const *actor, char const *changeStageID, char const *changeStageName, bool, int scenarioNo, ChangeStageInfo::SubScenarioType type);
    ChangeStageInfo *createChangeStageInfo(al::LiveActor const*, al::PlacementInfo const&, char const*, char const*, bool, int, ChangeStageInfo::SubScenarioType);
    ChangeStageInfo *createChangeStageInfo(const al::LiveActor *, const al::PlacementInfo *);

    bool isPlayerDamageStopDemo(const al::LiveActor *);

    PlayerActorBase * getPlayerActor(const al::Scene *);

    void get2DAreaPos(sead::Vector3<f32> *, al::AreaObj const *);

    bool isInChangeStageArea(PlayerActorHakoniwa const*, sead::Vector3f const *);

    bool isPlayerOnGround(const al::LiveActor *);

    void faceToCamera(al::LiveActor *actor);

    bool isPlayerActiveMarioAmiiboInvincible(al::LiveActor *);

    bool isMsgPlayerAndCapObjHipDropAll(al::SensorMsg const *);

    bool isMsgPlayerDamage(al::SensorMsg const *);

    bool isMsgShineGet(al::SensorMsg const *);

    void saveCoinStack(al::LiveActor const* actor, al::PlacementId const* placement, int stackCount);

    bool isActiveDemo(al::LiveActor const *);

    bool isActiveDemoWithPlayer(al::Scene const *);

    bool isActiveDemoWithPlayerKeepCarry(al::Scene const *);

    bool isActiveDemoWithPlayerUseCoin(al::Scene const *);

    bool isActiveDemoShineGet(al::Scene const *);

    bool isActiveDemoWarp(al::Scene const *);

    bool isActiveDemoScenarioCamera(al::Scene const *);

    bool isActiveDemoTalk(al::Scene const *);

    void recoveryPlayerOxygen(const al::LiveActor *);

    bool is2D(IUseDimension const *);

    void calcGroundNormalOrGravityDir(sead::Vector3f *result, al::LiveActor const *actor, IUsePlayerCollision const *col);

    void calcPlayerFrontDir(sead::Vector3f* result, al::LiveActor const*);

    int getStageShineAnimFrame(al::LiveActor const*, char const*);
    const char* getStageShineArchiveName(al::LiveActor const*, char const*);
    const char* getStageShineEmptyArchiveName(al::LiveActor const*, char const*);
}
