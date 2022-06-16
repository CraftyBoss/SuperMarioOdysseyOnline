#include <cstdlib>

#include "basis/seadNew.h"
#include "heap/seadHeap.h"
#include "heap/seadHeapMgr.h"

namespace sead
{
    namespace system
    {
        void* NewImpl(Heap* heap, size_t size, s32 alignment, bool abortOnFailure);
        void DeleteImpl(void* ptr);
    }  // namespace system
}  // namespace sead

// operator new(size_t)

// operator new(size_t)

void* operator new(size_t size)
{
    return sead::system::NewImpl(nullptr, size, 8, true);
}

void* operator new[](size_t size)
{
    return sead::system::NewImpl(nullptr, size, 8, true);
}

void* operator new(size_t size, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(nullptr, size, 8, false);
}

void* operator new[](size_t size, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(nullptr, size, 8, false);
}

// operator new(size_t, s32 alignment)

void* operator new(size_t size, s32 alignment)
{
    return sead::system::NewImpl(nullptr, size, alignment, true);
}

void* operator new[](size_t size, s32 alignment)
{
    return sead::system::NewImpl(nullptr, size, alignment, true);
}

void* operator new(size_t size, s32 alignment, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(nullptr, size, alignment, false);
}

void* operator new[](size_t size, s32 alignment, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(nullptr, size, alignment, false);
}

// operator new(size_t, sead::Heap*, s32 alignment)

void* operator new(size_t size, sead::Heap* heap, s32 alignment)
{
    return sead::system::NewImpl(heap, size, alignment, true);
}

void* operator new[](size_t size, sead::Heap* heap, s32 alignment)
{
    return sead::system::NewImpl(heap, size, alignment, true);
}

void* operator new(size_t size, sead::Heap* heap, s32 alignment, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(heap, size, alignment, false);
}

void* operator new[](size_t size, sead::Heap* heap, s32 alignment, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(heap, size, alignment, false);
}

// operator new(size_t, sead::Heap*, const std::nothrow_t&)

void* operator new(size_t size, sead::Heap* heap, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(heap, size, 8, false);
}

void* operator new[](size_t size, sead::Heap* heap, const std::nothrow_t&) noexcept
{
    return sead::system::NewImpl(heap, size, 8, false);
}

// operator delete(void*)

void operator delete(void* ptr) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete(void* ptr, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

// operator delete(void*, s32)

void operator delete(void* ptr, s32)
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, s32)
{
    sead::system::DeleteImpl(ptr);
}

void operator delete(void* ptr, s32, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, s32, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

// operator delete(void*, sead::Heap*, const std::nothrow_t&)

void operator delete(void* ptr, sead::Heap*, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, sead::Heap*, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

// operator delete(void*, sead::Heap*, s32)

void operator delete(void* ptr, sead::Heap*, s32)
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, sead::Heap*, s32)
{
    sead::system::DeleteImpl(ptr);
}

void operator delete(void* ptr, sead::Heap*, s32, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}

void operator delete[](void* ptr, sead::Heap*, s32, const std::nothrow_t&) noexcept
{
    sead::system::DeleteImpl(ptr);
}