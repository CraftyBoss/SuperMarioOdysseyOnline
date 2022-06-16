#include <cstdlib>
#include <limits>
#include <nn/os.h>

#include <sead/time/seadTickSpan.h>

/*
namespace sead
{
s64 TickSpan::cFrequency = nn::os::GetSystemTickFrequency();

s64 TickSpan::toNanoSeconds() const
{
    const s64 abs_span = std::abs(mSpan);
    const s64 max = std::numeric_limits<s64>::max();

    if(cFrequency == 0) {
        cFrequency = nn::os::GetSystemTickFrequency();
    }

    // Try to get as much precision as possible without overflowing.

    if (abs_span < max / 1'000'000'000)
        return 1'000'000'000 * mSpan / cFrequency;

    if (abs_span < max / 1'000'000)
        return 1000 * (1'000'000 * mSpan / cFrequency);

    if (abs_span < max / 1000)
        return 1'000'000 * (1000 * mSpan / cFrequency);

    return 1'000'000'000 * (mSpan / cFrequency);
}

void TickSpan::setNanoSeconds(s64 ns)
{
    const s64 threshold = std::numeric_limits<s64>::max() / cFrequency;
    const s64 abs_ns = std::abs(ns);

    if (abs_ns <= threshold)
        mSpan = cFrequency * ns / 1'000'000'000;
    else if (abs_ns <= 1000 * threshold)
        mSpan = cFrequency * (ns / 1000) / 1'000'000;
    else if (abs_ns <= 1'000'000 * threshold)
        mSpan = cFrequency * (ns / 1'000'000) / 1000;
    else
        mSpan = cFrequency * (ns / 1'000'000'000);
}

}  // namespace sead
*/