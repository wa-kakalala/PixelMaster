#ifndef XXX_LD_H_
#define XXX_LD_H_

#include "YoseenCPP/yc_type.h"

/*******************************************************************************************************
* basic
*
*
*
********************************************************************************************************/
#define Const_WidthMin		160
#define Const_HeightMin		120
#define Const_WidthMax		2560
#define Const_HeightMax		2048
#define Const_PixelsMax		(Const_WidthMax*Const_HeightMax)
#define Const_DiagMax		(Const_WidthMax+Const_HeightMax)


/*******************************************************************************************************
* LD
*
*
*
********************************************************************************************************/
#define LD_PointCountMax         5


struct LDConfig {
    /*
    mmpp = 1, 1 mm per pixel for test
    */
    float mmpp;

    /*
    *
    * pointArray = 25, 40, 60, 80
    * areaArray= <25, 25-40, 40-60, 60-80, >80
    *
    *
    * areaCount=pointCount+1
    */
    u32 pointCount;
    float pointArray[LD_PointCountMax];

    /*
    input width, height, roi
    */
    u16 width;
    u16 height;
    u16 cx0;
    u16 cy0;
    u16 cx1;
    u16 cy1;

    //other
};

struct LDOutput {
    /*
    */
    u32 areaCount;
    float areaArray[LD_PointCountMax];//ratio

    //
    u8* areaMap;//width*height, 8UC1, label
};

struct _LDContext;
typedef struct _LDContext LDContext;

extern "C" {

    /**
    */
    SDK_API LDContext* LD_Create();

    /**
    */
    SDK_API void LD_Free(LDContext** pp);

    /**
    */
    SDK_API s32 LD_SetConfig(LDContext* context, LDConfig* config);

    /**
    */
    SDK_API s32 LD_Execute(LDContext* context, u8* gray, u16 width, u16 height, LDOutput* output);
}

#endif
