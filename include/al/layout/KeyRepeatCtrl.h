#pragma once

namespace al
{
    struct KeyRepeatCtrl {
        KeyRepeatCtrl(void);
        void init(int, int);
        void update(bool isUp, bool isDown);
        void reset(void);
        bool isUp(void) const;
        bool isDown(void) const;

        int maxIndex = 0;
        int frameTime = 0;
        bool isNoMove = true;
    };
} // namespace al
