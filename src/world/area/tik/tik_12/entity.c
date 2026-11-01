#include "tik_12.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_TIK02_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

EvtScript EVS_SmashBlockA = {
    Set(GF_TIK12_Hammer3BlockA, true)
    Return
    End
};

EvtScript EVS_SmashBlockB = {
    Set(GF_TIK12_Hammer3BlockB, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    EVT_MAKE_SUPER_BLOCK(240, 0, -40, 0)
    IfEq(GF_TIK12_Hammer3BlockA, false)
        Call(MakeMarkerEntity, $Hammer3Block_1)
    EndIf
    IfEq(GF_TIK12_Hammer3BlockB, false)
        Call(MakeMarkerEntity, $Hammer3Block_2)
    EndIf
    Return
    End
};
