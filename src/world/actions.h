#ifndef _WORLD_ACTIONS_H_
#define _WORLD_ACTIONS_H_

#include "common.h"

typedef void (*ActionUpdate)(void);
typedef const char* ActionFamily;
typedef const char* ActionEntry;

typedef struct Action {
    /* 0x00 */ ActionFamily family;
    /* 0x04 */ ActionEntry entry;
    /* 0x08 */ s8 enabledForPeach;
    /* 0x09 */ PAD(3);
} Action; // size = 0x0C

extern Action PlayerActionsTable[ACTION_COUNT];

void unload_player_action(void);

#endif
