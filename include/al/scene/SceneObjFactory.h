#pragma once

#include "al/scene/ISceneObj.h"
#include "al/scene/SceneObjHolder.h"
#include "SceneObjs.h"

al::ISceneObj *sub_4C4300(int objIndex) {
    switch (objIndex)
    {
        case 0:
            return new AmiiboNpcDirector();
        case 1:
            return new BgmAnimeSyncDirector();
        case 3:
            return new CapManHeroDemoDirector();
        case 4:
            return new CapMessageDirector();
        case 5:
            return new CapMessageMoonNotifier();
        case 7:
            return new CoinCollectHolder();
        case 8:
            return new CoinCollectWatcher();
        case 9:
            return new CollectBgmPlayer();
        case 11:
            return new EchoEmitterHolder();
        case 12:
            return new ElectricWireCameraTicketHolder();
        case 17:
            return new FukankunZoomObjHolder();
        case 21:
            return new GrowPlantDirector();
        case 22:
            return new GuidePosInfoHolder();
        case 23:
            return new HintPhotoLayoutHolder();
        case 26:
            return new HtmlViewerRequester();
        case 29:
            return new KidsModeLayoutAccessor();
        case 34:
            return new LoginLotteryDirector();
        case 36:
            return new MoviePlayer();
        case 39:
            return new PaintObjHolder();
        case 42:
            return new PlayerStartInfoHolder();
        case 44:
            return new QuestInfoHolder(64);
        case 49:
            return new RandomItemSelector();
        case 52:
            return nullptr;
        case 53:
            return new RhyhtmInfoWatcher("");
        case 55:
            return new RouteGuideDirector();
        case 56:
            return new SceneEventNotifier();
        case 60:
            return new al::StageSyncCounter();
        case 62:
            return new TalkNpcParamHolder();
        case 63:
            return new TalkNpcSceneEventSwitcher();
        case 64:
            return new TestStageTimeDirector();
        case 65:
            return new TimeBalloonDirector();
        case 70:
            return new TsukkunTraceHolder();
        case 71:
            return new WipeHolderRequester();
        case 72:
            return new YoshiFruitWatcher();
        case 73:
            return new HelpAmiiboDirector();
        default:
            return nullptr;
    }
}

class SceneObjFactory {
public:
    al::SceneObjHolder *createSceneObjHolder(void) { return new al::SceneObjHolder(&sub_4C4300, 0x4A);}
};

