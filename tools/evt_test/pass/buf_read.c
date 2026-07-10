#include "../evt_test.h"

s32 TestIntBuf[] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26
};

f32 TestFloatBuf[] = {
    1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
    9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f,
    17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 23.0f, 24.0f,
    25.0f, 26.0f
};

EvtScript EVS_BufRead = {
    UseBuf(TestIntBuf)
    BufRead(LVar0)
    BufRead(LVar1, LVar2)
    BufRead(LVar3, LVar4, LVar5)
    BufRead(LVar6, LVar7, LVar8, LVar9)
    BufRead(LVar0, LVar1, LVar2, LVar3, LVar4, LVar5)
    BufRead1(LVar0)
    BufRead2(LVar1, LVar2)
    BufRead3(LVar3, LVar4, LVar5)
    BufRead4(LVar6, LVar7, LVar8, LVar9)

    UseFBuf(TestFloatBuf)
    FBufRead(LVar0)
    FBufRead(LVar1, LVar2)
    FBufRead(LVar3, LVar4, LVar5)
    FBufRead(LVar6, LVar7, LVar8, LVar9)
    FBufRead(LVar0, LVar1, LVar2, LVar3, LVar4, LVar5)
    FBufRead1(LVar0)
    FBufRead2(LVar1, LVar2)
    FBufRead3(LVar3, LVar4, LVar5)
    FBufRead4(LVar6, LVar7, LVar8, LVar9)
    End
};
