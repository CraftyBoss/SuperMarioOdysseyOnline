#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/async/FunctorV0M.hpp"
#include "al/async/FunctorBase.h"
#include "al/util.hpp"
#include "al/string/StringTmp.h"
#include "al/layout/BalloonMessage.h"

#include "game/Player/PlayerFunction.h"
#include "game/Player/PlayerJointControlPartsDynamics.h"
#include "game/Player/PlayerConst.h"
#include "game/Player/PlayerModelHolder.h"

#include "actors/PuppetCapActor.h"
#include "actors/PuppetHackActor.h"
#include "layouts/NameTag.h"
#include "sead/math/seadVector.h"
#include "server/DeltaTime.hpp"

#include "logger.hpp"
#include "puppets/PuppetInfo.h"
#include "puppets/HackModelHolder.hpp"
#include "helpers.hpp"
#include "algorithms/CaptureTypes.h"

class PuppetActor : public al::LiveActor {
    public:
        PuppetActor(const char *name);
        virtual void init(al::ActorInitInfo const &) override;
        virtual void initAfterPlacement(void) override;
        virtual void control(void) override;
        virtual void movement(void) override;
        virtual void makeActorAlive(void) override;
        virtual void makeActorDead(void) override;

        void initOnline(PuppetInfo *pupInfo);

        void startAction(const char *actName);
        void hairControl();

        void setBlendWeight(int index, float weight) { al::setSklAnimBlendWeight(getCurrentModel(), weight, index); };

        bool isNeedBlending();

        bool isInCaptureList(const char *hackName);

        PuppetInfo* getInfo() { return mInfo; }

        const char *getPuppetName() { return mInfo->puppetName; }

        bool addCapture(PuppetHackActor *capture, const char *hackType);

        al::LiveActor* getCurrentModel();

        int getMaxCaptures() {return mCaptures->getEntryCount(); };

        void debugTeleportCaptures(const sead::Vector3f& pos);

        void debugTeleportCapture(const sead::Vector3f& pos, int index);

        bool mIsDebug = false;

        float mClosingSpeed = 0;
        
        NameTag *mNameTag = nullptr; // temp public 
    private:
        void changeModel(const char* newModel);

        bool setCapture(const char* captureName);

        void syncPose();
        
        PlayerCostumeInfo *mCostumeInfo = nullptr;
        PuppetInfo *mInfo = nullptr;
        PuppetCapActor *mPuppetCap = nullptr;
        PlayerModelHolder *mModelHolder = nullptr;
        HackModelHolder* mCaptures = nullptr;

        CaptureTypes::Type mCurCapture = CaptureTypes::Type::Unknown;

        bool mIs2DModel = false;

        bool mIsCaptureModel = false;
};
