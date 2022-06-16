#pragma once

#include "al/actor/ActorCameraTarget.h"

namespace al {
    class CameraTargetHolder {
        public:
            al::ActorCameraTarget *tryGetViewTarget(int) const;
    };
}