#include "../evt_test.h"

EvtScript EVS_ExecArgFloatMarkerChild = {
    End
};

EvtScript EVS_ExecArgFloatMarkerMissingValue = {
    EVT_TEST_RAW_CMD(EVT_OP_EXEC_GET_ID, 3, (Bytecode) EVS_ExecArgFloatMarkerChild, LVar0, EVT_ARG_FLOAT_MARKER)
    End
};
