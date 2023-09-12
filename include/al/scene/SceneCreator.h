#pragma once

namespace al
{
    class SceneCreator;

    class IUseSceneCreator
    {
    public:
        virtual al::SceneCreator* getSceneCreator() const = 0;
        virtual void setSceneCreator(al::SceneCreator* ) = 0;
    };
};