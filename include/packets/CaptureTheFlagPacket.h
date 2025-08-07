#pragma once

#include "Packet.h"
#include "sead/math/seadVector.h"

enum CTFUpdateType : u8 {
    FLAG_CAPTURED    = 1 << 0,
    FLAG_DROPPED     = 1 << 1,
    FLAG_RETURNED    = 1 << 2,
    SCORE_UPDATE     = 1 << 3,
    TEAM_ASSIGN      = 1 << 4
};

enum CTFTeam : u8 {
    RED_TEAM = 0,
    BLUE_TEAM = 1,
    SPECTATOR = 2
};

struct CaptureTheFlagPacket : Packet {
    CaptureTheFlagPacket() : Packet() {
        mType = PacketType::CAPTURETHEFLAGPACKET;
        mPacketSize = sizeof(CaptureTheFlagPacket) - sizeof(Packet);
    }
    
    CTFUpdateType updateType;
    CTFTeam playerTeam;
    u8 redScore;
    u8 blueScore;
    sead::Vector3f flagPos;  // Position of dropped flag
    bool hasFlag;  // Does this player have the flag?
    u8 flagTeam;   // Which flag (RED or BLUE)
};