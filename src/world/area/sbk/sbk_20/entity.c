#include "sbk_20.h"
#include "effects.h"
#include "entity.h"

EvtScript EVS_OnHitInertBlock = {
    Add(MV_BlockHitCounter, 1)
    Switch(MV_BlockHitCounter)
        CaseEq(1)
            IfEq(GF_SBK20_ItemBlock_Mushroom, false)
                Call(PlaySound, SOUND_CHIME_SOLVED_PUZZLE)
                Call(PlaySoundAt, SOUND_SPAWN_BLOCK, SOUND_SPACE_DEFAULT, -80, 60, -200)
                PlayEffect(EFFECT_SPARKLES, 0, $SparklesPos_1.pos.x, $SparklesPos_1.pos.y, $SparklesPos_1.pos.z, 10)
                Call(MakeMarkerEntity, $YellowBlock_Mushroom_1)
            EndIf
        CaseEq(10)
            IfEq(GF_SBK20_ItemBlock_SuperShroom, false)
                Call(PlaySound, SOUND_CHIME_SOLVED_PUZZLE)
                Call(PlaySoundAt, SOUND_SPAWN_BLOCK, SOUND_SPACE_DEFAULT, -180, 60, -200)
                PlayEffect(EFFECT_SPARKLES, 0, $SparklesPos_2.pos.x, $SparklesPos_2.pos.y, $SparklesPos_2.pos.z, 10)
                Call(MakeMarkerEntity, $YellowBlock_SuperShroom_1)
            EndIf
        CaseEq(100)
            IfEq(GF_SBK20_ItemBlock_UltraShroom, false)
                Call(PlaySound, SOUND_CHIME_SOLVED_PUZZLE)
                Call(PlaySoundAt, SOUND_SPAWN_BLOCK, SOUND_SPACE_DEFAULT, -130, 60, -150)
                PlayEffect(EFFECT_SPARKLES, 0, $SparklesPos_3.pos.x, $SparklesPos_3.pos.y, $SparklesPos_3.pos.z, 10)
                Call(MakeMarkerEntity, $YellowBlock_UltraShroom_1)
            EndIf
    EndSwitch
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $InertYellowBlock_1)
    IfEq(GF_SBK20_ItemBlock_Mushroom, true)
        Call(MakeMarkerEntity, $YellowBlock_Mushroom_2)
    EndIf
    IfEq(GF_SBK20_ItemBlock_SuperShroom, true)
        Call(MakeMarkerEntity, $YellowBlock_SuperShroom_2)
    EndIf
    IfEq(GF_SBK20_ItemBlock_UltraShroom, true)
        Call(MakeMarkerEntity, $YellowBlock_UltraShroom_2)
    EndIf
    Return
    End
};
