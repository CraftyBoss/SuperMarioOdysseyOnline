#pragma once

#include "Packet.h"
#include "al/util.hpp"

struct PACKED GameInf : Packet {
    GameInf() : Packet() {this->mType = PacketType::GAMEINF; mPacketSize = sizeof(GameInf) - sizeof(Packet);};
    bool1 is2D = false;
    u8 scenarioNo = -1;
    char stageName[0x40] = {};

    bool operator==(const GameInf &rhs) const {
        return (
            is2D == rhs.is2D &&
            scenarioNo == rhs.scenarioNo &&
            al::isEqualString(stageName, rhs.stageName)
        );
    }

    bool operator!=(const GameInf& rhs) const { return !operator==(rhs); }

};