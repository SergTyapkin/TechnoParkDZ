// Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между
// какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами.
// Требуемая сложность O(V+E). Ввод: v: кол-во вершин (макс. 50000),
//n: кол-во ребер(макс. 200000),
//n пар реберных вершин,
//пара вершин (u, w) для запроса.

#include <queue>
#include <vector>
using std::vector;
using std::pair;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class ListGraph {
public:
    ListGraph(int vertexCount);

    virtual void AddEdge(int from, int to);

    virtual int VerticesCount() const;
    virtual vector<int> GetNextVertices(int vertex) const;
private:
    vector<vector<int>> adjacencyLists;
};

ListGraph::ListGraph(int vertexCount) {
    adjacencyLists.resize(vertexCount);
}

void ListGraph::AddEdge(int from, int to) {
    if ((from < 0 || from >= adjacencyLists.size()) ||
        (to < 0 || to >= adjacencyLists.size()))
        return;

    adjacencyLists[from].push_back(to);
    adjacencyLists[to].push_back(from);
}

int ListGraph::VerticesCount() const {
    return adjacencyLists.size();
}

vector<int> ListGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjacencyLists.size())
        throw std::exception();

    return adjacencyLists[vertex];
}

int BFS(const ListGraph& graph, int vertex, int finish, void (*visit)(int)) {
    vector<pair<int, int>> ways(graph.VerticesCount(), pair<int, int>(0, graph.VerticesCount()));
    std::queue<int> bfsQueue;
    bfsQueue.push(vertex);
    ways[vertex] = pair<int, int>(1, 0);

    while (bfsQueue.size() > 0) {
        int current = bfsQueue.front();
        if (bfsQueue.front() == finish)
            return ways[finish].first;
        bfsQueue.pop();
        visit(current);

        for (auto i: graph.GetNextVertices(current)) {
            if (ways[i].second == ways[current].second + 1) {
                ways[i].first += ways[current].first;
            } else if (ways[i].second > ways[current].second + 1) {
                ways[i].second = ways[current].second + 1;
                ways[i].first = ways[current].first;
                bfsQueue.push(i);
            }
        }
    }
    return 0;
}

int main() {
    int v;
    int n;
    cin >> v >> n;
    ListGraph graph(v);

    int from, to;
    for (int i = 0; i < n; i++) {
        cin >> from >> to;
        graph.AddEdge(from, to);
    }
    cin >> from >> to;
    int answer = BFS(graph, from, to, [](int vert){});
    cout << answer << endl;

    return 0;
}
