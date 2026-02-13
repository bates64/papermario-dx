#pragma once

#ifdef __cplusplus

#include "dx/hash.h"
#include "dx/cmp.h"
#include "dx/option.h"

namespace dx {
namespace collections {

using dx::option::Option;
using dx::hash::Hash;
using dx::cmp::Eq;
using dx::move;

/// An associative container that maps keys to values.
///
/// Use a HashMap when you need to associate arbitrary keys with values and
/// look them up efficiently. For dense integer keys in a known range, a plain
/// array or Vec is simpler and faster. HashMap is better suited for sparse,
/// non-contiguous, or non-integer keys (e.g. strings, pointers, structs).
///
/// Duplicate keys are not stored — inserting with an existing key overwrites
/// the previous value.
///
/// https://en.wikipedia.org/wiki/Hash_table
///
/// @tparam K Key type. Should specialize Hash<K> and Eq<K>.
/// @tparam V Value type.
template<typename K, typename V>
class HashMap {
public:
    HashMap(u32 initialCapacity = 0)
        : capacity(initialCapacity)
        , count(0)
    {
        printf("hello\n");
        if (capacity > 0) {
            buckets = new Entry*[capacity]();  // Zero-initialize
        } else {
            buckets = nullptr;
        }
    }

    ~HashMap() {
        clear();
        if (buckets != nullptr) {
            delete[] buckets;
        }
    }

    /// Overwrites value if it already exists
    void put(K key, V value) {
        // Allocate initial capacity on first insert
        if (capacity == 0) {
            capacity = 16;
            buckets = new Entry*[capacity];
        }
        // Resize if load factor > 0.75
        else if (count * 4 > capacity * 3) {
            resize();
        }

        u32 hash_value = hasher(key) % capacity;
        Entry* entry = buckets[hash_value];

        // Check if key already exists - overwrite if so (for "last instance" behavior)
        while (entry) {
            if (equals(entry->key, key)) {
                entry->value = move(value);
                return;
            }
            entry = entry->next;
        }

        // Add new entry at head of chain
        Entry* new_entry = new Entry{move(key), move(value), buckets[hash_value]};
        buckets[hash_value] = new_entry;
        count++;
    }

    /// Constructs key in-place from arguments (more ergonomic than put)
    template<typename KeyArg>
    void emplace(KeyArg&& key_arg, V value) {
        put(K(key_arg), move(value));
    }

    Option<V&> get(const K& key) {
        if (capacity == 0) {
            return Option<V&>::none();
        }
        u32 hashValue = hasher(key) % capacity;
        Entry* entry = buckets[hashValue];

        while (entry) {
            if (equals(entry->key, key)) {
                return Option<V&>::some(entry->value);
            }
            entry = entry->next;
        }

        return Option<V&>::none();
    }

    Option<const V&> get(const K& key) const {
        if (capacity == 0) {
            return Option<const V&>::none();
        }
        u32 hashValue = hasher(key) % capacity;
        Entry* entry = buckets[hashValue];

        while (entry) {
            if (equals(entry->key, key)) {
                return Option<const V&>::some(entry->value);
            }
            entry = entry->next;
        }

        return Option<const V&>::none();
    }

    /// Panics if key not found
    V& operator[](const K& key) {
        auto value = get(key);
        return value.unwrap();
    }

    /// Panics if key not found
    const V& operator[](const K& key) const {
        auto value = get(key);
        return value.unwrap();
    }

    void clear() {
        if (buckets != nullptr) {
            for (u32 i = 0; i < capacity; i++) {
                Entry* entry = buckets[i];
                while (entry) {
                    Entry* next = entry->next;
                    delete entry;  // Calls Entry destructor, which calls K and V destructors
                    entry = next;
                }
                buckets[i] = nullptr;
            }
        }
        count = 0;
    }

    u32 size() const {
        return count;
    }

private:
    struct Entry;  // Forward declaration

public:
    /// Iterator support for range-based for loops
    class Iterator {
    private:
        HashMap* map;
        u32 bucketIdx;
        Entry* current;

        void advance_to_next() {
            while (bucketIdx < map->capacity && map->buckets[bucketIdx] == nullptr) {
                bucketIdx++;
            }
            if (bucketIdx < map->capacity) {
                current = map->buckets[bucketIdx];
            } else {
                current = nullptr;
            }
        }

    public:
        struct Item {
            K& key;
            V& value;
        };

        Iterator(HashMap* map, u32 bucketIdx, Entry* entry)
            : map(map), bucketIdx(bucketIdx), current(entry) {
            if (current == nullptr) {
                advance_to_next();
            }
        }

        Item operator*() {
            return Item{current->key, current->value};
        }

        Iterator& operator++() {
            if (current) {
                current = current->next;
                if (current == nullptr) {
                    bucketIdx++;
                    advance_to_next();
                }
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current || bucketIdx != other.bucketIdx;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current && bucketIdx == other.bucketIdx;
        }
    };

    class ConstIterator {
    private:
        const HashMap* map;
        u32 bucketIdx;
        const Entry* current;

        void advance_to_next() {
            while (bucketIdx < map->capacity && map->buckets[bucketIdx] == nullptr) {
                bucketIdx++;
            }
            if (bucketIdx < map->capacity) {
                current = map->buckets[bucketIdx];
            } else {
                current = nullptr;
            }
        }

    public:
        struct Item {
            const K& key;
            const V& value;
        };

        ConstIterator(const HashMap* map, u32 bucketIdx, const Entry* entry)
            : map(map), bucketIdx(bucketIdx), current(entry) {
            if (current == nullptr) {
                advance_to_next();
            }
        }

        Item operator*() const {
            return Item{current->key, current->value};
        }

        ConstIterator& operator++() {
            if (current) {
                current = current->next;
                if (current == nullptr) {
                    bucketIdx++;
                    advance_to_next();
                }
            }
            return *this;
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current || bucketIdx != other.bucketIdx;
        }

        bool operator==(const ConstIterator& other) const {
            return current == other.current && bucketIdx == other.bucketIdx;
        }
    };

    Iterator begin() {
        return iterator(this, 0, nullptr);
    }

    Iterator end() {
        return iterator(this, capacity, nullptr);
    }

    ConstIterator begin() const {
        return const_iterator(this, 0, nullptr);
    }

    ConstIterator end() const {
        return const_iterator(this, capacity, nullptr);
    }

private:
    struct Entry {
        K key;
        V value;
        Entry* next;
    };

    Entry** buckets;
    Hash<K> hasher;
    Eq<K> equals;
    u32 capacity;
    u32 count;

    void resize() {
        u32 oldCapacity = capacity;
        Entry** oldBuckets = buckets;

        // Double capacity
        capacity *= 2;
        buckets = new Entry*[capacity];

        // Rehash all existing entries
        for (u32 i = 0; i < oldCapacity; i++) {
            Entry* entry = oldBuckets[i];
            while (entry) {
                Entry* next = entry->next;

                // Reinsert into new buckets
                u32 hashValue = hasher(entry->key) % capacity;
                entry->next = buckets[hashValue];
                buckets[hashValue] = entry;

                entry = next;
            }
        }

        delete[] oldBuckets;
    }
};

} // namespace collections
} // namespace dx

#endif // __cplusplus
