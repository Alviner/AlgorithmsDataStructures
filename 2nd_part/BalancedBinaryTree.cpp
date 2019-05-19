#include <stdio.h>

#define MAX_LEN 100

class BSTNode {
public:
    int NodeKey; // ключ узла
    BSTNode *Parent; // родитель или NULL для корня
    BSTNode *LeftChild; // левый потомок
    BSTNode *RightChild; // правый потомок
    int Level; // глубина узла

    BSTNode(int key, BSTNode *parent) {
        this->NodeKey = key;
        this->setParent(parent);
        this->LeftChild = nullptr;
        this->RightChild = nullptr;
    }

    void setParent(BSTNode *parent) {
        this->Parent = parent;
        if (parent != nullptr) {
            this->Level = parent->Level + 1;
        } else {
            this->Level = 1;
        }
    }
};


class BalancedBST {
public:
    BSTNode *Root;

    int array_length;

    int BSTArray[MAX_LEN]; // временный массив для ключей дерева

    BalancedBST() {
        this->Root = nullptr;
        this->array_length = 0;
    }

    void CreateFromArray(int *a, int a_len) {
        // создаём массив дерева BSTArray из заданного "a" длиной a_len
        this->array_length = a_len;
        for (int i = 0; i < MAX_LEN; i++) this->BSTArray[i] = -1;

        BalancedBST::quicksort(a, 0, this->array_length - 1);

        this->FillBBSTArray(this->BSTArray, a, this->array_length, 0, this->array_length - 1, 0);
    }

    void GenerateTree() {
        // создаём дерево с нуля из массива BSTArray

        this->Root = this->FillBBST(nullptr, 0);

    }

    bool IsBalanced(BSTNode *root_node) {
        printf("%d\n", this->MaxLevel(this->Root));

        int left_max = 0;
        int right_max = 0;
        if (root_node != nullptr) {
            left_max = this->MaxLevel(root_node->LeftChild);
            right_max = this->MaxLevel(root_node->RightChild);
        }

        return (left_max - right_max) <= 1 && (left_max - right_max) >= - 1; // сбалансировано ли дерево с корнем root_node
    }

    void __print(BSTNode *root, int space = 0) {
        // Base case
        if (root == nullptr)
            return;

        // Increase distance between levels
        space += 10;

        // Process right child first
        this->__print(root->RightChild, space);

        // Print current node after space
        // count
        printf("\n");
        for (int i = 10; i < space; i++)
            printf(" ");
        printf("%d\n", root->NodeKey);

        this->__print(root->LeftChild, space);
    }

    void print() {
        this->__print(this->Root, 0);
    }

private:
    struct partQuicksort {
        int sep;
        int pivots;
    };


    static void swap(int *list, int first, int second) {
        int temp = list[first];
        list[first] = list[second];
        list[second] = temp;
    }

    static int count_item(int *list, int start, int end, int item) {
        int res = 0;
        for (int i = start; i < end; i++) {
            if (list[i] == item) {
                res++;
            }
        }
        return res;
    }

    static partQuicksort _part_quicksort(int *list, int left, int right) {
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
                BalancedBST::swap(list, first_index, second_index);
            }
        }
        BalancedBST::swap(list, right, first_index);

        res.sep = first_index;
        res.pivots = BalancedBST::count_item(list, first_index, right, list[first_index]);
        return res;
    }

    static void quicksort(int *list, int left, int right) {
        if (right - left >= 1) {
            BalancedBST::partQuicksort part = BalancedBST::_part_quicksort(list, left, right);
            BalancedBST::quicksort(list, left, part.sep - 1);
            if (part.sep + part.pivots < right + 1) {
                BalancedBST::quicksort(list, part.sep + 1, right);
            }
        }
    }

    static int Depth2Size(int depth) {
        int res = 1;
        for (int i = 0; i < depth + 1; ++i) {
            res *= 2;
        }
        return res - 1;
    }

    static int log2(int n) {
        return (n > 1) ? 1 + log2(n / 2) : 0;
    }

    void FillBBSTArray(int *bst_list, int *list, int a_len, int start, int end, int index) {
        if (start <= end) {
            int list_index = (start + end) / 2;
            bst_list[index] = list[list_index];
            this->FillBBSTArray(bst_list, list, a_len / 2, start, list_index - 1, 2 * index + 1);
            this->FillBBSTArray(bst_list, list, a_len / 2, list_index + 1, end, 2 * index + 2);
        }
    }

    BSTNode *FillBBST(BSTNode *node, int index) {
        if (index < Depth2Size(log2(this->array_length))) {
            if (this->BSTArray[index] == -1) return nullptr;

            BSTNode *new_node = new BSTNode(this->BSTArray[index], node);

            new_node->LeftChild = this->FillBBST(new_node, 2 * index + 1);
            new_node->RightChild = this->FillBBST(new_node, 2 * index + 2);

            return new_node;
        }
        return nullptr;
    }

    int MaxLevel(BSTNode* node) {
        if (node != nullptr) {
            int left_level = node->Level;
            int right_level = node->Level;
            if (node->LeftChild != nullptr) left_level = this->MaxLevel(node->LeftChild);
            if (node->RightChild != nullptr) right_level = this->MaxLevel(node->RightChild);
            return left_level > right_level ? left_level : right_level;
        }
        return 0;
    }
};
