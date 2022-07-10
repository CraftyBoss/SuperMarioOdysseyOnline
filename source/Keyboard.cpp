#include "Keyboard.hpp"
#include "logger.hpp"
#include "nn/os.h"
#include "nn/swkbd/swkbd.h"

Keyboard::Keyboard(ulong strSize) : mResultString(strSize) {
    this->mThread =
        new al::AsyncFunctorThread("Swkbd", al::FunctorV0M<Keyboard*, void (Keyboard::*)(void)>(this, &Keyboard::keyboardThread), 0, 0x2000, {0});

    mWorkBufSize = nn::swkbd::GetRequiredWorkBufferSize(false);
    mWorkBuf = (char*)malloc(mWorkBufSize);

    mTextCheckSize = 0x400;
    mTextCheckBuf = (char*)malloc(mTextCheckSize);

    mCustomizeDicSize = 0x400;
    mCustomizeDicBuf = (char*)malloc(mCustomizeDicSize);
    
}

void Keyboard::keyboardThread() {
    
    nn::swkbd::ShowKeyboardArg keyboardArg = nn::swkbd::ShowKeyboardArg();
    nn::swkbd::MakePreset(&keyboardArg.keyboardConfig, nn::swkbd::Preset::Default);

    mSetupFunc(keyboardArg.keyboardConfig);

    nn::swkbd::SetHeaderText(&keyboardArg.keyboardConfig, mHeaderText);
    nn::swkbd::SetSubText(&keyboardArg.keyboardConfig, mSubText);
    
    keyboardArg.workBufSize = mWorkBufSize;
    keyboardArg.textCheckWorkBufSize = mTextCheckSize;
    keyboardArg._customizeDicBufSize = mCustomizeDicSize;

    keyboardArg.workBuf = mWorkBuf;
    keyboardArg.textCheckWorkBuf = mTextCheckBuf;
    keyboardArg._customizeDicBuf = mCustomizeDicBuf;

    if (mInitialText.calcLength() > 0) {
        nn::swkbd::SetInitialTextUtf8(&keyboardArg, mInitialText.cstr());
    }

    mIsCancelled =
        nn::swkbd::ShowKeyboard(&mResultString, keyboardArg) == 671;  // no idea what 671 could be
    
}

void Keyboard::openKeyboard(const char* initialText, KeyboardSetup setupFunc) {

    mInitialText = initialText;
    mSetupFunc = setupFunc;
    
    mThread->start();
}