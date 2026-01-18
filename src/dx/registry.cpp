#include "common.h"
#include "registry.h"
#include <stdint.h>

extern HeapNode heap_generalHead;

namespace registry {

HeapNode heap[0x4000];

__attribute__((constructor)) void create_heap() {
    _heap_create(heap, sizeof(heap));
}

/// Hash function for interned strings
static uint16_t fnv1a16(const char* s, uint16_t len) {
    uint16_t h = 0x811Cu;          // 16-bit offset basis
    for (uint16_t i = 0; i < len; ++i) {
        h ^= (uint8_t)s[i];
        h *= 0x0101u;              // 16-bit FNV prime (257)
    }
    return h ? h : 1u;
}

String*   String::table = nullptr;
u16  String::cap   = 0;
u16  String::size  = 0;

void String::init() {
    if (table != nullptr) return; // already initialized

    cap = 256;
    size = 0;
    table = (String*)_heap_malloc(heap, sizeof(String) * cap);
    memset(table, 0, sizeof(String) * cap);
}

void String::grow() {
    u16 old_cap = cap;
    String*  old     = table;

    cap = cap ? (cap * 2) : 256; // Double in capacity
    table = (String*)_heap_malloc(heap, (size_t)cap * sizeof(String));
    memset(table, 0, sizeof(String) * cap);

    size = 0;

    // Copy all the old entries into the new table
    u16 mask = cap - 1;
    for (u16 i = 0; i < old_cap; ++i) {
        String e = old[i];
        if (!e.ptr) continue;

        u16 j = mix16(e.hash) & mask;
        while (table[j].ptr != nullptr) j = (j + 1) & mask;
        table[j] = e;
        ++size;
    }

    _heap_free(heap, old);
}

String* String::intern_slot(const char* s) {
    init();

    u16 l = strlen(s);
    u16 h = fnv1a16(s, l);

    // Grow the table if the load factor exceeds 0.7
    if ((uint64_t)(size + 1) * 10ull >= (uint64_t)cap * 7ull) {
        grow();
    }

    u16 mask = cap - 1;
    u16 i = mix16(h) & mask;

    for (;;) {
        String& e = table[i];

        // Empty slot, insert here
        if (e.ptr == nullptr) {
            // Reallocate the string to make sure its owned by the general heap
            char* p = (char*)_heap_malloc(heap, (size_t)l + 1);
            if (l) memcpy(p, s, l);
            p[l] = '\0';

            e.hash = h;
            e.len  = l;
            e.ptr  = p;
            ++size;
            return &e;
        }

        if (e.hash == h && e.len == l &&
            (l == 0 || memcmp(e.ptr, s, l) == 0)) {
            return &e;
        }

        i = (i + 1) & mask;
    }
}

String::String(const char* str) {
    if (str == nullptr) {
        hash = 0;
        len  = 0;
        ptr  = nullptr;
        return;
    }

    String* slot = intern_slot(str);
    hash = slot->hash;
    len  = slot->len;
    ptr  = slot->ptr;
}

} // namespace registry
