#include "../evt_test.h"

s32 TestMemWord;

EvtScript EVS_MemVariableType = {
    MemSet(LVar0, TestMemWord, 10)
    End
};
