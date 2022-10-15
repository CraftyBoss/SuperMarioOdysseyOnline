#pragma once

#include "al/resource/Resource.h"
#include "game/Player/PlayerCostumeInfo.h"

namespace PlayerCostumeFunction {
    PlayerBodyCostumeInfo *createBodyCostumeInfo(al::Resource *,char const*);
    PlayerHeadCostumeInfo *createHeadCostumeInfo(al::Resource *,char const*,bool);
}