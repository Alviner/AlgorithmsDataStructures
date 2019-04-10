#include <stdio.h>
#include <typeinfo.h>

template<class T>
class Node {
public:
    T value;
    Node *next;
    Node *prev;

    Node(T valueNode) {
        value = valueNode;
        next = nullptr;
        prev = nullptr;
    }
};

template<class T>
class OrderedList {

private:
    bool _ascending;

public:
    Node<T> *head;
    Node<T> *tail;

    OrderedList(bool asc) {
        this->head = nullptr;
        this->tail = nullptr;
        this->_ascending = asc;
    }

    int compare(T v1, T v2) {
        if (v1 < v2) return -1;
        if (v1 == v2) return 0;
        return 1;

    }

    void add(T value) {
        Node<T> *node = new Node<T>(value);

        if (this->head == nullptr) {
            node->prev = nullptr;
            node->next = nullptr;
            this->head = node;
            this->tail = node;
            return;
        }

        Node<T> *curr = this->head;
        while (curr != nullptr) {
            int compare_result = compare(node->value, curr->value);

            if (!(!this->_ascending || !(compare_result == 0 || compare_result == -1)) ||
                !(this->_ascending || !(compare_result == 0 || compare_result == 1))) {

                if (curr == this->head) {
                    node->next = curr;
                    curr->prev = node;
                    this->head = node;
                    return;
                } else {
                    node->prev = curr->prev;
                    node->next = curr;
                    curr->prev->next = node;
                    curr->prev = node;
                    return;
                }

            }
            curr = curr->next;
        }

        node->prev = this->tail;
        this->tail->next = node;
        this->tail = node;
        this->tail->next = nullptr;

    }

    Node<T> *find(T val) {
        Node<T> *node = this->head;

        while (node != nullptr) {
            if (this->_ascending) {
                if (compare(node->value, val) == 1)
                    return nullptr;

                if (node->value == val)
                    return node;

            } else if (!this->_ascending) {
                if (compare(node->value, val) == -1)
                    return nullptr;

                if (node->value == val)
                    return node;
            }
            node = node->next;
        }

        return nullptr;
    }

    void del_from_head() {
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

    void del_from_tail() {
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

    void del(T val) {
        Node<T> *node = this->find(val);
        if (node != nullptr) {
            if (node == this->head) {
                this->del_from_head();
            } else if (node == this->tail) {
                this->del_from_tail();
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
        }
    }

    void clear(bool asc) {
        this->_ascending = asc;
        Node<T> *node = this->head;
        while (node != nullptr) {
            this->head = node->next;
            delete node;
            node = this->head;
        }
        this->head = nullptr;
        this->tail = nullptr;
    }

    int size() {
        Node<T> *node = this->head;
        int count = 0;

        while (node != nullptr) {
            count++;
            node = node->next;
        }
        return count;
    }

    T *get_all() {
        Node<T> *node = this->head;
        T *list = new T[this->size()];

        for (int i = 0; i < this->size(); i++) {
            list[i] = node->value;
            node = node->next;
        }
        return list;

    }

};