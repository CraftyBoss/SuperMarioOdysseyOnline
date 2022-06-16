#pragma once

#include <sead/container/seadTList.h>

namespace sead {
class Heap;
class WriteStream;
}  // namespace sead

namespace al {

class ByamlWriterStringTable;
class ByamlWriterContainer;
class ByamlWriterBigDataList;

class ByamlWriterArray;
class ByamlWriterHash;

class ByamlIter;

class ByamlWriter {
public:
    ByamlWriter(sead::Heap*, bool);
    virtual ~ByamlWriter();

    void addBool(bool);
    void addInt(int);
    void addUInt(u32);
    void addFloat(float);
    void addInt64(long);
    void addUInt64(u64);
    void addDouble(double);
    void addString(const char*);
    void addNull();
    void addBool(const char*, bool);
    void addInt(const char*, int);
    void addUInt(const char*, u32);
    void addFloat(const char*, float);
    void addInt64(const char*, long);
    void addUInt64(const char*, u64);
    void addDouble(const char*, double);
    void addString(const char*, char const*);
    void addNull(const char*);

    ByamlWriterArray* getArrayCurrentContainer();
    ByamlWriterHash* getHashCurrentContainer();
    ByamlWriterContainer* getCurrentContainer();
    void pushHash();
    void pushContainer(ByamlWriterContainer*);
    void pushArray();
    void pushArray(char const*);
    void pushHash(char const*);
    void pushIter(const ByamlIter&);
    void pushIter(const char*, const ByamlIter&);
    void pushLocalIter(const ByamlIter&, const char*);
    void pop();
    u32 calcHeaderSize() const;
    u32 calcPackSize() const;
    void write(sead::WriteStream*);
    void print() const;

private:
    sead::Heap* mHeap;
    ByamlWriterStringTable* mStringTable1 = nullptr;
    ByamlWriterStringTable* mStringTable2 = nullptr;
    sead::TList<ByamlWriterContainer*> mContainerList;
    ByamlWriterBigDataList* mBigDataList = nullptr;
    ByamlWriterContainer** mContainerStack = nullptr;
    int mContainerStackSize = 64;
    int mCurrentContainerIndex = -1;
    bool _mAlwaysFalse;
};

}  // namespace al
