#include <stdio.h>

class BSTNode {
public:
    int NodeKey; // ключ узла
    int NodeValue; // значение в узле
    BSTNode *Parent; // родитель или null для корня
    BSTNode *LeftChild; // левый потомок
    BSTNode *RightChild; // правый потомок

    BSTNode(int key, int val, BSTNode *parent) {
        this->NodeKey = key;
        this->NodeValue = val;
        this->Parent = parent;
        this->LeftChild = nullptr;
        this->RightChild = nullptr;
    }

    int Count() {
        int res = 1;
        if (this->LeftChild != nullptr) {
            res += this->LeftChild->Count();
        }
        if (this->RightChild != nullptr) {
            res += this->RightChild->Count();
        }
        return res;
    }
};

// промежуточный результат поиска
class BSTFind {
    // null если не найден узел, и в дереве только один корень
public:
    BSTNode *Node;

    // true если узел найден
    bool NodeHasKey;

    // true, если родительскому узлу надо добавить новый левым
    bool ToLeft;

    BSTFind() {
        this->Node = nullptr;
        this->NodeHasKey = false;
    }
};

class BST {
public:
    BSTNode *Root; // корень дерева, или null

    BST(BSTNode *node) {
        this->Root = node;
    }

    BSTFind *FindNodeByKey(int key) {
        // ищем в дереве узел и сопутствующую информацию по ключу
        BSTFind *find = new BSTFind();
        find->Node = this->Root;
        while (find->Node != nullptr) {
            if (find->Node->NodeKey > key) {
                find->ToLeft = true;
                if (find->Node->LeftChild == nullptr) {
                    return find;
                }
                find->Node = find->Node->LeftChild;
            } else if (find->Node->NodeKey < key) {
                find->ToLeft = false;
                if (find->Node->RightChild == nullptr) {
                    return find;
                }
                find->Node = find->Node->RightChild;
            } else {
                find->NodeHasKey = true;
                return find;
            }
        }
        return find;
    }

    bool AddKeyValue(int key, int val) {
        // добавляем ключ-значение в дерево
        BSTNode *node = new BSTNode(key, val, nullptr);
        BSTFind *find = FindNodeByKey(key);

        if (find->Node != nullptr) {
            if (find->NodeHasKey == true) {
                return false; // если ключ уже есть
            }

            if (find->ToLeft == true) {
                find->Node->LeftChild = node;
            }
            if (find->ToLeft == false) {
                find->Node->RightChild = node;
            }
            node->Parent = find->Node;
        } else {
            this->Root = node;
        }

        return true;
    }

    BSTNode *FinMinMax(BSTNode *FromNode, bool FindMax) {
        // ищем максимальное/минимальное в поддереве
        if (FromNode == nullptr) {
            return FromNode;
        }
        if (FindMax == true) {
            if (FromNode->RightChild != nullptr) {
                return this->FinMinMax(FromNode->RightChild, FindMax);
            }
        } else {
            if (FromNode->LeftChild != nullptr) {
                return this->FinMinMax(FromNode->LeftChild, FindMax);
            }
        }
        return FromNode;
    }

    bool DeleteNodeByKey(int key) {
        // удаляем узел по ключу
        BSTFind *find = this->FindNodeByKey(key);

        if (find->NodeHasKey) {
            if (find->Node->RightChild != nullptr) {
                BSTNode *min = this->FinMinMax(find->Node->RightChild, false);
                if (min != nullptr) {
                    int min_key = min->NodeKey;
                    int min_value = min->NodeValue;
                    if (this->DeleteNodeByKey(min_key)) {
                        find->Node->NodeKey = min_key;
                        find->Node->NodeValue = min_value;
                    }
                }
            } else if (find->Node->LeftChild != nullptr) {
                find->Node->LeftChild->Parent = find->Node->Parent;
                if (find->Node->Parent == nullptr) {
                    this->Root = find->Node->LeftChild;
                } else {
                    if (find->ToLeft == true) {
                        find->Node->Parent->LeftChild = find->Node->LeftChild;
                    } else {
                        find->Node->Parent->RightChild = find->Node->LeftChild;
                    }
                }
            } else {
                if (find->Node->Parent == nullptr) {
                    this->Root = nullptr;
                } else {
                    if (find->ToLeft == true) {
                        find->Node->Parent->LeftChild = nullptr;
                    } else {
                        find->Node->Parent->RightChild = nullptr;
                    }
                }
            }
        }
        return find->NodeHasKey;
    }

    int Count() {
        if (this->Root == nullptr) {
            return 0;
        }
        return this->Root->Count(); // количество узлов в дереве
    }

    void __print(BSTNode *root, int space = 0) {
        // Base case
        if (root == nullptr)
            return;

        // Increase distance between levels
        space += 10;

        // Process right child first
        __print(root->RightChild, space);

        // Print current node after space
        // count
        printf("\n");
        for (int i = 10; i < space; i++)
            printf(" ");
        printf("%d\n", root->NodeKey);

        __print(root->LeftChild, space);
    }

    void print() {
        this->__print(this->Root, 0);
    }

    BSTNode **WideAllNodes() {
        BSTNode **res = new BSTNode *[this->Count() + 1];
        for (int i = 0; i < this->Count() + 1; i++) res[i] = nullptr;
        int i = 0;
        this->pasteNode(this->Root, res);
        while (i < this->Count()) {
            if (res[i]->LeftChild != nullptr) {
                this->pasteNode(res[i]->LeftChild, res);
            }
            if (res[i]->RightChild != nullptr) {
                this->pasteNode(res[i]->RightChild, res);
            }
            i++;
        }

        return res;
    }

    BSTNode **DeepAllNodes(int order) {
        BSTNode **res = new BSTNode *[this->Count() + 1];
        for (int i = 0; i < this->Count() + 1; i++) res[i] = nullptr;
        switch (order) {
            case 0:
                this->inOrder(this->Root, res);
                break;
            case 1:
                this->postOrder(this->Root, res);
                break;
            case 2:
                this->preOrder(this->Root, res);
                break;
            default:
                this->inOrder(this->Root, res);
                break;
        }

        return res;
    }

private:
    void postOrder(BSTNode *node, BSTNode **list) {
        if (node != nullptr) {
            this->postOrder(node->LeftChild, list);
            this->postOrder(node->RightChild, list);
            this->pasteNode(node, list);
        }
    }

    void preOrder(BSTNode *node, BSTNode **list) {
        if (node != nullptr) {
            this->pasteNode(node, list);
            this->preOrder(node->LeftChild, list);
            this->preOrder(node->RightChild, list);
        }
    }

    void inOrder(BSTNode *node, BSTNode **list) {
        if (node != nullptr) {
            this->inOrder(node->LeftChild, list);
            this->pasteNode(node, list);
            this->inOrder(node->RightChild, list);
        }
    }

    void pasteNode(BSTNode *node, BSTNode **list) {
        if (node != nullptr) {
            int i = 0;
            while (list[i] != nullptr) {
                i++;
            }
            list[i] = node;
        }
    }

};
