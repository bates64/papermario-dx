#pragma once

#ifdef __cplusplus

#include "types.h"
#include <string.h>

namespace dx {
namespace cmp {

/// Equality trait - specialize this for custom key types
/// Default implementation uses operator==
template<typename K>
struct Eq {
    bool operator()(const K& lhs, const K& rhs) const {
        return lhs == rhs;
    }
};

/// Specialization for const char* keys
template<>
struct Eq<const char*> {
    bool operator()(const char* lhs, const char* rhs) const {
        return strcmp(lhs, rhs) == 0;
    }
};

} // namespace cmp
} // namespace dx

#endif // __cplusplus
