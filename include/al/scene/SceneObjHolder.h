#pragma once

#include "ISceneObj.h"

namespace al {

    class SceneObjHolder {
    public:
        SceneObjHolder(al::ISceneObj* (*)(int), int);
        
        ISceneObj *tryGetObj(int) const; // unsafe get still
        void setSceneObj(al::ISceneObj *,int);
        bool isExist(int) const;
        void initAfterPlacementSceneObj(struct ActorInitInfo const&);
        ISceneObj *getObj(int) const;
        void create(int);

    };

    class IUseSceneObjHolder
    {
    public:
        virtual al::SceneObjHolder* getSceneObjHolder() const = 0;

        static const char* sSceneObjName;
    };
};