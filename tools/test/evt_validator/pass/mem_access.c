#include "../evt_test.h"

u8 TestMemByte;
s16 TestMemValues[4];
f32 TestMemFloat;

EvtScript EVS_MemAccess = {
    MemGet(EVT_MEM_U8, LVar0, TestMemByte)
    MemSet(EVT_MEM_U8, TestMemByte, 200)
    MemGet(EVT_MEM_S16, LVar1, TestMemValues[2])
    MemGetIndex(EVT_MEM_S16, LVar2, TestMemValues, LVar0)
    MemSetIndex(EVT_MEM_S16, TestMemValues, LVar0, -7)
    MemGet(EVT_MEM_F32, LVar3, TestMemFloat)
    MemSet(EVT_MEM_F32, TestMemFloat, Float(1.25))
    End
};
