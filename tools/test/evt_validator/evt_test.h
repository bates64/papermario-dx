#pragma once
#include "common.h"
#include "script_api/macros.h"

#define EVT_TEST_RAW_CMD(opcode, argc, argv...) \
    EVT_CMD_HEADER((opcode), (argc), __LINE__), ##argv,

API_CALLABLE(EVT_TestDummyCall);
