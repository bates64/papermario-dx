#include "../evt_test.h"

EvtScript EVS_ExecArgIntMarkerChild = {
    End
};

EvtScript EVS_ExecArgIntMarkerMissingValue = {
    EVT_TEST_RAW_CMD(EVT_OP_EXEC, 2, (Bytecode) EVS_ExecArgIntMarkerChild, EVT_ARG_INT_MARKER)
    End
};
