#include "common.h"
#include <memory.h>

void* memset(void* dest, int val, size_t len) {
    unsigned char* ptr = dest;

    while (len--) {
        *ptr++ = val;
    }
    return dest;
}

void *__memmove_chk(void *dest, const void *src, size_t n, size_t destlen) {
    ASSERT_MSG(n <= destlen, "buffer overflow in bcopy/memmove");
    bcopy(src, dest, (int)n);
    return dest;
}
