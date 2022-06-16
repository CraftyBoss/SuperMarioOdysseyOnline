#pragma once

#include "Factory.h"
#include "logger.hpp"

namespace al {

    template <class T>
    LiveActor* createActorFunction(const char *name);

    template <class T>
    LiveActor *createCustomActor(const char *name)
    {
        return new T(name);
    };

    class LiveActor;

    typedef LiveActor* (*createActor)(const char* name);
    
    class ActorFactory : public Factory<createActor> {
        public:
            ActorFactory(const char *fName) {
                this->factoryName = fName;
                this->actorTable = nullptr;
                this->factoryCount = 0;
            };
    };
}