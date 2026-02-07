 // global heap, unlike general heap it is not wiped between maps/battles

#include "common.h"

static bool heapCreated = false;
static BSS HeapNode heap[1000]; // TODO: move to a new segment and increase size

extern "C" void* malloc(size_t size) {
    if (!heapCreated) {
        _heap_create(heap, sizeof(heap));
    }
    return _heap_malloc(heap, size);
}

extern "C" void free(void* ptr) {
    _heap_free(heap, ptr);
}

extern "C" void* realloc(void* ptr, size_t size) {
    return _heap_realloc(heap, ptr, size);
}

extern "C" void* calloc(size_t nmemb, size_t size) {
    size_t total = nmemb * size;
    void* ptr = _heap_malloc(heap, total);
    if (ptr != nullptr) {
        memset(ptr, 0, total);
    }
    return ptr;
}

void* operator new(size_t size) {
    void* ptr = malloc(size);
    ASSERT_MSG(ptr != nullptr, "operator new failed to allocate %zu bytes", size);
    return ptr;
}

void operator delete(void* ptr) noexcept {
    free(ptr);
}

void* operator new[](size_t size) {
    void* ptr = malloc(size);
    ASSERT_MSG(ptr != nullptr, "operator new[] failed to allocate %zu bytes", size);
    return ptr;
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}
