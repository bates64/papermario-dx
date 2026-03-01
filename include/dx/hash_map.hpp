#pragma once

#include <concepts>
#include <functional>
#include <utility>
#include "dx/optional.hpp"

namespace dx {

template<typename K>
concept HashMapKey = requires(K a, K b) {
    { std::hash<K>{}(a) } -> std::convertible_to<std::size_t>;
    { a == b } -> std::convertible_to<bool>;
};

template<HashMapKey K, typename V>
class HashMap {
public:
    HashMap(u32 initialCapacity = 0)
        : capacity(initialCapacity)
        , count(0)
    {
        if (capacity > 0) {
            buckets = new Entry*[capacity]();
        } else {
            buckets = nullptr;
        }
    }

    ~HashMap() {
        clear();
        delete[] buckets;
    }

    /// Inserts if key is not already present. No-op if it is.
    void insert(K key, V value) {
        if (capacity == 0) {
            capacity = 16;
            buckets = new Entry*[capacity]();
        } else if (count * 4 > capacity * 3) {
            resize();
        }

        u32 hashValue = hasher(key) % capacity;
        Entry* entry = buckets[hashValue];

        while (entry) {
            if (entry->key == key) {
                return;
            }
            entry = entry->next;
        }

        Entry* newEntry = new Entry{std::move(key), std::move(value), buckets[hashValue]};
        buckets[hashValue] = newEntry;
        count++;
    }

    /// Inserts or overwrites value for key.
    void insert_or_assign(K key, V value) {
        if (capacity == 0) {
            capacity = 16;
            buckets = new Entry*[capacity]();
        } else if (count * 4 > capacity * 3) {
            resize();
        }

        u32 hashValue = hasher(key) % capacity;
        Entry* entry = buckets[hashValue];

        while (entry) {
            if (entry->key == key) {
                entry->value = std::move(value);
                return;
            }
            entry = entry->next;
        }

        Entry* newEntry = new Entry{std::move(key), std::move(value), buckets[hashValue]};
        buckets[hashValue] = newEntry;
        count++;
    }

    optional<V&> find(const K& key) {
        if (capacity == 0) {
            return none;
        }
        u32 hashValue = hasher(key) % capacity;
        Entry* entry = buckets[hashValue];

        while (entry) {
            if (entry->key == key) {
                return entry->value;
            }
            entry = entry->next;
        }

        return none;
    }

    optional<const V&> find(const K& key) const {
        if (capacity == 0) {
            return none;
        }
        u32 hashValue = hasher(key) % capacity;
        Entry* entry = buckets[hashValue];

        while (entry) {
            if (entry->key == key) {
                return entry->value;
            }
            entry = entry->next;
        }

        return none;
    }

    void clear() {
        if (buckets != nullptr) {
            for (u32 i = 0; i < capacity; i++) {
                Entry* entry = buckets[i];
                while (entry) {
                    Entry* next = entry->next;
                    delete entry;
                    entry = next;
                }
                buckets[i] = nullptr;
            }
        }
        count = 0;
    }

    bool contains(const K& key) const {
        return find(key).has_value();
    }

    bool erase(const K& key) {
        if (capacity == 0) {
            return false;
        }
        u32 hashValue = hasher(key) % capacity;
        Entry* entry = buckets[hashValue];
        Entry* prev = nullptr;

        while (entry) {
            if (entry->key == key) {
                if (prev) {
                    prev->next = entry->next;
                } else {
                    buckets[hashValue] = entry->next;
                }
                delete entry;
                count--;
                return true;
            }
            prev = entry;
            entry = entry->next;
        }
        return false;
    }

    u32 size() const {
        return count;
    }

    template<typename F>
    void for_each(F&& fn) const {
        for (u32 i = 0; i < capacity; i++) {
            Entry* entry = buckets[i];
            while (entry) {
                fn(entry->key, entry->value);
                entry = entry->next;
            }
        }
    }

private:
    struct Entry {
        K key;
        V value;
        Entry* next;
    };

    Entry** buckets;
    std::hash<K> hasher;
    u32 capacity;
    u32 count;

    void resize() {
        u32 oldCapacity = capacity;
        Entry** oldBuckets = buckets;

        capacity *= 2;
        buckets = new Entry*[capacity]();

        for (u32 i = 0; i < oldCapacity; i++) {
            Entry* entry = oldBuckets[i];
            while (entry) {
                Entry* next = entry->next;
                u32 hashValue = hasher(entry->key) % capacity;
                entry->next = buckets[hashValue];
                buckets[hashValue] = entry;
                entry = next;
            }
        }

        delete[] oldBuckets;
    }
};

} // namespace dx
