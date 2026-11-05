#include "pra_27.h"
#include "world/area/pra/pra_36.h"

export s32 map_init(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_MARIO_REFLECT_FLOOR;
    use_map_geometry("pra_05");
    return false;
}

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"

s32 DoorModelsL[] = { MODEL_o772, MODEL_o844, -1 };
s32 DoorModelsR[] = { MODEL_o768, MODEL_o846, -1 };

EvtScript EVS_ExitDoors_pra_36_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $PalaceKeyHall.index)
    Set(LVar1, COLLIDER_deilittsw)
    Set(LVar2, DoorModelsL)
    Set(LVar3, DoorModelsR)
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_36.PalaceKeyRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_pra_36_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, $PalaceKeyHall.index)
    Set(LVar2, DoorModelsL)
    Set(LVar3, DoorModelsR)
    ExecWait(BaseEnterDoor)
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Set(LVar0, REFLECTION_FLOOR_ONLY)
    Set(LVar1, GF_PRA_BrokeIllusion)
    Exec(EVS_SetupReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
