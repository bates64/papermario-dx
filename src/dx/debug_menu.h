#ifndef _DX_DEBUG_MENU_H
#define _DX_DEBUG_MENU_H

#include "common.h"
#include "dx/config.h"
#if DX_DEBUG_MENU || defined(DX_QUICK_LAUNCH_BATTLE)

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#define DX_DEBUG_DUMMY_ID 0xDEAD

typedef enum DebugCheat {
    DEBUG_CHEAT_GOD_MODE,
    DEBUG_CHEAT_SPEED_MODE,
    DEBUG_CHEAT_FLY,
    DEBUG_CHEAT_IGNORE_WALLS,
    DEBUG_CHEAT_HIGH_JUMP,
} DebugCheat;

void dx_debug_menu_main();
void dx_debug_console_main();
void dx_debug_draw_collision();

bool dx_debug_menu_is_open();
bool dx_debug_should_hide_models();
bool dx_debug_is_cheat_enabled(DebugCheat cheat);

void dx_debug_set_map_info(const char* mapName, s32 entryID);
void dx_debug_set_battle_info(s32 battleID, char* stageName);

void dx_debug_begin_battle_with_IDs(s16 battle, s16 stage);

void dx_debug_evt_force_detach(Evt* evt);
void dx_debug_evt_reset();

enum DebugEvtStep {
    DEBUG_EVT_STEP_NONE,
    DEBUG_EVT_STEP_ONCE,
    DEBUG_EVT_STEP_OVER,
};

#define DEBUG_CONSOLE_MSG_BUF_SIZE 85

typedef struct DebugConsoleLine {
    u32 hash;
    s32 timeLeft;
    u8 buf[DEBUG_CONSOLE_MSG_BUF_SIZE];
    char asciiBuf[DEBUG_CONSOLE_MSG_BUF_SIZE];
} DebugConsoleLine;

extern DebugConsoleLine *DebugConsole[8];

void dx_hashed_debug_printf(const char* filename, s32 line, const char* fmt, ...);

#define debug_print(text) dx_hashed_debug_printf(__FILE__,__LINE__,text)
#define debug_printf(fmt, args...) dx_hashed_debug_printf(__FILE__,__LINE__,fmt,##args)

#define DebugPrint(text) Call(_dxDebugIntPrintf, Ref(__FILE__), __LINE__, Ref(text), 0)
#define DebugPrintf(args...) VFUNC(DebugPrintf, args)
#define DebugFloatPrintf(args...) VFUNC(DebugFloatPrintf, args)

API_CALLABLE(_dxDebugIntPrintf);
#define DebugPrintf1(text) \
    Call(_dxDebugIntPrintf, Ref(__FILE__), __LINE__, Ref(text), 0, 0, 0, 0, 0, 0, 0)
#define DebugPrintf2(text, a) \
    Call(_dxDebugIntPrintf, Ref(__FILE__), __LINE__, Ref(text), a, 0, 0, 0, 0, 0, 0)
#define DebugPrintf3(text, a, b) \
    Call(_dxDebugIntPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, 0, 0, 0, 0, 0)
#define DebugPrintf4(text, a, b, c) \
    Call(_dxDebugIntPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, c, 0, 0, 0, 0)
#define DebugPrintf5(text, a, b, c, d) \
    Call(_dxDebugIntPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, c, d, 0, 0, 0)
#define DebugPrintf6(text, a, b, c, d, e) \
    Call(_dxDebugIntPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, c, d, e, 0, 0)
#define DebugPrintf7(text, a, b, c, d, e, f) \
    Call(_dxDebugIntPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, c, d, e, f, 0)
#define DebugPrintf8(text, a, b, c, d, e, f, g) \
    Call(_dxDebugIntPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, c, d, e, f, g)

API_CALLABLE(_dxDebugFloatPrintf);
#define DebugFloatPrintf1(text) \
    Call(_dxDebugFloatPrintf, Ref(__FILE__), __LINE__, Ref(text), 0, 0, 0, 0, 0, 0, 0)
#define DebugFloatPrintf2(text, a) \
    Call(_dxDebugFloatPrintf, Ref(__FILE__), __LINE__, Ref(text), a, 0, 0, 0, 0, 0, 0)
#define DebugFloatPrintf3(text, a, b) \
    Call(_dxDebugFloatPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, 0, 0, 0, 0, 0)
#define DebugFloatPrintf4(text, a, b, c) \
    Call(_dxDebugFloatPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, c, 0, 0, 0, 0)
#define DebugFloatPrintf5(text, a, b, c, d) \
    Call(_dxDebugFloatPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, c, d, 0, 0, 0)
#define DebugFloatPrintf6(text, a, b, c, d, e) \
    Call(_dxDebugFloatPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, c, d, e, 0, 0)
#define DebugFloatPrintf7(text, a, b, c, d, e, f) \
    Call(_dxDebugFloatPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, c, d, e, f, 0)
#define DebugFloatPrintf8(text, a, b, c, d, e, f, g) \
    Call(_dxDebugFloatPrintf, Ref(__FILE__), __LINE__, Ref(text), a, b, c, d, e, f, g)

#ifdef _LANGUAGE_C_PLUS_PLUS
} // extern "C"
#endif

#else

#define debug_print(text)
#define debug_printf(fmt, args...)

#endif
#endif // _DX_DEBUG_MENU_H
