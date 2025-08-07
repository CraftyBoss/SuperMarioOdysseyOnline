#pragma once

#include <math.h>
#include "al/camera/CameraTicket.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/gamemode/GameModeInfoBase.hpp"
#include "server/gamemode/GameModeConfigMenu.hpp"
#include "server/gamemode/GameModeTimer.hpp"
#include "server/ctf/CaptureTheFlagConfigMenu.hpp"
#include "packets/CaptureTheFlagPacket.h"
#include "sead/math/seadVector.h"


struct CaptureTheFlagInfo : GameModeInfoBase {
    CaptureTheFlagInfo() { 
        mMode = GameMode::CAPTURETHEFLAG;
        mRedScore = 0;
        mBlueScore = 0;
        mMaxScore = 3;  // First to 3 captures wins
        mPlayerTeam = CTFTeam::SPECTATOR;
        mHasFlag = false;
        mRoundTime = GameTime();
    }
    
    u8 mRedScore;
    u8 mBlueScore;
    u8 mMaxScore;
    CTFTeam mPlayerTeam;
    bool mHasFlag;
    u8 mFlagTeam;  // Which flag player is carrying
    GameTime mRoundTime;
    sead::Vector3f mRedFlagPos;
    sead::Vector3f mBlueFlagPos;
    sead::Vector3f mRedFlagSpawn;  // Original positions
    sead::Vector3f mBlueFlagSpawn;
    bool mIsRedFlagHome;
    bool mIsBlueFlagHome;
};

//class CaptureTheFlagIcon;
class HideAndSeekIcon;  // Use HideAndSeekIcon for now, will change later

class CaptureTheFlagMode : public GameModeBase {
public:
    CaptureTheFlagMode(const char* name);
    
    void init(GameModeInitInfo const& info) override;
    void begin() override;
    void update() override;
    void end() override;
    
    CTFTeam getPlayerTeam() const { return mInfo->mPlayerTeam; }
    void setPlayerTeam(CTFTeam team) { mInfo->mPlayerTeam = team; }
    
    bool isCarryingFlag() const { return mInfo->mHasFlag; }
    void captureFlag(u8 flagTeam);
    void dropFlag();
    void returnFlag(u8 flagTeam);
    void scorePoint(CTFTeam team);
    
private:
    void checkFlagCapture();
    void checkFlagReturn();
    void updateFlagPositions();
    void spawnFlags();
    bool isNearFlag(sead::Vector3f flagPos, float distance);
    
    GameModeTimer* mModeTimer = nullptr;
    //CaptureTheFlagIcon* mModeLayout = nullptr;
    HideAndSeekIcon* mModeLayout = nullptr;  // Use HideAndSeekIcon for now, will change later
    CaptureTheFlagInfo* mInfo = nullptr;
    
    float mFlagCaptureDistance = 200.0f;
    float mFlagReturnDistance = 200.0f;
    float mRespawnTime = 3.0f;
    float mCurrentRespawnTimer = 0.0f;
};