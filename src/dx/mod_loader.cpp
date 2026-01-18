#include "mod_loader.hpp"
#include "libdragon/dragonfs.h"

RomAddress<LoadableMod> LoadableMod::first() {
    alignas(16) u32 romHeader[0x10];
    nuPiReadRom(0, &romHeader, sizeof(romHeader));
    return RomAddress<LoadableMod>(romHeader[7]); // "Unknown 2";
}

bool LoadableMod::check_version() const {
    char expected[4] = { 'D', 'X', 'v', '1' };
    return memcmp(version, expected, 4) == 0;
}

void LoadableMod::load() {
    ASSERT_MSG(check_version(), "mod '%s' uses an unsupported mod format", name);
    ASSERT(dfsAddress != 0);

    debug_printf("dfs at address 0x%08X\n", dfsAddress);

    int error = dfs_init(dfsAddress);
    if (error != DFS_ESUCCESS) {
        PANIC_MSG("%s when initing dfs for mod '%s'", dfs_strerror(error), name);
    }
    debug_printf("dfs_init OK");

    int file = dfs_open("dfs/hello.txt");
    if (file < 0) {
        PANIC_MSG("%s when opening dfs/hello.txt for mod '%s'", dfs_strerror(file), name);
    }
    debug_printf("dfs_open OK");

    char buffer[64];
    int size = dfs_size(file);
    if (size < 0) {
        PANIC_MSG("%s when getting size of dfs/hello.txt for mod '%s'", dfs_strerror(size), name);
    }
    if (size > sizeof(buffer) - 1) {
        size = sizeof(buffer) - 1;
    }
    int read = dfs_read(buffer, size, 1, file);
    if (read < 0) {
        PANIC_MSG("%s when reading dfs/hello.txt for mod '%s'", dfs_strerror(read), name);
    }
    buffer[read] = '\0';
    dfs_close(file);

    PANIC_MSG("file says: %s", buffer);
}

void load_all_mods() {
    auto addr = LoadableMod::first();
    debug_printf("First mod at address: 0x%08X\n", addr.address);
    while (!addr.is_null()) {
        debug_printf("Loading mod at address: 0x%08X\n", addr.address);
        auto mod = *addr;

        debug_printf("Loading mod: %s\n", mod->name);
        mod->load();

        addr = mod->next;
    }
}
