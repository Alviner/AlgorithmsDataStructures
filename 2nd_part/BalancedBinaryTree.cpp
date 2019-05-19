#include <stdio.h>

struct partQuicksort {
    int sep;
    int pivots;
};


void _swap(int *list, int first, int second) {
    int temp = list[first];
    list[first] = list[second];
    list[second] = temp;
}

int _count_item(int *list, int start, int end, int item) {
    int res = 0;
    for (int i = start; i < end; i++) {
        if (list[i] == item) {
            res++;
        }
    }
    return res;
}

partQuicksort _part_quicksort(int *list, int left, int right) {
    partQuicksort res = {0, 0};
    int first_index = left;
    int second_index = right;

    while (first_index != second_index) {
        while (list[first_index] < list[right] && first_index < second_index) {
            first_index++;
        }
        while (list[second_index] >= list[right] && first_index < second_index) {
            second_index--;
        }
        if (first_index != second_index) {
            _swap(list, first_index, second_index);
        }
    }
    _swap(list, right, first_index);

    res.sep = first_index;
    res.pivots = _count_item(list, first_index, right, list[first_index]);
    return res;
}

void quicksort(int *list, int left, int right) {
    if (right - left >= 1) {
        partQuicksort part = _part_quicksort(list, left, right);
        quicksort(list, left, part.sep - 1);
        if (part.sep + part.pivots < right + 1) {
            quicksort(list, part.sep + 1, right);
        }
    }
}

int Depth2Size(int depth) {
    int res = 1;
    for (int i = 0; i < depth + 1; ++i) {
        res *= 2;
    }
    return res - 1;
}

int log2(int n) {
    return (n > 1) ? 1 + log2(n / 2) : 0;
}

void FillBBSTArray(int *bst_list, int *list, int a_len, int start, int end, int index) {
    if (start <= end) {
        int list_index = (start + end) / 2;
        bst_list[index] = list[list_index];
        FillBBSTArray(bst_list, list, a_len / 2, start, list_index - 1, 2 * index + 1);
        FillBBSTArray(bst_list, list, a_len / 2, list_index + 1, end, 2 * index + 2);
    }
}

// a -- массив ключей
// a_len -- кол-во элементов в массиве ключей
int *GenerateBBSTArray(int a[], int a_len) {
    int res_length = Depth2Size(log2(a_len));
    int* res = new int[res_length];
    for (int i = 0; i < res_length; i++) res[i] = -1;

    quicksort(a, 0, a_len - 1);

    FillBBSTArray(res, a, a_len, 0, a_len - 1, 0);
    return res;
}
