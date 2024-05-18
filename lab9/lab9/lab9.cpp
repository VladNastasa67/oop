#include <iostream>
#include <cstdio>

template <typename KeyType, typename ValueType>
class SimpleMap {
private:
    struct Entry {
        KeyType key;
        ValueType value;
        Entry* next = nullptr;
    };

    Entry* firstEntry = nullptr;
    Entry* lastEntry = nullptr;
    size_t entryCount = 0;

public:
    SimpleMap() {}

    ~SimpleMap() {
        removeAllEntries();
    }

    ValueType& operator[](const KeyType& key) {
        Entry* current = firstEntry;
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        Entry* newEntry = new Entry{ key, ValueType(), nullptr };
        if (lastEntry != nullptr) {
            lastEntry->next = newEntry;
        }
        else {
            firstEntry = newEntry;
        }
        lastEntry = newEntry;
        entryCount++;
        return newEntry->value;
    }

    bool getValue(const KeyType& key, ValueType& value) const {
        Entry* current = firstEntry;
        while (current != nullptr) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool remove(const KeyType& key) {
        Entry* current = firstEntry, * previous = nullptr;
        while (current != nullptr) {
            if (current->key == key) {
                if (previous != nullptr) {
                    previous->next = current->next;
                }
                else {
                    firstEntry = current->next;
                }
                if (current == lastEntry) {
                    lastEntry = previous;
                }
                delete current;
                entryCount--;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    size_t size() const {
        return entryCount;
    }

    void clear() {
        removeAllEntries();
    }

    bool includes(const SimpleMap<KeyType, ValueType>& other) const {
        Entry* current = other.firstEntry;
        ValueType tmpValue;
        while (current != nullptr) {
            if (!getValue(current->key, tmpValue)) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    void removeAllEntries() {
        while (firstEntry != nullptr) {
            Entry* toDelete = firstEntry;
            firstEntry = firstEntry->next;
            delete toDelete;
        }
        firstEntry = lastEntry = nullptr;
        entryCount = 0;
    }

    class Iterator {
    private:
        Entry* pointer;
        size_t position;

    public:
        Iterator(Entry* ptr, size_t pos) : pointer(ptr), position(pos) {}

        bool operator!=(const Iterator& other) const {
            return pointer != other.pointer;
        }

        Iterator& operator++() {
            if (pointer != nullptr) {
                pointer = pointer->next;
                ++position;
            }
            return *this;
        }

        auto operator*() const -> std::tuple<const KeyType&, const ValueType&, size_t> {
            return { pointer->key, pointer->value, position };
        }
    };

    Iterator begin() const {
        return Iterator(firstEntry, 0);
    }

    Iterator end() const {
        return Iterator(nullptr, entryCount);
    }
};

int main() {
    SimpleMap<int, const char*> map;
    map[10] = "C++";
    map[20] = "test";
    map[30] = "Poo";
    for (auto [key, value, index] : map) {
        printf("Index:%zu, Key=%d, Value=%s\n", index, key, value);
    }
    map[20] = "result";
    for (auto [key, value, index] : map) {
        printf("Index:%zu, Key=%d, Value=%s\n", index, key, value);
    }
    return 0;
}
