/// @file overlay.h
/// @brief Load and run code from separate compilation units at runtime.
///
/// An overlay is a chunk of compiled code that lives in the ROM separately from the main binary.
/// It can be loaded into RAM on demand, executed, and then unloaded to free memory. This is how
/// we swap in map-specific logic and battle actors without keeping everything resident.
///
/// ## Usage
/// ```c
/// // Load the overlay src/battle/actor/my_actor
/// Overlay* ovl = ovl_load("my_actor", OVL_ACTOR);
///
/// // Run an exported function
/// void (*fn)(void) = ovl_import(ovl, "my_function");
/// fn();
///
/// // Use an exported global variable
/// int* var = ovl_import(ovl, "my_variable");
/// *var += 5;
///
/// // Unload the overlay when you're done with it (this frees memory)
/// ovl_unload(ovl);
/// ```
///
/// ## Source files
///
/// Each #OverlayType has a source glob. Files or directories matching the glob
/// are each built as an overlay, with the stem of the match as the overlay name. If the match
/// is a directory, all C/C++ files inside it (excluding `*.inc.c` and `*.inc.cpp`) are compiled
/// and linked together. If the match is a single file, that file alone is the overlay.
///
/// For example, `src/world/area_kmr/kmr_02/` is a directory matching `src/world/area_*/*/`,
/// so it becomes an #OVL_MAP overlay named "kmr_02". `src/battle/actor/goomba.c` matches
/// `src/battle/actor/*`, so it becomes an OVL_ACTOR overlay named "goomba".
///
/// ## Importing and exporting
///
/// Symbols marked with the `export` macro are accessible via #ovl_import().
/// For example, in an overlay, do this to export a symbol:
/// ```c
/// export void my_function(void) { /* ... */ }
/// ```
/// You can also export global variables:
/// ```c
/// export int foo = 10;
/// ```
///
/// ## Overlays are singletons
///
/// Loading the same name/type pair multiple times will return the same overlay. For example:
/// ```c
/// Overlay* first = ovl_load("my_overlay", OVL_ACTOR);
/// Overlay* second = ovl_load("my_overlay", OVL_ACTOR);
/// ASSERT(first == second);
/// ```
/// This means that **variables are shared** if a single overlay is loaded multiple times.
///
/// ## Dynamic linking
///
/// Most overlay types are dynamically linked. This means that they can be loaded to any
/// address, and thus many of that type can be loaded at the same time.
///
/// The exception to this is #OVL_MAP, which is always loaded to a specific address.
/// Therefore, only one map overlay can be loaded at once. Loading another map whilst
/// one is loaded is undefined behaviour; unload it first.
///
/// ## Adding a new overlay type
///
/// To add a new dynamically linked overlay type:
/// 1. Add a new variant to #OverlayType before #OVL_NUM_TYPES.
/// 2. Add the glob to `overlay_types` in `configure.py`.
///
/// ## Vanilla comparison
///
/// Vanilla did not have this abstraction and instead copied code directly from ROM into RAM with #dma_copy.
///
/// Vanilla did not have dynamic linking - every overlay was linked statically to a particular address.
/// Some other N64 games such as Ocarina of Time *do* use dynamic linking, however.

#pragma once

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Overlay Overlay;

typedef enum {
    OVL_ACTOR, ///< `src/battle/actor/*`
    OVL_MAP,   ///< `src/world/area_*/*/` -- only one loaded at a time
    OVL_NUM_TYPES,
} OverlayType;

/// Load an overlay by name, or return a cached instance if already loaded.
///
/// When you are done with this overlay, you must call #ovl_unload or #ovl_unload_type.
///
/// ## Panics
/// - No overlay named `name` exists for the given `type`.
/// - All overlay slots are occupied.
/// - The overlay data is corrupt.
__attribute__((returns_nonnull))
Overlay* ovl_load(const char* name, OverlayType type);

/// Unload an overlay. No-op if not loaded.
void ovl_unload(Overlay* ovl);

/// Unload all overlays of a given type.
void ovl_unload_type(OverlayType type);

/// Look up an exported symbol by name. Returns nullptr if not found.
void* ovl_import(const Overlay* ovl, const char* name);

/// Searches all loaded overlays for the symbol name nearest to `addr`.
const char* ovl_resolve_addr(u32 addr, const char** outOverlayName,
                             u32* outDebugRomStart, u32* outDebugRomEnd,
                             u32* outOverlayBase);

#ifdef __cplusplus
}
#endif
