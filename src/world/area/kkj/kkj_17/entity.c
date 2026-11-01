#include "kkj_17.h"

// immediately remove the item from Peach's inventory, keeping only the flag
EvtScript EVS_AutoRemoveDeepFocus = {
    Loop(0)
        IfEq(GF_KKJ17_Item_DeepFocus, true)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Wait(10)
    Call(RemoveItem, ITEM_DEEP_FOCUS_A)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_DeepFocusA_1)
    IfLt(GB_StoryProgress, STORY_CH8_REACHED_PEACHS_CASTLE)
        IfEq(GF_KKJ17_Item_DeepFocus, false)
            Exec(EVS_AutoRemoveDeepFocus)
        EndIf
    EndIf
    Return
    End
};
