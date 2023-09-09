#include "LD.h"
#include "YoseenCPP/yc_platform.h"
#include "AppConfig.h"

//
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define ConstUI_win               "test"

/*******************************************************************************************************
*
*
*
*
********************************************************************************************************/
static AppConfig __config = {};

//
static void test_frame(const char* fn) {
    s32 ret;

    //
    LDContext* context;
    LDConfig* config = &__config.core;
    LDOutput output = {};

    context = LD_Create();

    //
    s32 width = config->width;
    s32 height = config->height;
    s32 pixels = width * height;
    s32 roiWidth = config->cx1 - config->cx0;
    s32 roiHeight = config->cy1 - config->cy0;
    ret = LD_SetConfig(context, config);
    if (0 != ret) {
        printf("invalid config\n");
    }

    //
    cv::namedWindow(ConstUI_win, cv::WINDOW_NORMAL);
    cv::resizeWindow(ConstUI_win, width / 2, height / 2);
    cv::Mat frameBGR;
    cv::Mat frameGray;
    frameBGR = cv::imread(fn);
    cv::cvtColor(frameBGR, frameGray, cv::ColorConversionCodes::COLOR_BGR2GRAY);

    //get areaArray info
    char txtBuffer[256];
    ret = LD_Execute(context, (u8*)frameGray.data, width, height, &output);
    if (0 == ret) {
        char* p = txtBuffer;
        float* areaArray = output.areaArray;
        s32 i;
        for (i = 0; i < output.areaCount; i++) {
            ret = snprintf(p, 256, "%3.2f,", areaArray[i]);
            p += ret;
        }
        ret = 0;
    }
    else {
        snprintf(txtBuffer, 256, "error = %d", ret);
    }
    cv::putText(frameBGR, txtBuffer, cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);

    //show input
    cv::Rect rect(config->cx0, config->cy0, roiWidth, roiHeight);
    cv::rectangle(frameBGR, rect, cv::Scalar(0, 255, 0), 2);
    cv::imshow(ConstUI_win, frameBGR);

    //show areaMap
    if (0 < ret) {
        cv::Mat areaMap(height, width, CV_8UC1, output.areaMap);
        cv::imshow(ConstUI_win "-areaMap", areaMap);
    }

    //
    while (1) {
        ret = cv::waitKey(100);
        if ('0' == ret) {
            break;
        }
        else if ('w' == ret) {

        }
        else if ('s' == ret) {

        }
    }
}

static void test_stream(const char* fn) {

}

/*******************************************************************************************************
*
*
*
*
********************************************************************************************************/
int main(int argc, char* argv[]) {
    s32 ret;
    //ret = AppConfig_Init(__config);
    //if (0 != ret) {
     //   printf("invalid TestLD.json\n");
     //   return EError_InvalidArgs;
    //}

    printf("==============================================================================\n\
w: ctl_playMode\n\
s: ctl_isPause\n\
a: manual--\n\
d: manual++\n\
j: ctl_pauseOnBad\n\
==============================================================================\n");


    std::string& input = __config.debug_input;
    input = "E:/ParticleDetection/code/TestLD/img/img2/Image_20230727121946846.bmp";
    const char* fn = input.c_str();
    s32 fnlen = input.size();
    char c = fn[fnlen - 1];

    if (c == '4' || c == 'i') {
        //mp4, avi
        test_stream(fn);
    }
    else {
        test_frame(fn);
    }
    return 0;
}
