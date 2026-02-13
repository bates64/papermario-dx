#pragma once

#ifdef __cplusplus

#include "common.h"

namespace dx {

// Helper for move semantics without std::move
template<typename T>
constexpr T&& move(T& t) {
    return static_cast<T&&>(t);
}

// Type trait to detect pointers
template<typename T>
struct is_pointer {
    static const bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    static const bool value = true;
};

namespace option {

// Forward declarations
template<typename T> class Option;

namespace detail {
    /// Base class with shared Option methods (CRTP pattern - internal use only)
    template<typename Derived, typename T>
    class OptionBase {
protected:
    Derived& self() { return static_cast<Derived&>(*this); }
    const Derived& self() const { return static_cast<const Derived&>(*this); }

public:
    /// Allows: if (option) { ... }
    explicit operator bool() const { return self().is_some(); }

    /// Panics if none
    T& unwrap() {
        if (self().is_none()) PANIC_MSG("unwrap Option::none");
        return self().get_value();
    }

    /// Panics if none
    const T& unwrap() const {
        if (self().is_none()) PANIC_MSG("unwrap Option::none");
        return self().get_value();
    }

    /// Panics with given message if none
    T& expect(const char* msg) {
        if (self().is_none()) IS_DEBUG_PANIC(msg);
        return self().get_value();
    }

    /// Panics with given message if none
    const T& expect(const char* msg) const {
        if (self().is_none()) IS_DEBUG_PANIC(msg);
        return self().get_value();
    }

    /// Panics if none
    T& operator*() { return unwrap(); }

    /// Panics if none
    const T& operator*() const { return unwrap(); }

    /// Returns self if some, otherwise returns other
    Derived or_option(const Derived& other) const {
        return self().is_some() ? self() : other;
    }

    /// Returns self if some, otherwise calls func and returns its result
    template<typename F>
    Derived or_else(F func) const {
        return self().is_some() ? self() : func();
    }

    /// Returns none if self is none, otherwise returns other
    template<typename U>
    Option<U> and_option(const Option<U>& other) const;

    /// Map: applies func if some, returns none if none
    template<typename F>
    auto map(F func) const;

    /// AndThen: applies func (which returns Option) if some, returns none if none
    template<typename F>
    auto and_then(F func) const;

    /// Flatten: converts Option<Option<T>> to Option<T>
    template<typename U = T>
    auto flatten() const;
    };
} // namespace detail

/// Option<T> - owned value semantics
template<typename T>
class Option : public detail::OptionBase<Option<T>, T> {
    static_assert(!is_pointer<T>::value, "Option<T*> is not allowed - use Option<T&> instead");

    alignas(T) unsigned char storage[sizeof(T)];
    bool hasValue;

    T& get_ref() { return *reinterpret_cast<T*>(storage); }
    const T& get_ref() const { return *reinterpret_cast<const T*>(storage); }

public:
    Option() : hasValue(false) {}

    Option(const T& val) : hasValue(true) {
        new (storage) T(val);
    }

    Option(T&& val) : hasValue(true) {
        new (storage) T(move(val));
    }

    ~Option() {
        if (hasValue) {
            get_ref().~T();
        }
    }

    Option(const Option& other) : hasValue(other.hasValue) {
        if (hasValue) {
            new (storage) T(other.get_ref());
        }
    }

    Option(Option&& other) : hasValue(other.hasValue) {
        if (hasValue) {
            new (storage) T(move(other.get_ref()));
            other.hasValue = false;
        }
    }

    Option& operator=(const Option& other) {
        if (this != &other) {
            if (hasValue) {
                get_ref().~T();
            }
            hasValue = other.hasValue;
            if (hasValue) {
                new (storage) T(other.get_ref());
            }
        }
        return *this;
    }

    Option& operator=(Option&& other) {
        if (this != &other) {
            if (hasValue) {
                get_ref().~T();
            }
            hasValue = other.hasValue;
            if (hasValue) {
                new (storage) T(move(other.get_ref()));
                other.hasValue = false;
            }
        }
        return *this;
    }

    static Option some(const T& val) { return Option(val); }
    static Option some(T&& val) { return Option(move(val)); }
    static Option none() { return Option(); }

    bool is_some() const { return hasValue; }
    bool is_none() const { return !hasValue; }

    T* get() { return hasValue ? &get_ref() : nullptr; }
    const T* get() const { return hasValue ? &get_ref() : nullptr; }

    T& get_value() { return get_ref(); }
    const T& get_value() const { return get_ref(); }

    /// Set to some(value), destroying old value if present
    void set(const T& val) {
        if (hasValue) {
            get_ref().~T();
        }
        new (storage) T(val);
        hasValue = true;
    }

    /// Set to some(value) using move semantics
    void set(T&& val) {
        if (hasValue) {
            get_ref().~T();
        }
        new (storage) T(move(val));
        hasValue = true;
    }

    /// Set to none, destroying value if present
    void clear() {
        if (hasValue) {
            get_ref().~T();
            hasValue = false;
        }
    }

    /// Returns nullptr if none
    T* operator->() { return get(); }

    /// Returns nullptr if none
    const T* operator->() const { return get(); }

    /// Returns value if some, otherwise returns defaultValue
    T or_default(const T& defaultValue) const {
        return hasValue ? get_ref() : defaultValue;
    }
};

/// Option<T&> - reference specialization for efficiency
template<typename T>
class Option<T&> : public detail::OptionBase<Option<T&>, T> {
    T* ptr;

public:
    Option() : ptr(nullptr) {}
    Option(T& val) : ptr(&val) {}
    Option(T* val) : ptr(val) {}

    static Option some(T& val) { return Option(val); }
    static Option none() { return Option(); }

    bool is_some() const { return ptr != nullptr; }
    bool is_none() const { return ptr == nullptr; }

    T* get() { return ptr; }
    const T* get() const { return ptr; }

    T& get_value() { return *ptr; }
    const T& get_value() const { return *ptr; }

    /// Set to some(reference)
    void set(T& val) {
        ptr = &val;
    }

    /// Set to none
    void clear() {
        ptr = nullptr;
    }

    /// Returns nullptr if none
    T* operator->() { return ptr; }

    /// Returns nullptr if none
    const T* operator->() const { return ptr; }
};

// Template method definitions (after both Option specializations are declared)
namespace detail {
    template<typename Derived, typename T>
    template<typename U>
    Option<U> OptionBase<Derived, T>::and_option(const Option<U>& other) const {
        return self().is_some() ? other : Option<U>::none();
    }

    template<typename Derived, typename T>
    template<typename F>
    auto OptionBase<Derived, T>::map(F func) const {
        using U = decltype(func(self().get_value()));
        if (self().is_none()) {
            return Option<U>::none();
        }
        return Option<U>::some(func(self().get_value()));
    }

    template<typename Derived, typename T>
    template<typename F>
    auto OptionBase<Derived, T>::and_then(F func) const {
        if (self().is_none()) {
            return decltype(func(self().get_value()))::none();
        }
        return func(self().get_value());
    }

    template<typename Derived, typename T>
    template<typename U>
    auto OptionBase<Derived, T>::flatten() const {
        if (self().is_none()) {
            return U::none();
        }
        return self().get_value();
    }
} // namespace detail

} // namespace option
} // namespace dx

#endif // __cplusplus
