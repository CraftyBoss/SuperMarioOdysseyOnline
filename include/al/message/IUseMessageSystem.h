#pragma once

#include "MessageSystem.h"

namespace al {
    class IUseMessageSystem {
        public:
            virtual al::MessageSystem *getMessageSystem() const = 0;
    };
}