/*******************************************************************************************************
* yc_platform.h
*
* 2022-11-21: init
*
*
*
********************************************************************************************************/
#ifndef YC_PLATFORM_H_
#define YC_PLATFORM_H_

#include "yc_type.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//c, headers
#include <assert.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <signal.h>

//os, headers
#ifdef OS_WIN

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <Winsock2.h>
#include <WS2tcpip.h>

#define yc_sleep(s)     Sleep((s) * 1000)
#define yc_msleep(ms)   Sleep(ms)
#define yc_usleep(us)   Sleep((us) / 1000)
#define yc_delay(ms)    yc_msleep(ms)
#define yc_mkdir(dir)   mkdir(dir)

//
#define XMALLOC(size,alignment)	_aligned_malloc(size,alignment)
#define XFREE(x)				_aligned_free(x)
#define fsync(fd)
#define fileno(f)		_fileno(f)
#define fseek64			_fseeki64
#define ftell64			_ftelli64


//access
#ifndef F_OK
#define F_OK            0
#endif
#ifndef X_OK
#define X_OK            (1<<0)
#endif
#ifndef W_OK
#define W_OK            (1<<1)
#endif
#ifndef R_OK
#define R_OK            (1<<2)
#endif

//stat
#ifndef S_ISREG
#define S_ISREG(st_mode) (((st_mode) & S_IFMT) == S_IFREG)
#endif
#ifndef S_ISDIR
#define S_ISDIR(st_mode) (((st_mode) & S_IFMT) == S_IFDIR)
#endif

#else
#include <unistd.h>
#include <dirent.h>		//mkdir,rmdir,chdir,getcwd

//socket
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netdb.h>		//gethostbyname

//
#include <sys/time.h>
#include <pthread.h>

//
#ifdef OS_ANDROID
#define HAVE_PTHREAD_MUTEX_TIMEDLOCK	0
#define HAVE_PTHREAD_SPIN_LOCK			0
#define HAVE_SEM_TIMEDWAIT				0
#else
#define HAVE_PTHREAD_MUTEX_TIMEDLOCK	1
#define HAVE_PTHREAD_SPIN_LOCK			1
#define HAVE_SEM_TIMEDWAIT				1
#endif

#define yc_sleep(s)     sleep(s)
#define yc_msleep(ms)   usleep((ms) * 1000)
#define yc_usleep(us)   usleep(us)
#define yc_delay(ms)    yc_msleep(ms)
#define yc_mkdir(dir)   mkdir(dir, 0777)

//
#define MAX_PATH          260
#define fseek64			fseek
#define ftell64			ftell


inline void* XMALLOC(u32 size, u32 alignment) {
    void* p;
    if (0 == posix_memalign(&p, alignment, size)) {
        return p;
    }
    else {
        return NULL;
    }
}
inline void XFREE(void* p) {
    free(p);
}
#endif//end OS_WIN

//
#if 1//HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

//
#if 1//HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#endif//YC_PLATFORM_H_
