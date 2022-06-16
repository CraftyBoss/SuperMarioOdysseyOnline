#pragma once

#include "al/byaml/ByamlHashPair.h"

namespace al {
enum DataType : unsigned char {
    TYPE_STRING = 0xA0,
    TYPE_BINARY = 0xA1,
    TYPE_ARRAY = 0xC0,
    TYPE_HASH = 0xC1,
    TYPE_STRING_TABLE = 0xC2,
    TYPE_BOOL = 0xD0,
    TYPE_INT = 0xD1,
    TYPE_FLOAT = 0xD2,
    TYPE_UINT = 0xD3,
    TYPE_LONG = 0xD4,
    TYPE_ULONG = 0xD5,
    TYPE_DOUBLE = 0xD6,
    TYPE_NULL = 0xFF
};

class ByamlData {
public:
    ByamlData();

    void set(const ByamlHashPair*, bool);
    void set(unsigned char, unsigned int, bool);
    unsigned char getType() const;
    unsigned int getValue() const;

    unsigned int mValue;  // _0
    unsigned char mType;  // _4
};
};  // namespace al