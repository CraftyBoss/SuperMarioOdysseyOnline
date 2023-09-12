#pragma once

#include "SocketBase.hpp"
#include "nn/result.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadQuat.h"
#include "sead/container/seadPtrArray.h"

#include "al/util.hpp"

#include "nn/account.h"

#include "syssocket/sockdefines.h"

#include "types.h"

#include "packets/Packet.h"

class SocketClient : public SocketBase {
    public:
        SocketClient(const char *name) : SocketBase(name) {
            mPacketQueue = sead::PtrArray<Packet>();
            mPacketQueue.tryAllocBuffer(maxBufSize, nullptr);
        };
        nn::Result init(const char* ip, u16 port) override;
        bool closeSocket() override;
        bool SEND(Packet *packet);
        bool RECV();
        void printPacket(Packet* packet);
        bool isConnected() {return socket_log_state == SOCKET_LOG_CONNECTED; }

        sead::PtrArray<Packet> mPacketQueue;

    private:
        int maxBufSize = 100;

        /**
         * @param str a string containing an IPv4 address or a hostname that can be resolved via DNS
         * @param out IPv4 address
         * @return if this function was successfull and out contains a valid IP address
         */
        bool stringToIPAddress(const char* str, in_addr* out);
};
