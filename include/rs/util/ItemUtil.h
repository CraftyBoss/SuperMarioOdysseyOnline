#pragma once

#include "al/util/StringUtil.h"
#include "al/actor/ActorInitInfo.h"

namespace rs {
    enum ItemType {
        COIN,
        COIN2D,
        COINBLOW,
        COINBLOWVERYLITTLE,
        COINPOPUP,
        COINPOPUPWITHOUTHITREACTION,
        COIN3,
        COIN5,
        COIN10,
        COIN10AUTO,
        COIN100,
        COIN5COUNT,
        LIFEUPITEM,
        LIFEUPITEMBACK,
        LIFEUPITEM2D,
        LIFEMAXUPITEM,
        LIFEMAXUPITEM2D,
        SHINE,
        AIRBUBBLE,
        DOTMARIOCAT,
        KURIBOMINI3,
        KURIBOMINI8,
        COINSTACKBOUND,
        RANDOM
    };

    ItemType getItemType(const char *);

    ItemType getItemType(al::ActorInitInfo const &);
}