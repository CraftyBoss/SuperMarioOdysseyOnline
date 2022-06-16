#pragma once

#include "sead/math/seadVector.h"
#include "al/scene/Scene.h"
#include "al/LiveActor/LiveActor.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "types.h"

namespace al {

    class PadRumbleKeeper;

    class PlayerHolder {
        public:
            PlayerHolder(int bufSize);
            void clear(void);
            void registerPlayer(al::LiveActor *, al::PadRumbleKeeper *);
            PlayerActorHakoniwa *getPlayer(int) const;
            PlayerActorHakoniwa *tryGetPlayer(int) const;
            int getPlayerNum() const;
            int getBufferSize() const {return bufferSize;};
            bool isFull(void) const;
            bool isExistPadRumbleKeeper(int) const;
            al::PadRumbleKeeper *getPadRumbleKeeper(int) const;

            undefined unkPointer[0x8];
            int bufferSize;
    };

}