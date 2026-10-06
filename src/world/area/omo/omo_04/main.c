#include "omo_04.h"

EvtScript EVS_ExitWalk_omo_03_1 = EVT_EXIT_WALK(60, omo_04_ENTRY_0, "omo_03", omo_03_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_omo_03_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHY_GUYS_TOYBOX)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfEq(GF_OMO04_SpawnedPeachChoice1, false)
        Call(MakeNpcs, true, Ref(KammySceneNPCs))
        Call(EnableNpcShadow, NPC_Goomba, false)
        Call(EnableNpcShadow, NPC_Clubba, false)
    Else
        IfEq(GF_OMO04_Item_Mushroom, false)
            Switch(GB_OMO_PeachChoice1)
                CaseEq(0)
                    Call(MakeNpcs, true, Ref(GoombaAmbushNPCs))
                CaseEq(1)
                    Call(MakeNpcs, true, Ref(ClubbaAmbushNPCs))
                CaseEq(2)
                    Call(MakeNpcs, true, Ref(DefaultNPCs))
                    Call(MakeItemEntity, ITEM_MUSHROOM, 1100, 0, 0, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_OMO04_Item_Mushroom)
            EndSwitch
        Else
            Call(MakeNpcs, true, Ref(DefaultNPCs))
        EndIf
    EndIf
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupGizmos)
    ExecWait(EVS_SetupMusic)
    IfEq(GF_OMO04_SpawnedPeachChoice1, false)
        Exec(EVS_Scene_KammySetAmbush)
    Else
        Set(LVar0, Ref(EVS_BindExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};
