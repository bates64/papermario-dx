#include "kzn_07.h"
#include "effects.h"
#include "entity.h"

API_CALLABLE(NotifyChestDone) {
    get_entity_by_index(script->varTable[0])->dataBuf.chest->gotItemDone = true;
    return ApiStatus_DONE2;
}

EvtScript EVS_MonitorChestStatus = {
    IfEq(GF_KZN07_GiantChest, false)
        Label(10)
        IfEq(GF_KZN07_GiantChest, false)
            Wait(1)
            Goto(10)
        EndIf
        Wait(60)
        Exec(EVS_PlayUpgradeFanfare)
        Call(ShowMessageAtScreenPos, MSG_Menus_0186, 160, 40)
        // LVar0 is silently passed into this function, having been set by MakeEntity
        // in EVS_MakeEntities just before this script was executed
        Call(NotifyChestDone)
        Set(GB_StoryProgress, STORY_CH5_GOT_ULTRA_HAMMER)
    EndIf
    Return
    End
};

EvtScript EVS_OnBreakBlock = {
    Set(GF_KZN07_Hammer3Block, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $GiantChest)
    Exec(EVS_MonitorChestStatus)
    IfEq(GF_KZN07_Hammer3Block, false)
        Call(MakeMarkerEntity, $Hammer3BlockWideZ_1)
    EndIf
    Call(CreatePushBlockGrid, 0, 15, 5, -62, 0, 35, 0)
    Call(SetPushBlockFallEffect, 0, PushBlockFallCallback_Gravity)
    Call(SetPushBlock, 0, 8, 1, PUSH_GRID_BLOCK)
    Call(SetPushBlock, 0, 11, 4, PUSH_GRID_BLOCK)
    Return
    End
};
