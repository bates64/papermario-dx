#include "common.h"
#include "dx/config.h"
#if DX_DEBUG_MENU

void dx_debug_menu_push(void);
void dx_debug_menu_pop(void);
void dx_debug_menu_close(void);
void dx_render_debug_menu(void);

#endif

u8* dx_string_to_msg(u8* msg, const u8* str);
