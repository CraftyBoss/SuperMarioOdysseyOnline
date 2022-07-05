#pragma once

#include "ISceneObj.h"

namespace al {

    typedef al::ISceneObj* (*SceneObjCreator)(int);

    class SceneObjHolder {
    public:
        SceneObjHolder(SceneObjCreator, int);
        
        ISceneObj *tryGetObj(int) const; // unsafe get still
        void setSceneObj(al::ISceneObj *,int);
        bool isExist(int) const;
        void initAfterPlacementSceneObj(struct ActorInitInfo const&);
        ISceneObj *getObj(int) const;
        void create(int);

        SceneObjCreator mObjCreator;
        al::ISceneObj **mSceneObjs;
        int mMaxObjCount;
        
    };

    static_assert(sizeof(SceneObjHolder) == 0x18, "SceneObjHolder Size");

    class IUseSceneObjHolder
    {
    public:
        virtual al::SceneObjHolder* getSceneObjHolder() const = 0;

        static const char* sSceneObjName;
    };
};