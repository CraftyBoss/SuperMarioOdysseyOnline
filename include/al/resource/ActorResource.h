#pragma once

#include "prim/seadSafeString.h"
#include "types.h"
#include "Resource.h"

namespace al {

    class AnimInfoTable { char size[0x18]; };

    struct InitResourceDataAnim {
        al::AnimInfoTable *mInfoTable; // 0x0
        al::AnimInfoTable *mFclAnim; // 0x8
        al::AnimInfoTable *mFtsAnim; // 0x10
        al::AnimInfoTable *mFtpAnim; // 0x18
        al::AnimInfoTable *mInfoTable2; // 0x18
    };

    class ActorResource {
        public:
        ActorResource(sead::SafeString const&, al::Resource*, al::Resource*);
        virtual ~ActorResource();

        void initResourceData(char const*, bool);

        sead::FixedSafeString<0x80> unkStr;  // 0x8
        al::Resource *mResourceModel; // 0xA0
        al::Resource *mResourceAnim;  // 0xA8
        bool unkBool1;        // 0xB0
        al::InitResourceDataAnim *mAnimResData; // 0xB8
        void *unkPtr2; // 0xC0
    };
}

static_assert(sizeof(al::ActorResource) == 0xC8, "ActorResource Size");