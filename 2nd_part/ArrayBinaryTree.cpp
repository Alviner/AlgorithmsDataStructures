#include <stdio.h>

class aBST {
public:
    int *Tree; // массив положительных ключей
    int tree_size;

    aBST(int depth) {
        // правильно рассчитайте размер массива для дерева глубины depth:
        this->tree_size = aBST::Depth2Size(depth);
        this->Tree = new int[this->tree_size];
        for (int i = 0; i < this->tree_size; i++) this->Tree[i] = -1;
    }

    int FindKeyIndex(int key) {
        // ищем в массиве индекс ключа
        int i = 0;
        while (i < this->tree_size) {
            if (key < this->Tree[i]) {
                i = 2 * i + 1;
            } else if (key > this->Tree[i]) {
                i = 2 * i + 2;
            } else {
                return i;
            }

        }
        return -1; // не найден
    }

    int FindFreeCell(int key) {
        // подходящий слот в массиве
        // для размещения ключа
        if (this->FindKeyIndex(key) != -1) return -1;
        int i = 0;

        while (i < this->tree_size) {
            if (this->Tree[i] == -1) {
                return i;
            } else if (key < this->Tree[i]) {
                i = 2 * i + 1;
            } else if (key > this->Tree[i]) {
                i = 2 * i + 2;
            }
        }
        return -1; // не найден
    }

    int AddKey(int key) {
        // добавляем ключ в массив
        int index = FindFreeCell(key);
        if (index == -1) return -1;

        this->Tree[index] = key;
        return index;
        // индекс добавленного/существующего ключа или -1 если не удалось
    }

private:
    static int Depth2Size(int depth) {
        int res = 1;
        for (int i = 0; i < depth + 1; ++i) {
            res *= 2;
        }
        return res - 1;
    }

};