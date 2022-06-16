#pragma once

#include "al/actor/ActorDimensionKeeper.h"
#include "game/Info/QuestInfo.h"
#include "types.h"

#include "game/Info/ShineInfo.h"
#include "game/Interfaces/IUseDimension.h"
#include "al/LiveActor/LiveActor.h"

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

        unsigned char padding[0x10];
        // 0x11C mIsEmptyShine
        ShineInfo *curShineInfo; // 0x120
        unsigned char padding_290[0x278 - 0x128];
        QuestInfo *shineQuestInfo; // 0x278
        void *unkPtr1; // 0x280
        ActorDimensionKeeper *mDimensionKeeper; // 0x288
        int shineId; // 0x290
};