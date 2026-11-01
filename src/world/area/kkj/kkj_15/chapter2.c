#include "kkj_15.h"
#include "world/area/kkj/kkj_11.h"

EvtScript EVS_ExtiDoor_Chapter2 = {
    IfEq(AF_KKJ_PeachSawGrandHall, false)
        Call(DisablePlayerInput, true)
        Call(DisablePartnerAI, true)
        Call(SpeakToPlayer, NPC_PARTNER, ANIM_Twink_Talk, ANIM_Twink_Idle, 0, MSG_Peach_006B)
        Call(EnablePartnerAI)
        Call(DisablePlayerInput, false)
    EndIf
    Set(LVar0, $UpperHall.index)
    Set(LVar1, COLLIDER_tte)
    Set(LVar2, MODEL_o2)
    Set(LVar3, DOOR_SWING_IN)
    Exec(ExitSingleDoor)
    Wait(17)
    IfEq(AF_KKJ_PeachSawGrandHall, false)
        Call(GotoMap, $kkj_11.PassageOutletFirst)
    Else
        Call(GotoMap, $kkj_11.PassageOutlet)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript EVS_SetupChapter2 = {
    BindTrigger(EVS_ExtiDoor_Chapter2, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Return
    End
};
