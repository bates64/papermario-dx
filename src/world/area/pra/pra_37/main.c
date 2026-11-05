#include "pra_37.h"
#include "world/area/pra/pra_22.h"
#include "world/area/pra/pra_28.h"

export s32 map_init(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_MARIO_REFLECT_FLOOR;
    use_map_geometry("pra_10");
    return false;
}

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"

EvtScript EVS_ExitDoors_pra_22_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $SmallStatueRoom.index)
    Set(LVar1, COLLIDER_deilittsw)
    Set(LVar2, MODEL_o772)
    Set(LVar3, MODEL_o768)
    Set(LVar4, MODEL_o844)
    Set(LVar5, MODEL_o846)
    Exec(ExitSplitDoubleDoor)
    Wait(17)
    Call(GotoMap, $pra_22.PUpDDownHall)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_28_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $PUpDDownRoom.index)
    Set(LVar1, COLLIDER_deilittse)
    Set(LVar2, MODEL_o1019)
    Set(LVar3, MODEL_o1021)
    Set(LVar4, MODEL_o1020)
    Set(LVar5, MODEL_o1022)
    Exec(ExitSplitDoubleDoor)
    Wait(17)
    Call(GotoMap, $pra_28.PUpDDownHall)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_pra_22_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_28_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($SmallStatueRoom.index)
            Set(LVar2, MODEL_o772)
            Set(LVar3, MODEL_o768)
            Set(LVar4, MODEL_o844)
            Set(LVar5, MODEL_o846)
            ExecWait(EnterSplitDoubleDoor)
        CaseEq($PUpDDownRoom.index)
            Set(LVar2, MODEL_o1019)
            Set(LVar3, MODEL_o1021)
            Set(LVar4, MODEL_o1020)
            Set(LVar5, MODEL_o1022)
            ExecWait(EnterSplitDoubleDoor)
    EndSwitch
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    Exec(EVS_SetupMusic)
    Set(LVar0, REFLECTION_FLOOR_ONLY)
    Set(LVar1, GF_PRA_BrokeIllusion)
    Exec(EVS_SetupReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
