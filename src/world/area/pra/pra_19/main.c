#include "pra_19.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"
#include "../common/GlassShimmer.inc.c"

s32 DoorModelsL[] = { MODEL_o772, MODEL_o844, -1 };
s32 DoorModelsR[] = { MODEL_o768, MODEL_o846, -1 };

EvtScript EVS_ExitDoor_pra_35_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_19_ENTRY_0)
    Set(LVar1, COLLIDER_deilittsw)
    Set(LVar2, Ref(DoorModelsL))
    Set(LVar3, Ref(DoorModelsR))
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_35"), pra_35_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_pra_20_0 = EVT_EXIT_WALK(60, pra_19_ENTRY_1, "pra_20", pra_20_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoor_pra_35_1), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    IfGe(GB_StoryProgress, STORY_CH7_DEFEATED_KOOPER_DUPLIGHOSTS)
        BindTrigger(Ref(EVS_ExitWalk_pra_20_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilise, 1, 0)
    EndIf
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_19_ENTRY_0)
            Set(LVar2, Ref(DoorModelsL))
            Set(LVar3, Ref(DoorModelsR))
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(pra_19_ENTRY_1)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    Exec(EVS_SetupMusic)
    IfGe(GB_StoryProgress, STORY_CH7_DEFEATED_KOOPER_DUPLIGHOSTS)
        Call(EnableModel, MODEL_o1024, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o1054, COLLIDER_FLAGS_UPPER_MASK)
    Else
        Call(EnableModel, MODEL_o1026, false)
    EndIf
    Set(LVar0, MODEL_o945)
    Set(LVar1, MODEL_o947)
    Set(LVar2, TEX_PANNER_0)
    Exec(EVS_GlassShimmer)
    Set(LVar0, REFLECTION_FLOOR_WALL)
    Set(LVar1, true) // disable reflections in this room
    Exec(EVS_SetupReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
