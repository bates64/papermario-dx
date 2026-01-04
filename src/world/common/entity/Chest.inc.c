#include "common.h"

EvtScript N(EVS_Chest_ShowGotItem) = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_FULL)
    Wait(40)
    Call(ShowGotItem, LVar0, false, 0)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Return
    End
};

EvtScript N(EVS_Chest_GetItem) = {
    Call(DisablePlayerInput, true)
    Set(LVar0, LVarA)
    IfNe(LVarA, ITEM_NONE)
        ExecWait(N(EVS_Chest_ShowGotItem))
    EndIf
    Call(AddItem, LVarA, LVar0)
    Wait(15)
    Call(DisablePlayerInput, false)
    Return
    End
};

#define EVT_OPEN_CHEST(item, flag) \
    { \
        Set(LVarA, item) \
        Set(flag, true) \
        ExecWait(N(EVS_Chest_GetItem)) \
        Return \
        End \
    }
