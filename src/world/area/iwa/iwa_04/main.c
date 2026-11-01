#include "iwa_04.h"
#include "world/area/iwa/iwa_02.h"
#include "world/area/sbk/sbk_99.h"

EvtScript EVS_ExitWalk_iwa_02_2 = EVT_EXIT_WALK(60, $Iwa02, $iwa_02.Iwa04);
EvtScript EVS_ExitWalk_sbk_99_0 = EVT_EXIT_WALK(60, $DryDryDesert, $sbk_99.MtRugged);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_iwa_02_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_99_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_MT_RUGGED)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Call(ParentColliderToModel, COLLIDER_o962, MODEL_o962)
    Call(ParentColliderToModel, COLLIDER_o979, MODEL_o979)
    Call(ParentColliderToModel, COLLIDER_o980, MODEL_o980)
    Call(ParentColliderToModel, COLLIDER_o981, MODEL_o981)
    Call(ParentColliderToModel, COLLIDER_o982, MODEL_o982)
    Call(ParentColliderToModel, COLLIDER_o983, MODEL_o983)
    Call(ParentColliderToModel, COLLIDER_o984, MODEL_o984)
    Call(ParentColliderToModel, COLLIDER_o985, MODEL_o985)
    Call(ParentColliderToModel, COLLIDER_o992, MODEL_o992)
    Call(ParentColliderToModel, COLLIDER_o993, MODEL_o993)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
