#pragma once

#include "al/scene/ISceneObj.h"
#include "al/scene/SceneObjHolder.h"
#include "al/util/AudioUtil.h"
#include "al/util/ControllerUtil.h"
#include "al/util/GraphicsUtil.h"
#include "al/util/LayoutUtil.h"
#include "al/util/LiveActorUtil.h"
#include "al/util/MathUtil.h"
#include "al/util/NerveUtil.h"
#include "al/util/CameraUtil.h"

namespace al
{
    class LiveActor;

    class AreaObj;

}
#include <sead/math/seadVector.hpp>
#include <sead/prim/seadSafeString.hpp>
#include <sead/heap/seadHeap.h>
#include <sead/basis/seadNew.h>
#include <sead/gfx/seadFrameBuffer.h>

#include "al/scene/Scene.h"
#include "al/PlayerHolder/PlayerHolder.h"
#include "al/audio/AudioKeeper.h"
#include "al/camera/Projection.h"
#include "al/camera/CameraTargetBase.h"
#include "al/layout/IUseLayout.h"
#include "al/layout/LayoutKit.h"
#include "al/layout/LayoutActor.h"
#include "al/sensor/SensorMsg.h"
#include "al/stage/StageInfo.h"
#include "al/area/AreaObjGroup.h"
#include "al/async/FunctorBase.h"
#include "al/execute/ExecuteDirector.h"

#include "game/Player/PlayerActorHakoniwa.h"

#include "agl/DrawContext.h"

#include "nn/ui2d/Texture.h"

#include "types.h"

template<class T>
al::LiveActor* createActorFunction(const char *name);

namespace al
{
// getters

    struct SceneMsgCtrl;

    sead::Vector3f *getCameraUp(al::IUseCamera const *, int);

    sead::Vector3f *getScale(al::LiveActor const *);

    float *getScaleX(al::LiveActor const *);

    float *getScaleY(al::LiveActor const *);

    float *getScaleZ(al::LiveActor const *);

    al::PlayerHolder *getScenePlayerHolder(al::Scene const *);

    PlayerActorBase *getPlayerActor(al::LiveActor const *, int);

    PlayerActorBase *tryGetPlayerActor(al::PlayerHolder const *, int);

    sead::Heap *getCurrentHeap(void);
    sead::Heap* getStationedHeap();
    sead::Heap* getSequenceHeap();
    sead::Heap* getSceneHeap();

    al::Projection *getProjection(al::IUseCamera const *, int);

    int getSubActorNum(al::LiveActor const *);

    al::LiveActor *getSubActor(al::LiveActor const *, const char *);
    al::LiveActor *tryGetSubActor(al::LiveActor const *, const char *);

    al::LiveActor *getSubActor(al::LiveActor const *, int);

    int getPlayerControllerPort(int);

    char const *getActionName(al::LiveActor const *);

    char const *getActionFrame(al::LiveActor const *);

    bool isSklAnimExist(al::LiveActor const *, const char *);
    bool clearSklAnimInterpole(al::LiveActor *);

    // setters

    void setTransY(al::LiveActor *, float);

    void setTrans(al::LiveActor *, sead::Vector3f const &);

    void setScale(al::LiveActor *, sead::Vector3f const &);

    void setScale(al::LiveActor *, float, float, float);

    void setScaleAll(al::LiveActor *, float);

    void setScaleX(al::LiveActor *, float);

    void setScaleY(al::LiveActor *, float);

    void setScaleZ(al::LiveActor *, float);

    void setGravity(al::LiveActor const *, sead::Vector3f const &);

    void setFront(al::LiveActor *, sead::Vector3f const &);

    void setQuat(al::LiveActor *, const sead::Quatf &);

    void setVelocityZero(al::LiveActor *);

    void setEffectParticleScale(al::IUseEffectKeeper *actor, char const *effectName, float scale);

    // layout stuff

    al::LayoutInitInfo *getLayoutInitInfo(al::ActorInitInfo const&);

    void requestCaptureRecursive(al::LayoutActor const*);

    void startAction(IUseLayoutAction*, const char *, const char *);

    bool isActionPlaying(al::IUseLayoutAction *, const char *action, const char *group);

    bool isActionEnd(al::IUseLayoutAction const*, char const*);

    void setPaneTexture(al::IUseLayout *, char const *, nn::ui2d::TextureInfo const *);

    void setPaneString(al::IUseLayout *layout, char const *paneName, char16_t const *, ushort);

    void setPaneStringFormat(al::IUseLayout *layout, char const *paneName, char const *format,...);

    void setPaneLocalTrans(al::IUseLayout *layout, const char *paneName, sead::Vector3f const &);
    void setPaneLocalTrans(al::IUseLayout *layout, const char *paneName, sead::Vector2f const &);
    void setPaneLocalSize(al::IUseLayout *layout, const char *paneName, sead::Vector2f const &);
    void setPaneLocalScale(al::IUseLayout *layout, const char *paneName, sead::Vector2f const &);
    void setPaneLocalRotate(al::IUseLayout *layout, const char *paneName, sead::Vector3f const &);

    sead::Vector3f &getPaneLocalTrans(const al::IUseLayout *layout, const char *paneName);
    void getPaneLocalSize(sead::Vector2f *, const al::IUseLayout *layout, const char *paneName);
    sead::Vector2f &getPaneLocalScale(const al::IUseLayout *layout, const char *paneName);
    sead::Vector3f &getPaneLocalRotate(const al::IUseLayout *layout, const char *paneName);

    bool killLayoutIfActive(al::LayoutActor *);

    // camera stuff

    void setCameraTarget(al::IUseCamera *, al::CameraTargetBase *);

    // calc functions

    f32 calcDistance(al::LiveActor const *, al::LiveActor const*); // calculates distance between two actors

    f32 calcDistance(al::LiveActor const *, sead::Vector3f const&); // calculates distance between an actor and a position in the world

    void calcFrontDir(sead::Vector3f *result, al::LiveActor const *actor);

    // velocity stuff

    void addVelocity(al::LiveActor *,sead::Vector3f const&);

    void setVelocity(al::LiveActor *,sead::Vector3f const&);

    void scaleVelocityExceptDirection(al::LiveActor *,sead::Vector3f const&, float);

    void addVelocityToGravity(al::LiveActor *, float);

    // animation stuff

    void startVisAnimForAction(al::LiveActor*, char const*);
    
    void startVisAnim(al::LiveActor *, char const *);
    void startMtpAnim(al::LiveActor *, char const *);
    void startMclAnim(al::LiveActor *, char const *);

    float getSklAnimBlendWeight(al::LiveActor const*,int);
    void setSklAnimBlendWeight(al::LiveActor *,float,int);
    void setSklAnimBlendWeightDouble(al::LiveActor *,  float);
    void setSklAnimBlendWeightDouble(al::LiveActor *,  float,float);
    void setSklAnimBlendWeightTriple(al::LiveActor *,  float,float,float);
    void setSklAnimBlendWeightQuad(al::LiveActor *,    float,float,float,float);
    void setSklAnimBlendWeightFivefold(al::LiveActor *,float,float,float,float,float);
    void setSklAnimBlendWeightSixfold(al::LiveActor *, float,float,float,float,float,float);

    void offCalcAnim(al::LiveActor *);
    void onCalcAnim(al::LiveActor*);

    bool isVisAnimExist(const al::LiveActor *, const char *);
    bool isMtpAnimExist(const al::LiveActor *, const char *);
    bool isMclAnimExist(const al::LiveActor *, const char *);

    bool isActionEnd(al::LiveActor const *);

    bool isActionPlaying(al::LiveActor const *, char const *);

    bool tryStartActionSubActorAll(al::LiveActor *, char const *);

    bool tryStartActionIfNotPlaying(al::LiveActor*, char const*);
    
    bool tryStartAction(al::LiveActor *, char const *);

    void startAction(al::LiveActor *, char const *);

    const char * getPlayingSklAnimName(const al::LiveActor *actor, int index);

    bool tryStartSklAnimIfNotPlaying(al::LiveActor *actor, const char * animName);
    
    bool tryStartSklAnimIfExist(al::LiveActor *actor, const char * animName);

    // byml stuff

    bool tryGetByamlU8(uchar *,al::ByamlIter const&,char const*);
    bool tryGetByamlU16(ushort *,al::ByamlIter const&,char const*);
    bool tryGetByamlS16(short *,al::ByamlIter const&,char const*);
    bool tryGetByamlS32(int *,al::ByamlIter const&,char const*);
    bool tryGetByamlU32(uint *,al::ByamlIter const&,char const*);
    bool tryGetByamlS64(long *,al::ByamlIter const&,char const*);
    bool tryGetByamlU64(ulong *,al::ByamlIter const&,char const*);
    bool tryGetByamlF32(float *,al::ByamlIter const&,char const*);
    bool tryGetByamlV2f(sead::Vector2<float> *,al::ByamlIter const&);
    bool tryGetByamlV3f(sead::Vector3<float> *,al::ByamlIter const&);
    bool tryGetByamlV4f(sead::Vector4<float> *,al::ByamlIter const&);
    bool tryGetByamlScale(sead::Vector3<float> *,al::ByamlIter const&);
    bool tryGetByamlV2s32(sead::Vector2<int> *,al::ByamlIter const&);
    bool tryGetByamlV3s32(sead::Vector3<int> *,al::ByamlIter const&);
    bool tryGetByamlBox3f(sead::BoundBox3<float> *,al::ByamlIter const&);
    bool tryGetByamlV3f(sead::Vector3<float> *,al::ByamlIter const&,char const*);
    bool tryGetByamlV2f(sead::Vector2<float> *,al::ByamlIter const&,char const*);
    bool tryGetByamlV4f(sead::Vector4<float> *,al::ByamlIter const&,char const*);
    bool tryGetByamlScale(sead::Vector3<float> *,al::ByamlIter const&,char const*);
    bool tryGetByamlV2s32(sead::Vector2<int> *,al::ByamlIter const&,char const*);
    bool tryGetByamlV3s32(sead::Vector3<int> *,al::ByamlIter const&,char const*);
    bool tryGetByamlBox3f(sead::BoundBox3<float> *,al::ByamlIter const&,char const*);
    bool tryGetByamlString(char const**,al::ByamlIter const&,char const*);
    bool tryGetByamlColor(sead::Color4f *,al::ByamlIter const&);
    bool tryGetByamlColor(sead::Color4f *,al::ByamlIter const&,char const*);
    bool tryGetByamlBool(bool *,al::ByamlIter const&,char const*);
    const char * tryGetByamlKeyStringOrNULL(al::ByamlIter const&,char const*);
    bool tryGetByamlKeyIntOrZero(al::ByamlIter const&,char const*);
    bool tryGetByamlKeyU32OrZero(al::ByamlIter const&,char const*);
    bool tryGetByamlKeyFloatOrZero(al::ByamlIter const&,char const*);
    bool tryGetByamlKeyBoolOrFalse(al::ByamlIter const&,char const*);
    bool tryGetByamlIterByKey(al::ByamlIter *,al::ByamlIter const&,char const*);
    bool tryGetByamlKeyAndIntByIndex(char const**,int *,al::ByamlIter const&,int);

    // nerve stuff

    bool isLessStep(al::IUseNerve const*,int); // checks if the current nerve has been activated for a certain amount of frames(?)

    bool isFirstStep(al::IUseNerve const *);

    bool isNerve(al::IUseNerve const*, al::Nerve const*);

    void setNerve(al::IUseNerve *,al::Nerve const*);

    // effect stuff

    void emitEffect(al::IUseEffectKeeper *effectKeeper, char const *effectName, sead::Vector3f const *effectPosition);
    
    bool tryEmitEffect(al::IUseEffectKeeper *effectKeeper, char const *effectName, sead::Vector3f const *effectPosition);

    void tryDeleteEffect(al::IUseEffectKeeper *effectKeeper, char const *effectName);

    // sensor stuff

    // enum SensorType {
    //     Unknown, // 0
    //     Player, // 1
    //     PlayerAttack, // 2
    //     PlayerFoot // 3
    // };

    al::HitSensor *getHitSensor(al::LiveActor const *host, char const *name);

    al::LiveActor *getSensorHost(al::HitSensor const *);

    void invalidateHitSensors(al::LiveActor *);
    void validateHitSensors(al::LiveActor *);

    void invalidateHitSensor(al::LiveActor *, const char *);
    void validateHitSensor(al::LiveActor *, const char *);
    
    void addHitSensor(al::LiveActor *actor, al::ActorInitInfo const &initInfo, char const *sensorName, uint typeEnum, float radius, ushort maxCount, sead::Vector3f const& position);

    bool isMsgPlayerTrampleReflect(al::SensorMsg const *);

    bool isSensorPlayerAttack(al::HitSensor const *targetSensor);

    bool sendMsgPlayerHipDropKnockDown(al::HitSensor *target, al::HitSensor *source);

    // audio

    void tryPauseBgmIfLowPriority(al::IUseAudioKeeper const *keeper, const char *audioName, int unk);    

    // player stuff

    void getClassName(const char **namePtr, const al::ActorInitInfo &info);

    void getDisplayName(const char **namePtr, const al::ActorInitInfo &info);

    // stage switch stuff

    // stage init stuff


    bool tryInitPlacementSingleObject(al::Scene*, al::ActorInitInfo const&, int, char const*,
                                      char const*);
    
    bool tryInitPlacementSingleObject(al::Scene *,al::ActorInitInfo const&,int,char const*);
    
    al::StageInfo *getStageInfoMap(al::Scene const*,int);

    void tryGetPlacementInfoAndCount(al::PlacementInfo *, int *, al::StageInfo const*, char const*);

    void getPlacementInfoByIndex(al::PlacementInfo*, al::PlacementInfo const&, int);

    bool tryGetPlacementId(al::PlacementId *pId, al::PlacementInfo const &placement); //{ return pId->init(placement); };
    bool tryGetPlacementId(al::PlacementId *pId, al::ActorInitInfo const &placement);

    void getObjectName(const char **namePtr, const al::PlacementInfo &placementInfo);
    void getObjectName(const char **namePtr, const al::ActorInitInfo &placementInfo);

    bool tryGetObjectName(const char **namePtr, const al::PlacementInfo &placementInfo);
    bool tryGetObjectName(const char **namePtr, const al::ActorInitInfo &placementInfo);

    bool tryGetStringArg(const char **namePtr, const al::PlacementInfo &info, const char *key);
    bool tryGetStringArg(const char **namePtr, const al::ActorInitInfo &info, const char *key);

    bool tryGetClassName(const char **namePtr, const al::PlacementInfo &info);
    bool tryGetClassName(const char **namePtr, const al::ActorInitInfo &info);

    bool tryGetDisplayName(const char **namePtr, const al::PlacementInfo &info);
    bool tryGetDisplayName(const char **namePtr, const al::ActorInitInfo &info);

    bool tryGetTrans(sead::Vector3f *, al::PlacementInfo const&);

    // scene init

    void initPlacementObjectMap(al::Scene *, al::ActorInitInfo const &, char const *);
    void initPlacementObjectDesign(al::Scene *, al::ActorInitInfo const &, char const *);
    void initPlacementObjectSound(al::Scene *, al::ActorInitInfo const &, char const *);

    LiveActor* createPlacementActorFromFactory(al::ActorInitInfo const&, al::PlacementInfo const*);

    // layout init stuff

    void initLayoutActor(al::LayoutActor *,al::LayoutInitInfo const&,char const*,char const*);

    // actor init stuff

    bool tryGetArg(int *, al::ActorInitInfo const&, char const*);
    bool tryGetArg(int *, al::PlacementInfo const&, char const*);

    bool tryGetArg(float *, al::ActorInitInfo const&, char const*);
    bool tryGetArg(float *, al::PlacementInfo const&, char const*);

    bool tryGetArg(bool *, al::ActorInitInfo const&, char const*);
    bool tryGetArg(bool *, al::PlacementInfo const&, char const*);

    bool tryGetArgV3f(sead::Vector3<float> *,al::ActorInitInfo const&, char const*);
    bool tryGetArgV3f(sead::Vector3<float> *,al::PlacementInfo const&, char const*);

    bool tryGetArgV2f(sead::Vector2<float> *,al::ActorInitInfo const&, char const*);
    bool tryGetArgV2f(sead::Vector2<float> *,al::PlacementInfo const&, char const*);

    void registerExecutorFunctor(char const *, al::ExecuteDirector *, al::FunctorBase const &);

    void initExecutorPlayer(al::LiveActor *,al::ActorInitInfo const&);
    void initExecutorPlayerPreMovement(al::LiveActor *,al::ActorInitInfo const&);
    void initExecutorPlayerMovement(al::LiveActor *,al::ActorInitInfo const&);
    void initExecutorPlayerModel(al::LiveActor *,al::ActorInitInfo const&);
    void initExecutorPlayerDecoration(al::LiveActor *,al::ActorInitInfo const&);
    void initExecutorModelUpdate(al::LiveActor *, al::ActorInitInfo const &);
    void initActorWithArchiveName(al::LiveActor *actor, al::ActorInitInfo const &initInfo, sead::SafeString const &archiveName, char const *suffix);
    void initExecutorUpdate(al::LiveActor *,al::ActorInitInfo const&, const char *);
    void initExecutorDraw(al::LiveActor *,al::ActorInitInfo const&, const char *);
    void initActor(al::LiveActor *, al::ActorInitInfo const&);
    void initActorCommon(al::LiveActor *actor, al::ActorInitInfo const &info, char const *dataFolder, char const *archiveName, char const *suffix); // not a real symbol
    void initActorSuffix(al::LiveActor*, al::ActorInitInfo const&, char const*);
    void initActorInitInfo(al::ActorInitInfo *,al::Scene const*,al::PlacementInfo const*,al::LayoutInitInfo const*,al::ActorFactory const*,al::SceneMsgCtrl *,GameDataHolderBase *);

    // misc

    void readSaveDataSync(const char* dataFile, uint, uint);
    
    bool isSuccessSaveDataSequence();

    void validateCollisionParts(al::LiveActor*);
    
    void invalidateCollisionParts(al::LiveActor *);

    bool isExistCollisionParts(const al::LiveActor *);

    void copyPose(al::LiveActor *from, const al::LiveActor *to);

    void hideModelIfShow(al::LiveActor *);
    void showModelIfHide(al::LiveActor *);

    void invalidateClipping(al::LiveActor *);
    
    void validateClipping(al::LiveActor *);

    void hideSilhouetteModelIfShow(al::LiveActor *);

    bool isExistDitherAnimator(const al::LiveActor *);

    void validateDitherAnim(al::LiveActor *);
    void invalidateDitherAnim(al::LiveActor *);

    bool isHideModel(const al::LiveActor *);

    bool isDead(const al::LiveActor *);
    
    bool isAlive(const al::LiveActor *);

    char16_t *getSystemMessageString(al::IUseMessageSystem const *, char const *, char const *);

    void initPlacementByStageInfo(al::StageInfo const *, char const *, al::ActorInitInfo const &);

    al::AreaObjGroup *tryFindAreaObjGroup(al::IUseAreaObj const *, const char *areaName);

    sead::DrawContext *getSceneDrawContext(al::Scene const*); // these two things are all thats needed to setup text writer in the right context

    sead::LogicalFrameBuffer *getSceneFrameBufferMain(al::Scene const*);

    int getLayoutDisplayWidth();
    int getLayoutDisplayHeight();

    void executeDraw(al::LayoutKit const *, char const *);

    bool isExistFile(sead::SafeString const &filePath);

    al::StageInfo *getStageInfoMap(al::Scene const*,int);

    bool isVisAnimExist(const al::LiveActor *, const char *);

    bool isInAreaObj(al::LiveActor const *, const char *);

    al::AreaObj *tryFindAreaObj(al::LiveActor const *, const char *);

    void tryGetAreaObjArg(int *, al::AreaObj const *, const char *);
    void tryGetAreaObjArg(float *, al::AreaObj const *, const char *);
    void tryGetAreaObjArg(bool *, al::AreaObj const *, const char *);

    void tryGetAreaObjStringArg(const char **, al::AreaObj const *, const char *);

    void offCollide(al::LiveActor *);
    void onCollide(al::LiveActor *);

    bool tryStartSe(al::IUseAudioKeeper const *, sead::SafeStringBase<char> const &);

    void startSe(al::IUseAudioKeeper const *, sead::SafeStringBase<char> const &);

    void startHitReaction(al::LiveActor const *, char const*);

    bool isInDeathArea(al::LiveActor const *);

    void calcCameraUpDir(sead::Vector3f *, al::IUseCamera const*, int);

    const unsigned char *tryGetBymlFromArcName(sead::SafeStringBase<char> const &, sead::SafeStringBase<char> const &);

    class ActorInitInfo;

    bool getArg(int *, const al::ActorInitInfo &, const char *);

    bool isActiveDemo(const al::Scene *);

    bool isEqualString(char const *, char const *);
    bool isEqualString(sead::SafeStringBase<char> const &, sead::SafeStringBase<char> const &);

    bool isEqualSubString(char const *, char const *);

    bool isOnGround(al::LiveActor const*, uint);

    bool isActiveDemo(al::Scene const *);

    bool isInWaterPos(al::LiveActor const*, sead::Vector3f const &);

    // interpolation functions

    void lerpVec(sead::Vector3f *result, sead::Vector3f const& from, sead::Vector3f const& to, float rate);

    void slerpQuat(sead::Quatf *result, sead::Quatf const& from, sead::Quatf const& to, float rate);
    
    // dither anim stuff

    bool isExistDitherAnimator(al::LiveActor const *);

    void stopDitherAnimAutoCtrl(al::LiveActor *);
    void restartDitherAnimAutoCtrl(al::LiveActor *);

    void validateDitherAnim(al::LiveActor *);
    void invalidateDitherAnim(al::LiveActor *);

    float getDitherAnimNearClipStartDistance(al::LiveActor const *);
    float getDitherAnimNearClipEndDistance(al::LiveActor const *);

    void setDitherAnimSphereRadius(al::LiveActor *, float);
    void setDitherAnimBoundingBox(al::LiveActor *, sead::Vector3f const&);
    void setDitherAnimMaxAlpha(al::LiveActor *, float);
    void setDitherAnimClippingJudgeLocalOffset(al::LiveActor *, sead::Vector3f const&);
    void setDitherAnimClippingJudgeParam(al::LiveActor *, const char *);
}
