#pragma once

#include "al/effect/EffectKeeper.h"

namespace al {
    class ActionEffectCtrl {
        public:
            void startAction(char const *);
            IUseEffectKeeper *mEffectKeeper;
    };
}