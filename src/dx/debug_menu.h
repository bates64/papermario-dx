#include "common.h"
#include "dx/config.h"
#if DX_DEBUG_MENU

#define DX_DEBUG_DUMMY_ID 0xDEAD

void dx_debug_main();
void dx_debug_set_map_info(char* mapName, s32 entryID);
void dx_debug_set_battle_info(s32 battleID, char* stageName);

u8* dx_string_to_msg(u8* msg, const u8* str);

#endif
