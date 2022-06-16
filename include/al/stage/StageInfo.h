#pragma once

#include "al/byaml/ByamlIter.h"

namespace al {

    class Resource;

    struct StageInfo {
        StageInfo(al::Resource *, al::ByamlIter const &, al::ByamlIter const &);
    };
}