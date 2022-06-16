#pragma once

#include "types.h"

namespace nn
{
    namespace nex
    {   

        namespace TransportProtocol
        {
            static enum Type {
                unk1, // or this one
                unk2, // i think we need to use this one
                unk3,
                unk4,
                unk5,
                unk6
            };
        }

        namespace SocketDriver
        {
            struct InetAddress {

            };

            enum _SocketFlag {
                
            };
        } 
        

        namespace BerkeleySocketDriver {
            class BerkeleySocket
            {
            public:
                BerkeleySocket();
                BerkeleySocket(const nn::nex::BerkeleySocketDriver::BerkeleySocket *, int);
                ~BerkeleySocket();

                bool Open(nn::nex::TransportProtocol::Type);
                bool SetAsync(bool);
                bool SetBroadcastMode(bool); // empty class that always returns true
                bool Bind(ushort &);
                bool LastSocketErrorToResult(char const*, long);
                s32 GetLastSocketError(long); // unknown if this returns anything, it branches to an external function probably located in nnsdk, but uses of it seem to require some sort of int
                s32 RecvFrom(uchar *, ulong, nn:nex::SocketDriver::InetAddress *, unsigned long *, nn::nex::SocketDriver::_SocketFlag);
            };
        }
    };
};