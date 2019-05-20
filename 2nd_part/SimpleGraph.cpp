#include <stdio.h>

class Vertex {
public:
    int Value;

    Vertex() { Value = 0; }

    Vertex(int val) { Value = val; }
};

class SimpleGraph {
public:
    Vertex *vertex;
    int **m_adjacency;
    int max_vertex;

    SimpleGraph(int size) {
        this->max_vertex = size;
        this->m_adjacency = new int *[size];
        for (int i = 0; i < size; i++)
            this->m_adjacency[i] = new int[size];
        this->vertex = new Vertex[size];
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
};