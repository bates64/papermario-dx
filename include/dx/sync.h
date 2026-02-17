#pragma once

#ifdef __cplusplus

namespace dx {
namespace sync {

/// RAII guard that unlocks mutex when destroyed
template<typename T>
class MutexGuard {
    volatile bool* lockPtr;
public:
    T& value;

    MutexGuard(volatile bool* lock, T& val) : lockPtr(lock), value(val) {}
    ~MutexGuard() { __sync_lock_release(lockPtr); }

    T* operator->() { return &value; }
    T& operator*() { return value; }

    MutexGuard(const MutexGuard&) = delete;
    MutexGuard& operator=(const MutexGuard&) = delete;
};

/// Spinlock mutex that protects a value - must lock() to access
template<typename T>
class Mutex {
    volatile bool locked = false;
    T value;
public:
    Mutex() : value() {}
    Mutex(T initial) : value(initial) {}

    MutexGuard<T> lock() {
        while (__sync_lock_test_and_set(&locked, true)) {
            osYieldThread();
        }
        return MutexGuard<T>(&locked, value);
    }
};

} // namespace sync
} // namespace dx

#endif
