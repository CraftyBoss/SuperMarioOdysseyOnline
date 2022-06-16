#pragma once

#include "al/LiveActor/LiveActor.h"
#include "game/Interfaces/IUsePlayerCollision.h"
#include "game/Player/PlayerConst.h"
#include "game/Player/PlayerInput.h"

class PlayerActionGroundMoveControl {
public:
    PlayerActionGroundMoveControl(al::LiveActor *,PlayerConst const*,PlayerInput const*,IUsePlayerCollision const*);
    void initDash(struct IJudge *,float,int);
    void setupDash(float,int);
    void setup(float maxSpeed, float minSpeed, int normalAccelFrame, int stickOnBrakeFrame, int normalBrakeFrame, float gravityMove, float breakSpeed, int breakOnCounterBorder);
    void appear(void);
    void reset(sead::Vector3<float> const&);
    void calcInitBrakeOnCounter(void);
    void update(void);
    void updateSkateMove(void);
    void updateNormalMove(void);
    void updateNormalAndSnap(sead::Vector3<float> *);
    void calcTurnTiltRate(void);
    void calcMoveInput(sead::Vector3<float> *,sead::Vector3<float> const&);
    void isActiveSquatBrake(void);
    void updateHillAffect(sead::Vector3<float> const&,sead::Vector3<float> const&,bool);
    void calcMaxSpeed(float);
    void calcAccelRate(float);
    void updatePoseUpFront(sead::Vector3<float> const&, sead::Vector3<float> const&, float);

    void *qword0;
    PlayerConst *mPlayerConst;
    void *qword10;
    void *qword18;
    void *qword20;
    bool byte28;
    int dword2C;
    int dword30;
    int dword34;
    float mMaxSpeed;
    float mMinSpeed;
    void *qword40;
    int mNormalAccelFrame;
    int mStickOnBrakeFrame;
    int mNormalBrakeFrame;
    float mGravityMove;
    float mBreakSpeed;
    int mBreakOnCounterBorder;
    bool gap60[8];
    void *qword68;
    void *qword70;
    bool byte78;
    bool gap79[3];
    int dword7C;
    bool byte80;
    bool gap81[3];
    void *qword84;
    int dword8C;
    void *qword90;
    int dword98;
    bool byte9C;
    bool gap9D[3];
    int dwordA0;
    bool byteA4;
    bool gapA5[3];
    void *qwordA8;
    void *qwordB0;
    int dwordB8;
    s16 wordBC;
    bool gapBE[2];
    int dwordC0;
    bool byteC4;
    bool gapC5[15];
    s16 wordD4;
};