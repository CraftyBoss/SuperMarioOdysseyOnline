#pragma once

#include "al/hio/HioNode.h"
#include "al/message/IUseMessageSystem.h"
#include "al/scene/ISceneObj.h"

namespace al {
    class GameDataHolderBase : public ISceneObj, HioNode, IUseMessageSystem {
        public:
        
    };
}