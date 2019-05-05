#include <stdio.h>

class BSTNode {
public:
    int NodeKey; // ключ узла
    int NodeValue; // значение в узле
    BSTNode *Parent; // родитель или null для корня
    BSTNode *LeftChild; // левый потомок
    BSTNode *RightChild; // правый потомок

    BSTNode(int key, int val, BSTNode *parent) {
        NodeKey = key;
        NodeValue = val;
        Parent = parent;
        LeftChild = nullptr;
        RightChild = nullptr;
    }

    int Count() {
        int res = 1;
        if (this->LeftChild != nullptr) {
            res += this->LeftChild->Count();
        }
        if (this->RightChild != nullptr) {
            res += this->RightChild->Count();
        }
        return res; // количество узлов в поддереве
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

    BSTFind() { Node = nullptr; }
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
            if (find->Node->NodeKey == key) {
                find->NodeHasKey = true;
                return find;
            } else if (find->Node->NodeKey > key) {
                find->ToLeft = true;
                if (find->Node->LeftChild == nullptr) {
                    return find;
                }
                find->Node = find->Node->LeftChild;
            } else {
                find->ToLeft = false;
                if (find->Node->RightChild == nullptr) {
                    return find;
                }
                find->Node = find->Node->RightChild;
            }
        }
        return find;
    }

    bool AddKeyValue(int key, int val) {
        // добавляем ключ-значение в дерево
        BSTFind *find = this->FindNodeByKey(key);
        BSTNode *node = new BSTNode(key, val, nullptr);
        if (find->NodeHasKey) {
            return false; // если ключ уже есть
        }
        if (find->Node == nullptr) {
            this->Root = node;
        } else {
            if (find->ToLeft) {
                find->Node->LeftChild = node;
            } else if (!find->ToLeft) {
                find->Node->RightChild = node;
            }
        }
        node->Parent = find->Node;
        return true;
    }

    BSTNode *FinMinMax(BSTNode *FromNode, bool FindMax) {
        // ищем максимальное/минимальное в поддереве
        if (FromNode == nullptr) {
            return FromNode;
        }
        if (FindMax) {
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
        if (!find->NodeHasKey) {
            return false; // если узел не найден
        }

        if (find->Node->RightChild != nullptr) {
            find->Node->RightChild->Parent = find->Node->Parent;

            BSTNode *min = this->FinMinMax(find->Node->RightChild, false);
            if (min != nullptr) {
                if (find->Node->LeftChild != nullptr) {
                    find->Node->LeftChild->Parent = min;
                }
                min->LeftChild = find->Node->LeftChild;
            }

            if (find->Node->Parent == nullptr) {
                this->Root = find->Node->RightChild;
            } else {
                if (find->ToLeft) {
                    find->Node->Parent->LeftChild = find->Node->RightChild;
                } else {
                    find->Node->Parent->RightChild = find->Node->RightChild;
                }
            }
        } else if (find->Node->LeftChild != nullptr) {
            find->Node->LeftChild->Parent = find->Node->Parent;
            if (find->Node->Parent == nullptr) {
                this->Root = find->Node->LeftChild;
            } else {
                if (find->ToLeft) {
                    find->Node->Parent->LeftChild = find->Node->LeftChild;
                } else {
                    find->Node->Parent->RightChild = find->Node->LeftChild;
                }
            }
        } else {
            if (find->Node->Parent == nullptr) {
                this->Root = nullptr;
            } else {
                if (find->ToLeft) {
                    find->Node->Parent->LeftChild = nullptr;
                } else {
                    find->Node->Parent->RightChild = nullptr;
                }
            }
        }

        return true;
    }

    int Count() { // количество узлов в дереве
        if (this->Root != nullptr) {
            return this->Root->Count();
        }
        return 0;
    }

};