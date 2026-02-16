#include "dx/module.h"
#include "functions.h"

namespace dx {
namespace module {

using rc::Rc;
using rc::Weak;
using string::FixedString;
using collections::HashMap;

static constexpr u32 MOD_MAGIC = 0x4D4F4400; // "MOD\0"
static constexpr u32 MOD_VERSION = 2;
static constexpr u32 LINK_ADDR = 0x80000000;

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

HashMap<FixedString<64>, Weak<Module>> Module::cache_;

const Module::Export *Module::exports() const {
    return (const Export *)((u8*)asset_->data() + hdr_->export_offset);
}

const char *Module::strtab() const {
    return (const char *)((u8*)asset_->data() + hdr_->strtab_offset);
}

u32 Module::size() const {
    return hdr_->text_size + hdr_->data_size + hdr_->bss_size;
}

void Module::apply_relocs() {
    u32 load = (u32)base_;
    u32 delta = load - LINK_ADDR;
    u8* blob = (u8*)asset_->data();

    // R_MIPS_32: simple add delta (most common, especially for shape data)
    const u32* r32 = (const u32*)(blob + hdr_->r32_offset);
    for (u32 idx = 0; idx < hdr_->r32_count; idx++) {
        *(u32*)(load + r32[idx]) += delta;
    }

    // R_MIPS_26: j/jal instruction patching
    const u32* r26 = (const u32*)(blob + hdr_->r26_offset);
    for (u32 idx = 0; idx < hdr_->r26_count; idx++) {
        u32* loc = (u32*)(load + r26[idx]);
        u32 target = (((*loc & 0x03FFFFFFu) << 2) + delta);
        *loc = (*loc & 0xFC000000u) | ((target & 0x0FFFFFFCu) >> 2);
    }

    // R_MIPS_HI16/LO16: paired, must have same count
    ASSERT_MSG(hdr_->hi16_count == hdr_->lo16_count, "HI16/LO16 count mismatch");
    const u32* hi16 = (const u32*)(blob + hdr_->hi16_offset);
    const u32* lo16 = (const u32*)(blob + hdr_->lo16_offset);
    for (u32 idx = 0; idx < hdr_->hi16_count; idx++) {
        u32* hi_loc = (u32*)(load + hi16[idx]);
        u32* lo_loc = (u32*)(load + lo16[idx]);

        u16 hi_val = (u16)(*hi_loc & 0xFFFFu);
        s16 lo_val = (s16)(*lo_loc & 0xFFFFu);

        u32 addr = (((u32)hi_val) << 16) + (u32)(s32)lo_val + delta;

        // Update HI16 with carry adjustment
        u16 new_hi = (u16)(addr >> 16);
        if (addr & 0x8000u) new_hi++;
        *hi_loc = (*hi_loc & 0xFFFF0000u) | new_hi;

        // Update LO16
        *lo_loc = (*lo_loc & 0xFFFF0000u) | (u16)addr;
    }
}

void Module::run_table(u32 offset, u32 count) {
    u8* blob = (u8*)asset_->data();
    u32 *table = (u32 *)(blob + offset);
    s32 delta = (u32)base_ - LINK_ADDR;

    for (u32 i = 0; i < count; i++) {
        void (*fn)(void) = (void (*)(void))(table[i] + delta);
        fn();
    }
}

Rc<Module> Module::load(const char* name) {
    FixedString<64> key(name);

    // Try to upgrade existing weak reference
    auto existing = cache_.get(key);
    if (existing) {
        auto upgraded = existing.unwrap().upgrade();
        if (upgraded) {
            return upgraded.unwrap();
        }
    }

    // Construct new module
    Rc<Module> mod = Rc<Module>::make(name);

    // Cache weak reference
    cache_.put(key, mod.downgrade());
    return mod;
}

Module::Module(const char* filename)
    : asset_(asset::Asset::load(filename))
{
    OSTime start_time = osGetTime();

    // Mark asset as exclusive - prevents hot-reload from freeing our code buffer
    asset_->exclusive = true;

    u8* blob = (u8*)asset_->data();
    hdr_ = (Header*)blob;

    ASSERT_MSG(hdr_->magic == MOD_MAGIC, "Invalid module %s", filename);
    ASSERT_MSG(hdr_->version == MOD_VERSION, "Module %s has version %lu, expected %lu", filename, hdr_->version, MOD_VERSION);

    base_ = blob + hdr_->text_offset;

    if (hdr_->bss_size > 0) {
        bss_ = (u8 *)malloc(hdr_->bss_size);
        memset(bss_, 0, hdr_->bss_size);
    }

    apply_relocs();

    osWritebackDCache(base_, hdr_->text_size + hdr_->data_size);
    osInvalICache(base_, hdr_->text_size);

    // Build symbol lookup table
    const Export* exp = exports();
    const char* str = strtab();
    syms_.reserve(hdr_->export_count);
    for (u32 i = 0; i < hdr_->export_count; i++) {
        syms_.put(FixedString<64>(str + exp[i].name_offset), base_ + exp[i].offset);
    }

    OSTime elapsed = osGetTime() - start_time;
    u32 ms = OS_CYCLES_TO_USEC(elapsed) / 1000;

    u32 total_relocs = hdr_->r32_count + hdr_->r26_count + hdr_->hi16_count + hdr_->lo16_count;
    printf("Loaded module %s to %p (%lu relocs, %lu exports) in %lu ms\n",
           filename, base_, total_relocs, hdr_->export_count, ms);

    run_table(hdr_->ctor_offset, hdr_->ctor_count);
}

Module::~Module() {
    run_table(hdr_->dtor_offset, hdr_->dtor_count);

    // Release exclusivity - Asset will handle freeing the buffer
    asset_->exclusive = false;

    free(bss_);

}

void *Module::sym(const char *name) const {
    auto result = syms_.get(name);
    if (result) {
        return result.unwrap();
    }
    return nullptr;
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

bool Module::has_update() const {
    return asset_->has_pending_reload();
}

} // namespace module
} // namespace dx
