#pragma once

#include <cmath>
#include <math.h>
#include "puppets/PuppetHolder.hpp"
#include "al/actor/ActorInitInfo.h"
#include "al/actor/IUseName.h"
#include "al/scene/Scene.h"
#include "al/scene/SceneObjHolder.h"
#include "game/GameData/GameDataHolder.h"
#include "game/StageScene/StageScene.h"
#include "layouts/HideAndSeekIcon.h"
#include "prim/seadSafeString.h"
#include "server/gamemode/GameModeConfigMenu.hpp"

// enum for defining game mode types
enum GameMode : s8 {
    NONE = -1,
    HIDEANDSEEK
};

// struct containing info about the games state for use in gamemodes
struct GameModeInitInfo {
    GameModeInitInfo(al::ActorInitInfo* info, al::Scene *scene){
        mLayoutInitInfo = info->mLayoutInitInfo;
        mPlayerHolder = info->mActorSceneInfo.mPlayerHolder;
        mSceneObjHolder = info->mActorSceneInfo.mSceneObjHolder;
        mScene = scene;
        
    };

    void initServerInfo(GameMode mode, PuppetHolder *pupHolder) {
        mMode = mode;
        mPuppetHolder = pupHolder;
    }
    
    al::LayoutInitInfo* mLayoutInitInfo;
    al::PlayerHolder* mPlayerHolder;
    al::SceneObjHolder *mSceneObjHolder;
    al::Scene* mScene;
    GameMode mMode = GameMode::NONE;
    PuppetHolder *mPuppetHolder;
};

// base class for all gamemodes, must inherit from this to have a functional gamemode
class GameModeBase : public al::IUseName, public al::IUseSceneObjHolder {
public:
    GameModeBase(const char* name) { mName = name; }
    virtual ~GameModeBase() = default;
    const char* getName() const override { return mName.cstr(); }
    al::SceneObjHolder* getSceneObjHolder() const override { return mSceneObjHolder; }

    virtual GameMode getMode() { return mMode; }

    virtual bool isModeActive() const { return mIsActive; }

    virtual void init(GameModeInitInfo const &info);

    virtual void begin() { mIsActive = true; }
    virtual void update();
    virtual void end() { mIsActive = false; }
    
protected:
    sead::FixedSafeString<0x10> mName;
    al::SceneObjHolder *mSceneObjHolder = nullptr;
    GameMode mMode = GameMode::NONE;
    StageScene* mCurScene = nullptr;
    PuppetHolder *mPuppetHolder = nullptr;
    bool mIsActive = false;
    bool mIsFirstFrame = true;
};