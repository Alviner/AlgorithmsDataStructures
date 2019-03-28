//
// Created by blackfox on 28.03.19.
//


class Node {
public:
    int value;
    Node *next;
    Node *prev;

    Node(int valueNode) {
        value = valueNode;
        next = nullptr;
        prev = nullptr;
    }
};

class LinkedList2 {
public:
    Node *head;
    Node *tail;

    LinkedList2() {
        head = nullptr;
        tail = nullptr;
    }

    void add_in_tail(Node *item) {
        item->next = nullptr;
        item->prev = nullptr;
        if (head == nullptr) {
            head = item;
        } else {
            tail->next = item;
            item->prev = tail;
        }
        tail = item;
    }

    void add_in_head(Node *item) {
        item->prev = nullptr;
        item->next = nullptr;
        if (tail == nullptr) {
            tail = item;
        } else {
            head->prev = item;
            item->next = head;
        }
        head = item;

    }

    Node *find(int val) {
        Node *node = head;
        auto it = 0;
        while (node != nullptr) {
            if (node->value == val) {
                return node;
            }
            node = node->next;
            it++;
            if (it >= 1000) break;
        }
        return nullptr;
    }

    void remove_head() {
        if (this->head->next == nullptr) {
            this->head = nullptr;
            this->tail = nullptr;
        } else {
            if (this->head->next == this->tail) {
                this->head = this->tail;
                this->head->prev = nullptr;
            } else {
                this->head = this->head->next;
                this->head->prev = nullptr;
            }
        }
    }

    void remove_tail() {
        if (this->tail->prev == nullptr) {
            this->head = nullptr;
            this->tail = nullptr;
        } else {
            if (this->tail->prev == this->head) {
                this->tail = this->head;
                this->tail->next = nullptr;
            } else {
                this->tail = this->tail->prev;
                this->tail->next = nullptr;
            }
        }
    }

    bool remove(int val) {
        Node *node = head;
        auto it = 0;
        while (node != nullptr) {
            if (node->value == val) {
                if (node == this->head) {
                    remove_head();
                } else if (node == this->tail) {
                    remove_tail();
                } else {
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                }
                return true;
            }
            node = node->next;
            it++;
            if (it >= 1000) break;
        }
        return false;
    }

    void remove_all(int val) {
        Node *node = head;
        auto it = 0;
        while (node != nullptr) {
            if (node->value == val) {
                if (node == this->head) {
                    remove_head();
                } else if (node == this->tail) {
                    remove_tail();
                } else {
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                }
            }
            node = node->next;
            it++;
            if (it >= 1000) break;
        }
    }

    void clear() {
        Node *node;
        Node *nextNode;
        node = head;
        auto it = 0;
        while (node != nullptr) {
            nextNode = node->next;
            delete node;
            node = nextNode;
            it++;
            if (it >= 1000) break;
        }
        head = nullptr;
        tail = nullptr;
    }

    int size() {
        int length = 0;
        Node *node = head;
        auto it= 0;
        while (node != nullptr) {
            length++;
            node = node->next;
            it++;
            if (it >= 1000) break;
        }
        return length;
    }

    void insert_after(Node *nodeAfter, Node *nodeToInsert) {
        nodeToInsert->next = nullptr;
        nodeToInsert->prev = nullptr;
        if (nodeAfter == nullptr) {
            add_in_head(nodeToInsert);
            return;
        }
        Node *node = head;

        auto it = 0;

        while (node != nullptr) {
            if (node == nodeAfter) {
                if (node == tail) {
                    add_in_tail(nodeToInsert);
                    return;
                };
                nodeToInsert->next = node->next;
                nodeToInsert->prev = node;
                node->next->prev = nodeToInsert;
                node->next = nodeToInsert;
                return;
            }
            node = node->next;
            it++;
            if (it >= 1000) break;
        }
    }

};
