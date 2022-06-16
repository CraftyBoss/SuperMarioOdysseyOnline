#pragma once

#include "al/byaml/ByamlData.h"

namespace al {
class ByamlIter {
public:
    ByamlIter();
    ByamlIter(const char*);
    ByamlIter(const char*, const char*);

    bool isValid() const;
    bool isTypeHash() const;
    bool isTypeArray() const;
    bool isTypeContainer() const;
    bool isExistKey(char const* key) const;
    int getKeyIndex(char const* key) const;
    bool isInvertOrder() const;
    unsigned int getSize() const;
    al::ByamlIter* getIterByIndex(int index) const;
    bool getByamlDataByIndex(al::ByamlData*, int index) const;
    al::ByamlIter* getIterByKey(char const*) const;
    bool getByamlDataByKey(al::ByamlData*, char const*) const;
    bool getByamlDataByKeyIndex(al::ByamlData*, int) const;
    bool getByamlDataAndKeyName(al::ByamlData*, char const**, int) const;
    bool getKeyName(char const**, int) const;
    bool tryGetIterByIndex(al::ByamlIter*, int) const;
    bool tryGetIterAndKeyNameByIndex(al::ByamlIter*, char const**, int) const;
    bool tryGetIterByKey(al::ByamlIter*, char const*) const;
    bool tryGetStringByKey(char const**, char const*) const;
    bool tryConvertString(char const**, al::ByamlData const*) const;
    bool tryGetBinaryByKey(char const**, int*, char const*) const;
    bool tryGetBinary(char const**, int*, al::ByamlData const*) const;
    bool tryGetBoolByKey(bool*, char const*) const;
    bool tryConvertBool(bool*, al::ByamlData const*) const;
    bool tryGetIntByKey(int*, char const*) const;
    bool tryConvertInt32(int*, al::ByamlData const*) const;
    bool tryGetUInt32ByKey(unsigned int*, char const*) const;
    bool tryConvertUInt32(unsigned int*, al::ByamlData const*) const;
    bool tryGetFloatByKey(float*, char const*) const;
    bool tryConvertFloat(float*, al::ByamlData const*) const;
    bool tryGetInt64ByKey(long*, char const*) const;
    bool tryConvertInt64(long*, al::ByamlData const*) const;
    bool tryGetUInt64ByKey(unsigned long*, char const*) const;
    bool tryConvertUInt64(unsigned long*, al::ByamlData const*) const;
    bool tryGetDoubleByKey(double*, char const*) const;
    bool tryConvertDouble(double*, al::ByamlData const*) const;
    bool tryGetStringByIndex(char const**, int) const;
    bool tryGetBinaryByIndex(char const**, int*, int) const;
    bool tryGetBoolByIndex(bool*, int) const;
    bool tryGetInt32ByIndex(int*, int) const;
    bool tryGetUInt32ByIndex(unsigned int*, int) const;
    bool tryGetFloatByindex(float*, int) const;
    bool tryGetInt64ByIndex(long*, int) const;
    bool tryGetUInt64ByIndex(unsigned long*, int) const;
    bool tryGetDoubleByIndex(double*, int) const;
    bool tryConvertIter(al::ByamlIter*, al::ByamlData const*) const;
    bool isEqualData(al::ByamlIter const&) const;

    unsigned char* mData;       // _0
    unsigned long mDataOffset;  // _8
};
};  // namespace al