#pragma once
/**
 * @file HackCap.h
 * @brief Main Class for HackCap (Cappy)
* Vtable loc: 1D75520
*/

#include "al/LiveActor/LiveActor.h"
#include "al/sensor/HitSensor.h"
#include "al/sensor/SensorMsg.h"

#include "game/Player/PlayerInput.h"
#include "game/Interfaces/IUsePlayerCollision.h"

#include "HackCapThrowParam.h"
#include "HackCap/HackCapJointControlKeeper.h"
#include "HackCap/PlayerCapActionHistory.h"

class PlayerWallActionHistory;
class PlayerEyeSensorHitHolder;
class IUsePlayerHeightCheck;
class PlayerWetControl;
class PlayerJointControlKeeper;
class HackCapJudgePreInputSeparateThrow;
class HackCapJudgePreInputSeparateJump;
class PlayerSeparateCapFlag;

class CapTargetInfo;

class PlayerActorHakoniwa; // use a stub instead of the actual class file 


#define HACKSIZE sizeof(al::LiveActor)

class HackCap : public al::LiveActor {
    public: 

        HackCap(al::LiveActor const*,char const*,PlayerInput const*, struct PlayerAreaChecker const*, PlayerWallActionHistory const*, PlayerCapActionHistory const*, PlayerEyeSensorHitHolder const*,PlayerSeparateCapFlag const*,IUsePlayerCollision const*,  IUsePlayerHeightCheck const*,  PlayerWetControl const*,  PlayerJointControlKeeper const*, HackCapJudgePreInputSeparateThrow *, HackCapJudgePreInputSeparateJump *);

        enum SwingHandType {
            Left,
            Right
        };

        void init(al::ActorInitInfo const&);
        void hide(bool);
        void movement(void);
        void updateShadowMaskOffset(void);
        void control(void);
        void updateTargetLayout(void);
        void updateCollider(void);
        void updateFrameOutLayout(void);
        void attackSpin(al::HitSensor *,al::HitSensor *,float);
        void prepareLockOn(al::HitSensor *);
        void sendMsgStartHack(al::HitSensor *);
        void receiveRequestTransferHack(al::HitSensor *,al::HitSensor *);
        void startThrowSeparatePlayHack(al::HitSensor *, sead::Vector3f const&, sead::Vector3f const&,float);
        void startHack(void);
        void emitHackStartEffect(void);
        void noticeHackMarioEnter(void);
        void noticeHackDemoPuppetableEnd(void);
        void recordHack(void);
        void addHackStartDemo(void);
        void addLockOnKeepDemo(void);
        void syncHackDamageVisibility(bool);
        void endHack(void);
        void startSpinAttack(char const*);
        void startThrow(bool, sead::Vector3f const&, sead::Vector3f const&,float, sead::Vector2f const&, sead::Vector2f const&, sead::Vector3f const&,bool, sead::Vector3f const&, HackCap::SwingHandType,bool,float,int);
        void startThrowSeparatePlay( sead::Vector3f const&, sead::Vector3f const&,float,bool);
        void startThrowSeparatePlayJump( sead::Vector3f const&, sead::Vector3f const&,float);
        void startCatch(char const*,bool, sead::Vector3f const&);
        void forcePutOn(void);
        void forceHack(al::HitSensor *, CapTargetInfo const*); // :eyes:
        void resetLockOnParam(void);
        void setupStartLockOn(void);
        void cancelCapState(void);
        void requestReturn(bool *);
        void tryReturn(bool,bool *);
        void updateCapPose(void);
        void followTarget(void);
        void syncPuppetSilhouette(void);
        void recordCapJump(PlayerWallActionHistory *);
        void getFlyingSpeedMax(void);
        void getThrowSpeed(void);
        void requestLockOnHitReaction(CapTargetInfo const*,char const*);
        void startPuppet(void);
        void endPuppet(void);
        void hidePuppetCap(void);
        void showPuppetCap(void);
        void hidePuppetCapSilhouette(void);
        void showPuppetCapSilhouette(void);
        void startPuppetCheckpointWarp(void);
        void startHackShineGetDemo(void);
        void endHackThrowAndReturnHack(void);
        void endHackShineGetDemo(void);
        void calcHackFollowTrans( sead::Vector3f *,bool);
        void makeFollowMtx(sead::Matrix34<float> *);
        void updateCapEyeShowHide(bool,int);
        void activateInvincibleEffect(void);
        void syncInvincibleEffect(bool);
        void updateSeparateMode(PlayerSeparateCapFlag const*);
        void startRescuePlayer(void);
        void prepareCooperateThrow(void);
        void requestForceFollowSeparateHide(void);
        void calcSeparateHideSpeedH(sead::Vector3f const&);
        void updateModelAlphaForSnapShot(void);
        void getPadRumblePort(void);
        void updateThrowJoint(void);
        void setupThrowStart(void);
        void getThrowHeight(void);
        void checkEnableThrowStartSpace(sead::Vector3f *, sead::Vector3f *, sead::Vector3f *, sead::Vector3f const&,float,float,bool, sead::Vector3f const&);
        void updateWaterArea(void);
        void getThrowRange(void);
        void getThrowBrakeTime(void);
        void startThrowCapEyeThrowAction(void);
        void tryCollideReflectReaction(void);
        void tryCollideWallReaction(void);
        void changeThrowParamInWater(int,bool);
        void addCurveOffset(void);
        void tryAppendAttack(void);
        void tryCollideWallReactionSpiral(void);
        void endThrowSpiral(void);
        void tryCollideWallReactionReflect(void);
        void tryCollideWallReactionRollingGround(void);
        void rollingGround(void);
        void tryChangeSeparateThrow(void);
        void getThrowBackSpeed(void);
        void updateLavaSurfaceMove(void);
        void tryCollideWallReactionStay(void);
        void getThrowStayTime(void);
        void getThrowStayTimeMax(void);
        void getThrowSpeedAppend(void);
        void getThrowRangeAppend(void);
        void tryCollideWallLockOn(void);
        void endHackThrowAndReturnHackOrHide(void);
        void clearThrowType(void);
        void calcReturnTargetPos( sead::Vector3f *);
        void attackSensor(al::HitSensor *,al::HitSensor *);
        void stayRollingOrReflect(void);
        bool receiveMsg(al::SensorMsg const*,al::HitSensor *,al::HitSensor *);
        void endMove(void);
        void prepareTransferLockOn(al::HitSensor *);
        void collideThrowStartArrow(al::HitSensor *, sead::Vector3f const&, sead::Vector3f const&, sead::Vector3f const&);
        void trySendAttackCollideAndReaction(bool *);
        void stayWallHit(void);
        void endHackThrow(void);

        bool isFlying(void) const;
        bool isNoPutOnHide(void) const;
        bool isEnableThrow(void) const;
        bool isEnableSpinAttack(void) const;
        bool isSpinAttack(void) const;
        bool isEnableRescuePlayer(void) const;
        bool isRescuePlayer(void) const;
        bool isEnableHackThrow(bool *) const;
        bool isSeparateHipDropLand(void) const;
        bool isSeparateHide(void) const;
        bool isSeparateThrowFlying(void) const;
        bool isEnableThrowSeparate(void) const;
        bool isHoldInputKeepLockOn(void) const;
        bool isRequestableReturn(void) const;
        bool isLockOnEnableHackTarget(void) const;
        bool isWaitHackLockOn(void) const;
        bool isCatched(void) const;
        bool isHide(void) const;
        bool isPutOn(void) const;
        bool isLockOnInterpolate(void) const;
        bool isEnablePreInput(void) const;
        bool isForceCapTouchJump(void) const;
        bool isHackInvalidSeparatePlay(void) const;
        bool isHoldSpinCapStay(void) const;
        bool isThrowTypeSpiral(void) const;
        bool isThrowTypeRolling(void) const;
        bool isEnableHackThrowAutoCatch(void) const;
        bool isEnableCapTouchJumpInput(void) const;

        void exeLockOn(void);
        void exeHack(void);
        void exeSpinAttack(void);
        void exeCatch(void);
        void exeTrample(void);
        void exeTrampleLockOn(void);
        void exeRescue(void);
        void exeHide(void);
        void exeThrowStart(void);
        void exeThrow(void);
        void exeThrowBrake(void);
        void exeThrowSpiral(void);
        void exeThrowTornado(void);
        void exeThrowRolling(void);
        void exeThrowRollingBrake(void);
        void exeThrowStay(void);
        void exeThrowAppend(void);
        void exeRebound(void);
        void exeReturn(void);
        void exeBlow(void);
        
        void *unkPtr1; // 0x108
        void *unkPtr2; // 0x110
        al::LiveActor *mLockOnEyes; // 0x118
        al::LiveActor *mCapEyes; // 0x120
        PlayerActorHakoniwa *mPlayerActor; // 0x128
        unsigned char padding_220[0x220-0x130];
        HackCapThrowParam *throwParam; // 0x220
        unsigned char padding_2B8[0x2B8-0x228];
        PlayerCapActionHistory *mCapActionHistory; // 0x2B8
        unsigned char padding_2E0[0x2E0-0x2C0];
        HackCapJointControlKeeper *mJointKeeper; // 0x2E0
};