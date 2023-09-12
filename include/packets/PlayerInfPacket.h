#pragma once

#include "Packet.h"
#include "al/util.hpp"
#include "algorithms/PlayerAnims.h"

struct PACKED PlayerInf : Packet {
    PlayerInf() : Packet() {mType = PacketType::PLAYERINF; mPacketSize = sizeof(PlayerInf) - sizeof(Packet);};
    sead::Vector3f playerPos;
    sead::Quatf playerRot;
    float animBlendWeights[6];
    PlayerAnims::Type actName;
    PlayerAnims::Type subActName;

    bool operator==(const PlayerInf &rhs) const {
        bool isWeightsEqual = true;
        for (size_t i = 0; i < 6; i++)
        {
            if(animBlendWeights[i] != rhs.animBlendWeights[i]) {
                isWeightsEqual = false;
                break;
            }
        }
        return (
            playerPos == rhs.playerPos &&
            playerRot == rhs.playerRot &&
            isWeightsEqual &&
            actName == rhs.actName &&
            subActName == rhs.subActName
        );
    }

    bool operator!=(const PlayerInf& rhs) const { return !operator==(rhs); }
};