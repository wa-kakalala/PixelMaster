#ifndef XXX_LD_DATA_H_
#define XXX_LD_DATA_H_

#include "LD.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <numeric>

//
//#define XDEBUG_DUMP
//#define XDEBUG_CCL

//
#ifdef XDEBUG_DUMP
static void xdump_image(const char* name, cv::Mat& mat) {
    static s32 calls = 0;
    calls++;
    char namex[64];
    snprintf(namex, 64, "Debug/%02d-%s.jpg", calls, name);
    imwrite(namex, mat);
}
#define XDUMP_IMAGE(name,mat)      xdump_image(name,mat) 
#else
#define XDUMP_IMAGE(name,mat)
#endif

typedef struct _LDContext {
    LDConfig config;
    s32 cfg_width, cfg_height, cfg_pixels;
    s32 cfgroi_width, cfgroi_height, cfgroi_pixels;

    //
    u8* data_roi;
    u8* data_bin;
    u8* data_mask;
}LDContext;

#endif
