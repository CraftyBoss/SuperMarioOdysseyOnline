#pragma once

#include "Packet.h"

struct PACKED CostumeInf : Packet {
    CostumeInf() : Packet() {this->mType = PacketType::COSTUMEINF;  mPacketSize = sizeof(CostumeInf) - sizeof(Packet);};
    CostumeInf(const char* body, const char* cap) : Packet() {
        this->mType = PacketType::COSTUMEINF;
        mPacketSize = sizeof(CostumeInf) - sizeof(Packet);
        strcpy(bodyModel, body);
        strcpy(capModel, cap);
    }
    char bodyModel[COSTUMEBUFSIZE] = {};
    char capModel[COSTUMEBUFSIZE] = {};
};