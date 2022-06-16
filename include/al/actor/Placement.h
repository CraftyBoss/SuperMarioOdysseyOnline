#pragma once

#include "al/byaml/ByamlIter.h"
#include "sead/prim/seadSafeString.hpp"

namespace al
{
    class PlacementInfo
    {
    public:
        PlacementInfo();

        void set(const al::ByamlIter &, const al::ByamlIter &);

        al::ByamlIter _0;
        al::ByamlIter mZoneIter; // _10
    };

    class PlacementId
    {
    public:
        PlacementId();
        PlacementId(const char *unitConifgName, const char *objId, const char *commonId);

        bool init(const al::PlacementInfo &);
        bool isEqual(const al::PlacementId &) const;
        static bool isEqual(const al::PlacementId &, const al::PlacementId &);
        bool isValid() const;
        bool makeString(sead::BufferedSafeStringBase<char> *) const;

        const char* _0;
        const char* mUnitConfigName; // _8
        const char* mID; // _10
        const char* mCommonID; // _18
    };
}