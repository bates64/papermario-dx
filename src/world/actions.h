#pragma once

#include "common.h"

typedef struct Action {
    /* 0x00 */ void (*update)(void);
    /* 0x04 */ void* dmaStart;
    /* 0x08 */ void* dmaEnd;
    /* 0x0C */ s8 flag;
} Action; // size = 0x10

extern Action PlayerActionsTable[39];
