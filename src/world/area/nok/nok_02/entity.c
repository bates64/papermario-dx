#include "nok_02.h"
#include "entity.h"

#include "common/ItemEntityJumpToPos.inc.c"

EvtScript EVS_BreakBlock_DropStarPiece = {
    Call(ItemEntityJumpToPos, MV_StarPieceItem, 227.0, 0.0, 247.0, 20, 1.0)
    Return
    End
};

EvtScript EVS_GotoMap_tik_01_3 = {
    Call(GotoMap, "tik_01", tik_01_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Entity_BrickBlock, 151, 81, 251, 0, MAKE_ENTITY_END)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH1_KOOPER_JOINED_PARTY)
            IfEq(GF_NOK02_RecoveredShellB, false)
                Call(AssignScript, EVS_BreakBlock_DropShell)
            EndIf
        CaseGe(STORY_CH1_KOOPER_JOINED_PARTY)
            IfEq(GF_NOK02_Item_StarPiece, false)
                Call(AssignScript, EVS_BreakBlock_DropStarPiece)
                Call(MakeItemEntity, ITEM_STAR_PIECE, 150, 106, 250, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_NOK02_Item_StarPiece)
                Set(MV_StarPieceItem, LVar0)
            EndIf
    EndSwitch
    Call(CreatePushBlockGrid, 0, 5, 5, 88, -4, 188, 0)
    Call(SetPushBlock, 0, 0, 0, PUSH_GRID_BLOCK)
    IfEq(GF_NOK02_WarpPipe, false)
        IfEq(GF_TIK01_WarpPipes, true)
            Call(GetEntryID, LVar0)
            IfNe(LVar0, nok_02_ENTRY_2)
                Set(GF_NOK02_WarpPipe, true)
            EndIf
        EndIf
    EndIf
    Call(MakeEntity, Entity_BlueWarpPipe, 365, 0, 90, 30, nok_02_ENTRY_2, EVS_GotoMap_tik_01_3, EVT_INDEX_OF_GAME_FLAG(GF_NOK02_WarpPipe), MAKE_ENTITY_END)
    Return
    End
};
