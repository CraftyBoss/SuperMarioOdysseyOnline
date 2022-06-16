#pragma once

#include "Packet.h"

struct HackCapInf : Packet {
    HackCapInf() : Packet() {this->mType = PacketType::HACKCAPINF; mPacketSize = sizeof(HackCapInf) - sizeof(Packet);};
    sead::Vector3f capPos;
    sead::Quatf capQuat;
    bool isCapVisible = false;
    char capAnim[PACKBUFSIZE] = {};
};