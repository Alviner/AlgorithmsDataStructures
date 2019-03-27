//
// Created by blackfox on 27.03.19.
//


#include <stdio.h>

class Node {
public:
    int value;
    Node *next;

    Node(int valueNode) {
        value = valueNode;
        next = nullptr;
    }
};

class LinkedList {
public:
    Node *head;
    Node *tail;

    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void add_in_tail(Node *item) {
        if (head == nullptr) head = item;
        else tail->next = item;
        tail = item;
        tail->next = nullptr;
    }

    Node *find(int val) {
        Node *node = head;
        while (node != nullptr) {
            if (node->value == val) return node;
            node = node->next;
        }
        return nullptr;
    }

    bool remove(int val) {
        Node *prev_node = nullptr;
        Node *node = head;
        while (node != nullptr) {
            if (node->value == val) {
                if (node == tail) {
                    tail = prev_node;
                }
                if (prev_node == nullptr) {
                    head = node->next;
                } else {
                    prev_node->next = node->next;
                }
                return true;

            } else {
                prev_node = node;
            }
            node = node->next;
        }

        return false;
    }

    void remove_all(int val) {
        Node *prev_node = nullptr;
        Node *node = head;
        while (node != nullptr) {
            if (node->value == val) {
                if (node == tail) {
                    tail = prev_node;
                }
                if (prev_node == nullptr) {
                    head = node->next;
                } else {
                    prev_node->next = node->next;
                }

            } else {
                prev_node = node;
            }
            node = node->next;
        }
    }

    void clear() {
        Node *node;
        Node *nextNode;
        node = head;

        while (node != nullptr) {
            nextNode = node->next;
            delete node;
            node = nextNode;
        }
        head = nullptr;
        tail = nullptr;
    }

    int size() {
        int length = 0;
        Node *node = head;

        while (node != nullptr) {
            length += 1;
            node = node->next;
        }
        return length;
    }

    void insert_after(Node *nodeAfter, Node *nodeToInsert) {
        if (nodeAfter == nullptr) {
            if (head == nullptr) {
                add_in_tail(nodeToInsert);
            } else {
                nodeToInsert->next = head;
                head = nodeToInsert;
                return;
            }
        }
        Node *node = head;

        while (node != nullptr) {
            if (node == nodeAfter) {
                if (tail == node) {
                    tail = node;
                }
                nodeToInsert->next = node->next;
                node->next = nodeToInsert;
                return;
            }
            node = node->next;
        }
    }

};