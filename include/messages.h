#pragma once

#include "types.h"

// Prefer editing splat.yaml's msg ids section than using this directly!
#define MESSAGE_ID(section, index) (((section << 16) + index))
