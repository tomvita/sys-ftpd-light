#pragma once
#include <switch.h>

Result pauseInit();
void pauseExit();
bool isPaused();
void setPaused(bool newPaused);