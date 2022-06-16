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

    mIsDoneKeyboard = false;
    
}

void Keyboard::keyboardThread() {

    mIsDoneKeyboard = false;
    
    nn::swkbd::ShowKeyboardArg keyboardArg = nn::swkbd::ShowKeyboardArg();
    nn::swkbd::MakePreset(&keyboardArg.keyboardConfig, nn::swkbd::Preset::Default);

    keyboardArg.keyboardConfig.keyboardMode = nn::swkbd::KeyboardMode::ModeNumeric;
    keyboardArg.keyboardConfig.leftOptionalSymbolKey = '.';
    keyboardArg.keyboardConfig.textMaxLength = 15;
    keyboardArg.keyboardConfig.textMinLength = 1;
    keyboardArg.keyboardConfig.isUseUtf8 = true;
    keyboardArg.keyboardConfig.inputFormMode = nn::swkbd::InputFormMode::OneLine;

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

    nn::swkbd::ShowKeyboard(&mResultString, keyboardArg);

    mIsDoneKeyboard = true;

}

void Keyboard::openKeyboard(const char* initialText) {

    mInitialText = initialText;
    
    mThread->start();
}