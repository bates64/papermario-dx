 // global heap, unlike general heap it is not wiped between maps

#include "common.h"

extern HeapNode heap_globalHead;

extern "C" void create_global_heap() {
    _heap_create(&heap_globalHead, GLOBAL_HEAP_SIZE);
}

extern "C" void* malloc(size_t size) {
    return _heap_malloc(&heap_globalHead, size);
}

extern "C" void free(void* ptr) {
    _heap_free(&heap_globalHead, ptr);
}

extern "C" void* realloc(void* ptr, size_t size) {
    return _heap_realloc(&heap_globalHead, ptr, size);
}

extern "C" void* calloc(size_t nmemb, size_t size) {
    size_t total = nmemb * size;
    void* ptr = _heap_malloc(&heap_globalHead, total);
    if (ptr != nullptr) {
        memset(ptr, 0, total);
    }
    return ptr;
}

void* operator new(size_t size) {
    void* ptr = malloc(size);
    ASSERT_MSG(ptr != nullptr, "global heap is full");
    return ptr;
}

void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete(void* ptr, size_t size) noexcept {
    free(ptr);
}

void* operator new[](size_t size) {
    void* ptr = calloc(1, size);
    ASSERT_MSG(ptr != nullptr, "global heap is full");
    return ptr;
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    free(ptr);
}

// C++ runtime support for static initialization
extern "C" {
    void* __dso_handle = nullptr;

    int __cxa_atexit(void (*destructor)(void*), void* arg, void* dso) {
        // Since the game never exits normally, we don't need to register destructors
        return 0;
    }
}
