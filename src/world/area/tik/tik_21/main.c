#include "tik_21.h"
#include "world/area/tik/tik_14.h"
#include "world/area/tik/tik_20.h"
#include "world/area/tik/tik_22.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_tik_20_1 = EVT_EXIT_WALK(60, $SpikesRoom, $tik_20.HiddenBlocksRoom);

EvtScript EVS_ExitDoors_tik_22_0 =
    EVT_EXIT_DOUBLE_DOOR($PathToShiverCity, $tik_22.HiddenBlocksRoom, COLLIDER_tte, MODEL_o46, MODEL_o47);

EvtScript EVS_GotoMap_tik_14_0 = {
    Call(GotoMap, $tik_14.HiddenBlocksRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_14_0 = EVT_EXIT_PIPE_VERTICAL($RipCheatoAntechamber, COLLIDER_o49, EVS_GotoMap_tik_14_0);

EvtScript EVS_ShowMessage_DoorLocked = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_0177, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_tik_20_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    IfGe(GB_StoryProgress, STORY_CH7_INVITED_TO_STARBORN_VALLEY)
        BindTrigger(EVS_ExitDoors_tik_22_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Else
        BindTrigger(EVS_ShowMessage_DoorLocked, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    EndIf
    BindTrigger(EVS_ExitPipe_tik_14_0, TRIGGER_FLOOR_TOUCH, COLLIDER_o49, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($SpikesRoom.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($PathToShiverCity.index)
            Set(LVar2, MODEL_o46)
            Set(LVar3, MODEL_o47)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($RipCheatoAntechamber.index)
            EVT_ENTER_PIPE_VERTICAL(EVS_BindExitTriggers)
    EndSwitch
    Wait(1)
    Return
    End
};

#include "../common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 2,
    .volumes = {
        {
            .minPos = { $DripVolume_1.min.x, $DripVolume_1.min.z },
            .maxPos = { $DripVolume_1.max.x, $DripVolume_1.max.z },
            .startY = $DripVolume_1.max.y,
            .endY = $DripVolume_1.min.y,
            .duration = 60,
            .density  = 2,
        },
        {
            .minPos = { $DripVolume_2.min.x, $DripVolume_2.min.z },
            .maxPos = { $DripVolume_2.max.x, $DripVolume_2.max.z },
            .startY = $DripVolume_2.max.y,
            .endY = $DripVolume_2.min.y,
            .duration = 60,
            .density  = 1,
        }
    }
};

EvtScript EVS_SetupDrips = {
    Set(LVar0, DripVolumes)
    Set(LVar1, MODEL_sizuku)
    Exec(EVS_CreateDripVolumes)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Exec(EVS_SetupDrips)
    Call(SetTexPanner, MODEL_mizu, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(    0, -200, -100, -500)
        TEX_PAN_PARAMS_FREQ(    0,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Wait(1)
    Exec(EVS_EnterMap)
    Return
    End
};
