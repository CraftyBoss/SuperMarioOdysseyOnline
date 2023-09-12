#pragma once
/**
 * @file PlayerActorBase.h
 * @brief Main Class for the PlayerActor (Mario)
 * Player Pose: TQGMSV
*  Vtable loc: 1D780C0
*/

#include "game/Interfaces/IUseDimension.h"
#include "al/actor/ActorDimensionKeeper.h"
#include "al/actor/ActorInitInfo.h"
#include "PlayerActorBase.h"
#include "PlayerPuppet.h"
#include "PlayerInput.h"
#include "PlayerAnimator.h"
#include "HackCap.h"
#include "PlayerModelKeeper.h"
#include "PlayerColliderHakoniwa.h"
#include "PlayerConst.h"
#include "PlayerHackKeeper.h"
#include "PlayerInfo.h"
#include "PlayerModelChangerHakoniwa.h"
#include "PlayerFormSensorCollisionArranger.h"
#include "PlayerInitInfo.h"

#include "Attacks/PlayerSpinCapAttack.h"

namespace al {
class WaterSurfaceFinder;
}

class PlayerActorHakoniwa : public PlayerActorBase , public IUseDimension {
    public: 
        int *getPortNo(void) const;
        PlayerHackKeeper *getPlayerHackKeeper() const;
        void attackSensor(al::HitSensor *target, al::HitSensor *source);
        void startDemoPuppetable(void);
        void startPlayerPuppet(void);
        void initPlayer(al::ActorInitInfo const&, PlayerInitInfo const&);

        PlayerInfo *mPlayerInfo; // 0x128
        PlayerConst *mPlayerConst; // 0x130
        PlayerInput *mPlayerInput; //0x138 
        PlayerTrigger *mPlayerTrigger; // 0x140
        HackCap *mHackCap; // 0x148
        ActorDimensionKeeper *mDimKeeper; // 0x150
        PlayerModelKeeper *mPlayerModelKeeper; // 0x158
        PlayerModelChangerHakoniwa *mModelChanger; // 0x160
        PlayerAnimator *mPlayerAnimator; // 0x168 
        PlayerColliderHakoniwa *mPlayerCollider; // 0x170
        PlayerPuppet *mPlayerPuppet; // 0x178
        PlayerAreaChecker *mAreaChecker; // 0x180
        al::WaterSurfaceFinder *mWaterSurfaceFinder; // 0x188
        PlayerOxygen* mPlayerOxygen; // 0x190
        PlayerDamageKeeper* mPlayerDamageKeeper; // 0x198
        PlayerDemoActionFlag* mPlayerDemoActionFlag; // 0x1A0
        PlayerCapActionHistory* mPlayerCapActionHistory; // 0x1A8
        PlayerCapManHeroEyesControl* mPlayerCapManHeroEyesControl; // 0x1B0
        struct PlayerContinuousJump* mPlayerContinuousJump; // 0x1B8
        struct PlayerContinuousLongJump* mPlayerContinuousLongJump; // 0x1C0
        struct PlayerCounterAfterUpperPunch* mPlayerCounterAfterUpperPunch; // 0x1C8
        struct PlayerCounterForceRun* mPlayerCounterForceRun; // 0x1D0
        PlayerCounterIceWater* mPlayerCounterIceWater; // 0x1D8
        struct PlayerCounterQuickTurnJump* mPlayerCounterQuickTurnJump; // 0x1E0
        PlayerWallActionHistory* mPlayerWallActionHistory; // 0x1E8
        PlayerBindKeeper* mPlayerBindKeeper; // 0x1F0
        PlayerCarryKeeper* mPlayerCarryKeeper; // 0x1F8
        PlayerEquipmentUser* mPlayerEquipmentUser; // 0x200
        PlayerHackKeeper *mHackKeeper; // 0x208
        PlayerFormSensorCollisionArranger *mCollArranger; // 0x210
        struct PlayerJumpMessageRequest* mPlayerJumpMessageRequest; // 0x218
        struct PlayerSandSinkAffect* mPlayerSandSinkAffect; // 0x220
        PlayerSpinCapAttack* mSpinCapAttack;  // 0x228
        struct PlayerActionDiveInWater* mPlayerActionDiveInWater;
        struct PlayerEffect* mPlayerEffect;
        PlayerEyeSensorHitHolder* mPlayerEyeSensorHitHolder;
        struct PlayerPushReceiver* mPlayerPushReceiver;
        struct PlayerHitPush* mPlayerHitPush;
        struct PlayerExternalVelocity* mPlayerExternalVelocity;
        PlayerJointControlKeeper* mPlayerJointControlKeeper;
        PlayerPainPartsKeeper* mPlayerPainPartsKeeper;
        PlayerRecoverySafetyPoint* mPlayerRecoverySafetyPoint;
        struct PlayerRippleGenerator* mPlayerRippleGenerator;
        PlayerSeparateCapFlag* mPlayerSeparateCapFlag;
        PlayerWetControl* mPlayerWetControl;
        PlayerStainControl* mPlayerStainControl;
        al::FootPrintHolder* mFootPrintHolder;
        struct GaugeAir* mGaugeAir;
        struct WaterSurfaceShadow* mWaterSurfaceShadow;
        WorldEndBorderKeeper* mWorldEndBorderKeeper;
        void* gap;
        struct PlayerSeCtrl* mPlayerSeCtrl;
        al::HitSensor* mBodyHitSensor;
        bool mIsLongShadow;
        struct PlayerStateWait* mPlayerStateWait;
        struct PlayerStateSquat* mPlayerStateSquat;
        struct PlayerStateRunHakoniwa2D3D* mPlayerStateRunHakoniwa2D3D;
        struct PlayerStateSlope* mPlayerStateSlope;
        struct PlayerStateRolling* mPlayerStateRolling;
        struct PlayerStateSpinCap* mPlayerStateSpinCap;
        struct PlayerStateJump* mPlayerStateJump;
        struct PlayerStateCapCatchPop* mPlayerStateCapCatchPop;
        struct PlayerStateWallAir* mPlayerStateWallAir;
        struct PlayerStateWallCatch* mPlayerStateWallCatch;
        struct PlayerStateGrabCeil* mPlayerStateGrabCeil;
        struct PlayerStatePoleClimb* mPlayerStatePoleClimb;
        struct PlayerStateHipDrop* mPlayerStateHipDrop;
        struct PlayerStateHeadSliding* mPlayerStateHeadSliding;
        struct PlayerStateLongJump* mPlayerStateLongJump;
        struct PlayerStateFallHakoniwa* mPlayerStateFallHakoniwa;
        struct PlayerStateSandSink* mPlayerStateSandSink;
        struct ActorStateSandGeyser* mActorStateSandGeyser;
        struct PlayerStateRise* mPlayerStateRise;
        struct PlayerStateSwim* mPlayerStateSwim;
        struct PlayerStateDamageLife* mPlayerStateDamageLife;
        struct PlayerStateDamageSwim* mPlayerStateDamageSwim;
        struct PlayerStateDamageFire* mPlayerStateDamageFire;
        struct PlayerStatePress* mPlayerStatePress;
        struct PlayerStateBind* mPlayerStateBind;
        struct PlayerStateHack* mPlayerStateHack;
        struct PlayerStateEndHack* mPlayerStateEndHack;
        struct PlayerStateCameraSubjective* mPlayerStateCameraSubjective;
        struct PlayerStateAbyss* mPlayerStateAbyss;
        struct PlayerJudgeAirForceCount* mPlayerJudgeAirForceCount;
        struct PlayerJudgeCameraSubjective* mPlayerJudgeCameraSubjective;
        struct PlayerJudgeCapCatchPop* mPlayerJudgeCapCatchPop;
        struct PlayerJudgeDeadWipeStart* mPlayerJudgeDeadWipeStart;
        struct PlayerJudgeDirectRolling* mPlayerJudgeDirectRolling;
        struct PlayerJudgeEnableStandUp* mPlayerJudgeEnableStandUp;
        struct PlayerJudgeForceLand* mPlayerJudgeForceLand;
        struct PlayerJudgeForceSlopeSlide* mPlayerJudgeForceSlopeSlide;
        struct PlayerJudgeForceRolling* mPlayerJudgeForceRolling;
        struct PlayerJudgeGrabCeil* mPlayerJudgeGrabCeil;
        struct PlayerJudgeInWater* mPlayerJudgeInWater1;
        struct PlayerJudgeInWater* mPlayerJudgeInWater2;
        struct PlayerJudgeInWater* mPlayerJudgeInWater3;
        struct PlayerJudgeInWater* mPlayerJudgeInWater4;
        struct PlayerJudgeInvalidateInputFall* mPlayerJudgeInvalidateInputFall;
        struct PlayerJudgeLongFall* mPlayerJudgeLongFall;
        struct PlayerJudgeOutInWater* mPlayerJudgeOutInWater;
        struct PlayerJudgeRecoveryLifeFast* mPlayerJudgeRecoveryLifeFast;
        struct PlayerJudgeSandSink* mPlayerJudgeSandSink;
        struct PlayerJudgeSpeedCheckFall* mPlayerJudgeSpeedCheckFall;
        struct PlayerJudgeStartHipDrop* mPlayerJudgeStartHipDrop;
        struct PlayerJudgeStartRise* mPlayerJudgeStartRise;
        struct PlayerJudgeStartRolling* mPlayerJudgeStartRolling;
        struct PlayerJudgeStartRun* mPlayerJudgeStartRun;
        struct PlayerJudgeStartSquat* mPlayerJudgeStartSquat;
        struct PlayerJudgeStartWaterSurfaceRun* mPlayerJudgeStartWaterSurfaceRun;
        struct PlayerJudgeSlopeSlide* mPlayerJudgeSlopeSlide;
        struct PlayerJudgePoleClimb* mPlayerJudgePoleClimb;
        struct PlayerJudgePreInputJump* mPlayerJudgePreInputJump;
        struct PlayerJudgePreInputCapThrow* mPlayerJudgePreInputCapThrow;
        struct PlayerJudgePreInputHackAction* mPlayerJudgePreInputHackAction;
        struct HackCapJudgePreInputHoveringJump* mHackCapJudgePreInputHoveringJump;
        struct HackCapJudgePreInputSeparateThrow* mHackCapJudgePreInputSeparateThrow;
        struct HackCapJudgePreInputSeparateJump* mHackCapJudgePreInputSeparateJump;
        struct PlayerJudgeWallCatch* mPlayerJudgeWallCatch;
        struct PlayerJudgeWallCatchInputDir* mPlayerJudgeWallCatchInputDir;
        struct PlayerJudgeWallHitDown* mPlayerJudgeWallHitDown;
        struct PlayerJudgeWallHitDownForceRun* mPlayerJudgeWallHitDownForceRun;
        struct PlayerJudgeWallHitDownRolling* mPlayerJudgeWallHitDownRolling;
        struct PlayerJudgeWallKeep* mPlayerJudgeWallKeep;
        void* gap_2;
};