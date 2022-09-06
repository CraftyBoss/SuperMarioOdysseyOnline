#pragma once

#include "al/audio/AudioDirector.h"
#include "al/nerve/NerveExecutor.h"
#include "al/audio/AudioKeeper.h"
#include "al/scene/SceneCreator.h"
#include "game/System/GameDrawInfo.h"

namespace al {

    class GameSystemInfo;
    class SequenceInitInfo;
    class AudioSystemInfo;
    class Scene;

    class Sequence : public al::NerveExecutor, public al::IUseAudioKeeper, public al::IUseSceneCreator {
        public:
            Sequence(const char* name);
            virtual ~Sequence() override;
            virtual void init(const al::SequenceInitInfo& initInfo);
            virtual void update();
            virtual void kill();
            virtual void drawMain() const;
            virtual void drawSub() const;
            virtual bool isDisposable() { return false; }
            al::Scene* getCurrentScene() const;
            al::SceneCreator* getSceneCreator() const override;
            void setSceneCreator(al::SceneCreator* sceneCreator) override;

            al::AudioKeeper* getAudioKeeper() const override;
            void initAudio(const al::GameSystemInfo&, const char*, int, int, int, const char*);
            void initAudioKeeper(const char*);
            void initDrawSystemInfo(const al::SequenceInitInfo&);
            al::AudioSystemInfo* getAudioSystemInfo();

            al::GameDrawInfo* getDrawInfo() const {
                return mGameDrawInfo;
            }

            al::AudioDirector* getAudioDirector() const {
                return mAudioDirector;
            }

            void setNextScene(al::Scene* scene) {
                mNextScene = scene;
            }

            const sead::SafeString& getName() const {
                return mName;
            }

            const sead::FixedSafeString<0x40> mName;
            al::Scene* mNextScene;
            al::Scene* mCurrentScene;
            al::SceneCreator* mSceneCreator;
            al::AudioDirector* mAudioDirector;
            al::AudioKeeper* mAudioKeeper;
            al::GameDrawInfo* mGameDrawInfo;
            bool mIsAlive;
    };
}