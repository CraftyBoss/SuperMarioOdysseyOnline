#include "server/SocketClient.hpp"
#include <cstdlib>
#include <cstring>

#include "SocketBase.hpp"
#include "logger.hpp"
#include "nn/result.h"
#include "nn/socket.h"
#include "packets/Packet.h"
#include "types.h"

nn::Result SocketClient::init(const char* ip, u16 port) {

    sock_ip = ip;

    this->port = port;
    
    in_addr hostAddress = { 0 };
    sockaddr serverAddress = { 0 };

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

    
    nn::socket::InetAton(this->sock_ip, &hostAddress);

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

    this->socket_log_state = SOCKET_LOG_CONNECTED;

    return result;

}

bool SocketClient::SEND(Packet *packet) {

    if (this->socket_log_state != SOCKET_LOG_CONNECTED)
        return false;

    char* buffer = reinterpret_cast<char*>(packet);

    int valread = 0;

    if (packet->mType != PLAYERINF && packet->mType != HACKCAPINF)
        Logger::log("Sending packet: %s\n", packetNames[packet->mType]);

    if ((valread = nn::socket::Send(this->socket_log_socket, buffer, packet->mPacketSize + sizeof(Packet), this->sock_flags) > 0)) {
        return true;
    } else {
        Logger::log("Failed to Fully Send Packet! Result: %d Type: %s Packet Size: %d\n", valread, packetNames[packet->mType], packet->mPacketSize);
        this->socket_errno = nn::socket::GetLastErrno();
        this->closeSocket();
        return false;
    }
    return true;
}

bool SocketClient::RECV() {

    if (this->socket_log_state != SOCKET_LOG_CONNECTED) {
        Logger::log("Unable To Receive! Socket Not Connected.\n");
        this->socket_errno = nn::socket::GetLastErrno();
        return false;
    }
    
    int headerSize = sizeof(Packet);
    char headerBuf[sizeof(Packet)] = {};
    int valread = 0;

    // read only the size of a header
    while(valread < headerSize) {
        int result = nn::socket::Recv(this->socket_log_socket, headerBuf + valread,
                                      headerSize - valread, this->sock_flags);

        this->socket_errno = nn::socket::GetLastErrno();
        
        if(result > 0) {
            valread += result;
        } else {
            Logger::log("Header Read Failed! Value: %d Total Read: %d\n", result, valread);
            this->closeSocket();
            return false;
        }
    }

    if(valread > 0) {
        Packet* header = reinterpret_cast<Packet*>(headerBuf);

        int fullSize = header->mPacketSize + sizeof(Packet);

        if (header->mType != PacketType::UNKNOWN && fullSize <= MAXPACKSIZE && fullSize > 0) {

            if (header->mType != PLAYERINF && header->mType != HACKCAPINF)
                Logger::log("Received packet (from %02X%02X): %s\n",
                    header->mUserID.data[0], header->mUserID.data[1], packetNames[header->mType]);

            char* packetBuf = (char*)malloc(fullSize);

            if (packetBuf) {
                
                memcpy(packetBuf, headerBuf, sizeof(Packet));

                while (valread < fullSize) {

                    int result = nn::socket::Recv(this->socket_log_socket, packetBuf + valread,
                                                  fullSize - valread, this->sock_flags);

                    this->socket_errno = nn::socket::GetLastErrno();

                    if (result > 0) {
                        valread += result;
                    } else {
                        free(packetBuf);
                        Logger::log("Packet Read Failed! Value: %d\nPacket Size: %d\nPacket Type: %s\n", result, header->mPacketSize, packetNames[header->mType]);
                        this->closeSocket();
                        return false;
                    }
                }

                Packet *packet = reinterpret_cast<Packet*>(packetBuf);

                if(mPacketQueue.size() < maxBufSize - 1) {
                    mPacketQueue.pushBack(packet);
                } else {
                    free(packetBuf);
                }
            }
        }
        
        return true;
    } else {  // if we error'd, close the socket
        Logger::log("valread was zero! Disconnecting.\n");
        this->socket_errno = nn::socket::GetLastErrno();
        this->closeSocket();
        return false;
    }
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

bool SocketClient::closeSocket() {

    Logger::log("Closing Socket.\n");

    return SocketBase::closeSocket();
}