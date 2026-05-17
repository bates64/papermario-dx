#include "common.h"
#include <memory.h>

void* memset(void* dest, int val, size_t len) {
    unsigned char* ptr = dest;

    while (len--) {
        *ptr++ = val;
    }
    return dest;
}

void *__memset_chk(void *dest, int val, size_t len, size_t destlen) {
    ASSERT_MSG(len <= destlen, "buffer overflow in memset");
    return __builtin_memset(dest, val, len);
}

void *memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;

    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d += n;
        s += n;
        while (n--) {
            *--d = *--s;
        }
    }
    return dest;
}

void *__memmove_chk(void *dest, const void *src, size_t n, size_t destlen) {
    ASSERT_MSG(n <= destlen, "buffer overflow in bcopy/memmove");
    return __builtin_memmove(dest, src, n);
}
