#pragma once

namespace al {

template <s32 L>
class StringTmp : public sead::FixedSafeString<L> {  // equal to WFormatFixedSafeString
public:
    StringTmp(const char* format, ...) : sead::FixedSafeString<L>() {
        std::va_list args;
        va_start(args, format);
        this->formatV(format, args);
        va_end(args);
    }
    ~StringTmp() = default;
};

}  // namespace al
