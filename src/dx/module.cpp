#include "module.hpp"
#include "functions.h"

static constexpr u32 MOD_MAGIC = 0x4D4F4400; // "MOD\0"
static constexpr u32 LINK_ADDR = 0x80000000;

enum RelocType : u8 {
    R_MIPS_32   = 2,
    R_MIPS_26   = 4,
    R_MIPS_HI16 = 5,
    R_MIPS_LO16 = 6,
};

struct Module::Header {
    u32 magic;
    u32 version;
    u32 text_offset, text_size;
    u32 data_offset, data_size;
    u32 bss_size;
    u32 reloc_offset, reloc_count;
    u32 ctor_offset, ctor_count;
    u32 dtor_offset, dtor_count;
    u32 export_offset, export_count;
    u32 strtab_offset, strtab_size;
};

struct Module::Reloc {
    u8 type;
    u8 _pad[3];
    u32 offset;
};

struct Module::Export {
    u32 offset;
    u32 name_offset;
};

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
    const Reloc *relocs = (const Reloc *)(blob_ + hdr_->reloc_offset);

    for (u32 i = 0; i < hdr_->reloc_count; i++) {
        u32 off = relocs[i].offset;
        u32 *loc = (u32 *)(load + off);

        switch (relocs[i].type) {
        case R_MIPS_32:
            *loc += delta;
            break;

        case R_MIPS_26: {
            // j/jal: patch the 26-bit target field; keep top nibble from instruction.
            u32 target_addr = (((*loc & 0x03FFFFFFu) << 2) + delta);

            *loc = (*loc & 0xFC000000u) | ((target_addr & 0x0FFFFFFCu) >> 2);
            break;
        }

        case R_MIPS_HI16: {
            // Pair HI16 with the next LO16 relocation and apply carry fix.
            u16 hi = (u16)(*loc & 0xFFFFu);
            u32 addr = ((u32)hi) << 16;

            bool lo_found = false;

            for (u32 j = i + 1; j < hdr_->reloc_count; j++) {
                if (relocs[j].type != R_MIPS_LO16)
                    continue;

                u32 lo_off = relocs[j].offset;
                u32 *lo_loc = (u32 *)(load + lo_off);

                s16 lo = (s16)(*lo_loc & 0xFFFFu);     // signed immediate
                addr += (u32)(s32)lo;
                addr += (u32)delta;

                hi = (u16)(addr >> 16);
                if (addr & 0x8000u) hi++;              // carry from low half

                lo_found = true;
                break;
            }

            ASSERT_MSG(lo_found, "Unpaired R_MIPS_HI16 relocation");
            *loc = (*loc & 0xFFFF0000u) | (u32)hi;
            break;
        }

        case R_MIPS_LO16: {
            // Apply delta to low 16 bits (signed addiu-style immediate)
            u16 lo_u = (u16)(*loc & 0xFFFFu);
            s16 lo_s = (s16)lo_u;

            s32 new_lo = (s32)lo_s + (s32)delta;
            *loc = (*loc & 0xFFFF0000u) | (u32)(u16)new_lo;
            break;
        }
        }
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

Module::Module(const char* filename) {
    u32 size;
    void* compressedData = load_asset_by_name(filename, &size);
    ASSERT_MSG(compressedData, "Cannot read %s, out of memory", filename);
    void* decompressedData = malloc(size);
    ASSERT_MSG(decompressedData, "Cannot decompress %s, out of memory", filename);
    ASSERT_MSG(*(u32*)compressedData == ASCII_TO_U32('Y', 'a', 'y', '0'), "Module %s is uncompressed", filename);
    decode_yay0(compressedData, decompressedData);
    general_heap_free(compressedData);

    blob_ = (u8*)decompressedData;
    hdr_ = (Header *)decompressedData;

    ASSERT_MSG(hdr_->magic == MOD_MAGIC, "Invalid module");

    base_ = blob_ + hdr_->text_offset;

    if (hdr_->bss_size > 0) {
        bss_ = (u8 *)malloc(hdr_->bss_size);
        memset(bss_, 0, hdr_->bss_size);
    }

    apply_relocs();

    osWritebackDCache(base_, hdr_->text_size + hdr_->data_size);
    osInvalICache(base_, hdr_->text_size);

    printf("Loaded module '%s' to %p\n", filename, base_);

    run_table(hdr_->ctor_offset, hdr_->ctor_count);
}

Module::~Module() {
    run_table(hdr_->dtor_offset, hdr_->dtor_count);

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
