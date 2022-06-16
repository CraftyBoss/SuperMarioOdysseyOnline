#pragma once

namespace al
{
    class SceneCreator;

    class IUseSceneCreator
    {
    public:
        virtual al::SceneCreator* getSceneCreator() const = 0;
        virtual al::SceneCreator* setSceneCreator() const = 0;
    };
};