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

typedef struct {
    char* dst;
    size_t space;
} SnprintfState;

static char* proutSnprintf(char* arg, const char* src, size_t count) {
    SnprintfState* state = (SnprintfState*) arg;
    size_t copied = count < state->space ? count : state->space;

    memcpy((u8*) state->dst, (u8*) src, copied);
    state->dst += copied;
    state->space -= copied;
    return arg;
}

int snprintf(char* s, size_t size, const char* fmt, ...) {
    SnprintfState state = { s, size > 0 ? size - 1 : 0 };
    s32 ret;
    va_list argp;
    va_start(argp, fmt);

    ret = _Printf(&proutSnprintf, (char*) &state, fmt, argp);

    if (size > 0) {
        *state.dst = '\0';
    }

    return ret;
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
