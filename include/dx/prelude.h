/// Includes all dx C++ headers and brings commonly used items into scope

#pragma once

#ifdef __cplusplus

#include "dx/option.h"
#include "dx/collections.h"
#include "dx/string.h"
#include "dx/hash.h"
#include "dx/cmp.h"
#include "dx/asset.h"

using dx::option::Option;
using dx::collections::HashMap;
using dx::string::String;
using dx::hash::Hash;
using dx::cmp::Eq;
using dx::move;

#endif // __cplusplus
