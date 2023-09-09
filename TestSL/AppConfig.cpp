#include "AppConfig.h"
#include "YoseenCPP/yc_json.hpp"
#include <stdio.h>

using json = nlohmann::json;

/**************************************************************************************************
*
*
*
*
***************************************************************************************************/
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LDConfig,
mmpp,
pointCount,
pointArray,
width, height,
cx0, cy0, cx1, cy1);

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AppConfig, debug_input, core);

static s32 AppConfig_Deser(AppConfig& cls, char* str, s32 len) {
    s32 ret = 0;
    try {
        //
        std::string y(str, len);
        json j = json::parse(y);
        from_json(j, cls);
    }
    catch (...) {
        ret = EError_InvalidData;
    }
    return ret;
}

static s32 AppConfig_Ser(AppConfig& cls, char* str, s32& len) {
    s32 ret = 0;
    try {
        //
        json j;
        to_json(j, cls);
        std::string s = j.dump();
        s32 slen = s.size();
        if (len < slen)return EError_InvalidArgs;
        len = slen;
        strncpy(str, s.c_str(), slen);
    }
    catch (...) {
        ret = EError_InvalidData;
    }
    return ret;
}

s32 AppConfig_Init(AppConfig& config) {
    s32 ret;
    FILE* f = fopen("TestLD.json", "rb");
    if (NULL == f)return EError_FileOpen;

    //
    s32 bufferSize = 4096;
    char* buffer = (char*)calloc(1, bufferSize);
    if (NULL == buffer) { ret = EError_NoMemory; goto error1; }

    ret = fread(buffer, 1, bufferSize, f);
    if (ret <= 0 || ret >= bufferSize) { ret = EError_InternalError; goto error1; }
    ret = AppConfig_Deser(config, buffer, ret);

    //ret = AppConfig_Ser(config, buffer, bufferSize);

error1:
    free(buffer);
    fclose(f);
    return ret;
}
