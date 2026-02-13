#ifndef BACKTRACE_H
#define BACKTRACE_H

#include "common.h"

/**
 * @brief ROM address of the pointer to the symbol table.
 *
 * This particular location is an unused part of the header lol.
 * Don't modify this without also updating append_symbol_table.py.
 */
#define SYMBOL_TABLE_PTR_ROM_ADDR 0x18

typedef struct Symbol {
    u32 address; ///< RAM address.
    u32 nameOffset; ///< Offset of the symbol name string.
    u32 fileOffset; ///< Offset of the file name and line string.
} Symbol;

typedef struct SymbolTable {
    char magic[4]; // "SYMS"
    u32 symbolCount;
    struct Symbol symbols[0];
    // then lots of strings
} SymbolTable;

/**
 * @brief Walk the stack and return the current call stack
 *
 * This function will analyze the current execution context,
 * walking the stack and returning informations on the active
 * call frames.
 *
 * This function adheres to POSIX specification. It does not
 * allocate memory so it is safe to be called even in the
 * context of low memory conditions or possibly corrupted heap.
 *
 * If called within an interrupt or exception handler, the function
 * is able to correctly walk backward the interrupt handler and
 * show the context even before the exception was triggered.
 *
 * @param buffer    Empty array of pointers. This will be populated with pointers
 *                  to the return addresses for each call frame.
 * @param size      Size of the buffer, that is, maximum number of call frames
 *                  that will be walked by the function.
 * @return          Number of call frames walked (at most, size).
 */
int backtrace(void **buffer, int size);

int backtrace_thread(void **buffer, int size, OSThread *thread);

/** @brief Print a backtrace. */
void debug_backtrace(void);

/** @brief Converts a function address to a string representation using its name, offset, and file. */
void backtrace_address_to_string(u32 address, char* dest);

#endif
