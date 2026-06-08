#include "common.h"
#include <stdarg.h>
#include "PR/os_internal_thread.h"
#include <stdio.h>
#include <string.h>
#include "dx/backtrace.h"
#include "include_asset.h"

typedef struct {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ char stack[0x800];
    /* 0x9B0 */ OSMesgQueue queue;
    /* 0x9C8 */ OSMesg mesg;
    /* 0x9CC */ u16* frameBuf;
    /* 0x9D0 */ u16 width;
    /* 0x9D2 */ u16 height;
} CrashScreen; // size = 0x9D4

BSS CrashScreen gCrashScreen;

u8 gCrashScreencharToGlyph[128] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 41, -1, -1, -1, 43, -1, -1, 37, 38, -1, 42,
    -1, 39, 44, -1, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  36, -1, -1, -1, -1, 40, -1, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1,
};

INCLUDE_IMG("crash_screen/font.png", gCrashScreenFont);

// The font image is on 6x7 grid
#define GLYPH(x, y) (x + (y * 5))

// RGBA5551 colors
#define COLOR_WHITE  0xFFFF
#define COLOR_RED    0xF801
#define COLOR_YELLOW 0xFFE1
#define COLOR_CYAN   0x07FF
#define COLOR_GREY   0x8C63

u16 gCrashScreenColor = COLOR_WHITE;

const char* gFaultCauses[18] = {
    "Interrupt",
    "TLB modification",
    "TLB exception on load",
    "TLB exception on store",
    "Address error on load",
    "Address error on store",
    "Bus error on inst.",
    "Bus error on data",
    "System call exception",
    "Breakpoint exception",
    "Reserved instruction",
    "Coprocessor unusable",
    "Arithmetic overflow",
    "Trap exception",
    "Virtual coherency on inst.",
    "Floating point exception",
    "Watchpoint exception",
    "Virtual coherency on data",
};

const char* gFPCSRFaultCauses[6] = {
    "Unimplemented operation",
    "Invalid operation",
    "Division by zero",
    "Overflow",
    "Underflow",
    "Inexact operation",
};

char crashScreenAssertMessage[0x100] = {0};

void crash_screen_set_assert_info(const char* message) {
    strncpy(crashScreenAssertMessage, message, sizeof(crashScreenAssertMessage));
    crashScreenAssertMessage[sizeof(crashScreenAssertMessage) - 1] = '\0';
}

void crash_screen_sleep(s32 ms) {
    u64 cycles = ms * 1000LL * 46875000LL / 1000000ULL;

    osSetTime(0);

    while (osGetTime() < cycles) {
        // wait
    }
}

void crash_screen_draw_rect(s32 x, s32 y, s32 width, s32 height) {
    u16* ptr;
    s32 i;
    s32 j;

    if (gCrashScreen.width == (SCREEN_WIDTH * 2)) {
        x <<= 1;
        y <<= 1;
        width <<= 1;
        height <<= 1;
    }

    ptr = gCrashScreen.frameBuf + gCrashScreen.width * y + x;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            *ptr = ((*ptr & 0xE738) >> 2) | 1;
            ptr++;
        }

        ptr += gCrashScreen.width - width;
    }
}

/// Returns X advance.
s32 crash_screen_draw_glyph(s32 x, s32 y, s32 glyph) {
    s32 shift = ((glyph % 5) * 6);
    u16 width = gCrashScreen.width;
    const u32* data = &((u32*)gCrashScreenFont)[glyph / 5 * 7];
    s32 i;
    s32 j;
    u16 color = gCrashScreenColor;

    switch (glyph) {
        case GLYPH(3, 10): // ;
        case GLYPH(4, 10): // ,
            y += 1;
            break;
        case GLYPH(1, 14): // g
        case GLYPH(0, 16): // p
        case GLYPH(1, 16): // q
        case GLYPH(4, 17): // y
            y += 2;
            break;
    }

    if (width == SCREEN_WIDTH) {
        u16* ptr = gCrashScreen.frameBuf + (gCrashScreen.width) * y + x;

        for (i = 0; i < 7; i++) {
            u32 bit = 0x80000000U >> shift;
            u32 rowMask = *data++;

            for (j = 0; j < 6; j++) {
                if (bit & rowMask) {
                    *ptr++ = color;
                } else {
                    ptr++; // dont draw
                }
                bit >>= 1;
            }

            ptr += gCrashScreen.width - 6;
        }
    } else if (width == (SCREEN_WIDTH * 2)) {
        u16* ptr = gCrashScreen.frameBuf + (y * 0x500) + (x * 2);

        for (i = 0; i < 7; i++) {
            u32 bit = 0x80000000U >> shift;
            u32 rowMask = *data++;

            for (j = 0; j < 6; j++) {
                u16 temp = (bit & rowMask) ? color : 1;

                ptr[0] = temp;
                ptr[1] = temp;
                ptr[(SCREEN_WIDTH * 2)] = temp;
                ptr[(SCREEN_WIDTH * 2) + 1] = temp;
                ptr += 2;
                bit >>= 1;
            }

            ptr += (0x9E8 / 2);
        }
    }

    // Calculate x advance by counting the width of the glyph + 1 pixel of padding
    if (glyph == GLYPH(2, 15)) return 7; // m - fucked up hack
    s32 xAdvance = 0;
    data = &((u32*)gCrashScreenFont)[glyph / 5 * 7];
    for (i = 0; i < 7; i++) { // 7 rows
        u32 bit = 0x80000000U >> shift;
        u32 rowMask = *data++;
        for (j = 1; j < 6; j++) { // 6 columns
            if (bit & rowMask) {
                if (xAdvance < j) {
                    xAdvance = j;
                }
            }
            bit >>= 1;
        }
    }
    return xAdvance + 1;
}

char* crash_screen_copy_to_buf(char* dest, const char* src, size_t size) {
    memcpy(dest, src, size);
    return dest + size;
}

/// Returns y advance.
s32 crash_screen_printf(s32 x, s32 y, const char* fmt, ...) {
    u8* ptr;
    u32 glyph;
    s32 size;
    u8 buf[0x100];
    va_list args;
    s32 ox = x;

    va_start(args, fmt);

    size = _Printf(crash_screen_copy_to_buf, (s8*)buf, fmt, args);

    if (size > 0) {
        ptr = buf;

        while (size > 0) {
            u8* charToGlyph = gCrashScreencharToGlyph;

            glyph = charToGlyph[*ptr & 0x7F];

            if (glyph != 0xFF) {
                crash_screen_draw_glyph(x, y, glyph);
            }

            x += 6;

            if (*ptr == '\n') {
                x = ox;
                y += 10;
            }

            size--;
            ptr++;
        }
    }

    // If last character was not a newline, move to the next line
    if (x != ox) {
        y += 10;
    }
    return y;

    va_end(args);
}

/// Returns y advance.
s32 crash_screen_printf_proportional(s32 x, s32 y, const char* fmt, ...) {
    u8* ptr;
    u32 glyph;
    s32 size;
    u8 buf[0x200];
    va_list args;
    s32 ox = x;

    va_start(args, fmt);

    size = _Printf(crash_screen_copy_to_buf, (s8*)buf, fmt, args);

    if (size > 0) {
        ptr = buf;

        while (size > 0) {
            u8* charToGlyph = gCrashScreencharToGlyph;

            glyph = charToGlyph[*ptr & 0x7F];

            if (glyph != 0xFF) {
                x += crash_screen_draw_glyph(x, y, glyph);
            } else {
                x += 4;
            }

            if (*ptr == '\n') {
                x = ox;
                y += 10;
            }

            size--;
            ptr++;
        }
    }

    // If last character was not a newline, move to the next line
    if (x != ox) {
        y += 10;
    }
    return y;

    va_end(args);
}

void crash_screen_print_fpr(s32 x, s32 y, s32 regNum, void* addr) {
    u32 bits = *(u32*)addr;
    s32 exponent = ((bits & 0x7F800000U) >> 0x17) - 0x7F;

    if ((exponent >= -0x7E && exponent <= 0x7F) || bits == 0) {
        crash_screen_printf(x, y, "F%02d:%+.3e", regNum, *(f32*)addr);
    } else {
        crash_screen_printf(x, y, "F%02d:---------", regNum);
    }
}

void crash_screen_print_fpcsr(u32 value) {
    s32 i;
    u32 flag = 0x20000;

    crash_screen_printf(30, 155, "FPCSR:%08XH", value);

    for (i = 0; i < 6;) {
        if (value & flag) {
            crash_screen_printf(132, 155, "(%s)", gFPCSRFaultCauses[i]);
            break;
        }

        i++;
        flag >>= 1;
    }
}

static const char* sRegNames[32] = {
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0",   "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0",   "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8",   "t9", "k0", "k1", "gp", "sp", "fp", "ra",
};

#define RD(op) (((op) >> 11) & 0x1F)
#define RT(op) (((op) >> 16) & 0x1F)
#define RS(op) (((op) >> 21) & 0x1F)
#define IMM(op) ((s16)((op) & 0xFFFF))
#define SA(op) (((op) >> 6) & 0x1F)
#define TARGET(op, pc) ((((pc) & 0xF0000000) | (((op) & 0x03FFFFFF) << 2)))

/// Disassemble a single MIPS instruction into buf. Returns buf.
static char* crash_screen_disasm(u32 pc, u32 op, char* buf) {
    u32 opcode = op >> 26;
    u32 func = op & 0x3F;

    // Load/store instructions
    switch (opcode) {
        case 0x20: sprintf(buf, "lb    %s, %d(%s)", sRegNames[RT(op)], IMM(op), sRegNames[RS(op)]); return buf;
        case 0x21: sprintf(buf, "lh    %s, %d(%s)", sRegNames[RT(op)], IMM(op), sRegNames[RS(op)]); return buf;
        case 0x23: sprintf(buf, "lw    %s, %d(%s)", sRegNames[RT(op)], IMM(op), sRegNames[RS(op)]); return buf;
        case 0x24: sprintf(buf, "lbu   %s, %d(%s)", sRegNames[RT(op)], IMM(op), sRegNames[RS(op)]); return buf;
        case 0x25: sprintf(buf, "lhu   %s, %d(%s)", sRegNames[RT(op)], IMM(op), sRegNames[RS(op)]); return buf;
        case 0x28: sprintf(buf, "sb    %s, %d(%s)", sRegNames[RT(op)], IMM(op), sRegNames[RS(op)]); return buf;
        case 0x29: sprintf(buf, "sh    %s, %d(%s)", sRegNames[RT(op)], IMM(op), sRegNames[RS(op)]); return buf;
        case 0x2B: sprintf(buf, "sw    %s, %d(%s)", sRegNames[RT(op)], IMM(op), sRegNames[RS(op)]); return buf;
        case 0x31: sprintf(buf, "lwc1  f%d, %d(%s)", RT(op), IMM(op), sRegNames[RS(op)]); return buf;
        case 0x39: sprintf(buf, "swc1  f%d, %d(%s)", RT(op), IMM(op), sRegNames[RS(op)]); return buf;
    }

    // ALU immediate
    switch (opcode) {
        case 0x09: sprintf(buf, "addiu %s, %s, %d", sRegNames[RT(op)], sRegNames[RS(op)], IMM(op)); return buf;
        case 0x0C: sprintf(buf, "andi  %s, %s, 0x%X", sRegNames[RT(op)], sRegNames[RS(op)], (u16)IMM(op)); return buf;
        case 0x0D: sprintf(buf, "ori   %s, %s, 0x%X", sRegNames[RT(op)], sRegNames[RS(op)], (u16)IMM(op)); return buf;
        case 0x0A: sprintf(buf, "slti  %s, %s, %d", sRegNames[RT(op)], sRegNames[RS(op)], IMM(op)); return buf;
        case 0x0B: sprintf(buf, "sltiu %s, %s, %d", sRegNames[RT(op)], sRegNames[RS(op)], IMM(op)); return buf;
        case 0x0F: sprintf(buf, "lui   %s, 0x%04X", sRegNames[RT(op)], (u16)IMM(op)); return buf;
    }

    // Branch
    switch (opcode) {
        case 0x04: sprintf(buf, "beq   %s, %s, 0x%08X", sRegNames[RS(op)], sRegNames[RT(op)], pc + 4 + (IMM(op) << 2)); return buf;
        case 0x05: sprintf(buf, "bne   %s, %s, 0x%08X", sRegNames[RS(op)], sRegNames[RT(op)], pc + 4 + (IMM(op) << 2)); return buf;
        case 0x06: sprintf(buf, "blez  %s, 0x%08X", sRegNames[RS(op)], pc + 4 + (IMM(op) << 2)); return buf;
        case 0x07: sprintf(buf, "bgtz  %s, 0x%08X", sRegNames[RS(op)], pc + 4 + (IMM(op) << 2)); return buf;
    }

    // Jump
    if (opcode == 0x02) { sprintf(buf, "j     0x%08X", TARGET(op, pc)); return buf; }
    if (opcode == 0x03) { sprintf(buf, "jal   0x%08X", TARGET(op, pc)); return buf; }

    // SPECIAL (opcode 0)
    if (opcode == 0x00) {
        if (op == 0) { sprintf(buf, "nop"); return buf; }
        switch (func) {
            case 0x08: sprintf(buf, "jr    %s", sRegNames[RS(op)]); return buf;
            case 0x09: sprintf(buf, "jalr  %s", sRegNames[RS(op)]); return buf;
            case 0x21:
                if (RT(op) == 0) { sprintf(buf, "move  %s, %s", sRegNames[RD(op)], sRegNames[RS(op)]); return buf; }
                sprintf(buf, "addu  %s, %s, %s", sRegNames[RD(op)], sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x23: sprintf(buf, "subu  %s, %s, %s", sRegNames[RD(op)], sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x24: sprintf(buf, "and   %s, %s, %s", sRegNames[RD(op)], sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x25:
                if (RT(op) == 0) { sprintf(buf, "move  %s, %s", sRegNames[RD(op)], sRegNames[RS(op)]); return buf; }
                sprintf(buf, "or    %s, %s, %s", sRegNames[RD(op)], sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x26: sprintf(buf, "xor   %s, %s, %s", sRegNames[RD(op)], sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x27: sprintf(buf, "nor   %s, %s, %s", sRegNames[RD(op)], sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x2A: sprintf(buf, "slt   %s, %s, %s", sRegNames[RD(op)], sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x2B: sprintf(buf, "sltu  %s, %s, %s", sRegNames[RD(op)], sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x00: sprintf(buf, "sll   %s, %s, %d", sRegNames[RD(op)], sRegNames[RT(op)], SA(op)); return buf;
            case 0x02: sprintf(buf, "srl   %s, %s, %d", sRegNames[RD(op)], sRegNames[RT(op)], SA(op)); return buf;
            case 0x03: sprintf(buf, "sra   %s, %s, %d", sRegNames[RD(op)], sRegNames[RT(op)], SA(op)); return buf;
            case 0x18: sprintf(buf, "mult  %s, %s", sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x19: sprintf(buf, "multu %s, %s", sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x1A: sprintf(buf, "div   %s, %s", sRegNames[RS(op)], sRegNames[RT(op)]); return buf;
            case 0x10: sprintf(buf, "mfhi  %s", sRegNames[RD(op)]); return buf;
            case 0x12: sprintf(buf, "mflo  %s", sRegNames[RD(op)]); return buf;
        }
    }

    sprintf(buf, ".word 0x%08X", op);
    return buf;
}

/// Print disassembly context around the crash PC (1 line before, crash line, 1 line after).
static s32 crash_screen_print_disasm(s32 x, s32 y, u32 pc) {
    char buf[64];

    for (s32 i = -1; i <= 1; i++) {
        u32 addr = pc + (i * 4);
        u32 phys = 0x80000000 | osVirtualToPhysical((void*)addr);
        if (phys < 0x80000400 || phys >= 0x80800000 || (addr & 3) != 0) {
            continue;
        }
        u32 instr = *(u32*)phys;
        crash_screen_disasm(addr, instr, buf);

        if (i == 0) {
            gCrashScreenColor = COLOR_WHITE;
            y = crash_screen_printf(x, y, "  > %08X: %s", addr, buf);
        } else {
            gCrashScreenColor = COLOR_GREY;
            y = crash_screen_printf(x, y, "    %08X: %s", addr, buf);
        }
    }

    return y;
}

/// Formats a human-readable error message for the crash.
static s32 crash_screen_print_error(s32 x, s32 y, OSThread* faultedThread) {
    __OSThreadContext* ctx = &faultedThread->context;
    s16 causeIndex = ((ctx->cause >> 2) & 0x1F);

    gCrashScreenColor = COLOR_RED;

    if (crashScreenAssertMessage[0] != '\0') {
        y = crash_screen_printf_proportional(x, y, crashScreenAssertMessage);
        gCrashScreenColor = COLOR_WHITE;
        return y;
    }

    u32 badvaddr = (u32)ctx->badvaddr;

    switch (causeIndex) {
        case 1: // TLB modification
            y = crash_screen_printf_proportional(x, y, "Segfault: write to 0x%08X", badvaddr);
            break;
        case 2: // TLB exception on load
            if (badvaddr == 0) {
                y = crash_screen_printf_proportional(x, y, "Attempt to read from nullptr");
            } else {
                y = crash_screen_printf_proportional(x, y, "Segfault: read from 0x%08X", badvaddr);
            }
            break;
        case 3: // TLB exception on store
            if (badvaddr == 0) {
                y = crash_screen_printf_proportional(x, y, "Attempt to write to nullptr");
            } else {
                y = crash_screen_printf_proportional(x, y, "Segfault: write to 0x%08X", badvaddr);
            }
            break;
        case 4: // Address error on load
            y = crash_screen_printf_proportional(x, y, "Unaligned read from 0x%08X", badvaddr);
            break;
        case 5: // Address error on store
            y = crash_screen_printf_proportional(x, y, "Unaligned write to 0x%08X", badvaddr);
            break;
        case 6: // Bus error on inst
        case 7: // Bus error on data
            y = crash_screen_printf_proportional(x, y, "Bus error at 0x%08X", badvaddr);
            break;
        case 10: // Reserved instruction
            y = crash_screen_printf_proportional(x, y, "Invalid instruction at 0x%08X", (u32)ctx->pc);
            break;
        case 12: // Arithmetic overflow
            y = crash_screen_printf_proportional(x, y, "Integer overflow");
            break;
        case 13: // Trap
            y = crash_screen_printf_proportional(x, y, "Trap");
            break;
        case 15: { // Floating point exception
            u32 fpcsr = ctx->fpcsr;
            u32 flag = 0x20000;
            const char* fpCause = "Float exception";
            for (s32 i = 0; i < 6; i++, flag >>= 1) {
                if (fpcsr & flag) {
                    fpCause = gFPCSRFaultCauses[i];
                    break;
                }
            }
            y = crash_screen_printf_proportional(x, y, "Float: %s", fpCause);
            break;
        }
        default: {
            // Fall back to raw cause name
            s16 idx = causeIndex;
            if (idx == 23) idx = 16;
            if (idx == 31) idx = 17;
            y = crash_screen_printf_proportional(x, y, "%s", gFaultCauses[idx]);
            break;
        }
    }

    gCrashScreenColor = COLOR_WHITE;
    return y;
}

/// Print the location line (file:line and overlay) for a resolved symbol.
/// Returns y advance.
static s32 crash_screen_print_location(s32 x, s32 y, ResolvedSym* sym) {
    b32 hasFile = sym->file[0] != '\0';
    b32 hasOverlay = sym->overlay[0] != '\0';
    b32 hasLine = sym->line >= 0;

    if (!hasFile && !hasOverlay && !hasLine) {
        return y;
    }

    gCrashScreenColor = COLOR_GREY;
    if (hasFile && hasLine && hasOverlay) {
        y = crash_screen_printf_proportional(x, y, "    %s:%ld (%s)", sym->file, sym->line, sym->overlay);
    } else if (hasFile && hasLine) {
        y = crash_screen_printf_proportional(x, y, "    %s:%ld", sym->file, sym->line);
    } else if (hasFile && hasOverlay) {
        y = crash_screen_printf_proportional(x, y, "    %s (%s)", sym->file, sym->overlay);
    } else if (hasOverlay && hasLine) {
        y = crash_screen_printf_proportional(x, y, "    %s:%ld", sym->overlay, sym->line);
    } else if (hasOverlay) {
        y = crash_screen_printf_proportional(x, y, "    (%s)", sym->overlay);
    } else if (hasFile) {
        y = crash_screen_printf_proportional(x, y, "    %s", sym->file);
    } else {
        y = crash_screen_printf_proportional(x, y, "    :%ld", sym->line);
    }

    return y;
}

void crash_screen_draw(OSThread* faultedThread) {
    __OSThreadContext* ctx = &faultedThread->context;
    s32 bt[16];
    s32 max = backtrace_thread((void**)bt, ARRAY_COUNT(bt), faultedThread);
    s32 i = 0;
    ResolvedSym sym;
    b32 isFirstFrame = true;

    osWritebackDCacheAll();

    s32 x = 10;
    s32 y = 10;

    crash_screen_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Print error message
    y = crash_screen_print_error(x, y, faultedThread);
    if (crashScreenAssertMessage[0] != '\0') {
        i = 1; // Don't include is_debug_panic line in backtrace.
    }
    y += 5;

    b32 hasEvtBacktrace = EvtCurrentScript != nullptr;

    if (hasEvtBacktrace) {
        // Print C backtrace, stopping at EVT engine internals
        extern s32 evt_execute_next_command(Evt*);
        for (; i < max; i++) {
            u32 addr = bt[i];
            if (addr >= (u32)evt_execute_next_command && addr < (u32)evt_execute_next_command + 0x2000) {
                break;
            }
            backtrace_resolve_addr(addr, &sym, -1);
            gCrashScreenColor = COLOR_CYAN;
            y = crash_screen_printf_proportional(x, y, "%s", sym.name);
            y = crash_screen_print_location(x, y, &sym);
            if (isFirstFrame && crashScreenAssertMessage[0] == '\0') {
                y += 5;
                y = crash_screen_print_disasm(x, y, (u32)ctx->pc);
                y += 5;
                isFirstFrame = false;
            }
        }

        // Print EVT script chain (innermost to outermost)
        Evt* s = EvtCurrentScript;
        while (s != nullptr) {
            backtrace_resolve_addr((u32)s->ptrFirstLine, &sym, s->curLine);
            gCrashScreenColor = COLOR_YELLOW;
            y = crash_screen_printf_proportional(x, y, "%s", sym.name);
            y = crash_screen_print_location(x, y, &sym);
            s = s->blockingParent;
        }
    } else {
        for (; i < max; i++) {
            backtrace_resolve_addr(bt[i], &sym, -1);
            gCrashScreenColor = COLOR_CYAN;
            y = crash_screen_printf_proportional(x, y, "%s", sym.name);
            y = crash_screen_print_location(x, y, &sym);
            if (isFirstFrame && crashScreenAssertMessage[0] == '\0') {
                y += 5;
                y = crash_screen_print_disasm(x, y, (u32)ctx->pc);
                y += 5;
                isFirstFrame = false;
            }
        }
    }

    gCrashScreenColor = COLOR_WHITE;

    osViBlack(0);
    osViRepeatLine(0);
    osViSwapBuffer(gCrashScreen.frameBuf);
}

OSThread* crash_screen_get_faulted_thread(void) {
    OSThread* thread = __osGetActiveQueue();

    while (thread->priority != -1) {
        if (thread->priority > 0 && thread->priority < 0x7F && (thread->flags & 3)) {
            return thread;
        }

        thread = thread->tlnext;
    }

    return nullptr;
}

void crash_screen_thread_entry(void* unused) {
    OSMesg mesg;
    OSThread* faultedThread;

    osSetEventMesg(OS_EVENT_CPU_BREAK, &gCrashScreen.queue, (OSMesg)1);
    osSetEventMesg(OS_EVENT_FAULT, &gCrashScreen.queue, (OSMesg)2);

    do {
        osRecvMesg(&gCrashScreen.queue, &mesg, 1);
        faultedThread = crash_screen_get_faulted_thread();
    } while (faultedThread == nullptr);

    osStopThread(faultedThread);
    crash_screen_draw(faultedThread);

    while (true) {}
}

void crash_screen_set_draw_info(u16* frameBufPtr, s16 width, s16 height) {
    gCrashScreen.frameBuf = (u16*)((u32)frameBufPtr | 0xA0000000);
    gCrashScreen.width = width;
    gCrashScreen.height = height;
}

void crash_screen_init(void) {
    gCrashScreen.width = SCREEN_WIDTH;
    gCrashScreen.height = 16;
    gCrashScreen.frameBuf = (u16*)((osMemSize | 0xA0000000) - ((SCREEN_WIDTH * SCREEN_HEIGHT) * 2));
    osCreateMesgQueue(&gCrashScreen.queue, &gCrashScreen.mesg, 1);
    osCreateThread(&gCrashScreen.thread, THREAD_ID_CRASH, crash_screen_thread_entry, nullptr,
                   gCrashScreen.stack + sizeof(gCrashScreen.stack), 0x80);
    osStartThread(&gCrashScreen.thread);

    // gCrashScreencharToGlyph is hard to modify, so we'll just do it here
    u8 chars[] =
        "_[]<>"
        "|{};,"
        "\"#$&'"
        "/=@\\`"
        "abcde"
        "fghij"
        "klmno"
        "pqrst"
        "uvwxy"
        "z";
    s32 i;
    for (i = 0; i < ARRAY_COUNT(chars); i++) {
        gCrashScreencharToGlyph[chars[i]] = GLYPH(0, 9) + i;
    }
}

// unused
void crash_screen_printf_with_bg(s16 x, s16 y, const char* fmt, ...) {
    u8* ptr;
    u32 glyph;
    s32 size;
    u8 buf[0x100];
    va_list args;

    va_start(args, fmt);

    size = _Printf(crash_screen_copy_to_buf, (s8*)buf, fmt, args);

    if (size > 0) {
        crash_screen_draw_rect(x - 6, y - 6, (size + 2) * 6, 19);
        ptr = buf;

        while (size > 0) {
            u8* charToGlyph = gCrashScreencharToGlyph;

            glyph = charToGlyph[*ptr & 0x7F];

            if (glyph != 0xFF) {
                crash_screen_draw_glyph(x, y, glyph);
            }

            x += 6;
            size--;
            ptr++;
        }
    }

    va_end(args);
}
