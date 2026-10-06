#include "nok_04.h"

EvtScript EVS_ExitWalk_nok_03_1 = EVT_EXIT_WALK(60, nok_04_ENTRY_0, "nok_03", nok_03_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_nok_03_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deilisw, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_KOOPA_VILLAGE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(AF_NOK04_PlayingGame, false)
    Set(AF_NOK04_BattleStarted, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o147, COLLIDER_FLAGS_UPPER_MASK)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Set(LVar0, TREE_0)
    BindTrigger(Ref(EVS_HitTree), TRIGGER_WALL_HAMMER, COLLIDER_o59, 1, 0)
    Set(LVar0, TREE_1)
    BindTrigger(Ref(EVS_HitTree), TRIGGER_WALL_HAMMER, COLLIDER_o58, 1, 0)
    Set(LVar0, TREE_2)
    BindTrigger(Ref(EVS_HitTree), TRIGGER_WALL_HAMMER, COLLIDER_o57, 1, 0)
    Set(LVar0, TREE_3)
    BindTrigger(Ref(EVS_HitTree), TRIGGER_WALL_HAMMER, COLLIDER_o56, 1, 0)
    Exec(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitsw, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
