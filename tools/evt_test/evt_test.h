#pragma once
#include "common.h"
#include "script_api/macros.h"

#define EVT_TEST_RAW_CMD(opcode, argc, argv...) \
    opcode, ((argc) & 0xFFFF) | (__LINE__ << 16), ##argv,

ApiStatus EVT_TestDummyCall(Evt* script, s32 isInitialCall);
