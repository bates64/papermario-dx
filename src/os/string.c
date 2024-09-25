#include "ultra64.h"

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
