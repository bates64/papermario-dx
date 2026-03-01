#pragma once

#include "types.h"
#include <functional>
#include <string.h>

namespace dx {

/// A fixed-size string stored inline (no heap allocation).
/// Useful for HashMap keys with known max length.
template<u32 N>
struct FixedString {
    char data[N];

    FixedString() {
        data[0] = '\0';
    }

    FixedString(const char* str) {
        if (str) {
            u32 i;
            for (i = 0; i < N - 1 && str[i] != '\0'; i++) {
                data[i] = str[i];
            }
            data[i] = '\0';
        } else {
            data[0] = '\0';
        }
    }

    const char* c_str() const { return data; }

    operator const char*() const { return data; }

    bool operator==(const FixedString& other) const {
        return strcmp(data, other.data) == 0;
    }
};

} // namespace dx

/// std::hash specialization for FixedString
template<u32 N>
struct std::hash<dx::FixedString<N>> {
    size_t operator()(const dx::FixedString<N>& str) const {
        // FNV-1a
        u32 h = 2166136261u;
        const char* ptr = str.c_str();
        while (*ptr != '\0') {
            h ^= (u32)*ptr++;
            h *= 16777619u;
        }
        return h;
    }
};
