#pragma once

#include "SocketBase.hpp"
#include "al/async/AsyncFunctorThread.h"
#include "heap/seadHeap.h"
#include "nn/result.h"
#include "sead/math/seadVector.h"
#include "sead/math/seadQuat.h"
#include "sead/container/seadPtrArray.h"

#include "al/util.hpp"

#include "nn/account.h"

#include "syssocket/sockdefines.h"

#include "thread/seadMessageQueue.h"
#include "thread/seadMutex.h"
#include "types.h"

#include "packets/Packet.h"

class Client;

class SocketClient : public SocketBase {
    public:
        SocketClient(const char* name, sead::Heap* heap, Client* client);
        nn::Result init(const char* ip, u16 port) override;
        bool tryReconnect();
        bool closeSocket() override;

        bool startThreads();
        void endThreads();
        void waitForThreads();

        bool send(Packet* packet);
        bool recv();

        bool queuePacket(Packet *packet);
        bool trySendQueue();

        void sendFunc();
        void recvFunc();

        Packet *tryGetPacket(sead::MessageQueue::BlockType blockType = sead::MessageQueue::BlockType::Blocking);

        void printPacket(Packet* packet);
        bool isConnected() { return socket_log_state == SOCKET_LOG_CONNECTED; }

        u16 getLocalUdpPort();
        s32 setPeerUdpPort(u16 port);
        const char* getUdpStateChar();

        u32 getSendCount() { return mSendQueue.getCount(); }
        u32 getSendMaxCount() { return mSendQueue.getMaxCount(); }

        u32 getRecvCount() { return mRecvQueue.getCount(); }
        u32 getRecvMaxCount() { return mRecvQueue.getMaxCount(); }

        void clearMessageQueues();
        void setQueueOpen(bool value) { mPacketQueueOpen = value; }


        void setIsFirstConn(bool value) { mIsFirstConnect = value; }

    private:
        sead::Heap* mHeap = nullptr;
        Client* client = nullptr;
        
        al::AsyncFunctorThread* mRecvThread = nullptr;
        al::AsyncFunctorThread* mSendThread = nullptr;
        
        sead::MessageQueue mRecvQueue;
        sead::MessageQueue mSendQueue;
        char* recvBuf = nullptr;

        int maxBufSize = 100;
        bool mIsFirstConnect = true;
        bool mPacketQueueOpen = true;
        int pollTime = 0;


        bool mHasRecvUdp;
        s32 mUdpSocket;
        sockaddr mUdpAddress;

        bool recvTcp();
        bool recvUdp();

        /**
         * @param str a string containing an IPv4 address or a hostname that can be resolved via DNS
         * @param out IPv4 address
         * @return if this function was successfull and out contains a valid IP address
         */
        bool stringToIPAddress(const char* str, in_addr* out);
};

typedef void (SocketClient::*SocketThreadFunc)(void);
