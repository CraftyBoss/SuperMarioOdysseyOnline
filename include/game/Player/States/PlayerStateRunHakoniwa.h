#pragma once

#include "al/LiveActor/LiveActor.h"
#include "game/Interfaces/IUsePlayerCollision.h"
#include "game/Player/Actions/PlayerActionGroundMoveControl.h"
#include "game/Player/PlayerAnimator.h"
#include "game/Player/PlayerConst.h"
#include "game/Player/PlayerInput.h"
#include "al/nerve/ActorStateBase.h"

class PlayerStateRunHakoniwa : public al::ActorStateBase {
public:
    PlayerStateRunHakoniwa(al::LiveActor *,PlayerConst const*,PlayerInput const*,IUsePlayerCollision const*, struct PlayerCounterForceRun const*, struct PlayerCounterQuickTurnJump const*, struct PlayerTrigger *, PlayerAnimator *, struct PlayerEffect *, struct PlayerJointParamCenterDynamics *, struct IJudge const*,bool);
    void appear(void);
    void kill(void);
    void control(void);
    void isEnableLookAt(void);
    void isRunDashFast(void);
    void tryTurnJump(sead::Vector3<float> *);
    void getCenterTiltRateMax(void);
    void getCapDynamicsRate(void);
    void exePivot(void);
    void exeRun(void);
    void exeBrake(void);
    void exeTurn(void);
    void exeWallPush(void);
    ~PlayerStateRunHakoniwa();

    PlayerConst *mPlayerConst;
    PlayerInput *mPlayerInput;
    IUsePlayerCollision *mPlayerCollider;
    PlayerCounterForceRun *mCounterForceRun;
    PlayerCounterQuickTurnJump *mCounterQuickTurnJump;
    PlayerTrigger *mPlayerTrigger;
    PlayerAnimator *mPlayerAnimator;
    struct PlayerAnimControlRun *mPlayerAnimControlRun;
    struct PlayerActionPivotTurnControl *mActionPivotTurnControl;
    PlayerActionGroundMoveControl *mActionGroundMoveControl; // 0x68
    bool unkBool70;
    int dword74;
    int dword78;
    int qword7C;
    int qword80;
    int qword84;
    int dword88;
    float mMaxSpeed;
    int dword90;
    int unkInt94;
    struct PlayerJudgeWallPush *mPlayerJudgeWallPush;
    void *qwordA0;
    void *qwordA8;
    PlayerEffect *mPlayerEffect;
    bool byteB8;
    int dwordBC;
    void* mJointParamCenterDynamics;
    bool unkBoolC8;
};

static_assert(sizeof(PlayerStateRunHakoniwa) == 0xD0, "Player State Run Size");