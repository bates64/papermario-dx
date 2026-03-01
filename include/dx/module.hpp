#pragma once

#include "common.h"
#include "dx/hash_map.hpp"
#include "dx/string.hpp"

extern "C" const char* module_sym_for_addr(u32 addr, const char** out_module_name,
                                            u32* out_debug_rom_start, u32* out_debug_rom_end,
                                            u32* out_module_base);

namespace dx {

/** A loaded dynamic library. */
class Module {
public:
    /** Gets a module by name. Loads it from ROM if not already loaded. */
    static Module* get(const FixedString<64>& name);

    /** Unloads the module (removes from cache, runs dtors). */
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
    struct Export;

    Module(const FixedString<64>& name);

    void apply_relocs();
    void run_table(u32 offset, u32 count);

    const Export *exports() const;
    const char *strtab() const;

    FixedString<64> name_;
    u8 *blob_ = nullptr;
    u8 *base_ = nullptr;
    u8 *bss_ = nullptr;
    Header *hdr_ = nullptr;
    u32 debugRomStart_ = 0;
    u32 debugRomEnd_ = 0;

    static HashMap<FixedString<64>, Module*> loaded_;

    friend const char* ::module_sym_for_addr(u32 addr, const char** out_module_name,
                                              u32* out_debug_rom_start, u32* out_debug_rom_end,
                                              u32* out_module_base);
};

} // namespace dx
