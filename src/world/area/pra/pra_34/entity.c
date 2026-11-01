#include "pra_34.h"
#include "entity.h"

EvtScript EVS_Interact_Padlock = {
    Set(GF_PRA34_UnlockedDoor, true)
    BindTrigger(EVS_ExitDoors_pra_31_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_31_2, TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_PRA34_UnlockedDoor, false)
        Call(MakeMarkerEntity, $Padlock_1)
        Call(AssignScript, EVS_Interact_Padlock)
        Set(MV_FarPadlockEntityID, LVar0)
        Call(MakeMarkerEntity, $Padlock_2)
        Call(AssignScript, EVS_Interact_Padlock)
        Set(MV_NearPadlockEntityID, LVar0)
    EndIf
    Return
    End
};
