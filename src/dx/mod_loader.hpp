#pragma once
#include "common.h"

/// Referenced-counted pointer. Non-nullptr only.
template<typename T>
class Rc {
    // Pointers may not be nullptr
    T* ptr;
    u32* refcount;

    void retain() {
        (*refcount)++;
    }

    void release() {
        (*refcount)--;
        if (*refcount == 0) {
            delete ptr;
            delete refcount;
        }
    }

public:
    explicit Rc(T* p)
        : ptr(p)
        , refcount(nullptr)
    {
        ASSERT(ptr != nullptr);
        refcount = new u32;
        *refcount = 1;
    }

    Rc(const Rc& other)
        : ptr(other.ptr)
        , refcount(other.refcount)
    {
        retain();
    }

    Rc(Rc&& other)
        : ptr(other.ptr)
        , refcount(other.refcount)
    {
        other.ptr = nullptr;
        other.refcount = nullptr;
    }

    Rc& operator=(const Rc& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refcount = other.refcount;
            retain();
        }
        return *this;
    }

    Rc& operator=(Rc&& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refcount = other.refcount;
        }
        return *this;
    }

    ~Rc() {
        release();
    }

    void swap(Rc& other) {
        T* tmpPtr = ptr;
        u32* tmpRef = refcount;
        ptr = other.ptr;
        refcount = other.refcount;
        other.ptr = tmpPtr;
        other.refcount = tmpRef;
    }

    T& operator*() {
        return *ptr;
    }

    const T& operator*() const {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    const T* operator->() const {
        return ptr;
    }
};

/// A pointer to data stored in the ROM. Dereferencing this pointer will load the data into RAM.
template<typename T>
struct RomAddress {
    u32 address;

    RomAddress(u32 addr)
        : address(addr)
    {}

    void operator=(u32 addr) {
        address = addr;
    }

    Rc<T> operator*() {
        ASSERT(!is_null());
        T* data = static_cast<T*>(::operator new(sizeof(T)));

        u32 length = dma_copy((u8*)address, (u8*)(address + sizeof(T)), (void*)data);
        ASSERT(length == sizeof(T));

        return Rc(data);
    }

    Rc<T> operator->() {
        return *this;
    }

    bool is_null() const {
        return address == 0;
    }
};

/// A linked list of loadable mods. These appear at the end of the ROM.
struct LoadableMod {
    const char version[4]; // version of this datastructure as a magic string
    u32 uuid;
    const char name[32];
    RomAddress<LoadableMod> prev;
    RomAddress<LoadableMod> next;
    u32 dfsAddress; // for dfs_init

    bool check_version() const;

    void load();

    /// The first mod in the ROM.
    /// The first mod offset is at ROM address 0x1C, set by append_mod.py.
    static RomAddress<LoadableMod> first();
};

EXTERN_C void load_all_mods();
