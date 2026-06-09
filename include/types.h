#ifndef _TYPES_H_
#define _TYPES_H_

#include "ultra64.h"

#define UNK_PTR void*
#define UNK_FUN_PTR(name) void(*name)(void)

typedef char* (*PrintCallback)(void*, const char*, u32);

/// Linker symbol address, as in `ld_addrs.h`.
typedef u8 Addr[];

/// Terminates an extraAnimationList
#define ANIM_LIST_END -1

#endif
