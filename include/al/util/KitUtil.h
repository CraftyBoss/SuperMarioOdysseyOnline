#pragma once

#include "al/scene/Scene.h"

namespace al {

    class LayoutKit;
    class LiveActorKit;

    void updateKitList(al::Scene *,char const*,char const*);
    void updateKitList(al::Scene*, char const*);
    
    void executeUpdateList(al::LayoutKit *,char const*,char const*);
    void executeUpdateList(al::LiveActorKit*, char const*, char const*);

    void executeDrawList(al::LiveActorKit const*,char const*,char const*);
}