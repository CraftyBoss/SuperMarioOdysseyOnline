#pragma once

#include "Packet.h"

struct PACKED HackCapInf : Packet {
    HackCapInf() : Packet() {this->mType = PacketType::HACKCAPINF; mPacketSize = sizeof(HackCapInf) - sizeof(Packet);};
    sead::Vector3f capPos;
    sead::Quatf capQuat;
    bool1 isCapVisible = false;
    char capAnim[PACKBUFSIZE] = {};
};