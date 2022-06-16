#pragma once

#include "al/audio/AudioKeeper.h"
#include "sead/prim/seadSafeString.h"

namespace al {

bool checkIsPlayingSe(al::IUseAudioKeeper const*, const sead::SafeString&, const char*);

bool isPlayingBgm(al::IUseAudioKeeper const*);

bool isPlayingBgm(al::IUseAudioKeeper const*,char const*);

void stopAllBgm(al::IUseAudioKeeper const*, int);

bool tryStopAllBgm(al::IUseAudioKeeper const *, int);

}