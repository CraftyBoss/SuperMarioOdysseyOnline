#pragma once

#include "al/LiveActor/LiveActor.h"
#include "types.h"

namespace al {
class PartsModel : public al::LiveActor {
    public:
        PartsModel(char const*);
        void endClipped() override;
        void calcAnim() override;
        void attackSensor(al::HitSensor*, al::HitSensor*) override;
        bool receiveMsg(al::SensorMsg const*, al::HitSensor*, al::HitSensor*) override;

        void initPartsDirect(al::LiveActor*, al::ActorInitInfo const&, char const*, sead::Matrix34f const*, sead::Vector3f const&, sead::Vector3f const&, sead::Vector3f const&, bool);
        void initPartsSuffix(al::LiveActor*, al::ActorInitInfo const&, char const*, char const*, sead::Matrix34f const*, bool);
        void initPartsMtx(al::LiveActor*, al::ActorInitInfo const&, char const*, sead::Matrix34f const*, bool);
        void initPartsFixFile(al::LiveActor*, al::ActorInitInfo const&, char const*, char const*, char const*);
        void initPartsFixFileNoRegister(al::LiveActor*, al::ActorInitInfo const&, char const*,
                                        char const*, char const*);
        
        void updatePose();
        void offSyncAppearAndHide();
        void onSyncAppearAndHide();

        void *unkPtr1; // 0x108
        void* unkPtr2; // 0x110
        int unkInt1;   // 0x118
        int unkInt2; // 0x11C
        int unkInt3; // 0x120
        int unkInt4; // 0x124
        int unkInt5;  // 0x128
        int unkInt6;  // 0x12C
        int unkInt7;  // 0x130
        float unkFloat1; // 0x134
        float unkFloat2; // 0x138
        float unkFloat3;  // 0x13C
        bool unkBool; // 0x140
        bool unkBool2; // 0x141
        bool unkBool3; // 0x142
   };
}