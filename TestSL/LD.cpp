#include "LD_Data.h"

/**
*/
SDK_API LDContext* LD_Create() {
    LDContext* context = (LDContext*)calloc(1, sizeof(LDContext));

    return context;
}

/**
*/
SDK_API void LD_Free(LDContext** pp) {
    LDContext* context = *pp;
    if (NULL == context)return;

    free(context);
    *pp = NULL;
}

/**
*/
SDK_API s32 LD_SetConfig(LDContext* context, LDConfig* config) {
    LDConfig& old = context->config;
    if (0 == memcmp(&old, config, sizeof(LDConfig)))return 0;

    s32 ret = 0;

    return ret;
}

/**
*/
SDK_API s32 LD_Execute(LDContext* context, u8* gray, u16 width, u16 height, LDOutput* output) {
    LDConfig& old = context->config;


    return 0;
}
