#pragma once

#ifdef __cplusplus

#include "types.h"
#include "dx/option.h"

namespace dx {
namespace rc {

// Forward declarations
template<typename T> class Rc;
template<typename T> class Weak;

/// Control block for reference counting
/// Manages both strong (Rc) and weak (Weak) reference counts
struct ControlBlock {
    u32 strongCount;
    u32 weakCount;
    void* objPtr;  // For debug printing

    ControlBlock(void* ptr) : strongCount(1), weakCount(0), objPtr(ptr) {
    }

    ~ControlBlock() {
    }
};

/// Reference-counted smart pointer (like std::shared_ptr)
/// Manages shared ownership of an object through a pointer
/// For nullable semantics, use Option<Rc<T>>
template<typename T>
class Rc {
private:
    T* ptr;
    ControlBlock* control;

    friend class Weak<T>;

    /// Internal constructor for Weak::upgrade() - assumes strongCount already incremented
    static Rc<T> from_weak_internal(T* p, ControlBlock* ctrl) {
        Rc<T> rc;
        rc.ptr = p;
        rc.control = ctrl;
        // Note: strongCount already incremented by caller
        return rc;
    }

    /// Default constructor (private) - only for from_weak_internal
    Rc() : ptr(nullptr), control(nullptr) {}

    void release() {
        if (control) {
            control->strongCount--;

            if (control->strongCount == 0) {
                // Delete the managed object
                delete ptr;
                ptr = nullptr;

                // Delete control block if no weak references
                if (control->weakCount == 0) {
                    delete control;
                }
            }
        }
    }

public:
    /// Creates an Rc managing the given pointer (must be non-null)
    explicit Rc(T* p) : ptr(p), control(new ControlBlock(p)) {
        ASSERT(p != nullptr);
    }

    /// Copy constructor - shares ownership
    Rc(const Rc& other) : ptr(other.ptr), control(other.control) {
        if (control) {
            control->strongCount++;
        }
    }

    /// Move constructor - transfers ownership
    Rc(Rc&& other) : ptr(other.ptr), control(other.control) {
        other.ptr = nullptr;
        other.control = nullptr;
    }

    ~Rc() {
        release();
    }

    /// Copy assignment - shares ownership
    Rc& operator=(const Rc& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            if (control) {
                control->strongCount++;
            }
        }
        return *this;
    }

    /// Move assignment - transfers ownership
    Rc& operator=(Rc&& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            other.ptr = nullptr;
            other.control = nullptr;
        }
        return *this;
    }

    /// Dereference operator (mutable)
    /// WARNING: Reference is only valid while at least one Rc exists.
    /// Becomes invalid when the last Rc is destroyed.
    T& operator*() {
        return *ptr;
    }

    /// Dereference operator (const)
    /// WARNING: Reference is only valid while at least one Rc exists.
    /// Becomes invalid when the last Rc is destroyed.
    const T& operator*() const {
        return *ptr;
    }

    /// Member access operator (mutable)
    /// WARNING: Pointer is only valid while at least one Rc exists.
    /// Becomes invalid when the last Rc is destroyed.
    T* operator->() {
        return ptr;
    }

    /// Member access operator (const)
    /// WARNING: Pointer is only valid while at least one Rc exists.
    /// Becomes invalid when the last Rc is destroyed.
    const T* operator->() const {
        return ptr;
    }

    /// Get raw pointer (mutable)
    /// WARNING: Pointer is only valid while at least one Rc exists.
    /// Becomes invalid when the last Rc is destroyed.
    T* as_ptr() {
        return ptr;
    }

    /// Get raw pointer (const)
    /// WARNING: Pointer is only valid while at least one Rc exists.
    /// Becomes invalid when the last Rc is destroyed.
    const T* as_ptr() const {
        return ptr;
    }

    /// Check if pointer is non-null
    explicit operator bool() const {
        return ptr != nullptr;
    }

    /// Helper to create an Rc (like std::make_shared)
    template<typename... Args>
    static Rc<T> make(Args&&... args) {
        return Rc<T>(new T(static_cast<Args&&>(args)...));
    }

    /// Create a weak reference to this Rc
    Weak<T> downgrade() const {
        return Weak<T>(*this);
    }
};

/// Weak reference to a reference-counted object
/// Does not prevent the object from being deleted
/// Must be upgraded to Rc<T> to access the object
template<typename T>
class Weak {
private:
    T* ptr;
    ControlBlock* control;

    friend class Rc<T>;

    /// Private constructor - only Rc can create Weak references
    Weak(const Rc<T>& rc) : ptr(rc.ptr), control(rc.control) {
        if (control) {
            control->weakCount++;
        }
    }

    void release() {
        if (control) {
            control->weakCount--;

            // Delete control block if no references remain
            if (control->strongCount == 0 && control->weakCount == 0) {
                delete control;
            }
        }
    }

public:
    /// Default constructor - creates empty weak reference
    Weak() : ptr(nullptr), control(nullptr) {
    }

    /// Copy constructor
    Weak(const Weak& other) : ptr(other.ptr), control(other.control) {
        if (control) {
            control->weakCount++;
        }
    }

    /// Move constructor
    Weak(Weak&& other) : ptr(other.ptr), control(other.control) {
        other.ptr = nullptr;
        other.control = nullptr;
    }

    ~Weak() {
        release();
    }

    /// Copy assignment
    Weak& operator=(const Weak& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            if (control) {
                control->weakCount++;
            }
        }
        return *this;
    }

    /// Move assignment
    Weak& operator=(Weak&& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            other.ptr = nullptr;
            other.control = nullptr;
        }
        return *this;
    }

    /// Attempt to upgrade to a strong reference
    /// Returns None if the object has been deleted
    option::Option<Rc<T>> upgrade() const {
        if (control && control->strongCount > 0) {
            // Object still exists - increment strong count and create new Rc
            control->strongCount++;
            // Use copy constructor to create Rc from internal state
            Rc<T> rc = Rc<T>::from_weak_internal(ptr, control);
            return option::Option<Rc<T>>::some(dx::move(rc));
        }
        return option::Option<Rc<T>>::none();
    }

    /// Check if the weak reference is still valid
    bool is_alive() const {
        return control && control->strongCount > 0;
    }
};

} // namespace rc
} // namespace dx

#endif // __cplusplus
