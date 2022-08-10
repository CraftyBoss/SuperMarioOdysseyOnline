#pragma once

#include <sead/math/seadMatrix.h>
#include <sead/math/seadQuat.h>
#include <sead/math/seadVector.h>
#include <sead/prim/seadSafeString.h>
#include "al/LiveActor/LiveActor.h"
#include "al/async/FunctorBase.h"
#include "al/collision/Collider.h"
#include "game/Player/PlayerActorBase.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"

typedef unsigned int uint;

namespace al {

    void tryInitFixedModelGpuBuffer(const LiveActor*);
    void offUpdateMovementEffectAudioCollisionSensor(const LiveActor*);
    void hideModel(LiveActor *);
    void hideModelIfShow(const LiveActor*);
    void showModelIfHide(const LiveActor*);
    void setModelAlphaMask(const LiveActor*, float);
    void resetPosition(const LiveActor*);
    void onSyncClippingSubActor(LiveActor*, const LiveActor*);
    void onSyncHideSubActor(LiveActor*, const LiveActor*);
    void onSyncAlphaMaskSubActor(LiveActor*, const LiveActor*);
    void setMaterialProgrammable(LiveActor*);
    void startAction(LiveActor*, char const*);
    void startAction(IUseLayoutAction*, const char *, const char *);
    void startFreezeActionEnd(IUseLayoutAction *,char const*,char const*);
    void startHitReaction(const LiveActor *, char const*);
    void invalidateClipping(const LiveActor *);
    void validateClipping(const LiveActor *);
    void setNerveAtActionEnd(LiveActor*, const al::Nerve*);
    void updateMaterialCodeWater(LiveActor *);
    void updateMaterialCodeWater(LiveActor *, bool);
    void appearItem(const LiveActor *);
    void turnToTarget(LiveActor*, const sead::Vector3f&, float);
    void turnToTarget(LiveActor*, const al::LiveActor *, float);

    void expandClippingRadiusByShadowLength(LiveActor *,sead::Vector3f *, float);

    void initJointLocalXRotator(const LiveActor *,const float *,const char *);
    void initJointLocalYRotator(const LiveActor *,const float *,const char *);
    void initJointLocalZRotator(const LiveActor*, const float*, const char*);

    void initActorPoseTRSV(al::LiveActor *);
    void initActorPoseTRMSV(al::LiveActor *);
    void initActorPoseTRGMSV(al::LiveActor *);
    void initActorPoseTFSV(al::LiveActor *);
    void initActorPoseTFUSV(al::LiveActor *);
    void initActorPoseTFGSV(al::LiveActor *);
    void initActorPoseTQSV(al::LiveActor *);
    void initActorPoseTQGSV(al::LiveActor *);
    void initActorPoseTQGMSV(al::LiveActor *);
    void initActorPoseT(al::LiveActor *,sead::Vector3<float> const&);
    void initActorPoseTR(al::LiveActor *,sead::Vector3<float> const&,sead::Vector3<float> const&);

    void initLayoutPartsActor(LayoutActor*, LayoutActor*, const LayoutInitInfo&, char const*,
                              char const*);
    void initCreateActorWithPlacementInfo(LiveActor*, const al::ActorInitInfo&);
    void initMapPartsActor(LiveActor *, const al::ActorInitInfo  &, const char *);
    void initActorWithArchiveName(LiveActor*, const al::ActorInitInfo&, const sead::SafeString&, const char*);
    void initJointControllerKeeper(const LiveActor*, int);
    void initJointGlobalQuatController(const LiveActor*, const sead::Quatf*, const char*);

    void appearBreakModelRandomRotateY(LiveActor *);

    bool isNear(const LiveActor *, const LiveActor *, float);
    bool isClipped(const LiveActor*);
    bool isDead(const LiveActor*);
    bool isAlive(const LiveActor*);
    bool isHideModel(const LiveActor*);
    bool isEffectEmitting(const IUseEffectKeeper*, const char*);
    bool isActionEnd(const LiveActor*);
    bool isActionPlaying(const LiveActor*, const char *);
    bool isInvalidClipping(const LiveActor*);
    bool isInWater(const LiveActor *);
    bool isInWaterArea(const LiveActor *);
    bool isOnGround(const LiveActor *, unsigned int);
    bool isOnStageSwitch(IUseStageSwitch const *, const char *);
    bool isValidStageSwitch(IUseStageSwitch const *, const char *);
    bool isFallNextMove(const LiveActor *, const sead::Vector3f &, float, float);
    bool isInDeathArea(LiveActor *);
    bool isCollidedFloorCode(LiveActor *, const char *);
    bool isNoCollide(LiveActor const *);
    bool isNearPlayer(const LiveActor*, float);
    bool isFallOrDamageCodeNextMove(const LiveActor *,  const sead::Vector3f &, float, float);
    bool isFaceToTargetDegreeH(const LiveActor*, const sead::Vector3f &, const sead::Vector3f &, float);

    bool tryOnSwitchDeadOn(IUseStageSwitch *);
    bool trySyncStageSwitchAppear(LiveActor *);
    PlayerActorBase* tryFindNearestPlayerActor(const LiveActor *);
    bool tryFindNearestPlayerPos(sead::Vector3f *, const LiveActor *);
    bool tryAddRippleMiddle(LiveActor*);
    bool tryStartActionIfNotPlaying(LiveActor*, const char*);

    float getClippingRadius(al::LiveActor const*);
    sead::Vector3f *getClippingObb(al::LiveActor *);
    sead::Vector3f *getClippingCenterPos(al::LiveActor const*);

    sead::Vector3f& getTrans(const LiveActor*);
    sead::Vector3f* getTransPtr(LiveActor*);
    sead::Vector3f& getGravity(const LiveActor*);
    sead::Vector3f* getGravityPtr(const LiveActor*);
    sead::Vector3f& getFront(const LiveActor*);
    sead::Vector3f* getFrontPtr(LiveActor*);
    sead::Vector3f& getVelocity(const LiveActor*);
    sead::Vector3f* getVelocityPtr(LiveActor*);
    sead::Quatf& getQuat(al::LiveActor const*);
    sead::Quatf* getQuatPtr(al::LiveActor *);
    Collider* getActorCollider(LiveActor*);

    sead::Matrix34f* getJointMtxPtr(const LiveActor*, const char*); //return type might be const

    sead::Quatf* getQuatPtr(LiveActor *);

    sead::Vector3f* getOnGroundNormal(const LiveActor *, uint);

    void scaleVelocity(LiveActor*, float);
    void scaleVelocityDirection(LiveActor*, sead::Vector3f const&, float);

    void setClippingObb(LiveActor*, sead::BoundBox3f const&);
    void setClippingInfo(LiveActor*, float, sead::Vector3f const*);
    void setClippingNearDistance(LiveActor *,float);

    void setTrans(LiveActor *, sead::Vector3f const &);
    void setVelocity(LiveActor*, sead::Vector3f const&);
    void setVelocity(LiveActor*, float, float, float);
    void setVelocityX(LiveActor*, float);
    void setVelocityY(LiveActor*, float);
    void setVelocityZ(LiveActor*, float);
    void setVelocityZero(LiveActor*);
    void setVelocityBlowAttackAndTurnToTarget(LiveActor *, sead::Vector3f const&,
                                                  float, float);
    void setActionFrameRate(LiveActor*, float);

    void addVelocityToGravityFittedGround(LiveActor*, float, unsigned int);
    void addVelocityToGravity(LiveActor*, float);
    void addVelocityToDirection(LiveActor*, sead::Vector3f const &, float);
    void addVelocity(LiveActor*, sead::Vector3f const &);
    void addVelocityX(LiveActor*, float);
    void addVelocityY(LiveActor*, float);
    void addVelocityZ(LiveActor*, float);

    void calcFrontDir(sead::Vector3f *, const LiveActor *);
    void calcQuat(sead::Quatf*, const LiveActor*);
    void calcJointFrontDir(sead::Vector3f*, const LiveActor*, const char*);
    void calcJointPos(sead::Vector3f*, const LiveActor*, const char*);

    void makeQuatUpFront(sead::Quatf *, sead::Vector3f const &, sead::Vector3f const &);

    void rotateQuatYDirDegree(LiveActor *, float);

    f32* findActorParamF32(const LiveActor*, const char*);

    s32* findActorParamS32(const LiveActor*, const char*);

    LiveActor* getSubActor(const LiveActor*, const char*); //NOTE: unknown return type

    bool listenStageSwitchOnAppear(IUseStageSwitch *, al::FunctorBase const &functor);
}

namespace rs {

sead::Vector3f* getPlayerPos(const al::LiveActor*);

}
