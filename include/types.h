#pragma once

#include "ultra64.h"

/// Linker symbol address, as in `ld_addrs.h`.
typedef u8 Addr[];

#define MSG_PTR u8*
#define IMG_PTR u8*
#define PAL_PTR u16*

#define MSG_BIN u8
#define IMG_BIN u8
#define PAL_BIN u16

typedef s32 b32;
typedef s16 b16;
typedef s8 b8;

typedef s32 HitID;
typedef u32 AnimID;
typedef s32 HudElemID;
typedef s32 MsgID;
