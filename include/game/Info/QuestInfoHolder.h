#pragma once

#include <new>
#include "QuestInfo.h"
#include "al/actor/Placement.h"
#include "al/hio/HioNode.h"
#include "al/scene/ISceneObj.h"
#include "al/scene/SceneObjHolder.h"
#include "al/string/StringTmp.h"
#include "container/seadPtrArray.h"

class QuestInfoHolder : public al::ISceneObj, public al::HioNode {
public:
    QuestInfoHolder(int count);
    // QuestInfoHolder(int count) {
    //     QuestInfo* infoHolder = new QuestInfo[count]();
    //     for (int i = 0; i < count; i++) {
    //         infoHolder[i] = QuestInfo();
    //     }

    //     mQuestArr = &infoHolder;
    // };

    virtual const char *getSceneObjName(void) override;
    virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
    
    void validateQuest(QuestInfo const*);
    void updateActiveList(int);
    void tryFindQuest(al::PlacementInfo const&, al::SceneObjHolder *);
    void tryFindQuest(QuestInfo const*);
    void registerQuestInfo(QuestInfo const*);
    void isActiveQuest(QuestInfo const*);
    void invalidateQuest(QuestInfo const*);
    void initSceneObjHolder(al::SceneObjHolder *);
    void initAfterPlacementQuestObj(int);
    void getQuestNum(int) const;
    void getActiveQuestStageName(al::IUseSceneObjHolder const*) const;
    al::StringTmp<0x80> getActiveQuestLabel(void) const;
    void finalizeForScene(void);
    void clearMainQuest(void);
    void clearAll(void);

    int mMaxQuests;                   // 0x8
    QuestInfo **mQuestArr;            // 0x10
    int unkInt1 = 0;                  // 0x18
    int unkInt2 = -1;                 // 0x1C
    int unkInt3 = -1;                 // 0x20
    int mActiveQuestNo = -1;          // 0x24
    QuestInfo** mActiveQuestList = nullptr; // 0x28
    int mActiveQuestCount = 0;          // 0x30
    bool unkBool = 0;                 // 0x34
    void *unkPtr2 = nullptr;          // 0x38
};

static_assert(sizeof(QuestInfoHolder) == 0x40, "QuestInfoHolder Size");