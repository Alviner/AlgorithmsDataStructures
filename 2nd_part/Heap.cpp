#include <stdio.h>

class Heap {
public:
    int *HeapArray; // хранит неотрицательные числа-ключи
    int size;

    Heap() {
        HeapArray = nullptr;
        size = 0;
    }

    void MakeHeap(int *a, int depth) {
        // создаём массив кучи HeapArray из заданного
        // размер массива выбираем на основе глубины depth
        this->size = Heap::Depth2Size(depth);
        this->HeapArray = new int[this->size];
        for (int i = 0; i < this->size; i++) {
            this->HeapArray[i] = -1;
        }
        int i = 0;

        while (i < this->size) {
            this->Add(a[i]);
            i++;
        }

    }

    int GetMax() {
        // вернуть значение корня и перестроить кучу
        int res;
        if (this->Count() == 0) {
            return -1; // если куча пуста
        }
        res = this->HeapArray[0];
        this->HeapArray[0] = -1;
        Heap::swap(&this->HeapArray[0], &this->HeapArray[this->Count()]);
        this->ScreemDown(0);
        return res;
    }

    bool Add(int key) {
        // добавляем новый элемент key в кучу и перестраиваем её
        for (int i = 0; i < this->size; i++) {
            if (this->HeapArray[i] == -1) {
                this->HeapArray[i] = key;
                this->ScreenUp(i);
                return true;
            }
        }
        return false; // если куча вся заполнена
    }

    void __print(int index, int space = 0) {
        // Base case
        if (index >= this->size)
            return;

        // Increase distance between levels
        space += 10;

        // Process right child first
        this->__print(2 * index + 2, space);

        // Print current node after space
        // count
        printf("\n");
        for (int i = 10; i < space; i++)
            printf(" ");
        printf("%d\n", this->HeapArray[index]);

        this->__print(2 * index + 1, space);
    }

    void print() {
        this->__print(0, 0);
    }

    int Count() {
        int res = 0;
        for (int i = 0; i < this->size; i++) {
            if (this->HeapArray[i] != -1 ) {
                res++;
            }
        }
        return res;
    }

private:

    static int Depth2Size(int depth) {
        int res = 1;
        for (int i = 0; i < depth + 1; ++i) {
            res *= 2;
        }
        return res - 1;
    }

    static void swap(int *a, int *b) {
        int temp = *b;
        *b = *a;
        *a = temp;
    }

    void ScreenUp(int index) {
        while (this->HeapArray[index] > this->HeapArray[(index - 1) / 2]) {
            int parent_index = (index - 1) / 2;
            Heap::swap(&this->HeapArray[index], &this->HeapArray[parent_index]);
            index = parent_index;
        }
    }

    void ScreemDown(int index) {
        int l_child_index;
        int r_child_index;
        int max_child_index;
        while(2 * index + 1 < this->size) {
            l_child_index = 2 * index + 1;
            r_child_index = 2 * index + 2;
            max_child_index = this->HeapArray[r_child_index] > HeapArray[l_child_index] ? r_child_index : l_child_index;

            if(this->HeapArray[index] < this->HeapArray[max_child_index]) {
                swap(&this->HeapArray[index], &this->HeapArray[max_child_index]);
            }
            index = max_child_index;
        }
    }
};
