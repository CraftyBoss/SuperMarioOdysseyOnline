#pragma once

#include "sead/math/seadVector.h"

#include "al/sensor/HitSensor.h"

#include "game/Player/HackCap.h"
#include "game/Player/PlayerConst.h"
#include "game/Player/PlayerInput.h"
#include "game/Player/PlayerAnimator.h"

class PlayerTrigger;
class PlayerJudgePreInputCapThrow;
class PlayerCounterAfterCapCatch;

class PlayerSpinCapAttack {
    public:
        PlayerSpinCapAttack(HackCap *, const PlayerConst *, const PlayerTrigger *, const PlayerInput *, const PlayerCounterAfterCapCatch *, const PlayerJudgePreInputCapThrow *);
        void clearAttackInfo(void);
        void setupAttackInfo(void);
        void startCapSpinAttack(PlayerAnimator *, PlayerInput const *);
        void startCapSpinAttackAir(PlayerAnimator *, PlayerInput const *);
        void startCapSpinAttackSwim(PlayerAnimator *, PlayerInput const *);
        void startSpinSeparate(PlayerAnimator *, PlayerInput const *);
        void startSpinSeparateSwim(PlayerAnimator *, PlayerInput const *);
        void startSpinSeparateSwimSurface(PlayerAnimator *, PlayerInput const *);
        void startCapThrow(sead::Vector3f const & front, sead::Vector3f const & up, float speed, bool, sead::Vector3f const& unused);
        void attackSpinMsg(al::HitSensor *, al::HitSensor *);
        bool tryCancelCapState(PlayerAnimator *);
        bool tryStartCapSpinGroundMiss(PlayerAnimator *);
        bool tryStartCapSpinAirMiss(PlayerAnimator *);
        bool isCapSpinAttack(void) const;
        bool isValidAttackSensor(const PlayerAnimator *) const;
        bool isEnablePlaySpinCapMiss(const PlayerAnimator *) const;
        bool isSeparateSingleSpin(void) const;
        bool isThrowSwingRightDir(void) const;
        int getThrowFrameGround(void) const;
        int getThrowFrameAir(void) const;
        int getThrowFrameSwim(void) const;

        HackCap *mHackCap; // 0x0
        PlayerConst *mPlayerConst; // 0x8
        PlayerTrigger *mPlayerTrigger; // 0x10
        PlayerInput *mPlayerInput; // 0x18
        PlayerCounterAfterCapCatch *mCounterAfterCapCatch; // 0x20
        PlayerJudgePreInputCapThrow *jPreInputCapThrow; // 0x28
};