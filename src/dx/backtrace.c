// Backtrace (call stack) support.
// Heavily based on libdragon: https://github.com/DragonMinded/libdragon/blob/trunk/src/backtrace.c

#include "common.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "nu/nusys.h"
#include "backtrace.h"
#include "PR/osint.h"

/** @brief Enable to debug why a backtrace is wrong */
#define BACKTRACE_DEBUG 0

/** @brief Function alignment enfored by the compiler (-falign-functions). */
#define FUNCTION_ALIGNMENT      32

/** @brief The "type" of funciton as categorized by the backtrace heuristic (__bt_analyze_func) */
typedef enum {
    BT_FUNCTION,                ///< Regular function with a stack frame
    BT_FUNCTION_FRAMEPOINTER,   ///< The function uses the register fp as frame pointer (normally, this happens only when the function uses alloca)
    BT_EXCEPTION,               ///< This is an exception handler (inthandler.S)
    BT_LEAF                     ///< Leaf function (no calls), no stack frame allocated, sp/ra not modified
} bt_func_type;

/** @brief Description of a function for the purpose of backtracing (filled by __bt_analyze_func) */
typedef struct {
    bt_func_type type;       ///< Type of the function
    int stack_size;          ///< Size of the stack frame
    int ra_offset;           ///< Offset of the return address from the top of the stack frame
    int fp_offset;           ///< Offset of the saved fp from the top of the stack frame; this is != 0 only if the function modifies fp (maybe as a frame pointer, but not necessarily)
} bt_func_t;

#define MIPS_OP_ADDIU_SP(op)   (((op) & 0xFFFF0000) == 0x27BD0000)   ///< Matches: addiu $sp, $sp, imm
#define MIPS_OP_DADDIU_SP(op)  (((op) & 0xFFFF0000) == 0x67BD0000)   ///< Matches: daddiu $sp, $sp, imm
#define MIPS_OP_JR_RA(op)      (((op) & 0xFFFFFFFF) == 0x03E00008)   ///< Matches: jr $ra
#define MIPS_OP_SD_RA_SP(op)   (((op) & 0xFFFF0000) == 0xFFBF0000)   ///< Matches: sd $ra, imm($sp)
#define MIPS_OP_SW_RA_SP(op)   (((op) & 0xFFFF0000) == 0xAFBF0000)   ///< Matches: sw $ra, imm($sp)
#define MIPS_OP_SD_FP_SP(op)   (((op) & 0xFFFF0000) == 0xFFBE0000)   ///< Matches: sd $fp, imm($sp)
#define MIPS_OP_SW_FP_SP(op)   (((op) & 0xFFFF0000) == 0xAFBE0000)   ///< Matches: sw $fp, imm($sp)
#define MIPS_OP_LUI_GP(op)     (((op) & 0xFFFF0000) == 0x3C1C0000)   ///< Matches: lui $gp, imm
#define MIPS_OP_NOP(op)        ((op) == 0x00000000)                  ///< Matches: nop
#define MIPS_OP_MOVE_FP_SP(op) ((op) == 0x03A0F025)                  ///< Matches: move $fp, $sp

#define debugf printf

bool __bt_analyze_func(bt_func_t *func, uint32_t *ptr, uint32_t func_start, bool from_exception);

/** @brief Converts virtual addresses to physical
 *
 * If addr is a virtual address, its physical equivalent is returned. If it's already physical, it will be unchanged. If
 * the address is invalid, -1 is returned.
 * */
static u32 get_physical_address(u32 addr) {
    return 0x80000000 | osVirtualToPhysical((void*)addr);
}

/** @brief Check if addr is a valid PC address */
static bool is_valid_address(uint32_t addr) {
    addr = get_physical_address(addr);
    return addr >= 0x80000400 && addr < 0x80800000 && (addr & 3) == 0;
}

static void backtrace_foreach(void (*cb)(void *arg, void *ptr), void *arg) {
    /*
     * This function is called in very risky contexts, for instance as part of an exception
     * handler or during an assertion. We try to always provide as much information as
     * possible in these cases, with graceful degradation if something more elaborate cannot
     * be extracted. Thus, this function:
     *
     *  * Must not use malloc(). The heap might be corrupted or empty.
     *  * Must not use assert(), because that might trigger recursive assertions.
     *  * Must avoid raising exceptions. Specifically, it must avoid risky memory accesses
     *    to wrong addresses.
     */

    uint32_t* exception_ra;
    uint32_t func_start;

    // Current value of SP/RA/FP registers.
    uint32_t *sp, *ra, *fp;
    asm volatile (
        "move %0, $ra\n"
        "move %1, $sp\n"
        "move %2, $fp\n"
        : "=r"(ra), "=r"(sp), "=r"(fp)
    );

    #if BACKTRACE_DEBUG
    debugf("backtrace: start\n");
    #endif

    exception_ra = nullptr;      // If != nullptr,
    func_start = 0;            // Start of the current function (when known)

    // Start from the backtrace function itself. Put the start pointer somewhere after the initial
    // prolog (eg: 64 instructions after start), so that we parse the prolog itself to find sp/fp/ra offsets.
    ra = (uint32_t*)backtrace_foreach + 64;

    while (1) {
        // Analyze the function pointed by ra, passing information about the previous exception frame if any.
        // If the analysis fail (for invalid memory accesses), stop right away.
        bt_func_t func;
        if (!__bt_analyze_func(&func, ra, func_start, (bool)exception_ra))
            return;

        #if BACKTRACE_DEBUG
        debugf("backtrace: %s, ra=%p, sp=%p, fp=%p ra_offset=%d, fp_offset=%d, stack_size=%d\n",
            func.type == BT_FUNCTION ? "BT_FUNCTION" : (func.type == BT_EXCEPTION ? "BT_EXCEPTION" : (func.type == BT_FUNCTION_FRAMEPOINTER ? "BT_FRAMEPOINTER" : "BT_LEAF")),
            ra, sp, fp, func.ra_offset, func.fp_offset, func.stack_size);
        #endif

        switch (func.type) {
            case BT_FUNCTION_FRAMEPOINTER:
                if (!func.fp_offset) {
                    debugf("backtrace: framepointer used but not saved onto stack at %p\n", ra);
                } else {
                    // Use the frame pointer to refer to the current frame.
                    sp = fp;
                    if (!is_valid_address((uint32_t)sp)) {
                        debugf("backtrace: interrupted because of invalid frame pointer 0x%08lx\n", (uint32_t)sp);
                        return;
                    }
                }
                // FALLTHROUGH!
            case BT_FUNCTION:
                if (func.fp_offset)
                    fp = *(uint32_t**)((uint32_t)sp + func.fp_offset);
                ra = *(uint32_t**)((uint32_t)sp + func.ra_offset) - 2;
                sp = (uint32_t*)((uint32_t)sp + func.stack_size);
                exception_ra = nullptr;
                func_start = 0;
                break;
            /*
            case BT_EXCEPTION: {
                // Exception frame. We must return back to EPC, but let's keep the
                // RA value. If the interrupted function is a leaf function, we
                // will need it to further walk back.
                // Notice that FP is a callee-saved register so we don't need to
                // recover it from the exception frame (also, it isn't saved there
                // during interrupts).
                exception_ra = *(uint32_t**)((uint32_t)sp + func.ra_offset);

                // reg_block_t = __OSThreadContext ?

                // Read EPC from exception frame and adjust it with CAUSE BD bit
                ra = *(uint32_t**)((uint32_t)sp + offsetof(reg_block_t, epc) + 32);
                uint32_t cause = *(uint32_t*)((uint32_t)sp + offsetof(reg_block_t, cr) + 32);
                if (cause & C0_CAUSE_BD) ra++;

                sp = (uint32_t*)((uint32_t)sp + func.stack_size);

                // Special case: if the exception is due to an invalid EPC
                // (eg: a null function pointer call), we can rely on RA to get
                // back to the caller. This assumes that we got there via a function call
                // rather than a raw jump, but that's a reasonable assumption. It's anyway
                // the best we can do.
                if ((C0_GET_CAUSE_EXC_CODE(cause) == EXCEPTION_CODE_TLB_LOAD_I_MISS ||
                    C0_GET_CAUSE_EXC_CODE(cause) == EXCEPTION_CODE_LOAD_I_ADDRESS_ERROR) &&
                    !is_valid_address((uint32_t)ra)) {

                    // Store the invalid address in the backtrace, so that it will appear in dumps.
                    // This makes it easier for the user to understand the reason for the exception.
                    cb(arg, ra);
                    #if BACKTRACE_DEBUG
                    debugf("backtrace: %s, ra=%p, sp=%p, fp=%p ra_offset=%d, fp_offset=%d, stack_size=%d\n",
                        "BT_INVALID", ra, sp, fp, func.ra_offset, func.fp_offset, func.stack_size);
                    #endif

                    ra = exception_ra - 2;

                    // The function that jumped into an invalid PC was not interrupted by the exception: it
                    // is a regular function
                    // call now.
                    exception_ra = nullptr;
                    break;
                }

                // The next frame might be a leaf function, for which we will not be able
                // to find a stack frame. It is useful to try finding the function start.
                // Try to open the symbol table: if we find it, we can search for the start
                // address of the function.
                symtable_header_t symt = symt_open();
                if (symt.head[0]) {
                    int idx;
                    addrtable_entry_t entry = symt_addrtab_search(&symt, (uint32_t)ra, &idx);
                    while (!ADDRENTRY_IS_FUNC(entry))
                        entry = symt_addrtab_entry(&symt, --idx);
                    func_start = ADDRENTRY_ADDR(entry);
                    #if BACKTRACE_DEBUG
                    debugf("Found interrupted function start address: %08lx\n", func_start);
                    #endif
                }
            }   break;
            */
            case BT_LEAF:
                ra = exception_ra - 2;
                // A leaf function has no stack. On the other hand, an exception happening at the
                // beginning of a standard function (before RA is saved), does have a stack but
                // will be marked as a leaf function. In this case, we mus update the stack pointer.
                sp = (uint32_t*)((uint32_t)sp + func.stack_size);
                exception_ra = nullptr;
                func_start = 0;
                break;
        }

        if (is_valid_address((uint32_t)ra)) {
            // Call the callback with this stack frame
            cb(arg, ra);
        }
    }
}

static void backtrace_foreach_foreign(void (*cb)(void *arg, void *ptr), void *arg, uint32_t *sp, uint32_t *ra, uint32_t *fp) {
    uint32_t* exception_ra;
    uint32_t func_start;

    exception_ra = nullptr;      // If != nullptr,
    func_start = 0;            // Start of the current function (when known)

    while (1) {
        // Analyze the function pointed by ra, passing information about the previous exception frame if any.
        // If the analysis fail (for invalid memory accesses), stop right away.
        bt_func_t func;
        if (!__bt_analyze_func(&func, ra, func_start, (bool)exception_ra))
            return;

        #if BACKTRACE_DEBUG
        debugf("backtrace: %s, ra=%p, sp=%p, fp=%p ra_offset=%d, fp_offset=%d, stack_size=%d\n",
            func.type == BT_FUNCTION ? "BT_FUNCTION" : (func.type == BT_EXCEPTION ? "BT_EXCEPTION" : (func.type == BT_FUNCTION_FRAMEPOINTER ? "BT_FRAMEPOINTER" : "BT_LEAF")),
            ra, sp, fp, func.ra_offset, func.fp_offset, func.stack_size);
        #endif

        switch (func.type) {
            case BT_FUNCTION_FRAMEPOINTER:
                if (!func.fp_offset) {
                    debugf("backtrace: framepointer used but not saved onto stack at %p\n", ra);
                } else {
                    // Use the frame pointer to refer to the current frame.
                    sp = fp;
                    if (!is_valid_address((uint32_t)sp)) {
                        debugf("backtrace: interrupted because of invalid frame pointer 0x%08lx\n", (uint32_t)sp);
                        return;
                    }
                }
                // FALLTHROUGH!
            case BT_FUNCTION:
                if (func.fp_offset)
                    fp = *(uint32_t**)((uint32_t)sp + func.fp_offset);
                ra = *(uint32_t**)((uint32_t)sp + func.ra_offset) - 2;
                sp = (uint32_t*)((uint32_t)sp + func.stack_size);
                exception_ra = nullptr;
                func_start = 0;
                break;
            case BT_LEAF:
                ra = exception_ra - 2;
                // A leaf function has no stack. On the other hand, an exception happening at the
                // beginning of a standard function (before RA is saved), does have a stack but
                // will be marked as a leaf function. In this case, we mus update the stack pointer.
                sp = (uint32_t*)((uint32_t)sp + func.stack_size);
                exception_ra = nullptr;
                func_start = 0;
                break;
        }

        if (is_valid_address((uint32_t)ra)) {
            // Call the callback with this stack frame
            cb(arg, ra);
        }
    }
}

struct backtrace_cb_ctx {
    void **buffer;
    int size;
    int i;
};

static void backtrace_cb(void *arg, void *ptr) {
    struct backtrace_cb_ctx *ctx = arg;
    if (ctx->i >= 0 && ctx->i < ctx->size)
        ctx->buffer[ctx->i] = ptr;
    if (ctx->i < ctx->size)
        ctx->i++;
}

int backtrace(void **buffer, int size) {
    struct backtrace_cb_ctx ctx = {
        buffer,
        size,
        -1, // skip backtrace itself
    };
    backtrace_foreach(backtrace_cb, &ctx);
    return ctx.i;
}

int backtrace_thread(void **buffer, int size, OSThread *thread) {
    struct backtrace_cb_ctx ctx = {
        buffer,
        size,
        0,
    };
    u32 sp = (u32)thread->context.sp;
    u32 pc = (u32)thread->context.pc;
    u32 fp = (u32)thread->context.s8;
    backtrace_cb(&ctx, (void*)pc);
    backtrace_foreach_foreign(backtrace_cb, &ctx, (uint32_t*)sp, (uint32_t*)pc, (uint32_t*)fp);
    return ctx.i;
}

/**
 * @brief Uses the symbol table to look up the symbol corresponding to the given address.
 *
 * The address should be inside some function, otherwise an incorrect symbol will be returned.
 *
 * @param address Address to look up
 * @param out Output symbol
 * @return Offset into out->address, -1 if not found
 */
s32 address2symbol(u32 address, Symbol* out) {
    #define symbolsPerChunk 0x1000
    #define chunkSize ((sizeof(Symbol) * symbolsPerChunk))

    static u32 romHeader[0x10];
    nuPiReadRom(0, &romHeader, sizeof(romHeader));

    u32 symbolTableRomAddr = romHeader[SYMBOL_TABLE_PTR_ROM_ADDR / sizeof(*romHeader)];
    if (symbolTableRomAddr == nullptr) {
        debugf("address2symbol: no symbols available (SYMBOL_TABLE_PTR is nullptr)\n");
        return -1;
    }

    // Read the header
    SymbolTable symt;
    nuPiReadRom(symbolTableRomAddr, &symt, sizeof(SymbolTable));
    if (symt.magic[0] != 'S' || symt.magic[1] != 'Y' || symt.magic[2] != 'M' || symt.magic[3] != 'S') {
        debugf("address2symbol: no symbols available (invalid magic '%c%c%c%c')\n", symt.magic[0], symt.magic[1], symt.magic[2], symt.magic[3]);
        return -1;
    }
    if (symt.symbolCount <= 0) {
        debugf("address2symbol: no symbols available (symbolCount=%d)\n", symt.symbolCount);
        return -1;
    }

    // Read symbols in chunks
    static Symbol chunk[chunkSize];
    s32 i;
    for (i = 0; i < symt.symbolCount; i++) {
        // Do we need to load the next chunk?
        if (i % symbolsPerChunk == 0) {
            u32 chunkAddr = symbolTableRomAddr + sizeof(SymbolTable) + (i / symbolsPerChunk) * chunkSize;
            nuPiReadRom(chunkAddr, chunk, chunkSize);
        }

        Symbol sym = chunk[i % symbolsPerChunk];

        if (sym.address == address) {
            *out = sym;
            return 0;
        } else if (address < sym.address) {
            // Symbols are sorted by address, so if we passed the address, we can stop
            break;
        } else {
            // Keep searching, but remember this as the last symbol
            // incase we don't find an exact match
            *out = sym;
        }
    }
    return address - out->address;
}

char* load_symbol_string(char* dest, u32 addr, int n) {
    if (addr == nullptr) {
        return nullptr;
    }

    u32 aligned = addr & ~3;
    nuPiReadRom(aligned, dest, n);
    dest[n-1] = '\0'; // Ensure null-termination

    // Shift to start of string
    return (char*)((u32)dest + (addr & 3));
}

void backtrace_address_to_string(u32 address, char* dest) {
    Symbol sym;
    s32 offset = address2symbol(address, &sym);

    if (offset >= 0 && offset < 0x1000) { // 0x1000 = arbitrary func size limit
        char name[0x40];
        char file[0x40];
        char* namep = load_symbol_string(name, sym.nameOffset, ARRAY_COUNT(name));
        char* filep = load_symbol_string(file, sym.fileOffset, ARRAY_COUNT(file));

        offset = 0; // Don't show offsets

        if (filep == nullptr)
            if (offset == 0)
                sprintf(dest, "%s", namep);
            else
                sprintf(dest, "%s+0x%X", namep, offset);
        else
            if (offset == 0)
                sprintf(dest, "%s (%s)", namep, filep);
            else
                sprintf(dest, "%s (%s+0x%X)", namep, filep, offset);
    } else {
        sprintf(dest, "%p", address);
    }
}

void debug_backtrace(void) {
    s32 bt[32];
    s32 max = backtrace((void**)bt, ARRAY_COUNT(bt));
    s32 i;
    char buf[128];

    debugf("Backtrace:\n");
    for (i = 0; i < max; i++) {
        backtrace_address_to_string(bt[i], buf);
        debugf("    %s\n", buf);
    }
}

/**
 * @brief Analyze a function to find out its stack frame layout and properties (useful for backtracing).
 *
 * This function implements the core heuristic used by the backtrace engine. It analyzes the actual
 * code of a function in memory instruction by instruction, trying to find out whether the function
 * uses a stack frame or not, whether it uses a frame pointer, and where the return address is stored.
 *
 * Since we do not have DWARF informations or similar metadata, we can just do educated guesses. A
 * mistake in the heuristic will result probably in a wrong backtrace from this point on.
 *
 * The heuristic works as follows:
 *
 *  * Most functions do have a stack frame. In fact, 99.99% of the functions you can find in a call stack
 *    must have a stack frame, because the only functions without a stack frame are leaf functions (functions
 *    that do not call other functions), which in turns can never be part of a stack trace.
 *  * The heuristic walks the function code backwards, looking for the stack frame. Specifically, it looks
 *    for an instruction saving the RA register to the stack (eg: `sd $ra, nn($sp)`), and an instruction
 *    creating the stack frame (eg: `addiu $sp, $sp, -nn`). Once both are found, the heuristic knows how to
 *    fill in `.stack_size` and `.ra_offset` fields of the function description structure, and it can stop.
 *  * Some functions also modify $fp (the frame pointer register): sometimes, they just use it as one additional
 *    free register, and other times they really use it as frame pointer. If the heuristic finds the
 *    instruction `move $fp, $sp`, it knows that the function uses $fp as frame pointer, and will mark
 *    the function as BT_FUNCTION_FRAMEPOINTER. In any case, the field `.fp_offset` will be filled in
 *    with the offset in the stack where $fp is stored, so that the backtrace engine can track the
 *    current value of the register in any case.
 *  * The 0.01% of the functions that do not have a stack frame but appear in the call stack are leaf
 *    functions interrupted by exceptions. Leaf functions pose two important problems: first, $ra is
 *    not saved into the stack so there is no way to know where to go back. Second, there is no clear
 *    indication where the function begins (as we normally stops analysis when we see the stack frame
 *    creation). So in this case the heuristic would fail. We rely thus on two hints coming from the caller:
 *    * First, we expect the caller to set from_exception=true, so that we know that we might potentially
 *      deal with a leaf function.
 *    * Second, the caller should provide the function start address, so that we stop the analysis when
 *      we reach it, and mark the function as BT_LEAF.
 *    * If the function start address is not provided (because e.g. the symbol table was not found and
 *      thus we have no information about function starts), the last ditch heuristic is to look for
 *      the nops that are normally used to align the function start to the FUNCTION_ALIGNMENT boundary.
 *      Obviously this is a very fragile heuristic (it will fail if the function required no nops to be
 *      properly aligned), but it is the best we can do. Worst case, in this specific case of a leaf
 *      function interrupted by the exception, the stack trace will be wrong from this point on.
 *
 * @param func                        Output function description structure
 * @param ptr                         Pointer to the function code at the point where the backtrace starts.
 *                                    This is normally the point where a JAL opcode is found, as we are walking
 *                                    up the call stack.
 * @param func_start                  Start of the function being analyzed. This is optional: the heuristic can work
 *                                    without this hint, but it is useful in certain situations (eg: to better
 *                                    walk up after an exception).
 * @param from_exception              If true, this function was interrupted by an exception. This is a hint that
 *                                    the function *might* even be a leaf function without a stack frame, and that
 *                                    we must use special heuristics for it.
 *
 * @return true if the backtrace can continue, false if must be aborted (eg: we are within invalid memory)
 */
bool __bt_analyze_func(bt_func_t *func, uint32_t *ptr, uint32_t func_start, bool from_exception) {
    // exceptasm.s
    #define inthandler ((uint32_t*)0x8006A9F0)
    #define inthandler_end ((uint32_t*)0x8006B35C)

    uint32_t addr;

    *func = (bt_func_t){
        .type = (ptr >= inthandler && ptr < inthandler_end) ? BT_EXCEPTION : BT_FUNCTION,
        .stack_size = 0, .ra_offset = 0, .fp_offset = 0
    };

    addr = (uint32_t)ptr;
    while (1) {
        uint32_t op;

        // Validate that we can dereference the virtual address without raising an exception
        if (!is_valid_address(addr)) {
            // This address is invalid, probably something is corrupted. Avoid looking further.
            debugf("backtrace: interrupted because of invalid return address 0x%08x\n", addr);
            return false;
        }
        op = *(uint32_t*)get_physical_address(addr);
        if (MIPS_OP_ADDIU_SP(op) || MIPS_OP_DADDIU_SP(op)) {
            // Extract the stack size only from the start of the function, where the
            // stack is allocated (negative value). This is important because the RA
            // could point to a leaf basis block at the end of the function (like in the
            // assert case), and if we picked the positive ADDIU SP at the end of the
            // proper function body, we might miss a fp_offset.
            if (op & 0x8000)
                func->stack_size = -(int16_t)(op & 0xFFFF);
        } else if (MIPS_OP_SD_RA_SP(op)) {
            func->ra_offset = (int16_t)(op & 0xFFFF) + 4; // +4 = load low 32 bit of RA
            // If we found a stack size, it might be a red herring (an alloca); we need one
            // happening "just before" sd ra,xx(sp)
            func->stack_size = 0;
        } else if (MIPS_OP_SW_RA_SP(op)) {
            // 32-bit version of above
            func->ra_offset = (int16_t)(op & 0xFFFF);
            func->stack_size = 0;
        } else if (MIPS_OP_SD_FP_SP(op)) {
            func->fp_offset = (int16_t)(op & 0xFFFF) + 4; // +4 = load low 32 bit of FP
        } else if (MIPS_OP_SW_FP_SP(op)) {
            // 32-bit version of above
            func->fp_offset = (int16_t)(op & 0xFFFF);
        } else if (MIPS_OP_LUI_GP(op)) {
            // Loading gp is commonly done in _start, so it's useless to go back more
            return false;
        } else if (MIPS_OP_MOVE_FP_SP(op)) {
            // This function uses the frame pointer. Uses that as base of the stack.
            // Even with -fomit-frame-pointer (default on our toolchain), the compiler
            // still emits a framepointer for functions using a variable stack size
            // (eg: using alloca() or VLAs).
            func->type = BT_FUNCTION_FRAMEPOINTER;
        }
        // We found the stack frame size and the offset of the return address in the stack frame
        // We can stop looking and process the frame
        if (func->stack_size != 0 && func->ra_offset != 0)
            break;
        if (from_exception) {
            // The function we are analyzing was interrupted by an exception, so it might
            // potentially be a leaf function (no stack frame). We need to make sure to stop
            // at the beginning of the function and mark it as leaf function. Use
            // func_start if specified, or try to guess using the nops used to align the function
            // (crossing fingers that they're there).
            if (addr == func_start) {
                // The frame that was interrupted by an interrupt handler is a special case: the
                // function could be a leaf function with no stack. If we were able to identify
                // the function start (via the symbol table) and we reach it, it means that
                // we are in a real leaf function.
                func->type = BT_LEAF;
                break;
            } else if (!func_start && MIPS_OP_NOP(op) && (addr + 4) % FUNCTION_ALIGNMENT == 0) {
                // If we are in the frame interrupted by an interrupt handler, and we does not know
                // the start of the function (eg: no symbol table), then try to stop by looking for
                // a NOP that pads between functions. Obviously the NOP we find can be either a false
                // positive or a false negative, but we can't do any better without symbols.
                func->type = BT_LEAF;
                break;
            }
        }
        addr -= 4;
    }
    return true;
}
