#pragma once

//#include <inttypes.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "sead/prim/seadSafeString.h"

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef uint64_t            u64;
typedef __uint128_t         u128;

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef int64_t             s64;
typedef __int128_t          s128;

// bool size is implementation defined, so use these where it's important
typedef u8                  bool1;
typedef u32                 bool4;

typedef float               f32;
typedef double              f64;

typedef unsigned long int ulong;

typedef unsigned int        usize_t;

typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef unsigned char uchar;

typedef unsigned char   undefined;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined3;
typedef unsigned int    undefined4;
typedef unsigned long    undefined8;

const u8 MAX_HOSTNAME_LENGTH = 50;
typedef sead::FixedSafeString<MAX_HOSTNAME_LENGTH + 1> hostname;

enum SocketLogState {
    SOCKET_LOG_UNINITIALIZED = 0,
    SOCKET_LOG_CONNECTED = 1,
    SOCKET_LOG_UNAVAILABLE = 2,
    SOCKET_LOG_DISCONNECTED = 3
};

//typedef signed int          ssize_t;

//typedef unsigned int        uintptr_t;
//typedef signed int          intptr_t;

typedef __builtin_va_list va_list;
#define va_start(v,l) __builtin_va_start(v,l)
#define va_end(v) __builtin_va_end(v)

//using u64 = std::uint64_t;
//using s64 = std::int64_t;

// stores a result on a lot of OS-related functions
typedef u32 Result;
typedef u32 Handle;
typedef void (*ThreadFunc)(void*);

enum Direction
{
    RIGHT = 0,
    LEFT  = 1,
    UP    = 2,
    DOWN  = 3
};

struct Rect
{
	float left;
	float bottom;
	float right;
	float top;
};

#define PACKED __attribute__((packed))
#define USED __attribute__((used))
