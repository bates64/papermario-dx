#include "../evt_test.h"

s32 TestMemWord;

EvtScript EVS_MemInvalidType = {
    MemGet(99, LVar0, TestMemWord)
    End
};
