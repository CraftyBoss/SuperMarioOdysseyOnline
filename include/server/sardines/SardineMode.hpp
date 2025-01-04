#pragma once

#include "al/camera/CameraTicket.h"
#include "server/gamemode/GameModeBase.hpp"
#include "server/sardines/SardineIcon.h"

class SardineMode : public GameModeBase {
    public:
        SardineMode(const char* name);

        void init(GameModeInitInfo const& info) override;

        void begin() override;
        void update() override;
        void end() override;

        void pause() override;
        void unpause() override;

        bool showNameTag(PuppetInfo* other) override;

        void debugMenuControls(sead::TextWriter* gTextWriter) override;

        bool isUseNormalUI() const override { return false; }

        void processPacket(Packet* packet) override;
        Packet* createPacket() override;

        inline bool isPlayerAlone() const { return mInfo->isPlayerAlone(); }
        inline bool isPlayerPack()  const { return mInfo->isPlayerPack();  }

        void enableGravityMode()  { mInfo->mIsUseGravity = true;  }
        void disableGravityMode() { mInfo->mIsUseGravity = false; }
        bool isUseGravity() const { return mInfo->mIsUseGravity;  }
        void onBorderPullBackFirstStep(al::LiveActor* actor) override;

        bool hasCustomCamera() const override { return true; }
        void createCustomCameraTicket(al::CameraDirector* director) override;

        bool hasMarioCollision() override { return SardineInfo::mHasMarioCollision; }
        bool hasMarioBounce()    override { return SardineInfo::mHasMarioBounce;    }
        bool hasCappyCollision() override { return SardineInfo::mHasCappyCollision; }
        bool hasCappyBounce()    override { return SardineInfo::mHasCappyBounce;    }

    private:
        GameModeTimer*    mModeTimer  = nullptr;
        SardineIcon*      mModeLayout = nullptr;
        SardineInfo*      mInfo       = nullptr;
        al::CameraTicket* mTicket     = nullptr;

        float pullDistanceMax   = 2250.f;
        float pullDistanceMin   = 1000.f;
        float pullDistanceMaxSq = 5062500.f;
        float pullDistanceMinSq = 1000000.f;
        float pullPowerRate     = 75.f;

        int mSardineToggleCooldown = 0;
        const int mSardineToggleCooldownLength = 600;

        void updateTagState(bool isIt);
};
