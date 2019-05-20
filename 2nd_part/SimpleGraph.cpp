#include <stdio.h>

class Vertex {
public:
    int Value;
    bool Hit;

    Vertex() {
        this->Value = 0;
        this->set_unvisited();
    }

    Vertex(int val) {
        this->Value = val;
        this->set_unvisited();
    }

    void set_visited() {
        this->Hit = true;
    }

    void set_unvisited() {
        this->Hit = false;
    }

    bool is_visited() {
        return this->Hit == true;
    }
};

struct Node {
    Vertex *val;
    Node *prev;

    Node(Vertex *value) {
        this->prev = nullptr;
        this->val = value;
    }
};


class List {
public:
    Node *head;
    Node *tail;

    List() {
        this->head = nullptr;
        this->tail = nullptr;
    }
};


class Stack {
public:
    List *list;
    int stacksize;


    Stack() {
        this->list = new List();
        this->stacksize = 0;
    }

    int size() {
        return this->stacksize;
    }

    Vertex *pop() {
        if (this->list->head == nullptr) return nullptr;
        Vertex *value = this->list->head->val;
        this->list->head = this->list->head->prev;
        --this->stacksize;
        return value;
    }

    void push(Vertex *val) {
        Node *node = new Node(val);
        if (this->list->head == nullptr) {
            this->list->head = node;
            node->prev = nullptr;
        } else {
            node->prev = list->head;
            this->list->head = node;
        }
        ++this->stacksize;
    }

    Vertex *peek() {
        if (this->list->head != nullptr) {
            return this->list->head->val;
        } else
            return nullptr;
    }
};

class SimpleGraph {
public:
    Vertex *vertex;
    int **m_adjacency;
    int max_vertex;
    Stack *stack;

    SimpleGraph(int size) {
        this->max_vertex = size;
        this->m_adjacency = new int *[size];
        for (int i = 0; i < size; i++)
            this->m_adjacency[i] = new int[size];
        this->vertex = new Vertex[size];

        this->stack = new Stack();
    }

    void AddVertex(int value) {
        // ваш код добавления новой вершины 
        // с значением value 
        // в свободную позицию массива vertex
        int i = 0;

        while (i < this->max_vertex && this->vertex[i].Value != 0) {
            i++;
        }
        if (i >= max_vertex) {
            return;
        }
        this->vertex[i] = Vertex(value);

        for (int j = 0; j < max_vertex; ++j) {
            this->m_adjacency[i][j] = 0;
            this->m_adjacency[j][i] = 0;
        }
    }

    // здесь и далее, параметры v -- индекс вершины
    // в списке  vertex
    void RemoveVertex(int v) {
        // ваш код удаления вершины со всеми её рёбрами
        if (v < 0 || v >= max_vertex) {
            return;
        }

        for (int j = 0; j < max_vertex; ++j) {
            this->m_adjacency[v][j] = 0;
            this->m_adjacency[j][v] = 0;
        }

        this->vertex[v] = Vertex();
    }

    bool IsEdge(int v1, int v2) {
        // true если есть ребро между вершинами v1 и v2
        if (v1 < 0 || v2 < 0 || v1 >= max_vertex || v2 >= max_vertex)
            return false;
        return this->m_adjacency[v1][v2] == 1 && this->m_adjacency[v2][v1] == 1;
    }

    void AddEdge(int v1, int v2) {
        // добавление ребра между вершинами v1 и v2
        if (v1 < 0 || v2 < 0 || v1 >= max_vertex || v2 >= max_vertex)
            return;
        this->m_adjacency[v1][v2] = 1;
        this->m_adjacency[v2][v1] = 1;
    }

    void RemoveEdge(int v1, int v2) {
        // удаление ребра между вершинами v1 и v2
        if (v1 < 0 || v2 < 0 || v1 >= max_vertex || v2 >= max_vertex)
            return;
        this->m_adjacency[v1][v2] = 0;
        this->m_adjacency[v2][v1] = 0;
    }

    Vertex **GetAdjacent(int vertex_index) {
        Vertex **res = new Vertex *[this->max_vertex];
        for (int i = 0; i < this->max_vertex; i++) res[i] = nullptr;
        int k = 0;
        for (int i = 0; i < this->max_vertex; i++) {
            if (&this->vertex[i] != vertex && this->IsEdge(i, vertex_index)) {
                res[k++] = &this->vertex[i];
            }
        }
        return res;
    }

    Vertex **DepthFirstSearch(int VFrom, int VTo) {
        // Узлы задаются позициями в списке vertex.
        // Возвращается список узлов -- путь из VFrom в VTo.
        // Список завершается NULL-ом

        Vertex **res;

        while (this->stack->size() > 0) {
            this->stack->pop();
        }

        for (int i = 0; i < this->max_vertex; i++) {
            this->vertex[i].set_unvisited();
        }

        Vertex *current = &this->vertex[VFrom];

        while (current != nullptr) {
            if (current->is_visited() == false) {
                this->stack->push(current);
                current->set_visited();
            }

            int curr_index = 0;
            while (&this->vertex[curr_index] != current) {
                curr_index++;
            }

            Vertex **adjacent = this->GetAdjacent(curr_index);
            int ad_lenght = 0;
            while (adjacent[ad_lenght] != nullptr) {
                ad_lenght++;
            }
            if (ad_lenght == 0) {
                res = new Vertex *[1];
                res[0] = nullptr;
                return res;
            }
            bool secondInAdj = false;
            for (int i = 0; i < ad_lenght; i++) {
                if (adjacent[i] == &this->vertex[VTo]) {
                    this->stack->push(&this->vertex[VTo]);
                    current = nullptr;
                    secondInAdj = true;
                }
            }

            if (secondInAdj == false) {
                for (int i = 0; i < ad_lenght; ++i) {
                    if (adjacent[i]->is_visited() == false) {
                        current = adjacent[i];
                        break;
                    }

                    if (i == ad_lenght - 1) {
                        current = this->stack->pop();
                        if (this->stack->size() == 0) {
                            current = nullptr;
                        }
                        break;
                    }
                }
            }
        }

        res = new Vertex *[this->stack->size() + 1];
        for (int j = 0; j < this->stack->size() + 1; ++j) {
            res[j] = nullptr;
        }
        int j = this->stack->size() - 1;
        while(this->stack->size() > 0) {
            res[j--] = this->stack->pop();
        }

        return res;
    }
};
