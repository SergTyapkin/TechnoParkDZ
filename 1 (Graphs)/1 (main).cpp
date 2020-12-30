#include "AbstractGraph.h"

#include <vector>
using std::vector;
#include <queue>
#include <iostream>
using std::cout;
using std::endl;

void BFS(const AbstractGraph& graph, int vertex, void (*visit)(int)) {
    vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> bfsQueue;
    bfsQueue.push(vertex);
    visited[vertex] = true;

    while (bfsQueue.size() > 0) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        visit(current);

        for (auto i: graph.GetNextVertices(current)) {
            if (!visited[i]) {
                bfsQueue.push(i);
                visited[i] = true;
            }
        }
    }
}

void private_DFS(const AbstractGraph& graph, int vertex, void (*visit)(int), vector<bool> &visited) {
    visit(vertex);
    visited[vertex] = true;

    for (auto i: graph.GetNextVertices(vertex))
        if (!visited[i])
            private_DFS(graph, i, visit, visited);
}

void DFS(const AbstractGraph& graph, int vertex, void (*visit)(int)) {
    vector<bool> visited(graph.VerticesCount(), false);
    private_DFS(graph, vertex, visit, visited);
}

#include "1 (MatrixGraph).cpp"
#include "1 (ListGraph).cpp"
#include "1 (ArcGraph).cpp"
#include "1 (SetGraph).cpp"

int main() {
/** Bidirectional graph:
    0--2--6
    |\    |
    | 7-1 |
    |  \ /
    5---4
     \ /
      3
**/
    ListGraph tmp(8);

    // Тест заключается в том, что можно поудалять любые связи и увидеть,
    // что BFS и DFS обходы выводят одинаковые списки доступности для каждой вершины во всех графах.
    // Изначально граф полностью двунаправленный.
    tmp.AddEdge(0, 2);
    tmp.AddEdge(0, 7);
    tmp.AddEdge(0, 5);
    tmp.AddEdge(1, 7);
    tmp.AddEdge(2, 0);
    tmp.AddEdge(2, 6);
    tmp.AddEdge(3, 4);
    tmp.AddEdge(3, 5);
    tmp.AddEdge(4, 3);
    tmp.AddEdge(4, 5);
    tmp.AddEdge(4, 6);
    tmp.AddEdge(4, 7);
    tmp.AddEdge(5, 0);
    tmp.AddEdge(5, 3);
    tmp.AddEdge(5, 4);
    tmp.AddEdge(6, 2);
    tmp.AddEdge(6, 4);
    tmp.AddEdge(7, 0);
    tmp.AddEdge(7, 1);
    tmp.AddEdge(7, 4);

    SetGraph    S = tmp;
    ArcGraph    A = S;
    MatrixGraph M = S;
    ListGraph   L = M;

    for (int i = 0; i < 8; ++i) {
        std::cout << "BFS for " << i << ": " << std::endl;
        BFS(S, i, [](int vert){std::cout << vert << ", ";});
        std::cout << std::endl;
        BFS(A, i, [](int vert){std::cout << vert << ", ";});
        std::cout << std::endl;
        BFS(M, i, [](int vert){std::cout << vert << ", ";});
        std::cout << std::endl;
        BFS(L, i, [](int vert){std::cout << vert << ", ";});
        std::cout << std::endl;

        std::cout << "DFS for " << i << ": " << std::endl;
        DFS(S, i, [](int vert){std::cout << vert << ", ";});
        std::cout << std::endl;
        DFS(A, i, [](int vert){std::cout << vert << ", ";});
        std::cout << std::endl;
        DFS(M, i, [](int vert){std::cout << vert << ", ";});
        std::cout << std::endl;
        DFS(L, i, [](int vert){std::cout << vert << ", ";});
        std::cout << std::endl << std::endl;
    }
    std::cout << "All" << std::endl;

    return 0;
}
