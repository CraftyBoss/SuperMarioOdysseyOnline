#pragma once

#include "GameFrameWorkNx.h"

class Application {
    public:
        static const Application *sInstance;

        unsigned char padding_28[0x28];
        al::GameFrameworkNx *mFramework; // 0x28
};

// const Application *Application::sInstance;