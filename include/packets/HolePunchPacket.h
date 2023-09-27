#pragma once

#include "Packet.h"

struct PACKED HolePunch : Packet {
    HolePunch() : Packet() {this->mType = PacketType::HOLEPUNCH; mPacketSize = sizeof(HolePunch) - sizeof(Packet);};
};
