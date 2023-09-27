#include "server/SocketClient.hpp"
#include <cstdlib>
#include <cstring>
#include <basis/seadNew.h>

#include "SocketBase.hpp"
#include "al/async/FunctorV0M.hpp"
#include "logger.hpp"
#include "nn/result.h"
#include "nn/socket.h"
#include "packets/Packet.h"
#include "packets/UdpPacket.h"
#include "server/Client.hpp"
#include "thread/seadMessageQueue.h"
#include "types.h"

SocketClient::SocketClient(const char* name, sead::Heap* heap, Client* client) : mHeap(heap), SocketBase(name) {

    this->client = client;
#if EMU
    this->pollTime = 0;
#else
    this->pollTime = -1;
#endif

    mRecvThread = new al::AsyncFunctorThread("SocketRecvThread", al::FunctorV0M<SocketClient*, SocketThreadFunc>(this, &SocketClient::recvFunc), 0, 0x1000, {0});
    mSendThread = new al::AsyncFunctorThread("SocketSendThread", al::FunctorV0M<SocketClient*, SocketThreadFunc>(this, &SocketClient::sendFunc), 0, 0x1000, {0});
    
    mRecvQueue.allocate(maxBufSize, mHeap);
    mSendQueue.allocate(maxBufSize, mHeap);
	recvBuf = (char*)mHeap->alloc(MAXPACKSIZE+1);
};

nn::Result SocketClient::init(const char* ip, u16 port) {

    this->sock_ip = ip;
    this->port    = port;
    
    in_addr  hostAddress   = { 0 };
    sockaddr serverAddress = { 0 };
    sockaddr udpAddress    = { 0 };

    Logger::log("SocketClient::init: %s:%d sock %s\n", ip, port, getStateChar());

    nn::nifm::Initialize();
    nn::nifm::SubmitNetworkRequest();

    while (nn::nifm::IsNetworkRequestOnHold()) { }

    // emulators (ryujinx) make this return false always, so skip it during init
    #ifndef EMU
    if (!nn::nifm::IsNetworkAvailable()) {
        Logger::log("Network Unavailable.\n");
        this->socket_log_state = SOCKET_LOG_UNAVAILABLE;
        this->socket_errno = nn::socket::GetLastErrno();
        return -1;
    }
    #endif

    if ((this->socket_log_socket = nn::socket::Socket(2, 1, 6)) < 0) {
        Logger::log("Socket Unavailable.\n");
        this->socket_errno = nn::socket::GetLastErrno();
        this->socket_log_state = SOCKET_LOG_UNAVAILABLE;
        return -1;
    }

    if (! this->stringToIPAddress(this->sock_ip, &hostAddress)) {
        Logger::log("IP address is invalid or hostname not resolveable.\n");
        this->socket_errno = nn::socket::GetLastErrno();
        this->socket_log_state = SOCKET_LOG_UNAVAILABLE;
        return -1;
    }

    serverAddress.address = hostAddress;
    serverAddress.port = nn::socket::InetHtons(this->port);
    serverAddress.family = 2;

    int sockOptValue = true;

    nn::socket::SetSockOpt(this->socket_log_socket, 6, TCP_NODELAY, &sockOptValue, sizeof(sockOptValue));

    nn::Result result;
    
    if((result = nn::socket::Connect(this->socket_log_socket, &serverAddress, sizeof(serverAddress))).isFailure()) {
        Logger::log("Socket Connection Failed!\n");
        this->socket_errno = nn::socket::GetLastErrno();
        this->socket_log_state = SOCKET_LOG_UNAVAILABLE;
        return result;
    }

    if ((this->mUdpSocket = nn::socket::Socket(2, 2, 17)) < 0) {
        Logger::log("Udp Socket failed to create");
        this->socket_errno = nn::socket::GetLastErrno();
        this->socket_log_state = SOCKET_LOG_UNAVAILABLE;
        return -1;
    }

    udpAddress.address = hostAddress;
    udpAddress.port = 0;
    udpAddress.family = 2;
    this->mUdpAddress = udpAddress;
    this->mHasRecvUdp = false;
    this->mPacketQueueOpen = true;

    this->socket_log_state = SOCKET_LOG_CONNECTED;

    Logger::log("Socket fd: %d\n", socket_log_socket);

    startThreads();  // start recv and send threads after succesful connection

    // send init packet to server once we connect (an issue with the server prevents this from working properly, waiting for a fix to implement)
    
    PlayerConnect initPacket;
    initPacket.mUserID = Client::getClientId();
    strcpy(initPacket.clientName, Client::getUsername().cstr());

    if (mIsFirstConnect) {
        initPacket.conType = ConnectionTypes::INIT;
        mIsFirstConnect = false;
    } else {
        initPacket.conType = ConnectionTypes::RECONNECT;
    }

    send(&initPacket);

    // on a reconnect, resend some maybe missing packets
    if (initPacket.conType == ConnectionTypes::RECONNECT) {
      client->resendInitPackets();
    } else {
        // empty TagInf
        TagInf tagInf;
        tagInf.mUserID = initPacket.mUserID;
        tagInf.isIt = false;
        tagInf.minutes = 0;
        tagInf.seconds = 0;
        tagInf.updateType = static_cast<TagUpdateType>(TagUpdateType::STATE | TagUpdateType::TIME);
        send(&tagInf);

        // empty CaptureInf
        CaptureInf capInf;
        capInf.mUserID = initPacket.mUserID;
        strcpy(capInf.hackName, "");
        send(&capInf);
    }

    return result;

}

u16 SocketClient::getLocalUdpPort() {
    sockaddr udpAddress = { 0 };
    u32 size = sizeof(udpAddress);

    nn::Result result;
    if((result = nn::socket::GetSockName(this->mUdpSocket, &udpAddress, &size)).isFailure()) {
        this->socket_errno = nn::socket::GetLastErrno();
        return 0;
    }

    return nn::socket::InetNtohs(udpAddress.port);
}


s32 SocketClient::setPeerUdpPort(u16 port) {
    u16 net_port = nn::socket::InetHtons(port);
    this->mUdpAddress.port = net_port;

    nn::Result result;
    if((result = nn::socket::Connect(this->mUdpSocket, &this->mUdpAddress, sizeof(this->mUdpAddress))).isFailure()) {
        Logger::log("Udp socket connection failed to connect to port %d!\n", port);
        this->socket_errno = nn::socket::GetLastErrno();
        return -1;
    }

    return 0;

}

const char* SocketClient::getUdpStateChar() {
    if (this->mUdpAddress.port == 0) {
        return "Waiting for handshake";
    }

    if (!this->mHasRecvUdp) {
        return "Waiting for holepunch";
    }

    return "Utilizing UDP";
}
bool SocketClient::send(Packet *packet) {

    if (this->socket_log_state != SOCKET_LOG_CONNECTED || packet == nullptr)
        return false;

    char* buffer = reinterpret_cast<char*>(packet);

    int valread = 0;

    int fd = -1;
    if ((packet->mType != PLAYERINF && packet->mType != HACKCAPINF && packet->mType != HOLEPUNCH)
        || (!this->mHasRecvUdp && packet->mType != HOLEPUNCH)
        || this->mUdpAddress.port == 0) {

        if (packet->mType != PLAYERINF && packet->mType != HACKCAPINF) {
            Logger::log("Sending packet: %s\n", packetNames[packet->mType]);
        }

        fd = this->socket_log_socket;
    } else {

        fd = this->mUdpSocket;
    }


    if ((valread = nn::socket::Send(fd, buffer, packet->mPacketSize + sizeof(Packet), 0) > 0)) {
        return true;
    } else {
        Logger::log("Failed to Fully Send Packet! Result: %d Type: %s Packet Size: %d\n", valread, packetNames[packet->mType], packet->mPacketSize);
        this->socket_errno = nn::socket::GetLastErrno();
        return this->tryReconnect();
    }
    return true;
}

bool SocketClient::recv() {

    if (this->socket_log_state != SOCKET_LOG_CONNECTED) {
        Logger::log("Unable To Receive! Socket Not Connected.\n");
        this->socket_errno = nn::socket::GetLastErrno();
        return this->tryReconnect();
    }
    
    const int fd_count = 2;
    struct pollfd pfds[fd_count] = {{0}, {0}};

    // TCP Connection
    pfds[0].fd = this->socket_log_socket;
    pfds[0].events = 1;
    pfds[0].revents = 0;

    // UDP Connection
    pfds[1].fd = this->mUdpSocket;
    pfds[1].events = 1;
    pfds[1].revents = 0;


    int result = nn::socket::Poll(pfds, fd_count, this->pollTime);

    if (result == 0) {
        return true;
    } else if (result < 0) {
        Logger::log("Error occurred when polling for packets\n");
        this->socket_errno = nn::socket::GetLastErrno();
        return this->tryReconnect();
    }

    s32 index = -1;
    for (int i = 0; i < fd_count; i++){
        if (pfds[i].revents & 1) {
            index = i;
            break;
        }
    }

    switch (index) {
    case 0:
        return recvTcp();
    case 1:
        return recvUdp();
    default:
        return true;
    }


}

bool SocketClient::recvTcp() {
    int headerSize = sizeof(Packet);
    int valread = 0;
    s32 fd = this->socket_log_socket;

    // read only the size of a header
    while(valread < headerSize) {
        int result = 0;
        result = nn::socket::Recv(fd, recvBuf + valread,
                                        headerSize - valread, this->sock_flags);

        this->socket_errno = nn::socket::GetLastErrno();

        if(result > 0) {
            valread += result;
        } else {
            if(this->socket_errno==11){
                return true;
            } else {
                Logger::log("Header Read Failed! Value: %d Total Read: %d\n", result, valread);
                return this->tryReconnect();
            }
        }
    }

    if(valread <= 0) { // if we error'd, close the socket
        Logger::log("valread was zero! Disconnecting.\n");
        this->socket_errno = nn::socket::GetLastErrno();
        return this->tryReconnect();
    }

    Packet* header = reinterpret_cast<Packet*>(recvBuf);
    int fullSize = header->mPacketSize + sizeof(Packet);

    if (!(fullSize <= MAXPACKSIZE && fullSize > 0 && valread == sizeof(Packet))) {
        Logger::log("Failed to acquire valid data! Packet Type: %d Full Packet Size %d valread size: %d\n", header->mType, fullSize, valread);
        return true;
    }

    if (header->mType != PLAYERINF && header->mType != HACKCAPINF) {
        Logger::log("Received packet (from %02X%02X):", header->mUserID.data[0],
                    header->mUserID.data[1]);
        Logger::disableName();
        Logger::log(" Size: %d", header->mPacketSize);
        Logger::log(" Type: %d", header->mType);
        if(packetNames[header->mType])
            Logger::log(" Type String: %s\n", packetNames[header->mType]);
        Logger::enableName();
    }

    char* packetBuf = (char*)mHeap->alloc(fullSize);

    if (!packetBuf) {
        return true;
    }


    memcpy(packetBuf, recvBuf, sizeof(Packet));

    while (valread < fullSize) {

        int result = nn::socket::Recv(fd, packetBuf + valread,
                                      fullSize - valread, this->sock_flags);

        this->socket_errno = nn::socket::GetLastErrno();

        if (result > 0) {
            valread += result;
        } else {
            mHeap->free(packetBuf);
            Logger::log("Packet Read Failed! Value: %d\nPacket Size: %d\nPacket Type: %s\n", result, header->mPacketSize, packetNames[header->mType]);
            return this->tryReconnect();
        }
    }

    if (!(header->mType > PacketType::UNKNOWN && header->mType < PacketType::End)) {
        Logger::log("Failed to acquire valid packet type! Packet Type: %d Full Packet Size %d valread size: %d\n", header->mType, fullSize, valread);
        mHeap->free(packetBuf);
        return true;
    }

    Packet *packet = reinterpret_cast<Packet*>(packetBuf);

    if (!mRecvQueue.isFull() && mPacketQueueOpen) {
        mRecvQueue.push((s64)packet, sead::MessageQueue::BlockType::NonBlocking);
    } else {
        mHeap->free(packetBuf);
    }

    return true;
}

bool SocketClient::recvUdp() {
    int headerSize = sizeof(Packet);
    s32 fd = this->mUdpSocket;

    int valread = nn::socket::Recv(fd, recvBuf, MAXPACKSIZE, this->sock_flags);

    if (valread == 0) {
        Logger::log("Udp connection valread was zero. Disconnecting.\n");
        return this->tryReconnect();
    }

    if (valread < headerSize){
        return true;
    }

    Packet* header = reinterpret_cast<Packet*>(recvBuf);
    int fullSize = header->mPacketSize + sizeof(Packet);
    // Verify packet size is appropriate
    if (valread < fullSize || valread > MAXPACKSIZE || fullSize > MAXPACKSIZE){
        return true;
    }

    // Verify type of packet
    if (!(header->mType > PacketType::UNKNOWN && header->mType < PacketType::End)) {
        Logger::log("Failed to acquire valid packet type! Packet Type: %d Full Packet Size %d valread size: %d\n", header->mType, fullSize, valread);
        return true;
    }

    this->mHasRecvUdp = true;

    char* packetBuf = (char*)mHeap->alloc(fullSize);
    if (!packetBuf) {
        return true;
    }

    memcpy(packetBuf, recvBuf, fullSize);


    Packet *packet = reinterpret_cast<Packet*>(packetBuf);

    if(!mRecvQueue.isFull()) {
        mRecvQueue.push((s64)packet, sead::MessageQueue::BlockType::NonBlocking);
    } else {
        mHeap->free(packetBuf);
    }

    return true;
}

// prints packet to debug logger
void SocketClient::printPacket(Packet *packet) {
    packet->mUserID.print();
    Logger::log("Type: %s\n", packetNames[packet->mType]);

    switch (packet->mType)
    {
    case PacketType::PLAYERINF:
        Logger::log("Pos X: %f Pos Y: %f Pos Z: %f\n", ((PlayerInf*)packet)->playerPos.x, ((PlayerInf*)packet)->playerPos.y, ((PlayerInf*)packet)->playerPos.z);
        Logger::log("Rot X: %f Rot Y: %f Rot Z: %f\nRot W: %f\n", ((PlayerInf*)packet)->playerRot.x, ((PlayerInf*)packet)->playerRot.y, ((PlayerInf*)packet)->playerRot.z, ((PlayerInf*)packet)->playerRot.w);
        break;
    default:
        break;
    }
}

bool SocketClient::tryReconnect() {

    Logger::log("Attempting to Reconnect.\n");

    if (closeSocket()) { // unfortunately we cannot use the same fd from the previous connection, so close the socket entirely and attempt a new connection.
        if (init(sock_ip, port).isSuccess()) { // call init again
            Logger::log("Reconnect Successful.\n");
            return true;
        }
    }

    return false;
}

bool SocketClient::closeSocket() {

    Logger::log("Closing Socket.\n");

    mHasRecvUdp = false;
    mUdpAddress.port = 0;
    mPacketQueueOpen = false;

    bool result = false;

    if (!(result = SocketBase::closeSocket())) {
        Logger::log("Failed to close socket!\n");
    }

    return result;
}

bool SocketClient::stringToIPAddress(const char* str, in_addr* out) {
    // string to IPv4
    if (nn::socket::InetAton(str, out)) {
        return true;
    }

    // get IPs via DNS
    struct hostent *he = nn::socket::GetHostByName(str);
    if (! he) { return false; }

    // might give us multiple IP addresses, so pick the first one
    struct in_addr **addr_list = (struct in_addr **) he->h_addr_list;
    for (int i = 0 ; addr_list[i] != NULL ; i++) {
        *out = *addr_list[i];
        return true;
    }

    return false;
}

/**
 * @brief starts client read thread
 * 
 * @return true if read thread was successfully started
 * @return false if read thread was unable to start, or thread was already started.
 */
bool SocketClient::startThreads() {

    Logger::log("Recv Thread isDone: %s\n", BTOC(this->mRecvThread->isDone()));
    Logger::log("Send Thread isDone: %s\n", BTOC(this->mSendThread->isDone()));

    if(this->mRecvThread->isDone() && this->mSendThread->isDone()) {
        this->mRecvThread->start();
        this->mSendThread->start();
        Logger::log("Socket threads succesfully started.\n");
        return true;
    }else {
        Logger::log("Socket threads failed to start.\n");
        return false;
    }
}

void SocketClient::endThreads() {
    mRecvThread->mDelegateThread->destroy();
    mSendThread->mDelegateThread->destroy();
}

void SocketClient::waitForThreads() {
    while (!mRecvThread->isDone()){}
    while (!mSendThread->isDone()){}
}

void SocketClient::sendFunc() {

    Logger::log("Starting Send Thread.\n");

    while (trySendQueue() || socket_log_state != SOCKET_LOG_DISCONNECTED) {}

    Logger::log("Sending packet failed!\n");
    Logger::log("Ending Send Thread.\n");
}

void SocketClient::recvFunc() {

    nn::socket::Recv(this->socket_log_socket, nullptr, 0, 0);

    Logger::log("Starting Recv Thread.\n");

    while (recv() || socket_log_state != SOCKET_LOG_DISCONNECTED) {}

    // Free up all blocked threads
    mSendQueue.push(0, sead::MessageQueue::BlockType::NonBlocking);
    mRecvQueue.push(0, sead::MessageQueue::BlockType::NonBlocking);

    Logger::log("Receiving Packet Failed!\n");
    Logger::log("Ending Recv Thread.\n");
}

bool SocketClient::queuePacket(Packet* packet) {
    if (socket_log_state == SOCKET_LOG_CONNECTED && mPacketQueueOpen) {
        mSendQueue.push((s64)packet,
                        sead::MessageQueue::BlockType::NonBlocking);  // as this is non-blocking, it
                                                                      // will always return true.
        return true;
    } else {
        mHeap->free(packet);
        return false;
    }
}

bool SocketClient::trySendQueue() {

    Packet* curPacket = (Packet*)mSendQueue.pop(sead::MessageQueue::BlockType::Blocking);

    bool successful = send(curPacket);

    mHeap->free(curPacket);

    return successful;
}

Packet* SocketClient::tryGetPacket(sead::MessageQueue::BlockType blockType) {
    return socket_log_state == SOCKET_LOG_CONNECTED ? (Packet*)mRecvQueue.pop(blockType) : nullptr;
}

void SocketClient::clearMessageQueues() {
    bool prevQueueOpenness = this->mPacketQueueOpen;
    this->mPacketQueueOpen = false;

    while (mSendQueue.getCount() > 0) {
        Packet* curPacket = (Packet*)mSendQueue.pop(sead::MessageQueue::BlockType::Blocking);
        mHeap->free(curPacket);
    }

    while (mRecvQueue.getCount() > 0) {
        Packet* curPacket = (Packet*)mRecvQueue.pop(sead::MessageQueue::BlockType::Blocking);
        mHeap->free(curPacket);
    }

    this->mPacketQueueOpen = prevQueueOpenness;
}
