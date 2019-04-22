#include <stdio.h>

const int MAX_CHILD = 10; // максимальное кол-во дочерних узлов у родителя
// в тестах гарантируется, что это число не будет превышено

class SimpleTreeNode {
public:
    int NodeValue; // значение в узле
    int level;
    SimpleTreeNode *Parent; // родитель или NULL для корня
    SimpleTreeNode *Children[MAX_CHILD]; // список дочерних узлов

    SimpleTreeNode(int val, SimpleTreeNode *parent) {
        this->NodeValue = val;
        this->Parent = parent;
        this->level = 1;
        for (int i = 0; i < MAX_CHILD; i++) this->Children[i] = nullptr;
    }

    void AddChild(SimpleTreeNode *NewChild) {
        for (int i = 0; i < MAX_CHILD; i++) {
            if (this->Children[i] == nullptr) {
                this->Children[i] = NewChild;
                this->Children[i]->Parent = this;
                return;
            }
        }
    }

    int reload() {
        int res = 0;
        if (this->Parent == nullptr) {
            this->level = 1;
        } else {
            this->level = this->Parent->level + 1;
        }

        res = this->level;

        for (int i = 0; i < MAX_CHILD; i++) {
            if (this->Children[i] != nullptr) {
                int res_i = this->Children[i]->reload();
                if (res_i > res) {
                    res = res_i;
                }
            }
        }
        return res;
    }

    void GetAllNodes(SimpleTreeNode **list, int index = 0) {
        for (int i = 0; i < MAX_CHILD; i++) {
            if (list[index + i] == nullptr) {
                index += i;
                list[index] = this;
                break;
            }
        }

        for (int i = 0; i < MAX_CHILD; i++) {
            if (this->Children[i] != nullptr) {
                this->Children[i]->GetAllNodes(list, index);
            }
        }
    }

    int LeavesNumber() {
        int res = 0;
        if (this->Children[0] == nullptr) res++;

        for (int i = 0; i < MAX_CHILD; ++i)
            if (this->Children[i] != nullptr) {
                res += this->Children[i]->LeavesNumber();
            }
        return res;
    }

    int Count() {
        int res = 1;
        for (int i = 0; i < MAX_CHILD; ++i)
            if (this->Children[i] != nullptr) {
                res += this->Children[i]->Count();
            }
        return res;

    }


};

class SimpleTree {
public:
    SimpleTreeNode *Root; // корень, может быть NULL
    int levels;
    int count;

    SimpleTree(SimpleTreeNode *root) {
        this->Root = root;
        this->levels = 0;
        this->count = 0;

        if (this->Root != nullptr) {
            this->levels = 1;
            this->count = 1;
        }

    }

    void reload(SimpleTreeNode *Node = nullptr) {
        if (Node == nullptr) {
            this->levels = this->Root->reload();
        } else {
            this->levels = Node->reload();
        }
    }

    void AddChild(SimpleTreeNode *ParentNode, SimpleTreeNode *NewChild) {
        NewChild->Parent = nullptr;
        if (ParentNode != nullptr) {
            ParentNode->AddChild(NewChild);
        } else {
            if (this->Root != nullptr) {
                SimpleTreeNode *node = this->Root;
                this->DeleteNode(node);
                this->Root = NewChild;
                NewChild->AddChild(node);
            } else {
                this->Root = NewChild;
            }
        }

        this->reload();
        this->count += NewChild->Count();
    }

    void DeleteNode(SimpleTreeNode *NodeToDelete) {
        if (NodeToDelete->Parent == nullptr) {
            this->Root = nullptr;
            this->levels = 0;
            this->count = 0;
        } else {
            SimpleTreeNode *node = NodeToDelete->Parent;
            for (int i = 0; i < MAX_CHILD; i++) {
                if (node->Children[i] == NodeToDelete) {
                    for (int j = i; j < MAX_CHILD - 1; j++) {
                        node->Children[j] = node->Children[j + 1];
                    }
                    node->Children[MAX_CHILD - 1] = nullptr;
                    this->reload();
                    this->count -= NodeToDelete->Count();
                    break;
                }
            }
        }
    }

    SimpleTreeNode **GetAllNodes() {
        SimpleTreeNode **list = new SimpleTreeNode *[this->Count() + 1];

        for (int i = 0; i < this->Count() + 1; i++) {
            list[i] = nullptr;
        }

        if (this->Root != nullptr) {
            this->Root->GetAllNodes(list);
        }

        return list;
    }

    SimpleTreeNode **FindNodesByValue(int val) {
        SimpleTreeNode **list = this->GetAllNodes();
        SimpleTreeNode **res_list = new SimpleTreeNode *[this->Count()] + 1;
        for (int i = 0; i < this->Count() + 1; i++) {
            res_list[i] = nullptr;
        }
        int k = 0;
        for (int i = 0; i < this->Count(); i++) {
            if (list[i] != nullptr) {
                if (list[i]->NodeValue == val) {
                    res_list[k++] = list[i];
                }
            }
        }
        return res_list;
    }

    void MoveNode(SimpleTreeNode *OriginalNode, SimpleTreeNode *NewParent) {
        // ваш код перемещения узла вместе с его поддеревом --
        // в качестве дочернего для узла NewParent
        SimpleTreeNode *Node = OriginalNode;

        this->DeleteNode(Node);
        this->AddChild(NewParent, Node);
        this->reload();

    }

    int Count() {
        return this->count;
    }

    int LeafCount() {
        // количество листьев в дереве
        if (this->Root == nullptr) {
            return 0;
        }
        return this->Root->LeavesNumber();
    }
};