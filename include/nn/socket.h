#pragma once

#include "../types.h"

struct pollfd
{
	s32   fd;
	s16   events;
	s16   revents;
};

struct in_addr
{
    u32 data;           // 0
};

struct sockaddr
{
    u8 _0;              // 0
    u8 family;          // 1
    u16 port;           // 2
    in_addr address;    // 4
    u8 _8[8];           // 8
};

struct hostent
{
    char*   h_name;
    char**  h_aliases;
    int     h_addrtype;
    int     h_length;
    char**  h_addr_list;
};


namespace nn { namespace socket {

Result Initialize(void* pool, ulong poolSize, ulong allocPoolSize, int concurLimit);

s32 SetSockOpt(s32 socket, s32 socketLevel, s32 option, void const*, u32 len);

s32 Socket(s32 domain, s32 type, s32 protocol);
s32 Connect(s32 socket,	const sockaddr* address, u32 addressLen);
Result Close(s32 socket);

s32 Send(s32 socket, const void* data, ulong dataLen, s32 flags);
s32 SendTo(s32 socket, const void* data, ulong dataLen, s32 flags, const struct sockaddr* to, u32 toLen);
s32 Recv(s32 socket, void* out, ulong outLen, s32 flags);
s32 RecvFrom(s32 socket, void* out, ulong outLen, s32 flags, struct sockaddr* from, u32* fromLen);

s32 GetSockName(s32 socket, struct sockaddr* name, u32* dataLen);
u16 InetHtons(u16 val);
u16 InetNtohs(u16 val);
s32 InetAton(const char* addressStr, in_addr* addressOut);

struct hostent* GetHostByName(const char* name);

u32 GetLastErrno();
s32 Bind(s32 fd, sockaddr* addr, u32 addrlen);
s32 Poll(struct pollfd* fd, u64 addr, s32 timeout);

} }
