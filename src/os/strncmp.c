#include "ultra64.h"

int strncmp(const char* str1, const char* str2, size_t n) {
    size_t i;

    for (i = 0; (*str1 == *str2) && (i < n); i++) {
        if (*str1 == 0) {
            if (*str2 == 0) {
                return 0;
            }
            break;
        }
        if (*str2 == 0) {
            break;
        }
        str1++;
        str2++;
    }
    return (i != n) ? *str1 - *str2 : 0;
}
