#include "kzn_07.h"
#include "effects.h"
#include "entity.h"


API_CALLABLE(N(NotifyChestDone)) {
    get_entity_by_index(script->varTable[0])->dataBuf.chest->gotItemDone = true;
    return ApiStatus_DONE2;
}

EvtScript N(EVS_MonitorChestStatus) = {
    IfEq(GF_KZN07_GiantChest, false)
        Label(10)
        IfEq(GF_KZN07_GiantChest, false)
            Wait(1)
            Goto(10)
        EndIf
        Wait(60)
        Exec(N(EVS_PlayUpgradeFanfare))
        Call(ShowMessageAtScreenPos, MSG_Menus_0186, 160, 40)
        // LVar0 is silently passed into this function, having been set by MakeEntity
        // in EVS_MakeEntities just before this script was executed
        Call(N(NotifyChestDone))
        Set(GB_StoryProgress, STORY_CH5_GOT_ULTRA_HAMMER)
    EndIf
    Return
    End
};

EvtScript N(EVS_OnBreakBlock) = {
    Set(GF_KZN07_Hammer3Block, true)
    Return
    End
};

EvtScript N(EVS_MakeEntities) = {
    Call(MakeEntity, Ref(Entity_GiantChest), 0, 45, -290, 0, ITEM_ULTRA_HAMMER, MAKE_ENTITY_END)
    Call(AssignChestFlag, GF_KZN07_GiantChest)
    Exec(N(EVS_MonitorChestStatus))
    IfEq(GF_KZN07_Hammer3Block, false)
        Call(MakeEntity, Ref(Entity_Hammer3BlockWideZ), 175, 35, -185, 0, MAKE_ENTITY_END)
        Call(AssignScript, Ref(N(EVS_OnBreakBlock)))
    EndIf
    Call(CreatePushBlockGrid, 0, 15, 5, -62, 0, 35, 0)
    Call(SetPushBlockFallEffect, 0, Ref(PushBlockFallCallback_Gravity))
    Call(SetPushBlock, 0, 8, 1, PUSH_GRID_BLOCK)
    Call(SetPushBlock, 0, 11, 4, PUSH_GRID_BLOCK)
    Return
    End
};
