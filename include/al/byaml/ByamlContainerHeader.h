#pragma once

#include <basis/seadTypes.h>

namespace al {
class ByamlContainerHeader {
public:
    int getType() const;
    int getCount(bool) const;

    u32 mType;  // _0
};
};  // namespace al