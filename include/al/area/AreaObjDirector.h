#pragma once

namespace al
{
    class AreaObjDirector;

    class IUseAreaObj
    {
    public:
        virtual al::AreaObjDirector* getAreaObjDirector() const = 0;
    };
};