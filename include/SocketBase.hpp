#pragma once

#include <string>
#include <cstring>
#include "types.h"
#include "nn.h"
#include "sead/basis/seadNew.h"

class SocketBase {

    public:
        SocketBase(const char *name);

        virtual nn::Result init(const char * ip, u16 port) = 0;

        const char *getStateChar();
        u8 getLogState();
        s32 getSocket();

        void set_sock_flags(int flags);

        bool closeSocket();

        void setName(const char *name) {strcpy(sockName, name);};

    protected:
        s32 socket_log(const char* str);
        s32 socket_read_char(char *out);

        char sockName[0x10] = {};
        const char *sock_ip;

        u16 port;
        u8 socket_log_state;
        s32 socket_log_socket;
        
        int sock_flags;
};



