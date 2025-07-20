#include "common.h"
#include <string.h>

char* strcpy(char* dest, const char* src) {
    const unsigned char* var_a1 = src;
    unsigned char* var_v1 = dest;

    while (*var_a1 != 0) {
        *var_v1++ = *var_a1++;
    }
    *var_v1 = 0;
    return dest;
}

char* strncpy(char* dest, const char* src, size_t n) {
    const unsigned char* var_a1 = src;
    unsigned char* var_v1 = dest;

    while (n > 0 && *var_a1 != 0) {
        *var_v1++ = *var_a1++;
        n--;
    }
    *var_v1 = 0;
    return dest;
}

char *__strcpy_chk(char *dest, const char *src, size_t destlen) {
    ASSERT_MSG(strlen(src) < destlen, "buffer overflow in strcpy");
    return strcpy(dest, src);
}

char *__strncpy_chk(char *dest, const char *src, size_t n, size_t destlen) {
    ASSERT_MSG(strlen(src) < destlen, "buffer overflow in strncpy");
    return strncpy(dest, src, n);
}
