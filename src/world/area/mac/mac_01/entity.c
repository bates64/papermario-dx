#include "mac_01.h"
#include "entity.h"

EvtScript EVS_Inspect_StreetSign = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_0170, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfLt(GB_StoryProgress, STORY_EPILOGUE)
        Call(MakeMarkerEntity, $SavePoint_1)
    EndIf
    BindTrigger(EVS_Inspect_StreetSign, TRIGGER_WALL_PRESS_A, COLLIDER_o406, 1, 0)
    Return
    End
};
