#include "common.h"
#include "libc/xstdio.h"
#include <memory.h>

static char *proutSprintf(char *dst, const char *src, size_t count);

int sprintf(char* s, const char* fmt, ...) {
    s32 ret;
    va_list argp;
    va_start(argp, fmt);

    ret = _Printf(&proutSprintf, s, fmt, argp);

    if (ret >= 0) {
        s[ret] = 0;
    }

    return ret;
}

static char *proutSprintf(char *dst, const char *src, size_t count) {
    return (char *)memcpy((u8 *)dst, (u8 *)src, count) + count;
}

int __sprintf_chk(char * restrict s, int flag, size_t s_len, const char * restrict fmt, ...) {
    int ret;
    va_list argp;
    va_start(argp, fmt);

    ret = _Printf(&proutSprintf, s, fmt, argp);

    if (ret >= 0) {
        s[ret] = 0;
    }

    ASSERT_MSG(ret < s_len, "buffer overflow in sprintf");

    return ret;
}
