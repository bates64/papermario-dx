#ifndef _COMMON_H_
#define _COMMON_H_
#if defined __GNUC__ && __GNUC__ >= 14
#pragma GCC diagnostic warning "-Wimplicit-function-declaration"
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
#pragma GCC diagnostic warning "-Wint-conversion"
#pragma GCC diagnostic warning "-Wreturn-mismatch"
#endif

// TEMP until we get rid of all version differences
#define VERSION_US 1

#include "ultra64.h"
#include "gbi_custom.h"
#include "types.h"
#include "common_structs.h"
#include "functions.h"
#include "variables.h"
#include "macros.h"
#include "enums.h"
#include "evt.h"
#include "messages.h"
#include "battle/battle_names.h"
#include "battle/stage_names.h"
#include "battle/actor_types.h"

#endif
