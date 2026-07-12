#include "../evt_test.h"

s32 TestIntBuf[] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26
};

s32 TestFloatBuf[] = {
    Float(1.0), Float(2.0), Float(3.0), Float(4.0), Float(5.0), Float(6.0), Float(7.0), Float(8.0),
    Float(9.0), Float(10.0), Float(11.0), Float(12.0), Float(13.0), Float(14.0), Float(15.0), Float(16.0),
    Float(17.0), Float(18.0), Float(19.0), Float(20.0), Float(21.0), Float(22.0), Float(23.0), Float(24.0),
    Float(25.0), Float(26.0)
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
    BufPeek(LVarA, 0)

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
    FBufPeek(LVarB, 0)
    End
};
