#pragma once

#include "types.h"
#include "al/LiveActor/LiveActor.h"

class HackCapThrowParam { // stores parameters used in calculating the way HackCap is thrown
    public:
        HackCapThrowParam(al::LiveActor *);

        f32* mHackThrowHeight; // 投げる高さ
        f32* mMaxVel; // 最高速度
        f32* mConstThrowSpeed; // 連続投げ速度
        s32* mBreakTime; // ブレーキ時間
        f32* mMaxDist; // 到達距離
        s32* mEndpointStopTime; // 端点停止時間
        s32* mMaxEndpointStopTime; // 最大端点停止時間
        f32* mReturnStrength; // 戻り強さ
        f32* mMaxRetSpeed; // 戻り最高速度
        f32* mTurnAngleLimit; // ターン限界角度
        f32* mWaterMaxSpeed; // [水中]最高速度
        f32* mWaterDist; // [水中]到達距離
        s32* mWaterBreakTime; // [水中]ブレーキ時間
        f32* mWaterMaxRetSpeed; // [水中]戻り最高速度
        f32* mTornadoDist; // [竜巻投げ]到達距離
        f32* mTornadoMaxDist; // [竜巻投げ]最高到達距離
        s32* mTornadoReflectTime; // [竜巻投げ]反射時間
        f32* mRollSpeed; // [転がし投げ]速度
        f32* mRollDistTop; // [転がし投げ]到達距離[上]
        f32* mRollDistBottom; // [転がし投げ]到達距離[下]
        s32* mRollBrakeTimeTop; // [転がし投げ]ブレーキ時間[上]
        s32* mRollBrakeTimeBottom; // [転がし投げ]ブレーキ時間[下]
        f32* mRollGroundGroundedPoseTrack; // [転がし投げ]姿勢追従[接地]
        f32* mRollGroundAerialPoseTrack; // [転がし投げ]姿勢追従[空中]
};