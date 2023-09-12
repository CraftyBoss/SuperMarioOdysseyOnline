#pragma once

#include "al/actor/ActorDimensionKeeper.h"
#include "game/Info/QuestInfo.h"
#include "types.h"

#include "game/Info/ShineInfo.h"
#include "game/Interfaces/IUseDimension.h"
#include "al/LiveActor/LiveActor.h"

enum ShineType { Normal, Dot, Grand };

namespace al {
    struct RateParamV3f;
}

class Shine : public al::LiveActor , public IUseDimension {
    public:
        Shine(const char* actorName);

        ActorDimensionKeeper *getActorDimensionKeeper() const override;

        void offAppear();
        void onAppear();
        void getDirectWithDemo(void);
        void getDirect();
        void get();
        void onSwitchGet(void);
        bool isGot() const;
        void setGrandShine(void);

        void *qword110;
        int dword118;
        bool mIsGotShine;
        ShineInfo *curShineInfo; // 0x120
        unsigned char padding_188[0x188 - 0x128];
        al::RateParamV3f *mRateParam;
        void * qword190;
        void * qword198;
        ShineType mModelType;
        void * qword1A8;
        bool byte1B0;
        void * qword1B8;
        int dword1C0;
        int dword1C4;
        sead::FixedSafeString<0x80> mShineLabel;
        void * qword260;
        int dword268;
        bool byte26C;
        void * qword270;
        QuestInfo *shineQuestInfo; // 0x278
        void *unkPtr1; // 0x280
        ActorDimensionKeeper *mDimensionKeeper; // 0x288
        int shineId;                            // 0x290
        bool mIsMainShine;
        void *qword298;
        void *qword2A0;
        void *qword2A8;
        void *qword2B0;
        void *qword2B8;
        int dword2C0;
        __attribute__((packed)) void * qword2C4;
        int dword2CC;
        int dword2D0;
        bool mIsAddHeight;
        int dword2D8;
        al::LiveActor *mModelEmpty;
        al::LiveActor *mModelShine;
        int dword2F0;
        u16 word2F4;
        int dword2F8;
        bool mIsNoRotate;
        void * qword300;
        bool mIsUseDemoCam;
        struct WaterSurfaceShadow *mWaterShadow;
        void * qword318;
        int dword320;
        int dword324;
        bool byte328;
        void * qword330;
        bool mIsCheckGroundHeightMoon;
        bool mIsHintPhoto;
        void * qword340;
        bool byte348;
        void * qword350;
        bool mIsUseAppearDemoForce;
        int dword35C;
        int dword360;
        int dword364;
        int dword368;
        bool mIsPowerStar;
        bool mIsAppearDemoHeightHigh;
        void * qword370;
        u16 word378;
        int dword37C;
};

namespace rs {
    void setStageShineAnimFrame(al::LiveActor *,char const*,int,bool);
}