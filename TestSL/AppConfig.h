#ifndef APPCONFIG_H_
#define APPCONFIG_H_

#include "YoseenCPP/yc_type.h"
#include "LD.h"

#include <string>
using namespace std;

struct AppConfig {
    //
    std::string debug_input;
    LDConfig core;
};

s32 AppConfig_Init(AppConfig& config);


#endif
