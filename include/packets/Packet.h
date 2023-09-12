#pragma once

#include "sead/math/seadVector.h"
#include "sead/math/seadQuat.h"

#include "nn/account.h"

#include "types.h"

#define PACKBUFSIZE      0x30
#define COSTUMEBUFSIZE   0x20

#define MAXPACKSIZE      0x100

enum PacketType : short {
    UNKNOWN,
    CLIENTINIT,
    PLAYERINF,
    HACKCAPINF,
    GAMEINF,
    TAGINF,
    PLAYERCON,
    PLAYERDC,
    COSTUMEINF,
    SHINECOLL,
    CAPTUREINF,
    CHANGESTAGE,
    CMD,
    End // end of enum for bounds checking
};

// attribute otherwise the build log is spammed with unused warnings
USED static const char *packetNames[] = {
    "Unknown",
    "Client Initialization",
    "Player Info",
    "Player Cap Info",
    "Game Info",
    "Tag Info",
    "Player Connect",
    "Player Disconnect",
    "Costume Info",
    "Moon Collection",
    "Capture Info",
    "Change Stage",
    "Server Command"
};

enum SenderType {
    SERVER,
    CLIENT
};

enum ConnectionTypes {
    INIT,
    RECONNECT
};

// unused
/*
static const char *senderNames[] = {
    "Server",
    "Client"
};
*/

struct PACKED Packet {
    nn::account::Uid mUserID; // User ID of the packet owner
    PacketType mType = PacketType::UNKNOWN;
    short mPacketSize = 0; // represents packet size without size of header
};

// all packet types

#include "packets/PlayerInfPacket.h"
#include "packets/PlayerConnect.h"
#include "packets/PlayerDC.h"
#include "packets/GameInf.h"
#include "packets/TagInf.h"
#include "packets/CostumeInf.h"
#include "packets/ServerCommand.h"
#include "packets/ShineCollect.h"
#include "packets/CaptureInf.h"
#include "packets/HackCapInf.h"
#include "packets/ChangeStagePacket.h"
#include "packets/InitPacket.h"