#pragma once

#include "Packet.h"

struct PlayerDC : Packet {
    PlayerDC() : Packet() {this->mType = PacketType::PLAYERDC; mPacketSize = sizeof(PlayerDC) - sizeof(Packet);};
};