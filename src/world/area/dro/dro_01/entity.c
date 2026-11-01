#include "dro_01.h"
#include "world/area/tik/tik_01.h"
#include "entity.h"

EvtScript EVS_WarpPipeExit = {
    Set(GF_DRO01_HeardHintAboutSpinningRoof, false)
    Call(GotoMap, $tik_01.DryDryOutpost)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    IfEq(GF_DRO01_WarpPipe, false)
        IfEq(GF_TIK01_WarpPipes, true)
            Call(GetEntryID, LVar0)
            IfNe(LVar0, $Pipe.index)
                Set(GF_DRO01_WarpPipe, true)
            EndIf
        EndIf
    EndIf
    Call(MakeMarkerEntity, $BlueWarpPipe_1)
    Return
    End
};
