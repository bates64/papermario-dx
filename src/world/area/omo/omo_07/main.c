#include "omo_07.h"

EvtScript EVS_ExitWalk_omo_06_4 = EVT_EXIT_WALK(60, omo_07_ENTRY_0, "omo_06", omo_06_ENTRY_4);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_omo_06_4), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHY_GUYS_TOYBOX)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfEq(GF_OMO07_SpawnedPeachChoice2, false)
        Call(MakeNpcs, true, Ref(KammySceneNPCs))
        Call(EnableNpcShadow, NPC_Fuzzy, false)
        Call(EnableNpcShadow, NPC_HammerBros, false)
    Else
        IfEq(GF_OMO07_Item_ThunderRage, false)
            Switch(GB_OMO_PeachChoice2)
                CaseEq(0)
                    Call(MakeNpcs, true, Ref(FuzzyAmbushNPCs))
                CaseEq(1)
                    Call(MakeNpcs, true, Ref(HammerBrosAmbushNPCs))
                CaseEq(2)
                    Call(MakeNpcs, true, Ref(DefaultNPCs))
                    Call(MakeItemEntity, ITEM_THUNDER_RAGE, 1080, 0, 0, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_OMO07_Item_ThunderRage)
            EndSwitch
        Else
            Call(MakeNpcs, true, Ref(DefaultNPCs))
        EndIf
    EndIf
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupGizmos)
    ExecWait(EVS_SetupMusic)
    Exec(EVS_SetupShyGuyPool)
    IfEq(GF_OMO07_SpawnedPeachChoice2, false)
        Exec(EVS_Scene_KammySetAmbush)
        Wait(2)
    Else
        Set(LVar0, Ref(EVS_BindExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};
