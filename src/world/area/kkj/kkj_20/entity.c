#include "kkj_20.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_LastStand = {
    Set(LVarA, ITEM_LAST_STAND)
    Call(DisablePlayerInput, true)
    Set(LVar0, LVarA)
    ExecWait(EVS_Chest_ShowGotItem)
    IfGe(GB_StoryProgress, STORY_CH8_REACHED_PEACHS_CASTLE)
        Call(AddItem, LVarA, LVar0)
    EndIf
    Set(GF_KKJ20_Chest_LastStand, true)
    Wait(15)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Chest), 95, 0, 0, 0, 0, MAKE_ENTITY_END)
    Call(AssignChestFlag, GF_KKJ20_Chest_LastStand)
    Call(AssignScript, Ref(EVS_OpenChest_LastStand))
    Return
    End
};
