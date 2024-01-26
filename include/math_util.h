#pragma once

#include "macros.h"

// Float lerp.
// Return the value between [from, to] based on f's value between [0.0, 1.0].
ALWAYS_INLINE f32 lerpf(f32 from, f32 to, f32 f) {
    return (from + (f * (to - from)));
}

// Precise float lerp.
// Return the value between [from, to] based on f's value between [0.0, 1.0].
// Sloer but more precise than the regular float lerp.
ALWAYS_INLINE f32 lerpf_precise(f32 from, f32 to, f32 f) {
    return ((from * (1.0f - f)) + (to * f));
}

// Integer lerp.
// Return the value between [from, to] based on f's value between [0, 256].
// Faster than float lerps.
ALWAYS_INLINE s32 lerpi(s32 from, s32 to, u32 f) {
    return (((f * (to - from)) >> 8) + from);
}

// Helper function for smoothstop.
ALWAYS_INLINE f32 to_smoothstop(f32 x) {
    f32 sq = sqr(1.0f - x);
    return (1.0f - sq);
}

// Commonly known as ease-in.
ALWAYS_INLINE f32 smoothstart(f32 from, f32 to, f32 amount) {
    return lerpf(from, to, sqr(amount));
}

// Commonly known as ease-out.
ALWAYS_INLINE f32 smoothstop(f32 from, f32 to, f32 amount) {
    return lerpf(from, to, to_smoothstop(amount));
}

// Commonly known as ease-in-out.
ALWAYS_INLINE f32 smoothstep(f32 from, f32 to, f32 amount) {
    amount = sqr(amount) * (3.0f - (2.0f * amount));

    return lerpf(from, to, amount);
}

// Remaps a number from one range to another.
// Return the value between [fromB, toB] based on X's value between [fromA, toA].
// Equivalent to lerp but with a custom range for f.
ALWAYS_INLINE f32 remap(f32 f, f32 fromA, f32 toA, f32 fromB, f32 toB) {
    return ((((f - fromA) / (toA - fromA)) * (toB - fromB)) + fromB);
}

// Inline asm functions:

/// Load upper immediate.
ALWAYS_INLINE void lui(u32* dest, u32 val) {
    __asm__("lui %0, %1" : "=r"(*dest) : "K"(val));
}

/// OR immediate.
ALWAYS_INLINE void ori_self(u32* dest, u32 val) {
    __asm__("ori %0, $0, %1" : "+r"(*dest) : "K"(val));
}

/// Multiply two floats without a nop.
ALWAYS_INLINE float mul_without_nop(float a, float b) {
    float ret;
    __asm__("mul.s %0, %1, %2" : "=f"(ret) : "f"(a), "f"(b));
    return ret;
}

/// Write a 32 bit value into the low order bytes of a register.
ALWAYS_INLINE void swr(void* addr, int val, const int offset) {
    __asm__("swr %1, %2(%0)" : : "g"(addr), "g"(val), "I"(offset));
}

/// Write a 32 bit value into the high order bytes of a register.
ALWAYS_INLINE void swl(void* addr, int val, const int offset) {
    __asm__("swl %1, %2(%0)" : : "g"(addr), "g"(val), "I"(offset));
}

/// Convert a float to an int.
ALWAYS_INLINE int mfc1(float in) {
    int out;
    __asm__("mfc1 %0,%1" : "=r" (out) : "f" (in));
    return out;
}

/// Convert an int to a float.
ALWAYS_INLINE float mtc1(int in) {
    float out;
    __asm__("mtc1 %1, %0" : "=f"(out) : "r"(in));
    return out;
}

/// Rounds towards infinity
ALWAYS_INLINE s32 ceilf(const f32 in) {
    f32 tmp;
    __asm__("ceil.w.s %0,%1" : "=f" (tmp) : "f" (in));
    return mfc1(tmp);
}
/// Rounds towards negative infinity
ALWAYS_INLINE s32 floorf(const f32 in) {
    f32 tmp;
    __asm__("floor.w.s %0,%1" : "=f" (tmp) : "f" (in));
    return mfc1(tmp);
}
/// Rounds towards the nearest integer
ALWAYS_INLINE s32 roundf(const f32 in) {
    f32 tmp;
    __asm__("round.w.s %0,%1" : "=f" (tmp) : "f" (in));
    return mfc1(tmp);
}

/// Absolute value of a float value
ALWAYS_INLINE f32 absf(const f32 in) {
    f32 out;
    __asm__("abs.s %0,%1" : "=f" (out) : "f" (in)); //? __builtin_fabsf(x)
    return out;
}
/// Absolute value of a double value
ALWAYS_INLINE f64 absd(const f64 in) {
    f64 out;
    __asm__("abs.d %0,%1" : "=f" (out) : "f" (in));
    return out;
}

/// Absolute value of an integer value
ALWAYS_INLINE s32 absi(const s32 in) {
    s32 t0 = (in >> 31);
    return ((in ^ t0) - t0);
}
/// Absolute value of a short value
ALWAYS_INLINE s32 abss(const s16 in) {
    s32 t0 = (in >> 31);
    return ((in ^ t0) - t0);
}

/// Constructs a float in registers, which can be faster than gcc's default of loading a float from rodata.
/// Especially fast for halfword floats, which get loaded with a `lui` + `mtc1`.
ALWAYS_INLINE float construct_float(const float f) {
    u32 r;
    u32 i = *(u32*)(&f);

    if (!__builtin_constant_p(i)) {
        return *(float*)(&i);
    }

    u32 upper = (i >> 16);
    u32 lower = (i & BITMASK(16));

    if ((i & BITMASK(16)) == 0) {
        lui(&r, upper);
    } else if ((i & (BITMASK(16) << 16)) == 0) {
        ori_self(&r, lower);
    } else {
        lui(&r, upper);
        ori_self(&r, lower);
    }

    return mtc1(r);
}
