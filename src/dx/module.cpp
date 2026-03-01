#include "dx/module.hpp"
#include "functions.h"
#include "nu/nusys.h"

namespace dx {

static constexpr u32 MOD_MAGIC = 0x4D4F4400; // "MOD\0"
static constexpr u32 MOD_VERSION = 2;
static constexpr u32 LINK_ADDR = 0x80000000;

enum ModuleFlags : u32 {
    MODULE_FLAG_AUTOLOAD = 1 << 0,
};

struct ModuleEntry {
    char name[64];
    u32 romStart;
    u32 romEnd;
    u32 flags;
};

static constexpr u32 MODULE_DIR_CAPACITY = 1024;
static constexpr u32 MODULE_DIR_MAGIC = 0x4D4F4444; // "MODD"

struct ModuleDirectory {
    u32 magic;
    u32 count;
    ModuleEntry entries[MODULE_DIR_CAPACITY];
};

// Populated by module.py. Zeroed entries are empty.
extern "C"
__attribute__((aligned(16)))
volatile ModuleDirectory moduleDirectory = { MODULE_DIR_MAGIC, 0, {} };

struct Module::Header {
    u32 magic;
    u32 version;
    u32 text_offset, text_size;
    u32 data_offset, data_size;
    u32 bss_size;
    u32 r32_offset, r32_count;    // R_MIPS_32 relocs
    u32 r26_offset, r26_count;    // R_MIPS_26 relocs
    u32 hi16_offset, hi16_count;  // R_MIPS_HI16 relocs
    u32 lo16_offset, lo16_count;  // R_MIPS_LO16 relocs
    u32 ctor_offset, ctor_count;
    u32 dtor_offset, dtor_count;
    u32 export_offset, export_count;
    u32 strtab_offset, strtab_size;
};

struct Module::Export {
    u32 offset;
    u32 name_offset;
};

HashMap<FixedString<64>, Module*> Module::loaded_;

const Module::Export *Module::exports() const {
    return (const Export *)(blob_ + hdr_->export_offset);
}

const char *Module::strtab() const {
    return (const char *)(blob_ + hdr_->strtab_offset);
}

u32 Module::size() const {
    return hdr_->text_size + hdr_->data_size + hdr_->bss_size;
}

void Module::apply_relocs() {
    u32 load = (u32)base_;
    u32 delta = load - LINK_ADDR;

    const u32* r32 = (const u32*)(blob_ + hdr_->r32_offset);
    for (u32 idx = 0; idx < hdr_->r32_count; idx++) {
        *(u32*)(load + r32[idx]) += delta;
    }

    const u32* r26 = (const u32*)(blob_ + hdr_->r26_offset);
    for (u32 idx = 0; idx < hdr_->r26_count; idx++) {
        u32* loc = (u32*)(load + r26[idx]);
        u32 target = (((*loc & 0x03FFFFFFu) << 2) + delta);
        *loc = (*loc & 0xFC000000u) | ((target & 0x0FFFFFFCu) >> 2);
    }

    ASSERT_MSG(hdr_->hi16_count == hdr_->lo16_count, "HI16/LO16 count mismatch");
    const u32* hi16 = (const u32*)(blob_ + hdr_->hi16_offset);
    const u32* lo16 = (const u32*)(blob_ + hdr_->lo16_offset);
    for (u32 idx = 0; idx < hdr_->hi16_count; idx++) {
        u32* hi_loc = (u32*)(load + hi16[idx]);
        u32* lo_loc = (u32*)(load + lo16[idx]);

        u16 hi_val = (u16)(*hi_loc & 0xFFFFu);
        s16 lo_val = (s16)(*lo_loc & 0xFFFFu);

        u32 addr = (((u32)hi_val) << 16) + (u32)(s32)lo_val + delta;

        u16 new_hi = (u16)(addr >> 16);
        if (addr & 0x8000u) new_hi++;
        *hi_loc = (*hi_loc & 0xFFFF0000u) | new_hi;

        *lo_loc = (*lo_loc & 0xFFFF0000u) | (u16)addr;
    }
}

void Module::run_table(u32 offset, u32 count) {
    u32 *table = (u32 *)(blob_ + offset);
    s32 delta = (u32)base_ - LINK_ADDR;

    for (u32 i = 0; i < count; i++) {
        void (*fn)(void) = (void (*)(void))(table[i] + delta);
        fn();
    }
}

static const ModuleEntry* find_in_directory(const char* name) {
    u32 count = moduleDirectory.count;
    for (u32 i = 0; i < count; i++) {
        if (strcmp((const char*)moduleDirectory.entries[i].name, name) == 0) {
            return (const ModuleEntry*)&moduleDirectory.entries[i];
        }
    }
    return nullptr;
}

Module* Module::get(const FixedString<64>& name) {
    auto existing = loaded_.find(name);
    if (existing.has_value())
        return *existing;
    return new Module(name);
}

Module::Module(const FixedString<64>& name) : name_(name) {
    loaded_.insert_or_assign(name_, this);

    const ModuleEntry* entry = find_in_directory(name);
    ASSERT_MSG(entry != nullptr, "Module '%s' not found in directory", name.c_str());

    u32 romSize = entry->romEnd - entry->romStart;

    void* romData = malloc(romSize);
    ASSERT_MSG(romData, "Cannot allocate %lu bytes for module %s", romSize, name.c_str());

    nuPiReadRom(entry->romStart, romData, romSize);

    blob_ = (u8*)romData;
    hdr_ = (Header *)romData;

    ASSERT_MSG(hdr_->magic == MOD_MAGIC, "Invalid module %s", name.c_str());
    ASSERT_MSG(hdr_->version == MOD_VERSION, "Module %s has version %lu, expected %lu", name.c_str(), hdr_->version, MOD_VERSION);

    base_ = blob_ + hdr_->text_offset;

    if (hdr_->bss_size > 0) {
        bss_ = (u8 *)malloc(hdr_->bss_size);
        memset(bss_, 0, hdr_->bss_size);
    }

    apply_relocs();

    osWritebackDCache(base_, hdr_->text_size + hdr_->data_size);
    osInvalICache(base_, hdr_->text_size);

    run_table(hdr_->ctor_offset, hdr_->ctor_count);
}

Module::~Module() {
    run_table(hdr_->dtor_offset, hdr_->dtor_count);
    loaded_.erase(name_);
    free(bss_);
    free(blob_);
}

void *Module::sym(const char *name) const {
    const Export *exp = exports();
    const char *str = strtab();

    for (u32 i = 0; i < hdr_->export_count; i++) {
        if (strcmp(str + exp[i].name_offset, name) == 0)
            return base_ + exp[i].offset;
    }
    return nullptr;
}

u32 Module::addr(const char *name) const {
    return (u32)sym(name);
}

const char *Module::sym_for_addr(u32 addr) const {
    u32 off = addr - (u32)base_;
    const Export *exp = exports();
    const char *str = strtab();

    const char *best = nullptr;
    u32 best_off = 0;

    for (u32 i = 0; i < hdr_->export_count; i++) {
        if (exp[i].offset <= off && exp[i].offset >= best_off) {
            best_off = exp[i].offset;
            best = str + exp[i].name_offset;
        }
    }
    return best;
}

bool Module::contains(u32 addr) const {
    u32 b = (u32)base_;
    return addr >= b && addr < b + hdr_->text_size;
}

} // namespace dx

extern "C"
const char* module_sym_for_addr(u32 addr, const char** out_module_name) {
    using namespace dx;

    const char* result = nullptr;
    printf("module_sym_for_addr: addr=0x%08lX loaded=%lu\n", addr, Module::loaded_.size());
    Module::loaded_.for_each([&](const FixedString<64>& name, Module* mod) {
        if (result) return;
        u32 base = (u32)mod->base();
        u32 end = base + mod->size();
        printf("  module '%s': base=0x%08lX end=0x%08lX contains=%d\n",
               name.c_str(), base, end, mod->contains(addr));
        if (mod->contains(addr)) {
            const char* sym = mod->sym_for_addr(addr);
            printf("  -> sym='%s'\n", sym ? sym : "(null)");
            if (out_module_name)
                *out_module_name = name;
            result = sym;
        }
    });
    return result;
}

extern "C"
void load_autoload_modules(void) {
    using namespace dx;

    u32 count = moduleDirectory.count;
    for (u32 i = 0; i < count; i++) {
        const ModuleEntry* e = (const ModuleEntry*)&moduleDirectory.entries[i];
        if (e->flags & MODULE_FLAG_AUTOLOAD) {
            Module::get(e->name);
        }
    }
}
