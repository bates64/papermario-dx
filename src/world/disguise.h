#pragma once

#include "common.h"

typedef struct DisguiseAnims {
    /* 0x00 */ s32 idle;
    /* 0x04 */ s32 walk;
    /* 0x08 */ s32 run;
    /* 0x0C */ s32 talk;
    /* 0x10 */ s32 still;
    /* 0x14 */ s32 hold;
} DisguiseAnims; // size = 0x18

extern DisguiseAnims BasicPeachDisguiseAnims[4];
extern AnimID* PeachDisguiseExtraAnims[4];
