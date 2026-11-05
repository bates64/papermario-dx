#include "omo_04.h"
#include "world/area/omo/omo_03.h"

EvtScript EVS_ExitWalk_omo_03_1 = EVT_EXIT_WALK(60, $Omo03, $omo_03.Omo04);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_03_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    IfEq(GF_OMO04_SpawnedPeachChoice1, false)
        Call(MakeNpcs, true, KammySceneNPCs)
        Call(EnableNpcShadow, NPC_Goomba, false)
        Call(EnableNpcShadow, NPC_Clubba, false)
    Else
        IfEq(GF_OMO04_Item_Mushroom, false)
            Switch(GB_OMO_PeachChoice1)
                CaseEq(0)
                    Call(MakeNpcs, true, GoombaAmbushNPCs)
                CaseEq(1)
                    Call(MakeNpcs, true, ClubbaAmbushNPCs)
                CaseEq(2)
                    Call(MakeNpcs, true, DefaultNPCs)
                    Call(MakeMarkerEntity, $Item_Mushroom_1)
            EndSwitch
        Else
            Call(MakeNpcs, true, DefaultNPCs)
        EndIf
    EndIf
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupGizmos)
    ExecWait(EVS_SetupMusic)
    IfEq(GF_OMO04_SpawnedPeachChoice1, false)
        Exec(EVS_Scene_KammySetAmbush)
    Else
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};
