#pragma once

#include "Packet.h"

struct ServerCommand : Packet {
    ServerCommand(const char *command) : Packet() {this->mType = PacketType::CMD; strcpy(srvCmd, command); mPacketSize = sizeof(ServerCommand) - sizeof(Packet);};
    char srvCmd[PACKBUFSIZE] = {};
};