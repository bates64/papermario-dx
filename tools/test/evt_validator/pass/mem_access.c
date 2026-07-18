#include "../evt_test.h"

u8 TestMemByte;
s16 TestMemValues[4];
f32 TestMemFloat;

EvtScript EVS_MemAccess = {
    MemGet(LVar0, TestMemByte)
    MemSet(TestMemByte, 200)
    MemGet(LVar1, TestMemValues[2])
    MemGetIndex(LVar2, TestMemValues, LVar0)
    MemSetIndex(TestMemValues, LVar0, -7)
    MemGet(LVar3, TestMemFloat)
    MemSet(TestMemFloat, Float(1.25))
    End
};
