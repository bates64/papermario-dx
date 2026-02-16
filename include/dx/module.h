#pragma once

#include "common.h"
#include "dx/rc.h"
#include "dx/collections.h"
#include "dx/string.h"
#include "dx/asset.h"

namespace dx {
namespace module {

/** A loaded dynamic library. */
class Module {
public:
    /** Loads a module by name, with caching.
     *  Returns a shared reference - loading the same name twice returns the same instance. */
    static rc::Rc<Module> load(const char* name);

    /** Unloads the module, including running dtors. */
    ~Module();

    /** Returns a pointer to the symbol with the given name. */
    void *sym(const char *name) const;

    /** Returns the name of the symbol at the given address. */
    const char *sym_for_addr(u32 addr) const;

    /** Returns whether the module contains the given address. */
    bool contains(u32 addr) const;

    /** Returns the base address of the module. */
    u8 *base() const { return base_; }

    /** Returns the size of the module. */
    u32 size() const;

    /** Returns true if the underlying asset has a pending hot-reload. */
    bool has_update() const;

private:
    friend class rc::Rc<Module>;

    Module(const char* filename);

    struct Header;
    struct Reloc;
    struct Export;

    void apply_relocs();
    void run_table(u32 offset, u32 count);

    const Export *exports() const;
    const char *strtab() const;

    rc::Rc<asset::Asset> asset_;
    u8 *base_ = nullptr;
    u8 *bss_ = nullptr;
    Header *hdr_ = nullptr;
    collections::HashMap<string::FixedString<64>, void*> syms_;

    static collections::HashMap<string::FixedString<64>, rc::Weak<Module>> cache_;
};

} // namespace module
} // namespace dx
