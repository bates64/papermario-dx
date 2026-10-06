#include "kkj_19.h"

typedef struct IngredientSouce {
    /* 0x00 */ s32 itemID;
    /* 0x04 */ s32 colliderID;
    /* 0x08 */ s32 overrideDescMsg;
} IngredientSouce; // size = 0x0C

IngredientSouce IngredientSources[] = {
    { ITEM_BAKING_SUGAR,        COLLIDER_o101, MSG_NONE },
    { ITEM_BAKING_SALT,         COLLIDER_o102, MSG_NONE },
    { ITEM_BAKING_EGG,          COLLIDER_o103, MSG_NONE },
    { ITEM_BAKING_STRAWBERRY,   COLLIDER_o105, MSG_NONE },
    { ITEM_BAKING_CREAM,        COLLIDER_o106, MSG_NONE },
    { ITEM_BAKING_BUTTER,       COLLIDER_o107, MSG_NONE },
    { ITEM_BAKING_CLEANSER,     COLLIDER_o108, MSG_NONE },
    { ITEM_BAKING_WATER,        COLLIDER_o114, MSG_NONE },
    { ITEM_BAKING_FLOUR,        COLLIDER_o109, MSG_NONE },
    { ITEM_BAKING_MILK,         COLLIDER_o110, MSG_NONE },
};

s32 IngredientWindowsOpen = false;
s32 IngredientWindowsDismissTime = 0;
s32 IngredientWindowsIndex = 0;

API_CALLABLE(TryOpenIngredientWindows) {
    Bytecode* args = script->ptrReadPos;
    s32 canCheck;

    IngredientWindowsIndex = evt_get_variable(script, *args++);
    canCheck = evt_get_variable(nullptr, AF_KKJ19_CanTakeIngredients);

    if (canCheck == true) {
        IngredientWindowsOpen = true;
        IngredientWindowsDismissTime = 5;
    } else {
        IngredientWindowsOpen = false;
    }

    return ApiStatus_DONE2;
}

void worker_update_ingredient_windows(void) {
    if (IngredientWindowsOpen) {
        set_window_update(WIN_SHOP_ITEM_NAME, (s32)basic_window_update);
        set_window_update(WIN_SHOP_ITEM_DESC, (s32)basic_window_update);
    } else {
        set_window_update(WIN_SHOP_ITEM_NAME, (s32)basic_hidden_window_update);
        set_window_update(WIN_SHOP_ITEM_DESC, (s32)basic_hidden_window_update);
    }

    if (IngredientWindowsDismissTime > 0) {
        IngredientWindowsDismissTime--;
    } else {
        IngredientWindowsOpen = false;
    }
}

void draw_content_ingredient_name(
    MenuPanel* menu,
    s32 baseX, s32 baseY,
    s32 width, s32 height,
    s32 opacity, s32 darkening
) {
    IngredientSouce* ingredient = &IngredientSources[IngredientWindowsIndex];
    ItemData* item = &gItemTable[ingredient->itemID];
    s32 halfWidth = get_msg_width(item->nameMsg, 0) >> 1;

    draw_msg(item->nameMsg, baseX + 60 - halfWidth, baseY + 6, 255, 0, 0);
}

void draw_content_ingredient_desc(
    MenuPanel* menu,
    s32 baseX, s32 baseY,
    s32 width, s32 height,
    s32 opacity, s32 darkening
) {
    IngredientSouce* ingredient = &IngredientSources[IngredientWindowsIndex];
    ItemData* item = &gItemTable[ingredient->itemID];

    if (ingredient->overrideDescMsg != MSG_NONE) {
        draw_msg(ingredient->overrideDescMsg, baseX + 8, baseY, 255, 10, 0);
    } else {
        draw_msg(item->shortDescMsg, baseX + 8, baseY, 255, 10, 0);
    }
}

EvtScript EVS_TouchFloor_IngredientStation = {
    Call(TryOpenIngredientWindows, LVar0)
    Return
    End
};

WindowStyleCustom IngredientNameWS = {
    .background = {},
    .corners = {
        .imgData = ui_box_corners5_png,
        .fmt = G_IM_FMT_IA,
        .bitDepth = G_IM_SIZ_8b,
        .size1 = { 16, 8 },
        .size2 = { 16, 8 },
        .size3 = { 16, 8 },
        .size4 = { 16, 8 },
    },
    .opaqueCombineMode = gsDPSetCombineMode(PM_CC_30, PM_CC_BOX2_CYC2),
    .transparentCombineMode = gsDPSetCombineMode(PM_CC_31, PM_CC_BOX2_CYC2),
    .color1 = { 255, 183, 181, 255 },
    .color2 = { 122,  89,  63, 255 },
};

MenuWindowBP IngredientWindows[] = {
    {
        .windowID = WIN_SHOP_ITEM_NAME,
        .pos = { 100, 66 },
        .width = 120,
        .height = 28,
        .priority = WINDOW_PRIORITY_0,
        .fpDrawContents = &draw_content_ingredient_name,
        .tab = nullptr,
        .parentID = -1,
        .fpUpdate = { WINDOW_UPDATE_HIDE },
        .extraFlags = 0,
        .style = { .customStyle = &IngredientNameWS },
    },
    {
        .windowID = WIN_SHOP_ITEM_DESC,
        .pos = { 32, 184 },
        .width = 256,
        .height = 32,
        .priority = WINDOW_PRIORITY_0,
        .fpDrawContents = &draw_content_ingredient_desc,
        .tab = nullptr,
        .parentID = -1,
        .fpUpdate = { WINDOW_UPDATE_HIDE },
        .extraFlags = 0,
        .style = { -1 },
    }
};

API_CALLABLE(CreateIngredientInfoWindows) {
    s32 i;

    IngredientWindowsOpen = false;
    IngredientWindowsDismissTime = 0;
    IngredientWindowsIndex = 0;

    get_worker(create_worker_frontUI(worker_update_ingredient_windows, nullptr));
    setup_pause_menu_tab(IngredientWindows, ARRAY_COUNT(IngredientWindows));

    for (i = 0; i < ARRAY_COUNT(IngredientSources); i++) {
        bind_trigger_1(&EVS_TouchFloor_IngredientStation, TRIGGER_FLOOR_TOUCH, IngredientSources[i].colliderID, i, 0, 3);
    }

    return ApiStatus_DONE2;
}

EvtScript EVS_ExitDoor_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, kkj_19_ENTRY_0)
    Set(LVar1, COLLIDER_ttse)
    Set(LVar2, MODEL_o95)
    Set(LVar3, DOOR_SWING_IN)
    Exec(ExitSingleDoor)
    Wait(17)
    IfEq(GB_StoryProgress, STORY_INTRO)
        Call(GotoMap, Ref("kkj_00"), kkj_00_ENTRY_3)
    Else
        Call(GotoMap, Ref("kkj_10"), kkj_10_ENTRY_3)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoor_0), TRIGGER_WALL_PRESS_A, COLLIDER_ttse, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    IfEq(GB_StoryProgress, STORY_CH4_BEGAN_PEACH_MISSION)
        Exec(EVS_ManageBaking)
    Else
        Set(LVar0, kkj_19_ENTRY_0)
        Set(LVar2, MODEL_o95)
        Set(LVar3, DOOR_SWING_IN)
        ExecWait(EnterSingleDoor)
        Exec(EVS_BindExitTriggers)
    EndIf
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Switch(GB_StoryProgress)
        CaseEq(STORY_INTRO)
            Call(MakeNpcs, false, Ref(IntroNPCs))
        CaseEq(STORY_CH4_BEGAN_PEACH_MISSION)
            Call(MakeNpcs, false, Ref(PeachNPCs))
    EndSwitch
    Exec(EVS_SetupMusic)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Exec(EVS_EnterMap)
    Wait(1)
    IfEq(GB_StoryProgress, STORY_CH4_BEGAN_PEACH_MISSION)
        Call(CreateIngredientInfoWindows)
    EndIf
    Return
    End
};
