#include <stdio.h>


class DynArray
{
public:
    int count;
    int capacity;
    int* array;

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
        if (index < 0 or index >= this->count) {
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

        this->append(-1);

        for (int i = this->count; i > index; --i) {
            this->array[i] = this->array[i - 1];
        }
        this->array[index] = value;
    }

    void remove(int index) // O(n)
    {
        if (index < 0 or index >= this->count) {
            throw "Index out of bounds";
        }

        for (int i = index; i < this->count; ++i)
        {
            this->array[i] = this->array[i + 1];
        }
        --this->count;

        if (2 * this->count < this->capacity) {
            int new_capacity = 2 * this->capacity / 3;
            new_capacity = new_capacity > 16 ? new_capacity : 16;
            this->make_array(new_capacity);
        }
    }

    int pop() {
        auto index = this->count - 1;
        auto value = this->get_item(index);
        this->remove(index);
        return value;
    }

};


class Stack
{

public:
    DynArray *stack;
    Stack()
    {
        this->stack = new DynArray();
    }

    int size()
    {
        return this->stack->count;
    }

    int pop()
    {
        if (this->size() == 0) {
            return -1;
        }
        return this->stack->pop();
    }

    void push(int val)
    {
        this->stack->append(val);
    }

    int peek()
    {
        if (this->size() == 0) {
            return -1;
        }
        return this->stack->get_item(this->stack->count - 1);
    }
};


