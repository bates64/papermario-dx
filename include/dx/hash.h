#pragma once

#ifdef __cplusplus

#include "types.h"
#include <string.h>

namespace dx {
namespace hash {

/// Hash trait - specialize this for custom key types
/// Used by HashMap to compute hash values
template<typename K>
struct Hash;

/// Specialization for const char* keys
template<>
struct Hash<const char*> {
    u32 operator()(const char* str) const {
        // FNV-1a hash
        u32 hash = 2166136261u;
        while (*str != '\0') {
            hash ^= (u32)*str++;
            hash *= 16777619u;
        }
        return hash;
    }
};

} // namespace hash
} // namespace dx

#endif // __cplusplus
