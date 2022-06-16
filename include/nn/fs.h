#pragma once

#include "result.h"

namespace nn { namespace fs {

const s32 PathLengthMax = 0x300;

struct FileHandle
{
    u32 handle;
};

struct DirectoryHandle
{
    u32 handle;
};

struct DirectoryEntry
{
    char name[PathLengthMax+1];     // 0
    char _301[3];                   // 301
    u8 type;                        // 304
    s64 fileSize;                   // 308
};

enum OpenMode
{
    OpenMode_Read       = 1 << 0,
    OpenMode_Write      = 1 << 1,
    OpenMode_ReadWrite  = OpenMode_Read | OpenMode_Write
};

enum DirectoryMode
{
    DirectoryMode_Directories       = 1 << 0,
    DirectoryMode_Files             = 1 << 1,
    DirectoryMode_DirectoriesFiles  = DirectoryMode_Directories | DirectoryMode_Files
};

enum DirectoryEntryType
{
    DirectoryEntryType_Directory    = 0,
    DirectoryEntryType_File         = 1
};

struct ReadOption
{
    ReadOption(u32 flags = 0) : flags(flags) { }
    u32 flags;
};

struct WriteOption
{
    enum Flags
    {
        Flush = 1
    };

    WriteOption(u32 flags = 0) : flags(flags) { }
    u32 flags;
};


Result OpenFile(FileHandle* out, const char* path, s32 mode);
void CloseFile(FileHandle handle);
Result ReadFile(FileHandle handle, s64 offset, void* buffer, u32 size);
Result ReadFile(FileHandle handle, s64 offset, void* buffer, u32 size, const ReadOption& options);
Result WriteFile(FileHandle handle, s64 offset, const void* buffer, u32 size, const WriteOption& options = WriteOption(0));
Result FlushFile(FileHandle handle);
Result GetFileSize(s64* out, FileHandle handle);
Result SetFileSize(FileHandle handle, s64 size);

Result CreateFile(const char* path, s64 size);
Result DeleteFile(const char* path);
Result RenameFile(const char* path, const char* newPath);

Result OpenDirectory(DirectoryHandle* out, const char* path, s32 mode);
void CloseDirectory(DirectoryHandle handle);
Result ReadDirectory(s64* out, DirectoryEntry* entries, DirectoryHandle handle, s64 maxEntryCount);
Result GetDirectoryEntryCount(s64* out, DirectoryHandle handle);

Result CreateDirectory(char const* path);
Result DeleteDirectory(const char* path);
Result DeleteDirectoryRecursively(const char* path);
Result RenameDirectory(const char* path, const char* newPath);

Result MountSdCard(const char* mountPoint);
void Unmount(const char* mountPoint);

} }
