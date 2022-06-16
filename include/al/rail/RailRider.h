#pragma once

namespace al
{
    class RailRider;

    class IUseRail
    {
    public:
        virtual al::RailRider* getRailRider() const = 0;
    };
};