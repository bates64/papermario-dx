#pragma once

#include "common.h"

/** A loaded dynamic library. */
class Module {
public:
    /** Loads a module, including running ctors. */
    Module(const char* filename);

    /** Unloads the module, including running dtors. */
    ~Module();

    /** Returns a pointer to the symbol with the given name. */
    void *sym(const char *name) const;

    /** Returns the address of the symbol with the given name. */
    u32 addr(const char *name) const;

    /** Returns the name of the symbol at the given address. */
    const char *sym_for_addr(u32 addr) const;

    /** Returns whether the module contains the given address. */
    bool contains(u32 addr) const;

    /** Returns the base address of the module. */
    u8 *base() const { return base_; }

    /** Returns the size of the module. */
    u32 size() const;

private:
    struct Header;
    struct Reloc;
    struct Export;

    void apply_relocs();
    void run_table(u32 offset, u32 count);

    const Export *exports() const;
    const char *strtab() const;

    u8 *blob_ = nullptr;
    u8 *base_ = nullptr;
    u8 *bss_ = nullptr;
    Header *hdr_ = nullptr;
};
