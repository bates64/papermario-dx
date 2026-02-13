#pragma once

#ifdef __cplusplus

#include "types.h"
#include "dx/hash.h"
#include "dx/cmp.h"
#include <string.h>

namespace dx {
namespace string {

/// An owned string. Like `char*`, but frees the data in its destructor.
class String {
public:
    String() : data(nullptr), length(0) {}

    String(const char* str) {
        if (str) {
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
            length = 0;
        }
    }

    ~String() {
        delete[] data;
    }

    // Move semantics
    String(String&& other) : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
    }

    String& operator=(String&& other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    // No copy (use move or create new String from c_str())
    String(const String&) = delete;
    String& operator=(const String&) = delete;

    const char* c_str() const { return data ? data : ""; }
    u32 len() const { return length; }
    bool is_empty() const { return length == 0; }

private:
    char* data;
    u32 length;
};

} // namespace string

namespace hash {
    // Hash specialization for string::String
    template<>
    struct Hash<string::String> {
        u32 operator()(const string::String& str) const {
            // FNV-1a hash
            u32 hash = 2166136261u;
            const char* ptr = str.c_str();
            while (*ptr != '\0') {
                hash ^= (u32)*ptr++;
                hash *= 16777619u;
            }
            return hash;
        }
    };
} // namespace hash

namespace cmp {
    // Eq specialization for string::String
    template<>
    struct Eq<string::String> {
        bool operator()(const string::String& lhs, const string::String& rhs) const {
            return strcmp(lhs.c_str(), rhs.c_str()) == 0;
        }
    };
} // namespace cmp

} // namespace dx

#endif // __cplusplus
