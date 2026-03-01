#pragma once

#include <optional>
#include "common.h"

namespace dx {

inline constexpr std::nullopt_t none = std::nullopt;

/// optional<T> - inherits std::optional<T> with panicking value().
template<typename T>
class optional : public std::optional<T> {
    static_assert(!std::is_pointer<T>::value, "optional<T*> is not allowed - use optional<T&> instead");

public:
    using std::optional<T>::optional;
    using std::optional<T>::operator=;

    T& value() {
        if (!this->has_value()) PANIC_MSG("optional::value on none");
        return **this;
    }

    const T& value() const {
        if (!this->has_value()) PANIC_MSG("optional::value on none");
        return **this;
    }

    T value_or(const T& defaultValue) const {
        return this->has_value() ? **this : defaultValue;
    }
};

/// optional<T&> - reference specialization (std::optional doesn't support references).
template<typename T>
class optional<T&> {
    T* ptr;

public:
    optional() : ptr(nullptr) {}
    optional(T& val) : ptr(&val) {}
    optional(std::nullopt_t) : ptr(nullptr) {}

    bool has_value() const { return ptr != nullptr; }
    explicit operator bool() const { return ptr != nullptr; }

    T& operator*() {
        if (!ptr) PANIC_MSG("optional::operator* on none");
        return *ptr;
    }

    const T& operator*() const {
        if (!ptr) PANIC_MSG("optional::operator* on none");
        return *ptr;
    }

    T& value() {
        if (!ptr) PANIC_MSG("optional::value on none");
        return *ptr;
    }

    const T& value() const {
        if (!ptr) PANIC_MSG("optional::value on none");
        return *ptr;
    }

    T* operator->() { return ptr; }
    const T* operator->() const { return ptr; }

    void reset() { ptr = nullptr; }
};

} // namespace dx
