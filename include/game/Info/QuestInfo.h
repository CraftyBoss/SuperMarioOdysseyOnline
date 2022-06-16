#pragma once

#include "al/actor/ActorInitInfo.h"
#include "al/actor/Placement.h"
#include "al/scene/SceneObjHolder.h"
#include "math/seadVector.h"
#include "prim/seadSafeString.h"

class QuestInfo : public al::IUseSceneObjHolder {
public:
    
    QuestInfo(void);

    virtual al::SceneObjHolder* getSceneObjHolder(void) const override { return mSceneObjHolder; };

    void setStageName(char const*);
    void setLabel(char const*);
    void isEqual(QuestInfo const*);

    void init(al::PlacementInfo const&,al::SceneObjHolder *);
    void init(al::PlacementInfo const&,al::ActorInitInfo const&);
    void init(al::ActorInitInfo const&);

    void end(void);
    void copy(QuestInfo const*);
    void clear(void);

    int mQuestID = -1; //0x8
    sead::Vector3f mShineTrans = sead::Vector3f::zero; // 0xC
    bool mIsMainQuest; // 0x18
    al::SceneObjHolder *mSceneObjHolder;  // 0x20 
    sead::FixedSafeString<0x80> mLabel; // 0x28
    sead::FixedSafeString<0x80> mStageName;  // 0xC0
    bool mIsSingle; // 0x158
    sead::FixedSafeString<0x80> mObjID;  // 0x160
    sead::FixedSafeString<0x80> mPlacementStageName;  // 0x1F8
};

static_assert(sizeof(QuestInfo) == 0x290, "Quest Info Size");