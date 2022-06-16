#pragma once

#include "SocketBase.hpp"
#include "types.h"

class Logger : public SocketBase {
    public:
        Logger(const char* ip, u16 port, const char* name) : SocketBase(name) {
            this->init(ip, port);
        };
        nn::Result init(const char* ip, u16 port) override;
        
        static void createInstance();
        static void setLogName(const char *name) { if(sInstance) sInstance->setName(name); }
        static void log(const char* fmt, ...);
        static void log(const char* fmt, va_list args);

        static void enableName() { if(sInstance) sInstance->isDisableName = false; }
        static void disableName() { if(sInstance) sInstance->isDisableName = true; }
        
        int read(char *out);
        bool pingSocket();

    private:
        static Logger* sInstance;
        bool isDisableName;
};