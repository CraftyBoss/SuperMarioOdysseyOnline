#pragma once

namespace nn { namespace settings { 

struct LanguageCode
{
    char data[8];
};

void GetLanguageCode(LanguageCode* out);

} }
