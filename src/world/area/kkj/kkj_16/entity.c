#include "kkj_16.h"
#include "entity.h"

// immediately remove the item from Peach's inventory, keeping only the flag
EvtScript EVS_AutoRemovePowerRush = {
    Loop(0)
        IfEq(GF_KKJ16_Item_PowerRush, true)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Wait(10)
    Call(RemoveItem, ITEM_POWER_RUSH)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_LifeShroom_1)
    Call(MakeMarkerEntity, $Item_PowerRush_1)
    IfLt(GB_StoryProgress, STORY_CH8_REACHED_PEACHS_CASTLE)
        IfEq(GF_KKJ16_Item_PowerRush, false)
            Exec(EVS_AutoRemovePowerRush)
        EndIf
    EndIf
    Return
    End
};
