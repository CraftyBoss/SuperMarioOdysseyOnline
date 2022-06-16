#pragma once

#include "al/LiveActor/LiveActor.h"

namespace al
{
    class DemoActor : public LiveActor {
        public:
            DemoActor(const char* name);
            virtual void paddingFunc();
            virtual void init(ActorInitInfo const &);
            virtual void control(void);
            virtual void initDemoActor(al::ActorInitInfo const&, al::ActorInitInfo const&,
                               sead::Matrix34f const*, bool);
            virtual void initDemoActorSerial(al::ActorInitInfo const&, al::ActorInitInfo const&,
                                     sead::Matrix34f const*);
            virtual void initAfterCreateFromFactory(al::ActorInitInfo const&, al::ActorInitInfo const&,
                                            sead::Matrix34f const*, bool);
            virtual void startAction(int);
            virtual void resetDynamics(void);

            bool isExistAction(int) const;
            const char* getDemoActionName(int) const;
            void startActionByName(const char*);
            void hideModelBySwitch(void);
            void showModelBySwitch(void);
            void endDemo(void);

            void exeDelay(void);
            void exeAction(void);

            struct DemoActionList *mActList = nullptr; // 0x108
            sead::Matrix34f mPoseMtx = sead::Matrix34f::ident; // 0x110 (size 0x30)
            int mActDelay = 0; // 0x140
            int mActionIndex = 0; // 0x144
            int mSubActorNum = 0xFFFFFFFF; // 0x148
            int mShowModelStartFrame = 0xFFFFFFFF; // 0x14C
            int mShowModelEndFrame = 0; // 0x150
            bool unkBool1 = false;
            bool unkBool2 = false;
            struct JointSpringControllerHolder *mJointControllerHolder = nullptr; // 0x158
    };
}  // namespace al
