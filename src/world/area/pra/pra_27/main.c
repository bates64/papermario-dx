#include "pra_27.h"

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
    Set(LVar0, pra_27_ENTRY_0)
    Set(LVar1, COLLIDER_deilittsw)
    Set(LVar2, Ref(DoorModelsL))
    Set(LVar3, Ref(DoorModelsR))
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_36"), pra_36_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_pra_36_1), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, pra_27_ENTRY_0)
    Set(LVar2, Ref(DoorModelsL))
    Set(LVar3, Ref(DoorModelsR))
    ExecWait(BaseEnterDoor)
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
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
