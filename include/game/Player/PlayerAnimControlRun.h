#pragma once

#include "sead/math/seadVector.h"
#include "PlayerAnimator.h"
#include "PlayerConst.h"

class IJudge;

class PlayerEffect;

// 0x40 in size
class PlayerAnimControlRun {
    public:
        PlayerAnimControlRun(PlayerAnimator *, PlayerConst const*, IJudge const*, PlayerEffect *, bool isMoon);
        void reset(float, bool);
        bool isAnimDashFast(void);
        void update(float, sead::Vector3f const &);

        PlayerAnimator *mPlayerAnimator; // 0x0
        PlayerEffect *mPlayerEffect; // 0x8
        PlayerConst *mPlayerConst; // 0x10
        IJudge *mJudge; // 0x18
        bool unk1; // 0x20
        float unk2; // 0x24
        int unk3; // 0x28
        bool isMoveNormal; // 0x30 inverse of isMoon arg 
        undefined8 unk; // 0x32(?)
        char *animName; // 0x38
};