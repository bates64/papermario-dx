#include "nok_02.h"
#include "world/area/tik/tik_01.h"
#include "entity.h"

#include "common/ItemEntityJumpToPos.inc.c"

EvtScript EVS_BreakBlock_DropStarPiece = {
    Call(ItemEntityJumpToPos, MV_StarPieceItem, 227.0, 0.0, 247.0, 20, 1.0)
    Return
    End
};

EvtScript EVS_GotoMap_tik_01_3 = {
    Call(GotoMap, $tik_01.KoopaVillage)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $BrickBlock_1)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH1_KOOPER_JOINED_PARTY)
            IfEq(GF_NOK02_RecoveredShellB, false)
                Call(AssignScript, EVS_BreakBlock_DropShell)
            EndIf
        CaseGe(STORY_CH1_KOOPER_JOINED_PARTY)
            IfEq(GF_NOK02_Item_StarPiece, false)
                Call(AssignScript, EVS_BreakBlock_DropStarPiece)
                Call(MakeMarkerEntity, $Item_StarPiece_1)
                Set(MV_StarPieceItem, LVar0)
            EndIf
    EndSwitch
    Call(CreatePushBlockGrid, 0, 5, 5, 88, -4, 188, 0)
    Call(SetPushBlock, 0, 0, 0, PUSH_GRID_BLOCK)
    IfEq(GF_NOK02_WarpPipe, false)
        IfEq(GF_TIK01_WarpPipes, true)
            Call(GetEntryID, LVar0)
            IfNe(LVar0, $Pipe.index)
                Set(GF_NOK02_WarpPipe, true)
            EndIf
        EndIf
    EndIf
    Call(MakeMarkerEntity, $BlueWarpPipe_1)
    Return
    End
};
