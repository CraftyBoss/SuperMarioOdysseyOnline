#pragma once

namespace al
{
    class NerveKeeper;

    class IUseNerve
    {
    public:

        inline IUseNerve()
        {
            
        }

        virtual NerveKeeper* getNerveKeeper() const = 0;
    };

    class Nerve
    {
    public:
        virtual void execute(NerveKeeper *) = 0;
        virtual void executeOnEnd(NerveKeeper *) const;
    };
};