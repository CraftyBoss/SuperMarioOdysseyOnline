#pragma once

#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>
#include <resource/seadArchiveRes.h>
#include <filedevice/seadArchiveFileDevice.h>

#include "nn/g3d/g3d_ResFile.h"

namespace al {
    class Resource {
    public:
        Resource(sead::SafeString const&);
        Resource(sead::SafeString const&, sead::ArchiveRes*);

        bool isExistFile(sead::SafeString const&) const;
        bool isExistByml(char const*) const;

        int getSize() const;

        int getEntryNum(sead::SafeString const&) const;
        const char *getEntryName(sead::BufferedSafeString*, sead::SafeString const&, unsigned int) const;

        void getFileSize(sead::SafeString const&) const;
        void getByml(sead::SafeString const&) const;
        void getFile(sead::SafeString const&) const;
        void tryGetByml(sead::SafeString const&) const;
        void getKcl(sead::SafeString const&) const;
        void tryGetKcl(sead::SafeString const&) const;
        void getPa(sead::SafeString const&) const;
        void tryGetPa(sead::SafeString const&) const;
        void getOtherFile(sead::SafeString const&) const;
        const char* getArchiveName() const;
        
        bool tryCreateResGraphicsFile(sead::SafeString const&, nn::g3d::ResFile*);
        void cleanupResGraphicsFile();

        sead::ArchiveRes* mArc;                // 0x0
        sead::ArchiveFileDevice *mFileDevice;  // 0x8
        sead::FixedSafeString<0x80> mArcName;  // 0x10
        sead::Heap* mCurrentHeap;              // 0xA8
        void *unkPtr;                          // 0xB0
        nn::g3d::ResFile *mResGfxFile;         // 0xB8

    };
}  // namespace al

static_assert(sizeof(al::Resource) == 0xC0, "al::Resource Size");    
