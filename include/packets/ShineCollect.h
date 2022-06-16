#pragma once

#include "Packet.h"

struct ShineCollect : Packet {
    ShineCollect() : Packet() {this->mType = PacketType::SHINECOLL; mPacketSize = sizeof(ShineCollect) - sizeof(Packet);};
    int shineId = -1;
    bool isGrand = false;
};