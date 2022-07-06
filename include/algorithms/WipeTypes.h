#pragma once

// Probably will go unused

#include <cstddef>
#include "crc32.h"
#include "basis/seadTypes.h"

namespace WipeTypes {

    enum class Type : s16 {
        Unknown = -1,
        中間ワープ, // Intermediate warp,
        タイトルロゴ, // Title logo,
        ワープ絵画, // Warp painting,
        ホーム離陸, // Home takeoff,
        地下工場, // Underground factory,
        樹海, // Aokigahara,
        クッパLV1後, // After Bowser LV1,
        教会崩落, // Church collapse,
        教会落下, // Church fall,
        電線脱出ED, // Wire escape ED,
        ワールドワープホール, // World Warp Hall,
        教会に入る, // Enter the church,
        教会から出る, // Get out of the church,
        墜落W前, // Before the crash W,
        オープニング, // opening,
        ホーム陥落, // Home fall,
        溶岩シナリオ1終了, // Lava scenario 1 end,
        ワールド間移動デモ室内へ用, // For inter-world movement demo room,
        ワールド間移動デモ終了, // Inter-world movement demo finished,
        End
    };

    static constexpr size_t ToValue(Type type) { return static_cast<std::uint16_t>(type); }

    static constexpr Type ToType(std::uint16_t value) {return static_cast<Type>(value);}

    static constexpr std::array<const char*, ToValue(Type::End)> s_Strs {
        "中間ワープ", 
        "タイトルロゴ", 
        "ワープ絵画", 
        "ホーム離陸", 
        "地下工場", 
        "樹海", 
        "クッパLV1後", 
        "教会崩落", 
        "教会落下", 
        "電線脱出ED", 
        "ワールドワープホール", 
        "教会に入る", 
        "教会から出る", 
        "墜落W前", 
        "オープニング", 
        "ホーム陥落", 
        "溶岩シナリオ1終了", 
        "ワールド間移動デモ室内へ用", 
        "ワールド間移動デモ終了用"
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