#pragma once

namespace al
{
    class CollisionDirector;

    class IUseCollision
    {
    public:
        virtual al::CollisionDirector* getCollisionDirector() const = 0;
    };
};