#include "util.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <unistd.h>

#include <switch.h>

static bool inputThreadRunning = true;

void inputPoller()
{
    do
    {
        hidScanInput();
        u64 kDown = 0;
        u64 kHeld = 0;
        for (u8 controller = 0; controller != 8; controller++)
        {
            kDown |= hidKeysDown(controller);
            kHeld |= hidKeysHeld(controller);
        }

        if ((kDown & KEY_PLUS || kDown & KEY_MINUS || kDown & KEY_X) && (kHeld & KEY_PLUS && kHeld & KEY_MINUS && kHeld & KEY_X))
            setPaused(!isPaused());
        svcSleepThread(1e+8);
    } while (inputThreadRunning);
}


static bool paused = false;
static Mutex pausedMutex = 0;
static Thread pauseThread;

Result pauseInit() {
    Result rc;
    mutexLock(&pausedMutex);

    FILE *should_pause_file = fopen("/config/sys-ftpd/ftpd_paused", "r");
    if (should_pause_file != NULL) {
        paused = true;
        fclose(should_pause_file);
    }

    inputThreadRunning = true;

    rc = threadCreate(&pauseThread, inputPoller, NULL, NULL, 0x300, 0x3B, -2);
    if (R_FAILED(rc))
        goto exit;

    rc = threadStart(&pauseThread);
    if (R_FAILED(rc))
        goto exit;

exit: 
    mutexUnlock(&pausedMutex);
    return rc;
}

void pauseExit()
{
    inputThreadRunning = false;
    threadWaitForExit(&pauseThread);
    threadClose(&pauseThread);
}


bool isPaused() {
    mutexLock(&pausedMutex);
    bool ret = paused;
    mutexUnlock(&pausedMutex);
    return ret;
}

void setPaused(bool newPaused) {
    mutexLock(&pausedMutex);
    paused = newPaused;
    if(paused) {
        FILE *should_pause_file = fopen("/config/sys-ftpd/ftpd_paused", "w");
        fclose(should_pause_file);
    } else {
        unlink("/config/sys-ftpd/ftpd_paused");
    }
    mutexUnlock(&pausedMutex);
}
