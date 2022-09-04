#pragma once

#include "SceneInitInfo.h"
#include <al/nerve/NerveExecutor.h>
#include "al/audio/AudioKeeper.h"
#include "al/camera/CameraDirector.h"
#include "al/scene/SceneObjHolder.h"
#include "prim/seadSafeString.h"

namespace al
{

    class GraphicsInitArg;
    class StageResourceKeeper;
    class LiveActorKit;
    class LayoutKit;
    class SceneStopCtrl;   
    class SceneMsgCtrl;    
    class ScreenCoverCtrl; 
    class AudioDirector;   

    class Scene : public al::NerveExecutor, public al::IUseAudioKeeper, public al::IUseCamera, public al::IUseSceneObjHolder
    {
    public:
        Scene(const char *);

        virtual ~Scene();
        virtual void init(const al::SceneInitInfo &);
        virtual void appear();
        virtual void kill();
        virtual void movement();
        virtual void control();
        virtual void drawMain();
        virtual void drawSub();
        virtual al::AudioKeeper* getAudioKeeper();
        virtual al::SceneObjHolder* getSceneObjHolder();
        virtual al::CameraDirector* getCameraDirector();

        void initDrawSystemInfo(al::SceneInitInfo const&);

        void initLiveActorKitWithGraphics(al::GraphicsInitArg const &, al::SceneInitInfo const &, int, int, int);

        bool mIsAlive;
        sead::FixedSafeString<0x40> mName;
        al::StageResourceKeeper *mStageResourceKeeper;
        al::LiveActorKit *mActorKit;
        al::LayoutKit *mLayoutKit;
        al::SceneObjHolder *mSceneObjHolder;
        al::SceneStopCtrl *mSceneStopCtrl;
        al::SceneMsgCtrl *mSceneMsgCtrl;
        al::ScreenCoverCtrl *mScreenCoverCtrl;
        al::AudioDirector *mAudioDirector;
        al::AudioKeeper *mAudioKeeper;
        al::NerveKeeper *mNerveKeeper;
    };
};