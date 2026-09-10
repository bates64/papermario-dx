#include "../evt_test.h"

s32 TestMemWord;

EvtScript EVS_MemGetWrongArgc = {
    EVT_TEST_RAW_CMD(EVT_OP_MEM_GET, 3, EVT_MEM_S32, LVar0, Ref(TestMemWord))
    End
};
