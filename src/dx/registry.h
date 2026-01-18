#pragma once
#include "common.h"
#include "dx/debug_menu.h"
#include <stdint.h>
#include <new>

#ifndef __cplusplus

/// Represents a key in the registry, like "vanilla:kmr_20".
/// In C, RegistryKeys are opaque structs. They can be compared by pointer for equality.
typedef struct RegistryKey RegistryKey;

#else

namespace registry {

/// Mix function for hash table indexing
static u16 mix16(u16 x) {
    x ^= x >> 7;
    x *= 0x9E37u;
    x ^= x >> 5;
    x *= 0x85EBu;
    x ^= x >> 3;
    return x;
}

/// Globally interned string.
/// Note: strings that are interned are never freed.
class String {
    u16 hash = 0;
    u16 len = 0;
    const char* ptr = nullptr; // owned by heap

    // Interned strings table
    static String* table;
    static u16 cap; // power of two
    static u16 size;

    static void init();
    static void grow();
    static String* intern_slot(const char* s);

public:
    explicit String(const char* str);

    bool operator==(const String& other) const {
        // Compare by pointer since strings are interned
        // Two Strings can share a hash if there is a collision, but
        // they will never share the same pointer unless they are equal.
        return ptr == other.ptr;
    }

    const char* c_str() const {
        return ptr;
    }

    u16 get_hash() const {
        return hash;
    }
};

/// Represents a key in a registry, like "vanilla:kmr_20".¬
struct Key {
    String mod; // e.g. "vanilla"
    String name; // e.g. "kmr_20"

    explicit Key(const char* modName, const char* keyName)
        : mod(modName), name(keyName) {}

    explicit Key(const String& modName, const String& keyName)
        : mod(modName), name(keyName) {}

    bool operator==(const Key& other) const {
        return mod == other.mod && name == other.name;
    }
};

/// A registry mapping keys to values, with layering by mod.
///
/// Layers are implicit by order of insertion. For example:
///     registry.insert(foo, a) by mod "vanilla"
///     registry.insert(foo, b) by mod "cool_mod"
/// Will result in the following entries in the registry:
///     foo -> [ "cool_mod": a, "vanilla": b ]
/// And looking up "foo" will return `a` until "cool_mod" is unloaded, after which, it will return `b`.
/// If "vanilla" is unloaded then reloaded, it will keep its position in the stack.
/// It won't override "cool_mod" despite being inserted later, because it was inserted previously.
template<typename T>
class Registry {
    struct Layer {
        String mod; // Mod that registered this layer
        bool live; // Whether value is initialised i.e. is this mod loaded?
        T value;
        Layer* next; // Next layer down the stack (older); ptr owned by parent Entry
    };

    struct Entry {
        String name; // key.name
        Layer* top; // newest layer, if nullptr then this slot is unused

        Entry() : name(String(nullptr)), top(nullptr) {}

        ~Entry() {
            Layer* layer = top;
            while (layer) {
                Layer* next = layer->next;
                layer->~Layer();
                ::operator delete(layer);
                layer = next;
            }
        }
    };

    Entry* table;
    u16 cap = 0; // power of two
    u16 size = 0;

    void grow() {
        u16 old_cap = cap;
        Entry*  old     = table;

        cap = (cap != 0) ? (cap * 2) : 128; // Double in capacity
        table = static_cast<Entry*>(::operator new[]((size_t)cap * sizeof(Entry)));
        for (u16 i = 0; i < cap; ++i) {
            ::new (&table[i]) Entry();
        }

        size = 0;

        // Copy all the old entries into the new table
        u16 mask = cap - 1;
        for (u16 i = 0; i < old_cap; ++i) {
            Entry& e = old[i];
            if (e.top == nullptr) continue;

            u16 j = mix16(e.name.get_hash()) & mask;
            while (table[j].top != nullptr) j = (j + 1) & mask;
            table[j] = e;
            ++size;
        }

        if (old != nullptr) {
            for (u16 i = 0; i < old_cap; ++i) {
                old[i].~Entry();
            }
            ::operator delete[](old);
        }
    }

public:

    Registry() : table(nullptr), cap(0), size(0) {
        clear();
    }

    ~Registry() {
        clear();
    }

    Registry(const Registry&) = delete;
    Registry& operator=(const Registry&) = delete;
    Registry(Registry&&) = delete;
    Registry& operator=(Registry&&) = delete;

    /// Maps a key to the given value. If it already exists, replaces it.
    void insert(const Key& key, const T& value) {
        // Grow the table if the load factor exceeds 0.7
        if ((uint64_t)(size + 1) * 10ull >= (uint64_t)cap * 7ull) {
            grow();
        }

        u16 mask = cap - 1;
        u16 i = mix16(key.name.get_hash()) & mask;

        while (i < cap) {
            Entry& e = table[i];

            // Empty slot, insert here
            if (e.top == nullptr) {
                e.name = key.name;

                Layer* new_layer = static_cast<Layer*>(::operator new(sizeof(Layer)));
                ::new (new_layer) Layer{ key.mod, true, value, nullptr };
                e.top = new_layer;
                ++size;
                return;
            }

            // Found existing entry
            if (e.name == key.name) {
                // Search for mod in stack
                Layer* layer = e.top;
                while (layer) {
                    if (layer->mod == key.mod) {
                        // Found existing layer, replace value
                        layer->value = value;
                        layer->live = true;
                        return;
                    }
                    layer = layer->next;
                }

                // Mod not found, insert new layer at top of stack
                Layer* new_layer = static_cast<Layer*>(::operator new(sizeof(Layer)));
                ::new (new_layer) Layer{ key.mod, true, value, nullptr };
                e.top = new_layer;
                return;
            }

            i = (i + 1) & mask;
        }

        PANIC_MSG("Registry insert failed: table full");
    }

    /// Removes a key.
    /// Actually marks it as dead so that its position in its layer stack is preserved if reinserted.
    void remove(const Key& key) {
        u16 mask = cap - 1;
        u16 i = mix16(key.name.get_hash()) & mask;

        while (i < cap) {
            Entry& e = table[i];

            // Empty slot, key not found
            if (e.top == nullptr) {
                return;
            }

            // Found existing entry
            if (e.name == key.name) {
                // Search for mod in stack
                Layer* layer = e.top;
                while (layer) {
                    if (layer->mod == key.mod) {
                        // Found existing layer, mark dead
                        layer->live = false;
                        return;
                    }
                    layer = layer->next;
                }

                return;
            }

            i = (i + 1) & mask;
        }
    }

    /// Looks up a name. Returns nullptr if not found.
    T* try_get(const String& name) {
        u16 mask = cap - 1;
        u16 i = mix16(name.get_hash()) & mask;

        while (i < cap) {
            Entry& e = table[i];

            // Empty slot, key not found
            if (e.name.c_str() == nullptr) {
                return nullptr;
            }

            // Found existing entry
            if (e.name == name) {
                // Search for mod in stack
                Layer* layer = e.top;
                while (layer) {
                    // Found existing layer
                    if (layer->live) {
                        return &layer->value;
                    }
                    layer = layer->next;
                }

                return nullptr;
            }

            i = (i + 1) & mask;
        }

        return nullptr;
    }

    /// Looks up a name. Panics if not found.
    T& get(const String& name) {
        T* val = try_get(name);
        if (val == nullptr) {
            PANIC_MSG("Attempt to lookup %s in Registry but not found", name.c_str());
        }
        return *val;
    }

    /// Looks up by index.
    T* try_get_by_index(u16 index) {
        if (index >= cap) {
            return nullptr;
        }
        Entry& e = table[index];
        if (e.name.c_str() == nullptr) {
            return nullptr;
        }
        Layer* layer = e.top;
        while (layer != nullptr) {
            if (layer->live) {
                return &layer->value;
            }
            layer = layer->next;
        }
        return nullptr;
    }

    u16 get_index(const String& name) {
        u16 mask = cap - 1;
        u16 i = mix16(name.get_hash()) & mask;

        while (i < cap) {
            Entry& e = table[i];

            // Empty slot, key not found
            if (e.top == nullptr) {
                PANIC_MSG("Attempt to get index of %s in Registry but not found", name.c_str());
            }

            // Found existing entry
            if (e.name == name) {
                return i;
            }

            i = (i + 1) & mask;
        }

        PANIC_MSG("Attempt to get index of %s in Registry but not found", name.c_str());
    }

    /// Gets the mod that has precedence for `name`.
    const String& get_mod(const String& name) {
        u16 mask = cap - 1;
        u16 i = mix16(name.get_hash()) & mask;

        while (i < cap) {
            Entry& e = table[i];

            // Empty slot, key not found
            if (e.name.c_str() == nullptr) {
                PANIC_MSG("Attempt to get mod of %s in Registry but not found", name.c_str());
            }

            // Found existing entry
            if (e.name == name) {
                // Search for mod in stack
                Layer* layer = e.top;
                while (layer) {
                    // Found existing layer
                    if (layer->live) {
                        return layer->mod;
                    }
                    layer = layer->next;
                }

                PANIC_MSG("Attempt to get mod of %s in Registry but not found", name.c_str());
            }

            i = (i + 1) & mask;
        }

        PANIC_MSG("Attempt to get mod of %s in Registry but not found", name.c_str());
    }

    /// Marks all entries owned by `mod` dead.
    void unload_mod(const String& mod) {
        for (u16 i = 0; i < cap; ++i) {
            Entry& e = table[i];

            Layer* layer = e.top;
            while (layer) {
                if (layer->mod == mod) {
                    layer->live = false;
                }
                layer = layer->next;
            }
        }
    }

    void clear() {
        // Free all layers
        for (u16 i = 0; i < cap; ++i) {
            table[i].~Entry();
        }
        ::operator delete[](table);
        table = nullptr;
        cap = 0;
        size = 0;
    }

    /// Visits every value in the registry at the top of its stack.
    template<typename Func>
    void for_each(Func func) {
        for (u16 i = 0; i < cap; ++i) {
            Entry& e = table[i];

            if (e.top != nullptr)
                debug_printf("%d %p", i, e.top);

            Layer* layer = e.top;
            while (layer) {
                if (layer->live) {
                    func(i, e.name, layer->value);
                    break;
                }
                layer = layer->next;
            }
        }
    }
};

};

#endif
