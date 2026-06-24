#include "dro_01.h"
#include "entity.h"

EvtScript N(EVS_WarpPipeExit) = {
    Set(GF_DRO01_HeardHintAboutSpinningRoof, false)
    Call(GotoMap, Ref("tik_01"), tik_01_ENTRY_4)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_MakeEntities) = {
    Call(MakeEntity, Ref(Entity_SavePoint), -211, 60, -50, 30, MAKE_ENTITY_END)
    IfEq(GF_DRO01_WarpPipe, false)
        IfEq(GF_TIK01_WarpPipes, true)
            Call(GetEntryID, LVar0)
            IfNe(LVar0, dro_01_ENTRY_2)
                Set(GF_DRO01_WarpPipe, true)
            EndIf
        EndIf
    EndIf
    Call(MakeEntity, Ref(Entity_BlueWarpPipe), 430, 0, -120, 0,
        dro_01_ENTRY_2, Ref(N(EVS_WarpPipeExit)),
        EVT_INDEX_OF_GAME_FLAG(GF_DRO01_WarpPipe), MAKE_ENTITY_END)
    Return
    End
};
