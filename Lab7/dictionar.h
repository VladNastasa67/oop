#include <iostream>
#include <string>

using namespace std;

template<typename Key, typename Value>
class Dictionar {
private:
    static const int TABLE_SIZE = 100;
    pair<Key, Value> table[TABLE_SIZE];

    long long hash(const Key& key) const {
        long long hash_value = 5381;
        for (char c : key) {
            hash_value = ((hash_value << 5) + hash_value) + c; // hash * 33 + c
        }
        return hash_value % TABLE_SIZE;
    }

public:
    Value& operator[](const Key& key) {
        long long index = hash(key);
        return table[index].second;
    }
};

