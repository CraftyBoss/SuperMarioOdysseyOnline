#pragma once


namespace al {
    class ISceneObj {
        public:
            virtual const char* getSceneObjName(void) = 0;
            virtual ~ISceneObj();
            virtual void initAfterPlacementSceneObj(struct ActorInitInfo const&) = 0;
            virtual void initSceneObj(void) = 0;
    };
}