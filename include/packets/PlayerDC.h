#pragma once

#include "Packet.h"

struct PACKED PlayerDC : Packet {
    PlayerDC() : Packet() {this->mType = PacketType::PLAYERDC; mPacketSize = sizeof(PlayerDC) - sizeof(Packet);};
};