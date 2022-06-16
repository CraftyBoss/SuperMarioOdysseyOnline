/**
 * @file IUseLayout.h
 * @brief Interface for classes that are layouts.
 */

#pragma once

#include "al/actor/IUseName.h"

namespace al {

struct LayoutKeeper;

class IUseLayout : virtual public al::IUseName {
    public:
        virtual al::LayoutKeeper* getLayoutKeeper(void) const = 0;
};
}  // namespace al