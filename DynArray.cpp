#include <stdio.h>

class DynArray
{
public:
    int count;
    int capacity;
    int* array;  // хранит неотрицательные значения

    DynArray()
    {
        count = 0;
        make_array(16);
    }

    void make_array(int new_capacity)
    {
        int* new_array = new int[new_capacity];
        for (int i = 0; i < new_capacity; ++i) {
            new_array[i] = -1;
        };
        for (int i = 0; i < this->count; i++) {
            new_array[i] = this->array[i];
        }
        delete[] this->array;
        this->array = new_array;
        this->capacity = new_capacity;
    }

    int get_item(int index)
    {
        if (index < 0 or index >= this->capacity) {
            throw "Index out of bounds";
        }
        return this->array[index];
    }

    void append(int value)
    {
        if (this->count == this->capacity) {
            this->make_array(2 * this->capacity);
        }

        this->array[this->count] = value;
        ++this->count;
    }

    void insert(int value, int index)   // O(n)
    {
        if (index < 0 or index > this->count) {
            throw "Index out of bounds";
        }

        if (this->count == index) {
            this->append(value);
            return;
        }

        this->append(0);

        for (int i = this->count; i > 0; i --) {
            if (i > index) {
                this->array[i] = this->array[i - 1];
            } else if (i == index) {
                this->array[i] = value;
            }
        }
    }

    void remove(int index) // O(n)
    {
        if (index < 0 or index > this->count) {
            throw "Index out of bounds";
        }

        for (int i = index; i < this->count - 1; i++) {
            this->array[i] = this->array[i + 1];
        }
        --this->count;

        if (2 * this->count < this->capacity) {
            int new_capacity = 2 * this->capacity / 3;
            new_capacity = new_capacity > 16 ? new_capacity : 16;
            this->make_array(new_capacity);
        }
    }

};