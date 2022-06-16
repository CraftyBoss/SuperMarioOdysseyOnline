#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/util.hpp"

#include "game/Player/PlayerFunction.h"
#include "game/Player/HackCap/HackCapJointControlKeeper.h"

#include "logger.hpp"
#include "puppets/PuppetInfo.h"
#include "helpers.hpp"

class PuppetCapActor : public al::LiveActor {
    public:
        PuppetCapActor(const char *name);
        virtual void init(al::ActorInitInfo const &) override;
        virtual void initAfterPlacement() override;
        virtual void control(void) override;
        virtual void movement(void) override;
        void initOnline(PuppetInfo *info);
        
        void startAction(const char *actName);
        void update();

    private:
        HackCapJointControlKeeper *mJointKeeper;
        PuppetInfo *mInfo;
};
