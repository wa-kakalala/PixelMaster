/*******************************************************************************************************
* yc_type.h
*
* 2022-11-21: init
*
*
*
********************************************************************************************************/
#ifndef YC_TYPE_H_
#define YC_TYPE_H_


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//ARCH
#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64)
#define ARCH_X64
#define ARCH_X86_64
#elif defined(__i386) || defined(__i386__) || defined(_M_IX86)
#define ARCH_X86
#define ARCH_X86_32
#elif defined(__arm__)
#define ARCH_ARM
#elif defined(__aarch64__) || defined(__ARM64__)
#define ARCH_ARM644
#else
#warning "invalid arch"
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//OS
#if defined(WIN64) || defined(_WIN64)
#define OS_WIN
#define OS_WIN64
#elif defined(WIN32)|| defined(_WIN32)
#define OS_WIN
#define OS_WIN32
#elif defined(linux) || defined(__linux) || defined(__linux__)
#define OS_LINUX
#else
#error "invalid os"
#endif

#if defined(ANDROID) || defined(__ANDROID__)
#define OS_ANDROID
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//COMPILER
#if defined(_MSC_VER)
#define COMPILER_MSVC

//C4018: signed/unsigned mismatch
//C4200: zero-sized array in struct/union
//C4244: 's32' to 'float'
//C4267: 'u32' to 's32'
//C4305: 'double' to 'float'
//C4819: unicode
//C4838: 's32' to 'u32'
//C4996: _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4018 4200 4244 4267 4305 4819 4838 4996)

#elif defined(__MINGW32__) || defined(__MINGW64__)
#define COMPILER_MINGW
#elif defined(__GNUC__)
#define COMPILER_GCC
#else
##error "invalid compiler"
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EError {
    EError_None = 0,
    EError_InternalError = -1,
    EError_NotSupported = -2,
    EError_NotImplemented = -3,
    EError_SDKUninited = -4,
    EError_NoMemory = -5,
    EError_NoHandle = -6,
    EError_InvalidState = -7,
    EError_InvalidArgs = -8,
    EError_InvalidResp = -9,
    EError_InvalidHandle = -10,
    EError_InvalidData = -11,
    EError_PreviewCreateBuffer = -12,
    EError_PreviewOpenInput = -13,
    EError_PreviewOpenDisplay = -14,
    //-15, -16
    EError_PreviewRecoverBegin = -17,
    EError_PreviewRecoverEnd = -18,

    //Socket
    EError_SocketOpen = -100,
    EError_SocketConn,
    EError_SocketSend,
    EError_SocketRecv,
    EError_SocketConfig,
    EError_SocketData,

    //File
    EError_FileOpen = -200,
    EError_FileClose,
    EError_FileRead,
    EError_FileWrite,
    EError_FileEOF,
    EError_FileType,
    EError_FileData,

    //Ffmpeg
    EError_FfmpegEncode = -300,
    EError_FfmpegDecode,
    EError_FfmpegMuxOpen,
    EError_FfmpegMuxWrite,
    EError_FfmpegMuxClose,
    EError_FfmpegDemuxOpen,
    EError_FfmpegDemuxRead,
    EError_FfmpegDemuxClose,

    //MVSError = -1000
    //WebError = -2000
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;

#define S8_MIN			(-128)
#define S8_MAX			127
#define S16_MIN			(-32768)
#define S16_MAX			32767
#define S16_RANGE		(65536)
#define U16_MAX			(65535)
#define U16_RANGE		(65536)

#define S32_MIN			(-2147483647 - 1)
#define U32_MAX			0xffffffff

//
#define ARRAY_SIZE(x)			(sizeof(x)/sizeof(x[0]))
#define MIN(a,b)				((a)<(b)?(a):(b))
#define MAX(a,b)				((a)>(b)?(a):(b))
#define ABS(a)					((a)>0?(a):-(a))

//
#ifdef OS_WIN

#else
#define SOCKET				int
#define INVALID_SOCKET		(-1)
#define HWND				void*
#define __stdcall
#define stricmp     strcasecmp
#define strnicmp    strncasecmp
#endif

typedef struct _bgra {
    u8 b;
    u8 g;
    u8 r;
    u8 a;
}bgra;

typedef struct _yuvx {
    u8 y;
    u8 u;
    u8 v;
    u8 x;
}yuvx;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//YC_EXPORT, YC_DEPRECATED, YC_UNUSED
#if defined(YC_STATICLIB) || defined(YC_SOURCELIB)
#define YC_EXPORT
#elif defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
#if defined(YC_DYNAMICLIB) || defined(YC_EXPORTS)
#define YC_EXPORT			__declspec(dllexport)
#else
#define YC_EXPORT			__declspec(dllimport)
#endif
#define YC_DEPRECATED		__declspec(deprecated)
#define YC_UNUSED

#elif defined(__GNUC__)
#define YC_EXPORT			__attribute__((visibility("default")))
#define YC_DEPRECATED		__attribute__((deprecated))
#define YC_UNUSED			__attribute__((visibility("unused")))

#else
#define YC_EXPORT
#define YC_DEPRECATED
#define YC_UNUSED
#endif

//
#define SDK_API			YC_EXPORT
#define SDK_EXPORT		YC_EXPORTS

//
#define YC_INLINE		static inline

//
#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

//
#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
//C4018: signed/unsigned mismatch
//C4200: zero-sized array in struct/union
//C4244: 's32' to 'float'
//C4267: 'u32' to 's32'
//C4305: 'double' to 'float'
//C4819: unicode
//C4838: 's32' to 'u32'
//C4996: _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4018 4200 4244 4267 4305 4819 4838 4996)
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//c++, namespace
#ifdef __cplusplus
#ifndef EXTERN_C
#define EXTERN_C			extern "C"
#endif

#ifndef BEGIN_EXTERN_C
#define BEGIN_EXTERN_C		extern "C" {
#endif

#ifndef END_EXTERN_C
#define END_EXTERN_C		}
#endif

#ifndef BEGIN_NAMESPACE
#define BEGIN_NAMESPACE(ns)	namespace ns {
#endif

#ifndef END_NAMESPACE
#define END_NAMESPACE(ns)   }
#endif

#ifndef USING_NAMESPACE
#define USING_NAMESPACE(ns) using namespace ns;
#endif

//delete
#define YC_SAFE_DELETE(p)  do {if (p) {delete (p); (p) = nullptr;}} while(0)
#define YC_SAFE_DELETE_ARRAY(p) do {if (p) {delete[] (p); (p) = nullptr;}} while(0)
#define YC_SAFE_RELEASE(p) do {if (p) {(p)->Release(); (p) = nullptr;}} while(0)

#else
#define EXTERN_C			extern
#define BEGIN_EXTERN_C
#define END_EXTERN_C

#define BEGIN_NAMESPACE(ns)
#define END_NAMESPACE(ns)
#define USING_NAMESPACE(ns)

//bool
#define bool  s32
#define false 0
#define true  1

#endif//__cplusplus

#endif//YC_TYPE_H_
