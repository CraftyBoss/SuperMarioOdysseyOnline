#pragma once

#include "al/LiveActor/LiveActor.h"
#include "game/Interfaces/IUsePlayerCollision.h"
#include "game/Player/PlayerConst.h"
#include "math/seadVector.h"

class PlayerCapActionHistory {
public:
    PlayerCapActionHistory(al::LiveActor const*,PlayerConst const*,struct PlayerTrigger const*,IUsePlayerCollision const*);
    void update(void);
    void clearLandLimit(void);
    void clearLimitHeight(void);
    void clearCapJump(void);
    void clearLandLimitStandAngle(void);
    void clearWallAirLimit(void);
    void recordLimitHeight(void);
    bool isOverLimitHeight(void) const;

    al::LiveActor* mHostActor;       // 0x0
    PlayerConst* mPlayerConst;       // 0x8
    PlayerTrigger* mPlayerTrigger;   // 0x10
    IUsePlayerCollision* mCollider;  // 0x18
    struct PlayerCounterAfterCapCatch* mCapCatchCounter;  // 0x20
    bool mIsCapBounced = false;                           // 0x28
    sead::Vector3f mUnkVec = sead::Vector3f::zero;        // 0x2C
    bool mIsCapJumpReady = true;                          // 0x38
    bool mIsLimited = true;                               // 0x39 (unsure what this actually is called)
};