#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/action/ActionEffectCtrl.h"

#include "sead/math/seadVector.h"

namespace al
{

    class ActorResource;
    class ActionAnimCtrl;
    class NerveActionCtrl;
    class ActionFlagCtrl;
    class ActionSeCtrl;
    class ActionBgmCtrl;
    class ActionPadAndCameraCtrl  {
        public:
            ActionPadAndCameraCtrl(LiveActor const *, al::ActorResource const *, sead::Vector3f const *, char const *);
            unsigned char padding[0x18];
            int mRumbleCount; // 0x18
    };
    class ActionScreenEffectCtrl;
    class ActorActionKeeper
    {
    public:
        inline ActorActionKeeper(LiveActor *, char const*, ActionAnimCtrl *, NerveActionCtrl *, ActionFlagCtrl *, ActionEffectCtrl *, ActionSeCtrl *, ActionBgmCtrl *, ActionPadAndCameraCtrl *, ActionScreenEffectCtrl *);
        void tryCreate(al::LiveActor *,al::ActorResource const*,char const*,char const*);
        void startAction(char const*);
        void tryStartActionNoAnim(char const*);
        void updatePrev(void);
        void updatePost(void);
        void init(void);

        LiveActor *mParentActor; // 0x0
        const char *mActorName; // 0x8
        bool unkBool; // 0x10
        ActionAnimCtrl *mAnimCtrl; // 0x18
        NerveActionCtrl *mNrvActionCtrl; // 0x20
        ActionFlagCtrl *mFlagCtrl; // 0x28
        ActionEffectCtrl *mEffectCtrl; // 0x30
        ActionSeCtrl *mSeCtrl; // 0x38
        ActionScreenEffectCtrl *mScreenEffectCtrl; // 0x40
        ActionPadAndCameraCtrl *mPadAndCamCtrl; // 0x48
        ActionBgmCtrl *mBgmCtrl; // 0x50
    };
} // namespace al
