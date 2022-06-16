#pragma once

#include "Packet.h"

struct PlayerConnect : Packet {
    PlayerConnect() : Packet() {this->mType = PacketType::PLAYERCON; mPacketSize = sizeof(PlayerConnect) - sizeof(Packet);};
    ConnectionTypes conType;
    u16 maxPlayerCount;
    char clientName[COSTUMEBUFSIZE] = {};
};