#pragma once

#include <cstddef>
#include "crc32.h"
#include "basis/seadTypes.h"

namespace CaptureTypes {

    enum class Type : s16 {
        Unknown = -1,
        AnagramAlphabetCharacter,
        Byugo, 
        Bubble, 
        Bull, 
        Car, 
        ElectricWire,
        KillerLauncherMagnum, 
        KuriboPossessed,
        WanwanBig,
        KillerLauncher, 
        Koopa,
        Wanwan,
        Pukupuku, 
        PukupukuSnow,
        Gamane,
        FireBrosPossessed, 
        PackunFire, 
        Frog, 
        Kakku, 
        Hosui, 
        HammerBrosPossessed, 
        Megane,
        KaronWing, 
        KuriboWing, 
        PackunPoison, 
        Radicon, 
        Tank, 
        Tsukkun, 
        TRex, 
        TRexSleep,
        TRexPatrol,
        Imomu, 
        SenobiGeneratePoint,
        End
    };

    static constexpr size_t ToValue(Type type) { return static_cast<std::uint16_t>(type); }

    static constexpr Type ToType(std::uint16_t value) {return static_cast<Type>(value);}

    static constexpr std::array<const char*, ToValue(Type::End)> s_Strs {
        "AnagramAlphabetCharacter",
        "Byugo", 
        "Bubble", 
        "Bull", 
        "Car", 
        "ElectricWire",
        "KillerLauncherMagnum", 
        "KuriboPossessed",
        "WanwanBig",  // has sub-actors
        "KillerLauncher", 
        "Koopa",
        "Wanwan",  // has sub-actors
        "Pukupuku", 
        "PukupukuSnow",
        "Gamane",  // has sub-actors
        "FireBrosPossessed", 
        "PackunFire", 
        "Frog", 
        "Kakku", 
        "Hosui", 
        "HammerBrosPossessed", 
        "Megane",
        "KaronWing", 
        "KuriboWing", 
        "PackunPoison", 
        "Radicon", 
        "Tank", 
        "Tsukkun", 
        "TRex", 
        "TRexSleep",
        "TRexPatrol",
        "Imomu", 
        "SenobiGeneratePoint"
    };

    // these ifdefs are really dumb but it makes clangd happy so /shrug
#ifndef ANALYZER
    static constexpr crc32::HashArray s_Hashes(s_Strs);
#endif

    static constexpr Type FindType(std::string_view const& str) {
#ifndef ANALYZER
        return ToType(s_Hashes.FindIndex(str));
#else
        return Type::Unknown;
#endif
    }

    static constexpr const char *FindStr(Type type) {
        const s16 type_ = (s16)type;
        if (0 <= type_ && type_ < s_Strs.size())
            return s_Strs[type_];
        else
            return "";
    }
}