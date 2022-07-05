#pragma once

#include "al/scene/ISceneObj.h"
#include "al/scene/SceneObjHolder.h"
#include "game/SceneObjs/RouteGuideDirector.h"

// temp header to cleanup SceneObjFactory

namespace al {
    struct StageSyncCounter : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
    };
}

struct AmiiboNpcDirector : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct BgmAnimeSyncDirector : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct CapManHeroDemoDirector : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct CapMessageDirector : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct CapMessageMoonNotifier : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct CoinCollectHolder : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct CoinCollectWatcher : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct CollectBgmPlayer : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct EchoEmitterHolder : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct ElectricWireCameraTicketHolder : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct FukankunZoomObjHolder : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct GrowPlantDirector : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct GuidePosInfoHolder : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct HintPhotoLayoutHolder : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct HtmlViewerRequester : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct KidsModeLayoutAccessor : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct LoginLotteryDirector : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct MoviePlayer : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct PaintObjHolder : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct PlayerStartInfoHolder : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct RandomItemSelector : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct SceneEventNotifier : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct TalkNpcParamHolder : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct TalkNpcSceneEventSwitcher : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct TestStageTimeDirector : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct TimeBalloonDirector : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct TsukkunTraceHolder : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct WipeHolderRequester : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct YoshiFruitWatcher : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};
struct HelpAmiiboDirector : public al::ISceneObj {
        virtual const char* getSceneObjName() override;
        virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
        virtual void initSceneObj(void) override;
};

struct QuestInfoHolder : public al::ISceneObj {
    QuestInfoHolder(int);
    virtual const char* getSceneObjName() override;
    virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
    virtual void initSceneObj(void) override;
};
struct RhyhtmInfoWatcher : public al::ISceneObj {
    RhyhtmInfoWatcher(const char*);
    virtual const char* getSceneObjName() override;
    virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) override;
    virtual void initSceneObj(void) override;
};