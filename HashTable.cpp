#include <stdio.h>

class HashTable {
public:
    int size;
    int step;
    char **slots;

    HashTable(int sz, int stp) {
        size = sz;
        step = stp;
        slots = new char *[size];
        for (int i = 0; i < size; i++) slots[i] = nullptr;
    }

    int hashFun(char *value) {
        if (value == nullptr) {
            return -1;
        }
        int hash_value = 0;

        for (int i = 0; value[i] != 0; i++) {
            hash_value += int(value[i]);
        }
        return hash_value % this->size;
    }

    int seekSlot(char *value) {
        int hash_key = this->hashFun(value);

        if (hash_key == -1) {
            return -1;
        }
        int limit = this->step * (this->size / this->step);
        for (int i = 0; i < limit; ++i) {
            while (hash_key < this->size) {
                if (slots[hash_key] == nullptr) {
                    return hash_key;
                }
                hash_key += this->step;
            }
            hash_key = hash_key - this->size;
        }
        return -1;
    }

    int put(char *value) {
        int hash_key = this->seekSlot(value);

        if (hash_key == -1) {
            return -1;
        }

        this->slots[hash_key] = value;
        return hash_key;
    }

    int find(char *value) {
        int hash_key = this->seekSlot(value);

        if (hash_key == -1) {
            return -1;
        }

        int limit = this->step * (this->size / this->step);
        for (int i = 0; i < limit; ++i) {
            while (hash_key < this->size) {
                if (this->slots[hash_key] != nullptr && HashTable::is_equal_strings(this->slots[hash_key], value) == 1) {
                    return hash_key;
                }
                hash_key += this->step;
            }
            hash_key = hash_key - this->size;
        }

        return -1;
    }

    static int is_equal_strings(char *first, char *second) {
        int size_first = 0;
        int size_second = 0;
        for (int i = 0; first[i] != 0; i++) {
            size_first += 1;
        }
        for (int i = 0; second[i] != 0; i++) {
            size_second += 1;
        }
        if (size_first != size_second) {
            return 0;
        }
        for (int i = 0; first[i] != 0; i++) {
            if (first[i] != second[i]) {
                return 0;
            }
        }
        return 1;
    }
};