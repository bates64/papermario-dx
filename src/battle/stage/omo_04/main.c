#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

extern Formation fromation_slot_machine;
extern ActorBlueprint slot_machine_stop;
extern ActorBlueprint slot_machine_start;

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetTexPanner, MODEL_o409, TEX_PANNER_A)
    Thread
        Set(LVarE, 0)
        Loop(0)
            Add(LVarE, 0x8000)
            Call(SetTexPanOffset, TEX_PANNER_A, TEX_PANNER_MAIN, LVarE, 0)
            Wait(10)
        EndLoop
    EndThread
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_itigo,
    MODEL_kisya,
    MODEL_kusari,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "omo_tex",
    .bg = "omo_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
    .stageEnemyCount = 4,
    .stageFormation = &fromation_slot_machine,
};

Vec3i slot_machine_pos1 = { -49, 56, -68 };
Vec3i slot_machine_pos2 = { -13, 56, -68 };
Vec3i slot_machine_pos3 = { 20, 56, -68 };
Vec3i slot_machine_pos4 = { 53, 56, -68 };

Formation fromation_slot_machine = {
    RAW_ACTOR_BY_POS(slot_machine_start, slot_machine_pos1, 0, 0),
    RAW_ACTOR_BY_POS(slot_machine_stop, slot_machine_pos2, 0, 1),
    RAW_ACTOR_BY_POS(slot_machine_stop, slot_machine_pos3, 0, 2),
    RAW_ACTOR_BY_POS(slot_machine_stop, slot_machine_pos4, 0, 3),
};

#include "slot_machine.inc.c"
