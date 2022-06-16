#pragma once

#include "HackCap.h"
#include "PlayerAnimator.h"
#include "PlayerInput.h"
#include "al/sensor/HitSensor.h"
#include "PlayerColliderHakoniwa.h"
#include "PlayerHackKeeper.h"
#include "PlayerCostumeInfo.h"
#include "PlayerModelChangerHakoniwa.h"

class PlayerInfo {
    public:
        PlayerInfo();

        PlayerModelChangerHakoniwa *pModelChanger; // 0x0
        struct PlayerOxygen *pOxygen; // 0x8
        PlayerAnimator *mPlayerAnimator; // 0x10
        struct PlayerBindKeeper *pBindKeeper; // 0x18
        struct PlayerDamageKeeper *pDamageKeeper; // 0x20
        struct PlayerDemoActionFlag *pDemoActionFlag; // 0x28
        struct PlayerEquipmentUser *pEquipmentUser; // 0x30
        HackCap *mHackCap; // 0x38 
        struct WorldEndBorderKeeper *mWorldEndBorderKeeper; // 0x40
        struct PlayerCarryKeeper *pCarryKeeper; // 0x48
        struct PlayerJointControlKeeper *pJoinControlKeeper; // 0x50
        struct PlayerCounterIceWater *pCounterIceWater; // 0x58
        struct PlayerStainControl *pStainControl; // 0x60
        struct FootPrintHolder *mFootPrintHolder; // 0x68
        al::HitSensor *mHitSensor; // 0x70
        struct PlayerFormSensorCollisionArranger *pSensorCollArranger; // 0x78
        PlayerInput *pInput; // 0x80
        PlayerColliderHakoniwa *pColliderHakoniwa; // 0x88
        struct PlayerModelHolder *pModelHolder; // 0x90
        PlayerHackKeeper *pHackKeeper; // 0x98
        struct PlayerCapManHeroEyesControl *pCapManHeroEyesCtrl; // 0xA0
        struct PlayerRecoverySafetyPoint *pRecoverySafetyPoint; // 0xA8
        PlayerCostumeInfo *pCostumeInfo; // 0xB0
        struct PlayerJudgeCameraInWater *pJudgeCameraInWater; // 0xB8
        struct PlayerJudgeTalkGround *pJudgeTalkGround; // 0xC0
        struct PlayerJudgeTalkSwim *pJudgeTalkSwim; // 0xC8
        struct PlayerJudgeDead *pJudgeDead; // 0xD0
        struct PlayerJudgeDeadWipeStart *pJudgeDeadWipeStart; // 0xD8
        struct PlayerJudgeDrawForward *pJudgeDrawForward; // 0xE0
        struct PlayerJudgeSameNerve *pJudgeSameNervePoleClimb; // 0xE8
        struct PlayerJudgeSameNerve *pJudgeSameNerveGrabCeil; // 0xF0
        struct PlayerJudgeSameNerve *pJudgeSameNerveWallCatch; // 0xF8
        struct PlayerJudgeActiveCameraSubjective *pJudgeActiveCameraSubjective; // 0x100
        // theres a lot more judges and same nerves but im too lazy to get them all
};