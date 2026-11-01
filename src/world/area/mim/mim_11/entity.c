#include "mim_11.h"
#include "world/area/tik/tik_09.h"
#include "entity.h"

EvtScript EVS_UseBluePipe = {
    Call(GotoMap, $tik_09.ForeverForest)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_MIM11_WarpPipe, false)
        IfEq(GF_TIK09_WarpPipe, true)
            Call(GetEntryID, LVar0)
            IfNe(LVar0, $Pipe.index)
                Set(GF_KMR02_WarpPipe, true)
            EndIf
        EndIf
    EndIf
    Call(MakeMarkerEntity, $BlueWarpPipe_1)
    Call(MakeMarkerEntity, $HeartBlock_1)
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $YellowBlock_VoltShroom_1)
    Return
    End
};
