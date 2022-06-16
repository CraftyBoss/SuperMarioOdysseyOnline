#pragma once

#include "result.h"
#include "settings.h"

namespace nn { namespace err {

class ApplicationErrorArg
{
public:
    ApplicationErrorArg();
    ApplicationErrorArg(u32 code, const char* str1, const char* str2, const nn::settings::LanguageCode& languageCode);

    u8 data[0x1014];
};

void ShowError(Result result);
void ShowApplicationError(const ApplicationErrorArg& arg);
void ShowUnacceptableApplicationVersionError();
void ShowUnacceptableAddOnContentVersionError();

} }
