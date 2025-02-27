#pragma once
#include <switch.h>

#define sizearray(a) (sizeof(a) / sizeof((a)[0]))

#define TITLE_ID 0x420000000000000D
#define CONFIGPATH "/config/sys-ftpd-10k/config.ini"

#define R_ASSERT(res_expr)            \
    ({                                \
        const Result rc = (res_expr); \
        if (R_FAILED(rc))             \
        {                             \
            fatalThrow(rc);           \
        }                             \
    })

Result pauseInit();
void pauseExit();
bool isPaused();
void setPaused(bool newPaused);
bool isHidHandheld();
void initPads();