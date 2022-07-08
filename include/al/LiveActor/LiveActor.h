#pragma once

#include "al/actor/ActorInitInfo.h"
#include "al/actor/ActorSceneInfo.h"
#include "al/actor/ActorActionKeeper.h"
#include "al/area/AreaObjDirector.h"
#include "al/audio/AudioKeeper.h"
#include "al/camera/CameraDirector.h"
#include "al/collision/CollisionDirector.h"
#include "al/effect/EffectKeeper.h"
#include "al/hio/HioNode.h"
#include "al/nerve/Nerve.h"
#include "al/nerve/NerveStateCtrl.h"
#include "al/pose/ActorPoseKeeper.h"
#include "al/rail/RailKeeper.h"
#include "al/rail/RailRider.h"
#include "al/scene/SceneObjHolder.h"
#include "al/screen/ScreenPointKeeper.h"
#include "al/sensor/HitSensorKeeper.h"
#include "al/switch/StageSwitchKeeper.h"
#include "al/actor/SubActorKeeper.h"

// vtable for LiveActor: 1C4EB58

namespace al
{

    class ActorPoseKeeperBase;
    class ActorExecuteInfo;
    class ActorItemKeeper;
    class ActorScoreKeeper;
    class Collider;
    class CollisionParts;
    class ModelKeeper;
    class ShadowKeeper;
    class ActorPrePassLightKeeper;
    class ActorOcclusionKeeper;
    class LiveActorFlag;

    class ActorInitInfo;
    class HitSensor;
    class SensorMsg;
    class ScreenPointer;
    class ScreenPointTarget;

    class LiveActor : public al::IUseNerve, public al::IUseEffectKeeper, public al::IUseAudioKeeper, public al::IUseStageSwitch, public al::IUseSceneObjHolder, public al::IUseAreaObj, public al::IUseCamera, public al::IUseCollision, public al::IUseRail, public al::IUseHioNode
    {
    public:
        LiveActor(const char *);

        virtual al::NerveKeeper* getNerveKeeper() const;

        virtual void init(const ActorInitInfo &);
        virtual void initAfterPlacement();
        virtual void appear();
        virtual void makeActorAlive();
        virtual void kill();
        virtual void makeActorDead();
        virtual void movement();
        virtual void calcAnim();
        virtual void draw() const;
        virtual void startClipped();
        virtual void endClipped();
        // source = sensor belonging to this actor
        // target = sensor belonging to other actor
        virtual void attackSensor(HitSensor *source, HitSensor *target);
        virtual bool receiveMsg(const SensorMsg *msg, HitSensor *source, HitSensor *target);
        virtual bool receiveMsgScreenPoint(const SensorMsg *, ScreenPointer *, ScreenPointTarget *);

        virtual const char *getName() const { return this->mActorName; };

        virtual sead::Matrix34f *getBaseMtx() const;

        virtual al::EffectKeeper *getEffectKeeper() const { return this->mEffectKeeper; };

        virtual al::AudioKeeper *getAudioKeeper() const { return this->mAudioKeeper; };

        virtual al::StageSwitchKeeper *getStageSwitchKeeper() const { return this->mStageSwitchKeeper; };

        virtual al::RailRider *getRailRider() const
        {
            if (this->mRailKeeper)
                return this->mRailKeeper->getRailRider();
            return nullptr;
        };

        virtual al::SceneObjHolder *getSceneObjHolder() const { return this->mSceneInfo->mSceneObjHolder; };

        virtual al::CollisionDirector *getCollisionDirector() const { return this->mSceneInfo->mCollisionDirector; };

        virtual al::AreaObjDirector *getAreaObjDirector() const { return this->mSceneInfo->mAreaObjDirector; };

        virtual al::CameraDirector *getCameraDirector() const { return this->mSceneInfo->mCameraDirector; };

        virtual void initStageSwitchKeeper() { this->mStageSwitchKeeper = new StageSwitchKeeper(); };

        virtual void control();

        virtual void updateCollider();

        const char *mActorName;                                // 0x48
        al::ActorPoseKeeperBase *mPoseKeeper;                  // 0x50
        al::ActorExecuteInfo *mLayoutExecuteInfo;              // 0x58
        al::ActorActionKeeper *mActorActionKeeper;             // 0x60
        al::ActorItemKeeper *mActorItemKeeper;                 // 0x68
        al::ActorScoreKeeper *mActorScoreKeeper;               // 0x70
        al::Collider *mCollider;                               // 0x78
        al::CollisionParts *mCollisionParts;                   // 0x80
        al::ModelKeeper *mModelKeeper;                         // 0x88
        al::NerveKeeper *mNerveKeeper;                         // 0x90
        al::HitSensorKeeper *mHitSensorKeeper;                 // 0x98
        al::ScreenPointKeeper *mScreenPointKeeper;             // 0xA0
        al::EffectKeeper *mEffectKeeper;                       // 0xA8
        al::AudioKeeper *mAudioKeeper;                         // 0xB0
        void *gap_4;                                           // 0xB8
        al::StageSwitchKeeper *mStageSwitchKeeper;             // 0xC0
        al::RailKeeper *mRailKeeper;                           // 0xC8
        al::ShadowKeeper *mShadowKeeper;                       // 0xD0
        al::ActorPrePassLightKeeper *mActorPrePassLightKeeper; // 0xD8
        al::ActorOcclusionKeeper *mActorOcclusionKeeper;       // 0xE0
        al::SubActorKeeper *mSubActorKeeper;                   // 0xE8
        void *gap_6;                                           // 0xF0
        al::ActorSceneInfo *mSceneInfo;                        // 0xF8
        al::LiveActorFlag *mLiveActorFlag;                     // 0x100
    };
};