#include "../evt_test.h"

s32 TestMemWord;

EvtScript EVS_MemRelocatedType = {
    MemGet(Ref(TestMemWord), LVar0, TestMemWord)
    End
};
