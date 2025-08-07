#include "server/ctf/CaptureTheFlagMode.hpp"
#include <cmath>
#include "al/util.hpp"
#include "al/util/ControllerUtil.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/StageScene/StageScene.h"
#include "layouts/CaptureTheFlagIcon.h"
#include "logger.hpp"
#include "rs/util.hpp"
#include "server/Client.hpp"
#include "server/gamemode/GameModeTimer.hpp"
#include "server/DeltaTime.hpp"

CaptureTheFlagMode::CaptureTheFlagMode(const char* name) : GameModeBase(name) {}

void CaptureTheFlagMode::init(const GameModeInitInfo& info) {
    mSceneObjHolder = info.mSceneObjHolder;
    mMode = info.mMode;
    mCurScene = (StageScene*)info.mScene;
    mPuppetHolder = info.mPuppetHolder;
    
    GameModeInfoBase* curGameInfo = Client::getModeInfo();
    
    if (curGameInfo && curGameInfo->mMode == mMode) {
        mInfo = (CaptureTheFlagInfo*)curGameInfo;
        mModeTimer = new GameModeTimer(mInfo->mRoundTime);
    } else {
        if (curGameInfo) {
            delete curGameInfo;
        }
        
        mInfo = createModeInfo<CaptureTheFlagInfo>();
        Client::setModeInfo(mInfo);
        mModeTimer = new GameModeTimer();
    }
    mModeLayout  = new HideAndSeekIcon("CaptureTheFlagIcon", *info.mLayoutInitInfo);
    //mModeLayout = new CaptureTheFlagIcon("HideAndSeekIcon", *info.mLayoutInitInfo);
    mModeTimer->disableTimer();
}

void CaptureTheFlagMode::begin() {
    mModeLayout->appear();
    mIsFirstFrame = true;
    
    mModeTimer->enableTimer();
    
    // Set flag spawn positions based on current stage
    spawnFlags();
    
    // Hide coin counters and other UI elements
    CoinCounter* coinCollect = mCurScene->stageSceneLayout->mCoinCollectLyt;
    CoinCounter* coinCounter = mCurScene->stageSceneLayout->mCoinCountLyt;
    
    if(coinCounter->mIsAlive)
        coinCounter->tryEnd();
    if(coinCollect->mIsAlive)
        coinCollect->tryEnd();
    
    GameModeBase::begin();
}

void CaptureTheFlagMode::end() {
    mModeLayout->tryEnd();
    mModeTimer->disableTimer();
    
    // Restore UI elements
    CoinCounter* coinCollect = mCurScene->stageSceneLayout->mCoinCollectLyt;
    CoinCounter* coinCounter = mCurScene->stageSceneLayout->mCoinCountLyt;
    
    if(!coinCounter->mIsAlive)
        coinCounter->tryStart();
    if(!coinCollect->mIsAlive)
        coinCollect->tryStart();
    
    GameModeBase::end();
}

void CaptureTheFlagMode::update() {
    PlayerActorHakoniwa* mainPlayer = rs::getPlayerActor(mCurScene);
    
    if (!mainPlayer) return;
    
    if (mIsFirstFrame) {
        mIsFirstFrame = false;
    }
    
    // Update timer
    mModeTimer->updateTimer();
    mInfo->mRoundTime = mModeTimer->getTime();
    
    // Check for flag captures and returns
    checkFlagCapture();
    checkFlagReturn();
    updateFlagPositions();
    
    // Update UI
    mModeLayout->updateScore(mInfo->mRedScore, mInfo->mBlueScore);
    mModeLayout->showFlagCarrier(mInfo->mHasFlag, mInfo->mFlagTeam);
    
    // Handle team switching (debug)
    if (al::isPadTriggerUp(-1) && !al::isPadHoldZL(-1)) {
        if (mInfo->mPlayerTeam == CTFTeam::RED_TEAM) {
            setPlayerTeam(CTFTeam::BLUE_TEAM);
            mModeLayout->showTeamBlue();
        } else if (mInfo->mPlayerTeam == CTFTeam::BLUE_TEAM) {
            setPlayerTeam(CTFTeam::SPECTATOR);
            mModeLayout->showSpectator();
        } else {
            setPlayerTeam(CTFTeam::RED_TEAM);
            mModeLayout->showTeamRed();
        }
        
        // Send team update packet
        CaptureTheFlagPacket packet;
        packet.mUserID = Client::sInstance->mUserID;
        packet.updateType = CTFUpdateType::TEAM_ASSIGN;
        packet.playerTeam = mInfo->mPlayerTeam;
        Client::sInstance->mSocket->SEND(&packet);
    }
    
    // Check win condition
    if (mInfo->mRedScore >= mInfo->mMaxScore || mInfo->mBlueScore >= mInfo->mMaxScore) {
        Logger::log("Game Over! Red: %d, Blue: %d\n", mInfo->mRedScore, mInfo->mBlueScore);
        end();
    }
}

void CaptureTheFlagMode::checkFlagCapture() {
    PlayerActorHakoniwa* mainPlayer = rs::getPlayerActor(mCurScene);
    if (!mainPlayer || mInfo->mPlayerTeam == CTFTeam::SPECTATOR) return;
    
    sead::Vector3f playerPos = al::getTrans(mainPlayer);
    
    // Can't capture if already carrying a flag
    if (mInfo->mHasFlag) return;
    
    // Check if near enemy flag
    if (mInfo->mPlayerTeam == CTFTeam::RED_TEAM) {
        // Red team captures blue flag
        if (isNearFlag(mInfo->mBlueFlagPos, mFlagCaptureDistance)) {
            captureFlag(CTFTeam::BLUE_TEAM);
        }
    } else if (mInfo->mPlayerTeam == CTFTeam::BLUE_TEAM) {
        // Blue team captures red flag
        if (isNearFlag(mInfo->mRedFlagPos, mFlagCaptureDistance)) {
            captureFlag(CTFTeam::RED_TEAM);
        }
    }
}

void CaptureTheFlagMode::checkFlagReturn() {
    PlayerActorHakoniwa* mainPlayer = rs::getPlayerActor(mCurScene);
    if (!mainPlayer) return;
    
    // If carrying flag and reached own base, score a point
    if (mInfo->mHasFlag) {
        if (mInfo->mPlayerTeam == CTFTeam::RED_TEAM && 
            isNearFlag(mInfo->mRedFlagSpawn, mFlagReturnDistance)) {
            scorePoint(CTFTeam::RED_TEAM);
            returnFlag(mInfo->mFlagTeam);
        } else if (mInfo->mPlayerTeam == CTFTeam::BLUE_TEAM && 
                   isNearFlag(mInfo->mBlueFlagSpawn, mFlagReturnDistance)) {
            scorePoint(CTFTeam::BLUE_TEAM);
            returnFlag(mInfo->mFlagTeam);
        }
    }
}

void CaptureTheFlagMode::captureFlag(u8 flagTeam) {
    mInfo->mHasFlag = true;
    mInfo->mFlagTeam = flagTeam;
    
    Logger::log("Flag captured! Team: %d\n", flagTeam);
    
    // Send packet
    CaptureTheFlagPacket packet;
    packet.mUserID = Client::sInstance->mUserID;
    packet.updateType = CTFUpdateType::FLAG_CAPTURED;
    packet.playerTeam = mInfo->mPlayerTeam;
    packet.flagTeam = flagTeam;
    packet.hasFlag = true;
    Client::sInstance->mSocket->SEND(&packet);
}

void CaptureTheFlagMode::dropFlag() {
    if (!mInfo->mHasFlag) return;
    
    PlayerActorHakoniwa* mainPlayer = rs::getPlayerActor(mCurScene);
    if (!mainPlayer) return;
    
    sead::Vector3f dropPos = al::getTrans(mainPlayer);
    
    // Update flag position
    if (mInfo->mFlagTeam == CTFTeam::RED_TEAM) {
        mInfo->mRedFlagPos = dropPos;
        mInfo->mIsRedFlagHome = false;
    } else {
        mInfo->mBlueFlagPos = dropPos;
        mInfo->mIsBlueFlagHome = false;
    }
    
    mInfo->mHasFlag = false;
    
    // Send packet
    CaptureTheFlagPacket packet;
    packet.mUserID = Client::sInstance->mUserID;
    packet.updateType = CTFUpdateType::FLAG_DROPPED;
    packet.flagPos = dropPos;
    packet.flagTeam = mInfo->mFlagTeam;
    packet.hasFlag = false;
    Client::sInstance->mSocket->SEND(&packet);
}

void CaptureTheFlagMode::returnFlag(u8 flagTeam) {
    // Return flag to spawn position
    if (flagTeam == CTFTeam::RED_TEAM) {
        mInfo->mRedFlagPos = mInfo->mRedFlagSpawn;
        mInfo->mIsRedFlagHome = true;
    } else {
        mInfo->mBlueFlagPos = mInfo->mBlueFlagSpawn;
        mInfo->mIsBlueFlagHome = true;
    }
    
    mInfo->mHasFlag = false;
    
    // Send packet
    CaptureTheFlagPacket packet;
    packet.mUserID = Client::sInstance->mUserID;
    packet.updateType = CTFUpdateType::FLAG_RETURNED;
    packet.flagTeam = flagTeam;
    Client::sInstance->mSocket->SEND(&packet);
}

void CaptureTheFlagMode::scorePoint(CTFTeam team) {
    if (team == CTFTeam::RED_TEAM) {
        mInfo->mRedScore++;
    } else if (team == CTFTeam::BLUE_TEAM) {
        mInfo->mBlueScore++;
    }
    
    Logger::log("Score! Red: %d, Blue: %d\n", mInfo->mRedScore, mInfo->mBlueScore);
    
    // Send score update
    CaptureTheFlagPacket packet;
    packet.mUserID = Client::sInstance->mUserID;
    packet.updateType = CTFUpdateType::SCORE_UPDATE;
    packet.redScore = mInfo->mRedScore;
    packet.blueScore = mInfo->mBlueScore;
    Client::sInstance->mSocket->SEND(&packet);
}

void CaptureTheFlagMode::spawnFlags() {
    // Set default spawn positions (these should be customized per stage)
    PlayerActorHakoniwa* mainPlayer = rs::getPlayerActor(mCurScene);
    if (!mainPlayer) return;
    
    sead::Vector3f playerPos = al::getTrans(mainPlayer);
    
    // Place flags 1000 units apart
    mInfo->mRedFlagSpawn = playerPos + sead::Vector3f(500, 0, 0);
    mInfo->mBlueFlagSpawn = playerPos + sead::Vector3f(-500, 0, 0);
    
    mInfo->mRedFlagPos = mInfo->mRedFlagSpawn;
    mInfo->mBlueFlagPos = mInfo->mBlueFlagSpawn;
    
    mInfo->mIsRedFlagHome = true;
    mInfo->mIsBlueFlagHome = true;
}

bool CaptureTheFlagMode::isNearFlag(sead::Vector3f flagPos, float distance) {
    PlayerActorHakoniwa* mainPlayer = rs::getPlayerActor(mCurScene);
    if (!mainPlayer) return false;
    
    float dist = al::calcDistance(mainPlayer, flagPos);
    return dist < distance;
}

void CaptureTheFlagMode::updateFlagPositions() {
    // Update flag positions for carried flags
    if (mInfo->mHasFlag) {
        PlayerActorHakoniwa* mainPlayer = rs::getPlayerActor(mCurScene);
        if (mainPlayer) {
            sead::Vector3f playerPos = al::getTrans(mainPlayer);
            if (mInfo->mFlagTeam == CTFTeam::RED_TEAM) {
                mInfo->mRedFlagPos = playerPos;
            } else {
                mInfo->mBlueFlagPos = playerPos;
            }
        }
    }
}