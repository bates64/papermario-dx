#include "tik_06.h"
#include "world/area/tik/tik_08.h"
#include "entity.h"

EvtScript EVS_MonitorPlayerFallDown = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfGt(LVar0, -230)
            Goto(0)
        EndIf
        IfGe(LVar1, -10)
            Goto(0)
        EndIf
    Call(GrabCamera, CAM_DEFAULT, LVar2, LVar3, LVar4, LVar5)
    Label(1)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfGt(LVar1, -70)
            Goto(1)
        EndIf
    Call(GotoMap, $tik_08.BoardedFloor)
    Wait(100)
    Return
    End
};

EvtScript EVS_OnPound_BoardedFloor = {
    Set(GF_TIK02_BoardedFloor, true)
    Exec(EVS_MonitorPlayerFallDown)
    Return
    End
};

EvtScript EVS_OnSmash_Block1 = {
    Set(GF_TIK02_Hammer1Block, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o93, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_OnSmash_Block2 = {
    Set(GF_TIK02_Hammer2Block, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o90, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(EnableModel, MODEL_o49, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o49, COLLIDER_FLAGS_UPPER_MASK)
    IfEq(GF_TIK02_BoardedFloor, false)
        Call(MakeMarkerEntity, $BoardedFloor_1)
    Else
        Exec(EVS_MonitorPlayerFallDown)
    EndIf
    IfEq(GF_TIK02_Hammer1Block, false)
        Call(MakeMarkerEntity, $Hammer1Block_1)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o93, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    IfEq(GF_TIK02_Hammer2Block, false)
        Call(MakeMarkerEntity, $Hammer2Block_1)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o90, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Return
    End
};
