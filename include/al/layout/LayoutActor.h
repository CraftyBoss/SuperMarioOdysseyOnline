#pragma once

#include "al/actor/IUseName.h"
#include "al/audio/AudioKeeper.h"
#include "al/camera/CameraDirector.h"
#include "al/effect/EffectKeeper.h"
#include "al/hio/HioNode.h"
#include "al/layout/IUseLayout.h"
#include "al/message/IUseMessageSystem.h"
#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"
#include "al/scene/SceneObjHolder.h"
#include "sead/prim/seadSafeString.h"
#include "LayoutSceneInfo.h"

#include "al/LiveActor/LiveActor.h"

namespace al {

class LayoutActionKeeper;

class IUseLayoutAction : virtual public IUseName {
    public:
        virtual al::LayoutActionKeeper* getLayoutActionKeeper() const = 0;
};

class LayoutTextPaneAnimator {};

class LayoutExecuteInfo {};

class HitReactionKeeper {};
                //: public al::IUseNerve, public al::IUseEffectKeeper, public al::IUseAudioKeeper, public al::IUseStageSwitch, public al::IUseSceneObjHolder, public al::IUseAreaObj, public al::IUseCamera, public al::IUseCollision, public al::IUseRail, public al::IUseHioNode
                //: public al::IUseStageSwitch, public al::IUseAreaObj, public al::IUseCollision, public al::IUseRail,
class LayoutActor : public al::IUseHioNode, public al::IUseNerve, public al::IUseLayout, public al::IUseLayoutAction, public al::IUseMessageSystem, public al::IUseCamera, public al::IUseAudioKeeper, public al::IUseEffectKeeper, public al::IUseSceneObjHolder 
{
    public:
        LayoutActor(char const*);

        virtual al::NerveKeeper* getNerveKeeper(void) const {return mNerveKeeper;}

        virtual void appear();
        virtual void kill();
        virtual void movement();
        virtual void calcAnim(bool);

        virtual const char *getName(void) const {return mName.cstr();}
        virtual al::EffectKeeper *getEffectKeeper(void) const {return mEffectKeeper;}
        virtual al::AudioKeeper *getAudioKeeper(void) const {return mAudioKeeper;}
        virtual al::LayoutActionKeeper *getLayoutActionKeeper(void) const {return mLytActionKeeper;}
        virtual al::LayoutKeeper* getLayoutKeeper(void) const {return mLytKeeper;}

        void initLayoutKeeper(al::LayoutKeeper *);
        void initActionKeeper(void);
        void initTextPaneAnimator(al::LayoutTextPaneAnimator *);
        void initExecuteInfo(al::LayoutExecuteInfo *);
        void initHitReactionKeeper(al::HitReactionKeeper *);
        void initSceneInfo(al::LayoutSceneInfo *);
        void initLayoutPartsActorKeeper(int);
        void initEffectKeeper(al::EffectKeeper *);
        void initAudioKeeper(al::AudioKeeper *);
        void initNerve(al::Nerve const*, int);
        void setMainGroupName(char const*);
        void syncAction();
        
        virtual al::CameraDirector *getCameraDirector(void) const {return mLytSceneInfo->mCameraDirector;}
        virtual al::SceneObjHolder *getSceneObjHolder(void) const {return mLytSceneInfo->mSceneObjHolder;}
        virtual al::MessageSystem* getMessageSystem(void) const {return mLytSceneInfo->mMessageSystem;}

        virtual void control();

        sead::FixedSafeString<0x80> mName; // 0x40
        NerveKeeper *mNerveKeeper; // 0xD8
        LayoutKeeper *mLytKeeper; // 0xE0
        LayoutActionKeeper *mLytActionKeeper; // 0xE8
        LayoutTextPaneAnimator *mTextPaneAnimator; // 0xF0
        EffectKeeper *mEffectKeeper; // 0xF8
        AudioKeeper *mAudioKeeper; // 0x100
        LayoutExecuteInfo *mExecuteInfo; // 0x108
        HitReactionKeeper *mHitReactionKeeper; // 0x110 
        LayoutSceneInfo *mLytSceneInfo; // 0x118
        struct LayoutPartsActorKeeper *mLytPartsActorKeeper; // 0x120
        bool mIsAlive; // 0x128
};
}  // namespace al

static_assert(sizeof(al::LayoutActor) == 0x130);

