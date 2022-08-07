#include "server/hns/HideAndSeekMode.hpp"
#include <cmath>
#include "al/async/FunctorV0M.hpp"
#include "al/util.hpp"
#include "al/util/ControllerUtil.h"
#include "game/GameData/GameDataHolderAccessor.h"
#include "game/Layouts/CoinCounter.h"
#include "game/Layouts/MapMini.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "heap/seadHeapMgr.h"
#include "layouts/HideAndSeekIcon.h"
#include "logger.hpp"
#include "rs/util.hpp"
#include "server/gamemode/GameModeBase.hpp"
#include "server/Client.hpp"
#include "server/gamemode/GameModeTimer.hpp"
#include <heap/seadHeap.h>
#include "server/gamemode/GameModeManager.hpp"
#include "server/gamemode/GameModeFactory.hpp"

#include "basis/seadNew.h"
#include "server/hns/HideAndSeekConfigMenu.hpp"

HideAndSeekMode::HideAndSeekMode(const char* name) : GameModeBase(name) {}

void HideAndSeekMode::init(const GameModeInitInfo& info) {
    mSceneObjHolder = info.mSceneObjHolder;
    mMode = info.mMode;
    mCurScene = (StageScene*)info.mScene;
    mPuppetHolder = info.mPuppetHolder;

    GameModeInfoBase* curGameInfo = GameModeManager::instance()->getInfo<HideAndSeekInfo>();

    sead::ScopedCurrentHeapSetter heapSetter(GameModeManager::instance()->getHeap());

    if (curGameInfo) Logger::log("Gamemode info found: %s %s\n", GameModeFactory::getModeString(curGameInfo->mMode), GameModeFactory::getModeString(info.mMode));
    else Logger::log("No gamemode info found\n");
    if (curGameInfo && curGameInfo->mMode == mMode) {
        mInfo = (HideAndSeekInfo*)curGameInfo;
        mModeTimer = new GameModeTimer(mInfo->mHidingTime);
        Logger::log("Reinitialized timer with time %d:%.2d\n", mInfo->mHidingTime.mMinutes, mInfo->mHidingTime.mSeconds);
    } else {
        if (curGameInfo) delete curGameInfo;  // attempt to destory previous info before creating new one
        
        mInfo = GameModeManager::instance()->createModeInfo<HideAndSeekInfo>();
        
        mModeTimer = new GameModeTimer();
    }

    mModeLayout = new HideAndSeekIcon("HideAndSeekIcon", *info.mLayoutInitInfo);

    mModeLayout->showSeeking();

    mModeTimer->disableTimer();

}

void HideAndSeekMode::begin() {
    mModeLayout->appear();

    mIsFirstFrame = true;

    if (!mInfo->mIsPlayerIt) {
        mModeTimer->enableTimer();
        mModeLayout->showHiding();
    } else {
        mModeTimer->disableTimer();
        mModeLayout->showSeeking();
    }

    CoinCounter *coinCollect = mCurScene->stageSceneLayout->mCoinCollectLyt;
    CoinCounter* coinCounter = mCurScene->stageSceneLayout->mCoinCountLyt;
    MapMini* compass = mCurScene->stageSceneLayout->mMapMiniLyt;
    al::SimpleLayoutAppearWaitEnd* playGuideLyt = mCurScene->stageSceneLayout->mPlayGuideMenuLyt;

    if(coinCounter->mIsAlive)
        coinCounter->tryEnd();
    if(coinCollect->mIsAlive)
        coinCollect->tryEnd();
    if (compass->mIsAlive)
        compass->end();
    if (playGuideLyt->mIsAlive)
        playGuideLyt->end();

    GameModeBase::begin();
}

void HideAndSeekMode::end() {

    mModeLayout->tryEnd();

    mModeTimer->disableTimer();

    CoinCounter *coinCollect = mCurScene->stageSceneLayout->mCoinCollectLyt;
    CoinCounter* coinCounter = mCurScene->stageSceneLayout->mCoinCountLyt;
    MapMini* compass = mCurScene->stageSceneLayout->mMapMiniLyt;
    al::SimpleLayoutAppearWaitEnd* playGuideLyt = mCurScene->stageSceneLayout->mPlayGuideMenuLyt;

    if(!coinCounter->mIsAlive)
        coinCounter->tryStart();
    if(!coinCollect->mIsAlive)
        coinCollect->tryStart();
    if (!compass->mIsAlive)
        compass->appearSlideIn();
    if (!playGuideLyt->mIsAlive)
        playGuideLyt->appear();

    GameModeBase::end();
}

void HideAndSeekMode::update() {

    PlayerActorHakoniwa* mainPlayer = rs::getPlayerActor(mCurScene);

    if (mIsFirstFrame) {

        if (mInfo->mIsUseGravityCam && mTicket) {
            al::startCamera(mCurScene, mTicket, -1);
        }

        mIsFirstFrame = false;
    }

    if (!mInfo->mIsPlayerIt) {
        if (mInvulnTime >= 5) {  

            if (mainPlayer) {
                for (int i = 0; i < mPuppetHolder->getSize(); i++)
                {
                    PuppetInfo *curInfo = Client::getPuppetInfo(i);

                    if (!curInfo) {
                        Logger::log("Checking %d, hit bounds %d-%d\n", i, mPuppetHolder->getSize(), Client::getMaxPlayerCount());
                        break;
                    }

                    if(curInfo->isConnected && curInfo->isInSameStage && curInfo->isIt) { 

                        float pupDist = al::calcDistance(mainPlayer, curInfo->playerPos); // TODO: remove distance calculations and use hit sensors to determine this

                        if(pupDist < 200.f && mainPlayer->mDimKeeper->is2DModel == curInfo->is2D) {
                            if(!PlayerFunction::isPlayerDeadStatus(mainPlayer)) {
                                
                                GameDataFunction::killPlayer(GameDataHolderAccessor(this));
                                mainPlayer->startDemoPuppetable();
                                al::setVelocityZero(mainPlayer);
                                rs::faceToCamera(mainPlayer);
                                mainPlayer->mPlayerAnimator->endSubAnim();
                                mainPlayer->mPlayerAnimator->startAnimDead();

                                mInfo->mIsPlayerIt = true;
                                mModeTimer->disableTimer();
                                mModeLayout->showSeeking();
                                
                                Client::sendTagInfPacket();
                            }
                        } else if (PlayerFunction::isPlayerDeadStatus(mainPlayer)) {

                            mInfo->mIsPlayerIt = true;
                            mModeTimer->disableTimer();
                            mModeLayout->showSeeking();

                            Client::sendTagInfPacket();
                            
                        }
                    }
                }
            }
            
        }else {
            mInvulnTime += Time::deltaTime;
        }

        mModeTimer->updateTimer();
    }

    if (mInfo->mIsUseGravity) {
        sead::Vector3f gravity;
        if (rs::calcOnGroundNormalOrGravityDir(&gravity, mainPlayer, mainPlayer->mPlayerCollider)) {
            gravity = -gravity;
            al::normalize(&gravity);
            al::setGravity(mainPlayer, gravity);
            al::setGravity(mainPlayer->mHackCap, gravity);
        }
        
        if (al::isPadHoldL(-1)) {
            if (al::isPadTriggerRight(-1)) {
                if (al::isActiveCamera(mTicket)) {
                    al::endCamera(mCurScene, mTicket, -1, false);
                    mInfo->mIsUseGravityCam = false;
                } else {
                    al::startCamera(mCurScene, mTicket, -1);
                    mInfo->mIsUseGravityCam = true;
                }
            }
        } else if (al::isPadTriggerZL(-1)) {
            if (al::isPadTriggerLeft(-1)) {
                killMainPlayer(mainPlayer);
            }
        }
    }

    if (al::isPadTriggerUp(-1) && !al::isPadHoldZL(-1))
    {
        mInfo->mIsPlayerIt = !mInfo->mIsPlayerIt;

        mModeTimer->toggleTimer();

        if(!mInfo->mIsPlayerIt) {
            mInvulnTime = 0;
            mModeLayout->showHiding();
        } else {
            mModeLayout->showSeeking();
        }

        Client::sendTagInfPacket();
    }

    mInfo->mHidingTime = mModeTimer->getTime();
}