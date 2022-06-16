#pragma once

namespace al {
class ByamlHashPair {
public:
    int getKey(bool) const;
    char getType() const;
    int getValue(bool) const;

    union {
        const int mData;
        struct {
            const char _0, _1, _2, mType;
        };
    };

    const int mValue;
};
};  // namespace al