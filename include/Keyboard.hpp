#pragma once

#include <cstddef>
#include "al/async/AsyncFunctorThread.h"
#include "al/async/FunctorV0M.hpp"

#include "nn/swkbd/swkbd.h"

#include "logger.hpp"
#include "sead/prim/seadSafeString.h"

typedef void (*KeyboardSetup)(nn::swkbd::KeyboardConfig&);

class Keyboard {
    public:
        Keyboard(ulong strSize);
        void keyboardThread();

        void openKeyboard(const char* initialText, KeyboardSetup setup);

        const char* getResult() {
            if (mThread->isDone()) {
                return mResultString.cstr();
            }
            return nullptr;
        };

        bool isThreadDone() { return mThread->isDone(); }

        void setHeaderText(const char16_t* text) { mHeaderText = text; }
        void setSubText(const char16_t* text) { mSubText = text; }

    private:

        al::AsyncFunctorThread* mThread;
        nn::swkbd::String mResultString;

        bool mIsDoneKeyboard;

        sead::FixedSafeString<0x10> mInitialText;
        KeyboardSetup mSetupFunc;

        const char16_t *mHeaderText = u"Enter Server IP Here!";
        const char16_t *mSubText = u"Must be a Valid Address.";
        
        char* mWorkBuf;
        int mWorkBufSize;
        char* mTextCheckBuf;
        int mTextCheckSize;
        char* mCustomizeDicBuf;
        int mCustomizeDicSize;
};