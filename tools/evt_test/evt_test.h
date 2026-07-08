#pragma once
#include "common.h"
#include "script_api/macros.h"

#define EVT_TEST_RAW_CMD(opcode, argc, argv...) \
    EVT_CMD_HEADER((opcode), (argc), __LINE__), ##argv,

ApiStatus EVT_TestDummyCall(Evt* script, s32 isInitialCall);
