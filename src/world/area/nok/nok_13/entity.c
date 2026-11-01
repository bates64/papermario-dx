#include "nok_13.h"
#include "entity.h"
#include "effects.h"

EvtScript EVS_BreakBlock_First = {
    IfEq(AB_NOK13_BlockPuzzleState, 0)
        Set(AB_NOK13_BlockPuzzleState, 1)
    EndIf
    Return
    End
};

EvtScript EVS_BreakBlock_Second = {
    IfEq(AB_NOK13_BlockPuzzleState, 1)
        Set(AB_NOK13_BlockPuzzleState, 2)
    EndIf
    Return
    End
};

EvtScript EVS_BreakBlock_Third = {
    IfEq(AB_NOK13_BlockPuzzleState, 2)
        Call(PlaySound, SOUND_CHIME_SOLVED_PUZZLE)
        Call(PlaySoundAt, SOUND_SPAWN_BLOCK, SOUND_SPACE_DEFAULT, 40, 60, -285)
        Set(AB_NOK13_BlockPuzzleState, 3)
        PlayEffect(EFFECT_SPARKLES, 0, $SparklesPos_1.pos.x, $SparklesPos_1.pos.y, $SparklesPos_1.pos.z, 10)
        Call(MakeMarkerEntity, $RedBlock_AttackFxB_1)
    EndIf
    Return
    End
};

EvtScript EVS_ReadSign_Directions = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_0178, 160, 40)
    Call(DisablePlayerInput, false)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Signpost_1)
    IfEq(GF_NOK13_BadgeBlock_AttackFXB, false)
        Set(AB_NOK13_BlockPuzzleState, 0)
        Call(MakeMarkerEntity, $BrickBlock_1)
        Call(MakeMarkerEntity, $BrickBlock_2)
        Call(MakeMarkerEntity, $BrickBlock_3)
    Else
        Call(MakeMarkerEntity, $BrickBlock_4)
        Call(MakeMarkerEntity, $BrickBlock_5)
        Call(MakeMarkerEntity, $BrickBlock_6)
        Call(MakeMarkerEntity, $RedBlock_AttackFxB_2)
    EndIf
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Call(MakeMarkerEntity, $Item_HoneySyrup_1)
    Return
    End
};
