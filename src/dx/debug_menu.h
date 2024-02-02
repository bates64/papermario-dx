#include "common.h"
#include "dx/config.h"
#if DX_DEBUG_MENU || defined(DX_QUICK_LAUNCH_BATTLE)

#define DX_DEBUG_DUMMY_ID 0xDEAD

void dx_debug_menu_main();
void dx_debug_console_main();
void dx_debug_draw_collision();

b32 dx_debug_menu_is_open();
b32 dx_debug_should_hide_models();

void dx_debug_set_map_info(char* mapName, s32 entryID);
void dx_debug_set_battle_info(s32 battleID, char* stageName);

void dx_debug_begin_battle_with_IDs(s16 battle, s16 stage);

#define debug_print(text) dx_hashed_debug_printf(__FILE__,__LINE__,text)
#define debug_printf(fmt, args...) dx_hashed_debug_printf(__FILE__,__LINE__,fmt,args)

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

#endif
