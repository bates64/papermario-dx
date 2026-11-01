#include "iwa_02.h"
#include "world/area/iwa/iwa_01.h"
#include "world/area/iwa/iwa_04.h"

EvtScript EVS_ExitWalk_iwa_01_2 = EVT_EXIT_WALK(60, $Iwa01Lower, $iwa_01.Iwa02Lower);
EvtScript EVS_ExitWalk_iwa_01_3 = EVT_EXIT_WALK(60, $Iwa01Upper, $iwa_01.Iwa02Upper);
EvtScript EVS_ExitWalk_iwa_04_0 = EVT_EXIT_WALK(60, $Iwa04, $iwa_04.Iwa02);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_iwa_01_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_iwa_01_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(EVS_ExitWalk_iwa_04_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_MT_RUGGED)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Call(SetMusic, 0, SONG_MT_RUGGED, 0, VOL_LEVEL_FULL)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt1, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};
