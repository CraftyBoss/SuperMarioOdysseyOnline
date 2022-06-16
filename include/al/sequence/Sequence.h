#pragma once

#include "al/nerve/NerveExecutor.h"
#include "al/audio/AudioKeeper.h"
#include "al/scene/SceneCreator.h"

namespace al {
    class Sequence : public al::NerveExecutor, public al::IUseAudioKeeper, public al::IUseSceneCreator {
        public:
            Sequence(const char *seqName);
    };
}