#include<stdio.h>
#include<string.h>

class NativeCache {
public:
    int slots_size;
    char **slots;
    int *values;
    int *usages;

    NativeCache(int sz) {
        this->step = 1;
        this->slots_size = sz;

        this->slots = new char *[this->slots_size];
        this->values = new int[this->slots_size];
        this->usages = new int[this->slots_size];

        for (int i = 0; i < this->slots_size; ++i) this->slots[i] = nullptr;
        for (int i = 0; i < this->slots_size; ++i) this->values[i] = -1;
        for (int i = 0; i < this->slots_size; ++i) this->usages[i] = 0;
    }

    int hashFun(char *key) {
        if (key == nullptr) return -1;

        int index = 0;
        for (int i = 0; key[i] != 0; ++i) {
            index += (int) key[i];
        }
        return index % this->slots_size;
    }

    bool is_key(char *key) {
        int hash_key = this->find(key);
        if (hash_key == -1) return false;

        this->usages[hash_key]++;
        return true;

    }

    void put(char *key, int value) {
        int hash_key = seekSlot(key);

        if (hash_key == -1) {
            hash_key = this->get_remove();
            this->usages[hash_key] = 0;
        }
        slots[hash_key] = key;
        values[hash_key] = value;
    }

    int get(char *key) {
        int hash_key = this->find(key);
        if (hash_key == -1) return -1;
        this->usages[hash_key]++;
        return values[hash_key];
    }

private:
    int step;

    int get_remove() {
        int min = this->usages[0];
        int res = 0;

        for (int i = 0; i < this->slots_size; ++i) {
            if (min > this->usages[i]) {
                min = this->usages[i];
                res = i;
            }
        }
        return res;
    }

    int seekSlot(char *value) {
        int hash_key = this->hashFun(value);

        if (hash_key == -1) {
            return -1;
        }
        for (int i = 0; i < this->step; ++i) {
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

        for (int i = 0; i < this->step; ++i) {
            while (hash_key < this->slots_size) {
                if (this->slots[hash_key] != nullptr &&
                    NativeCache::is_equal_strings(this->slots[hash_key], value) == 1) {
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