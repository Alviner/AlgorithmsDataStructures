#include <stdio.h>

class NativeDictionary {
private:
    int step;
public:
    int slots_size;
    char **slots;
    int *values;

    NativeDictionary(int sz) {
        this->slots_size = sz;
        this->slots = new char *[this->slots_size];
        for (int i = 0; i < this->slots_size; i++) this->slots[i] = nullptr;
        this->values = new int[this->slots_size];
        for (int i = 0; i < this->slots_size; i++) this->values[i] = -1;

        this->step = 3;
    }

    int hashFun(char *key) {
        if (key == nullptr) {
            return -1;
        }
        int hash_value = 0;

        for (int i = 0; key[i] != 0; i++) {
            hash_value += (int) key[i];
        }
        return hash_value % this->slots_size;
    }

    bool is_key(char *key) {
        return this->find(key) != -1;
    }

    void put(char *key, int value) {
        int hash_key = this->find(key);

        if (hash_key != -1) {
            this->values[hash_key] = value;
            return;
        }

        hash_key = this->seekSlot(key);

        if (hash_key != -1) {
            this->slots[hash_key] = key;
            this->values[hash_key] = value;
        }
    }

    int get(char *key) {
        int hash_key = this->find(key);

        if (hash_key == -1) {
            return -1;
        }
        return this->values[hash_key];
    }

    int seekSlot(char *value) {
        int hash_key = this->hashFun(value);

        if (hash_key == -1) {
            return -1;
        }
        int limit = this->step * (this->slots_size / this->step);
        for (int i = 0; i < limit; ++i) {
            while (hash_key < this->slots_size) {
                if (this->slots[hash_key] == nullptr) {
                    return hash_key;
                }
                hash_key += this->step;
            }
            hash_key -= this->slots_size;
        }
        return -1;
    }

    int find(char *value) {
        int hash_key = this->hashFun(value);

        if (hash_key == -1) {
            return -1;
        }

        int limit = this->step * (this->slots_size / this->step);
        for (int i = 0; i < limit; ++i) {
            while (hash_key < this->slots_size) {
                if (this->slots[hash_key] != nullptr &&
                    NativeDictionary::is_equal_strings(this->slots[hash_key], value) == 1) {
                    return hash_key;
                }
                hash_key += this->step;
            }
            hash_key -= this->slots_size;
        }

        return -1;
    }

    static int is_equal_strings(const char *first, const char *second) {
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