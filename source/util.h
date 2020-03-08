#pragma once
#include <switch.h>

#define R_ASSERT(res_expr) \
    ({ \
        const Result rc = (res_expr); \
        if (R_FAILED(rc)) {  \
            fatalThrow(rc); \
        } \
    })


Result pauseInit();
void pauseExit();
bool isPaused();
void setPaused(bool newPaused);