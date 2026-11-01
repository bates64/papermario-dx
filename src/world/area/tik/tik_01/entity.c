#include "tik_01.h"
#include "world/area/dro/dro_01.h"
#include "world/area/kmr/kmr_02.h"
#include "world/area/nok/nok_02.h"
#include "entity.h"

EvtScript EVS_SpawnSwitch = {
    Call(GetPlayerPos, LVar2, LVar3, LVar4)
    Add(LVar2, -75)
    Call(PlaySoundAt, SOUND_FALL_QUICK, SOUND_SPACE_DEFAULT, LVar2, 200, 25)
    Call(MakeLerp, 200, -10, 25, EASING_QUADRATIC_IN)
    Loop(0)
        Call(UpdateLerp)
        Call(SetEntityPosition, MV_EntityID_Switch, LVar2, LVar0, 25)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(PlaySoundAt, SOUND_OBJECT_LAND, SOUND_SPACE_DEFAULT, LVar2, LVar0, 25)
    Call(ShakeCam, CAM_DEFAULT, 0, 5, 1.0)
    Wait(10)
    Return
    End
};

EvtScript EVS_SmashBlock = {
    Set(GF_TIK01_Hammer2Block, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o64, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_GotoMap_kmr_02_3 = {
    Call(GotoMap, $kmr_02.WarpPipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_GotoMap_nok_02_2 = {
    Call(GotoMap, $nok_02.Pipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_GotoMap_dro_01_2 = {
    Call(GotoMap, $dro_01.Pipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_OnSwitchActivate = {
    Wait(10)
    Call(PlaySound, SOUND_GROW)
    Set(GF_TIK01_WarpPipes, true)
    Unbind
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_TIK01_Hammer2Block, false)
        Call(MakeMarkerEntity, $Hammer2Block_1)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o64, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o63, COLLIDER_FLAGS_UPPER_MASK)
    IfEq(GF_TIK01_WarpPipes, false)
        Call(MakeEntity, Entity_BlueSwitch, NPC_DISPOSE_LOCATION, 0, MAKE_ENTITY_END)
        Call(AssignSwitchFlag, EVT_INDEX_OF_AREA_FLAG(AF_TIK01_Switch_WarpPipe))
        Set(MV_EntityID_Switch, LVar0)
        BindTrigger(EVS_OnSwitchActivate, TRIGGER_AREA_FLAG_SET, AF_TIK01_Switch_WarpPipe, 1, 0)
        IfEq(GF_TIK01_Defeated_Blooper, true)
            Call(SetEntityPosition, MV_EntityID_Switch, 125, -10, 25)
        EndIf
    EndIf
    Call(MakeMarkerEntity, $BlueWarpPipe_1)
    Call(MakeMarkerEntity, $BlueWarpPipe_2)
    Call(MakeMarkerEntity, $BlueWarpPipe_3)
    Return
    End
};
