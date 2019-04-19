#include <stdio.h>

class PowerSet {
private:
    int slots_step;
public:
    int slots_size;
    char **slots;

    PowerSet() {
        this->slots_size = 5;
        this->slots_step = 1;
        this->slots = new char *[this->slots_size];

        for (int i = 0; i < this->slots_size; i++) this->slots[i] = nullptr;
    }

    int size() {
        int res = 0;
        for (int i = 0; i < this->slots_size; i++) {
            if (this->slots[i] != nullptr) {
                res++;
            }
        }
        return res;
    }

    void put(char *value) {
        int hash_key = this->seekSlot(value);

        if (this->find(value) != -1) {
            return;
        }

        if (hash_key == -1) {
            int new_size = this->slots_size * 2 + 1;
            char **new_slots = new char *[new_size];
            for (int i = 0; i < new_size; i++) new_slots[i] = nullptr;
            int k = 0;
            for (int i = 0; i < this->slots_size; i++) {
                if (this->slots[i] != nullptr) {
                    new_slots[k++] = this->slots[i];
                }
            }
            delete[] this->slots;
            this->slots = new_slots;
            this->slots_size = new_size;
            this->put(value);
        } else {
            this->slots[hash_key] = value;
        }
    }

    bool get(char *value) {
        return this->find(value) != -1;
    }

    bool remove(char *value) {

        if (2 * this->size() < this->slots_size && this->slots_size > 5) {
            int new_size = 2 * this->slots_size / 3 + 1;
            char **new_slots = new char *[new_size];
            for (int i = 0; i < new_size; i++) new_slots[i] = nullptr;
            int k = 0;
            for (int i = 0; i < this->slots_size; i++) {
                if (this->slots[i] != nullptr) {
                    new_slots[k++] = this->slots[i];
                }
            }
            delete[] this->slots;
            this->slots_size = new_size;
            this->slots = new_slots;
            return this->remove(value);
        }

        int hash_key = this->find(value);
        if (hash_key != -1) {
            this->slots[hash_key] = nullptr;
            return true;
        }
        return false;
    }

    PowerSet *intersection(PowerSet *set2) {
        PowerSet *res_set = new PowerSet();

        for (int i = 0; i < this->slots_size; i++) {
            if (set2->get(this->slots[i])) {
                res_set->put(this->slots[i]);
            }
        }
        return res_set;
    }

    PowerSet *_union(PowerSet *set2) {
        PowerSet *res_set = new PowerSet();
        if (set2->size() == 0) {
            return this;
        } else if (this->size() == 0) {
            return set2;
        }

        for (int i = 0; i < this->slots_size; i++) {
            if (this->slots[i] != nullptr) {
                res_set->put(this->slots[i]);
            }
        }

        for (int i = 0; i < set2->slots_size; i++) {
            if (set2->slots[i] != nullptr) {
                res_set->put(set2->slots[i]);
            }
        }
        return res_set;
    }

    PowerSet *difference(PowerSet *set2) {
        PowerSet *res_set = new PowerSet();
        if (this->size() == 0) {
            return res_set;
        }
        if (set2->size() == 0) {
            return this;
        }

        for (int i = 0; i < this->size(); i++) {
            if (this->slots[i] != nullptr) {
                if (!set2->get(this->slots[i])) {
                    res_set->put(this->slots[i]);
                }
            }
        }

        return res_set;
    }

    bool is_subset(PowerSet *set2) {
        for (int i = 0; i < set2->slots_size; i++) {
            if (set2->slots[i] != nullptr) {
                if (!this->get(set2->slots[i])) {
                    return false;
                }
            }
        }
        return true;
    }

    int hashFun(char *value) {
        if (value == nullptr) {
            return -1;
        }
        int hash_value = 0;

        for (int i = 0; value[i] != 0; i++) {
            hash_value += (int) value[i];
        }
        return hash_value % this->slots_size;
    }

    int seekSlot(char *value) {
        int hash_key = this->hashFun(value);

        if (hash_key == -1) {
            return -1;
        }
        for (int i = 0; i < this->slots_step + 1; ++i) {
            while (hash_key < this->slots_size) {
                if (this->slots[hash_key] == nullptr) {
                    return hash_key;
                }
                hash_key += this->slots_step;
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
        for (int i = 0; i < this->slots_step + 1; ++i) {
            while (hash_key < this->slots_size) {
                if (this->slots[hash_key] != nullptr && PowerSet::is_equal_strings(this->slots[hash_key], value) == 1) {
                    return hash_key;
                }
                hash_key += this->slots_step;
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