#pragma once

#ifdef NNSDK
#include <nn/os.h>
#endif

namespace sead
{
class Heap;

class MessageQueue
{
public:
#ifdef NNSDK
    using Element = s64;
#else
#error "Unknown platform"
    using Element = u64;
#endif

    enum class BlockType
    {
        Blocking = 0,
        NonBlocking = 1,
    };

    MessageQueue();
    ~MessageQueue();

    void allocate(s32 size, Heap* heap);
    void free();
    bool push(Element message, BlockType block_type);
    Element pop(BlockType block_type);
    Element peek(BlockType block_type) const;
    bool jam(Element message, BlockType block_type);

    // custom funcs
    inline u32 getCount() {return mMessageQueueInner.Count;}
    inline u32 getMaxCount() {return mMessageQueueInner.MaxCount;}
    inline bool isFull() const {return mMessageQueueInner.Count == mMessageQueueInner.MaxCount;}

    static constexpr Element cNullElement = 0;

private:
#ifdef NNSDK
    nn::os::MessageQueueType mMessageQueueInner;
    Element* mBuffer = nullptr;
#else
#error "Unknown platform"
#endif
};
}  // namespace sead
