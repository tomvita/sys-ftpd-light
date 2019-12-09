#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <unistd.h>

#include <switch.h>

#include "mp3.h"

void fatalLater(Result err)
{
    Handle srv;

    while (R_FAILED(smGetServiceOriginal(&srv, smEncodeName("fatal:u"))))
    {
        // wait one sec and retry
        svcSleepThread(1000000000L);
    }

    // fatal is here time, fatal like a boss
    fatalThrow(err);
}


bool paused = false;
static Mutex pausedMutex;
void pauseInit() {
    mutexInit(&pausedMutex);
    mutexLock(&pausedMutex);
    FILE *should_pause_file = fopen("/config/sys-ftpd/ftpd_paused", "r");
    if (should_pause_file != NULL) {
        paused = true;
        fclose(should_pause_file);
    }
    mutexUnlock(&pausedMutex);
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
        playMp3("/config/sys-ftpd/pauseon.mp3");
    } else {
        unlink("/config/sys-ftpd/ftpd_paused");
        playMp3("/config/sys-ftpd/pauseoff.mp3");
    }
    mutexUnlock(&pausedMutex);
}
