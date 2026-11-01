#include "kzn_06.h"
#include "effects.h"
#include "entity.h"

EvtScript EVS_OnBreakBlock = {
    Set(GF_KZN06_Hammer3Block, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenYellowBlock_LifeShroom_1)
    IfEq(GF_KZN06_Hammer3Block, false)
        Call(MakeMarkerEntity, $Hammer3BlockWideZ_1)
    EndIf
    IfLt(GB_StoryProgress, STORY_CH5_LAVA_STREAM_BLOCKED)
        Call(CreatePushBlockGrid, 0, 12, 1, -330, 145, -90, 0)
        Call(SetPushBlockFallEffect, 0, PushBlockFallCallback_Gravity)
        Call(SetPushBlock, 0, 4, 0, PUSH_GRID_BLOCK)
        Call(SetPushBlock, 0, 6, 0, PUSH_GRID_BLOCK)
        Call(SetPushBlock, 0, 8, 0, PUSH_GRID_BLOCK)
    Else
        Call(CreatePushBlockGrid, 0, 12, 1, -330, 120, -90, 0)
        Call(SetPushBlock, 0,  9, 0, PUSH_GRID_BLOCK)
        Call(SetPushBlock, 0, 10, 0, PUSH_GRID_BLOCK)
        Call(SetPushBlock, 0, 11, 0, PUSH_GRID_BLOCK)
    EndIf
    Return
    End
};
