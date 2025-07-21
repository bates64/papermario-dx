#include "common.h"

char* strchr(const char* s, int c) {
    const char ch = c;
    while (*s != ch) {
        if (*s == 0)
            return NULL;
        s++;
    }
    return (char *)s;
}

size_t strlen(const char* s) {
    const char* sc = s;
    while (*sc) {
        sc++;
    }
    return sc - s;
}

char* strcat(char* dest, const char* src) {
    char* d = dest;
    while (*d) {
        d++;
    }
    while (*src) {
        *d++ = *src++;
    }
    *d = 0;
    return dest;
}

void* memcpy(void* s1, const void* s2, size_t n) {
    char* su1 = (char*)s1;
    const char *su2 = (const char*)s2;
    while (n > 0) {
        *su1++ = *su2++;
        n--;
    }
    return (void*)s1;
}

void* __memcpy_chk(void* s1, const void* s2, size_t n, size_t destlen) {
    ASSERT_MSG(n <= destlen, "buffer overflow in memcpy");
    return memcpy(s1, s2, n);
}

void* memmove(void* dest, const void* src, size_t n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;

    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d += n;
        s += n;
        while (n--) {
            *(--d) = *(--s);
        }
    }
    return dest;
}

int memcmp(const void* s1, const void* s2, size_t n) {
    const unsigned char* su1 = (const unsigned char*)s1;
    const unsigned char* su2 = (const unsigned char*)s2;

    while (n--) {
        if (*su1 != *su2) {
            return *su1 - *su2;
        }
        su1++;
        su2++;
    }
    return 0;
}
