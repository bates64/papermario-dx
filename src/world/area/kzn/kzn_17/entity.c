#include "kzn_17.h"
#include "entity.h"

s32 Unused_80243610_3610[] = {
    0x01010101, 0x01010101, 0x01010101, 0x01010101,
    0x01010101, 0x01010101, 0x01010101, 0x01010101,
    0x01010101, 0x01010101, 0x01010101, 0x01010101,
    0x01010101, 0x01010101, 0x01010000,
};

EvtScript EVS_OnBreakBlockA = {
    Set(GF_KZN17_Hammer3BlockA, true)
    Return
    End
};

EvtScript EVS_OnBreakBlockB = {
    Set(GF_KZN17_Hammer3BlockB, true)
    Return
    End
};

EvtScript EVS_OnBreakBlockC = {
    Set(GF_KZN17_Hammer3BlockC, true)
    Return
    End
};

EvtScript EVS_OnBreakBlockD = {
    Set(GF_KZN17_Hammer3BlockD, true)
    Return
    End
};

EvtScript EVS_OnBreakBlockE = {
    Set(GF_KZN17_Hammer3BlockE, true)
    Return
    End
};

EvtScript EVS_OnBreakBlockF = {
    Set(GF_KZN17_Hammer3BlockF, true)
    Return
    End
};

EvtScript EVS_OnBreakBlockG = {
    Set(GF_KZN17_Hammer3BlockG, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_KZN17_Hammer3BlockA, false)
        Call(MakeMarkerEntity, $Hammer3Block_1)
    EndIf
    IfEq(GF_KZN17_Hammer3BlockB, false)
        Call(MakeMarkerEntity, $Hammer3Block_2)
    EndIf
    IfEq(GF_KZN17_Hammer3BlockC, false)
        Call(MakeMarkerEntity, $Hammer3Block_3)
    EndIf
    IfEq(GF_KZN17_Hammer3BlockD, false)
        Call(MakeMarkerEntity, $Hammer3Block_4)
    EndIf
    IfEq(GF_KZN17_Hammer3BlockE, false)
        Call(MakeMarkerEntity, $Hammer3Block_5)
    EndIf
    IfEq(GF_KZN17_Hammer3BlockF, false)
        Call(MakeMarkerEntity, $Hammer3Block_6)
    EndIf
    IfEq(GF_KZN17_Hammer3BlockG, false)
        Call(MakeMarkerEntity, $Hammer3Block_7)
    EndIf
    Call(CreatePushBlockGrid, 0, 29, 2, -119, -3, 5, 0)
    Call(SetPushBlock, 0, 28, 1, PUSH_GRID_BLOCK)
    Return
    End
};
