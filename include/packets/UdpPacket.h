#pragma once

#include "Packet.h"

struct PACKED UdpInit : Packet {
    UdpInit() : Packet() {this->mType = PacketType::UDPINIT; mPacketSize = sizeof(UdpInit) - sizeof(Packet);};
    u16 port = 0;
};
