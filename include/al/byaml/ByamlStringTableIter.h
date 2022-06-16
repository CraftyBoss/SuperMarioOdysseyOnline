#pragma once

#include <basis/seadTypes.h>

namespace al {
class ByamlStringTableIter {
public:
    ByamlStringTableIter();
    ByamlStringTableIter(const unsigned char*, bool);

    int getSize() const;
    const u32* getAddressTable() const;
    int getStringAddress(int) const;
    int getEndAddress() const;
    const char* getString(int) const;
    int getStringSize(int) const;
    int findStringIndex(const char*) const;
    bool isValidate() const;

    const u8* mData;  // _0
    bool mReversed;
};
};  // namespace al