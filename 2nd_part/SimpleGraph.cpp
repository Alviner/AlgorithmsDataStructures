#include <stdio.h>

class Vertex {
public:
    int Value;
    bool Hit;

    Vertex() {
        this->Value = -1;
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
    int val;
    Node *prev;

    Node(int value) {
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

    int pop() {
        if (this->list->head == nullptr) return -1;
        int value = this->list->head->val;
        this->list->head = this->list->head->prev;
        --this->stacksize;
        return value;
    }

    void push(int val) {
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

    int peek() {
        if (this->list->head != nullptr) {
            return this->list->head->val;
        } else
            return -1;
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

        while (i < this->max_vertex && this->vertex[i].Value >= 0) {
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
        return this->m_adjacency[v1][v2] == 1;
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

    int *GetAdjacent(int vertex_index) {
        int *res = new int[this->max_vertex + 1];
        for (int i = 0; i <= this->max_vertex; i++) res[i] = -1;
        int k = 0;
        for (int i = 0; i < this->max_vertex; i++) {
            if (i != vertex_index && this->IsEdge(i, vertex_index)) {
                res[k++] = i;
            }
        }
        return res;
    }

    bool HasIndex(int *adj, int index) {
        int i = 0;
        while (adj[i] != -1) {
            if (adj[i] == index) {
                return true;
            }
            i++;
        }
        return false;
    }

    int GetUnvisitedIndex(int *adj) {
        int i = 0;
        while (adj[i] != -1) {
            if (this->GetVertex(adj[i])->is_visited() == false) {
                return adj[i];
            }
            i++;
        }
        return -1;
    }

    Vertex *GetVertex(int index) {
        if (index < 0 or index >= this->max_vertex or this->vertex[index].Value < 0) {
            return nullptr;
        }
        return &this->vertex[index];
    }

    int GetVertexIndex(Vertex *vertex) {
        int i = 0;
        while (i < this->max_vertex) {
            if (&this->vertex[i] == vertex) {
                return i;
            }
            i++;
        }
    }

    Vertex **DepthFirstSearch(int VFrom, int VTo) {
        // Узлы задаются позициями в списке vertex.
        // Возвращается список узлов -- путь из VFrom в VTo.
        // Список завершается NULL-ом

        Vertex **res;

        int *adjacent;
        int ad_length, k;

        while (this->stack->size() > 0) {
            this->stack->pop();
        }

        for (int i = 0; i < this->max_vertex; i++) {
            this->vertex[i].set_unvisited();
        }

        int current_index = VFrom;
        this->GetVertex(current_index)->set_visited();
        this->stack->push(current_index);

        while (this->stack->size() > 0) {
            current_index = this->stack->peek();

            adjacent = this->GetAdjacent(current_index);

            if (this->HasIndex(adjacent, VTo)) {
                this->stack->push(VTo);
                break;
            }

            int unvisited = this->GetUnvisitedIndex(adjacent);
            if (unvisited != -1) {
                this->GetVertex(unvisited)->set_visited();
                this->stack->push(unvisited);
            } else {
                this->stack->pop();
            }
        }

        res = new Vertex *[this->stack->size() + 1];
        for (int j = 0; j < this->stack->size() + 1; ++j) {
            res[j] = nullptr;
        }
        int j = this->stack->size() - 1;
        while (this->stack->size() > 0) {
            res[j--] = this->GetVertex(this->stack->pop());
        }

        return res;
    }
};
