//Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.
//Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
//N ≤ 10000, M ≤ 250000.
//Длина каждой дороги ≤ 10000.

#include <set>
#include <queue>
#include <vector>
using std::vector;
using std::pair;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define INFINITY 2147483647

class ListGraph {
public:
    ListGraph(int vertexCount);

    virtual void AddEdge(int from, int to, int w);

    virtual int VerticesCount() const;
    virtual vector<pair<int, int>> GetNextVertices(int vertex) const;
private:
    vector<vector<pair<int, int>>> adjacencyLists;
};

ListGraph::ListGraph(int vertexCount) {
    adjacencyLists.resize(vertexCount);
}

void ListGraph::AddEdge(int from, int to, int w) {
    if ((from < 0 || from >= adjacencyLists.size()) ||
        (to < 0 || to >= adjacencyLists.size()))
        return;

    adjacencyLists[from].push_back(pair<int, int>(to, w));
    adjacencyLists[to].push_back(pair<int, int>(from, w));
}

int ListGraph::VerticesCount() const {
    return adjacencyLists.size();
}

vector<pair<int, int>> ListGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjacencyLists.size())
        throw std::exception();

    return adjacencyLists[vertex];
}


struct cmp {
    bool operator() (const pair<int, int> &a, const pair<int, int> &b) {
        return a.first > b.first;
    }
};

int prim(ListGraph &graph, int from, int to) {
    vector<int> ways(graph.VerticesCount(), INFINITY);
    ways[from] = 0;

    std::set<pair<int, int>, cmp> que;
    que.insert(pair<int, int>(from, 0));
    while(!que.empty()) {
        auto cur = (*que.begin());
        que.erase(que.begin());
        for (auto i: graph.GetNextVertices(cur.first)){
            cout << i.first << "=" <<  i.second << ", ";
            if (ways[i.first] > ways[cur.first] + i.second) {
                ways[i.first] = ways[cur.first] + i.second;
                que.insert(i);
            }
        }
        cout << ": NEXT" << endl;
        for (auto i: ways)
            cout << i << ", ";
        cout << ": ARR" << endl;
    }
    return ways[to];
}


int main() {
    int v;
    int n;
    cin >> v >> n;
    ListGraph graph(v);

    int from, to, w;
    for (int i = 0; i < n; i++) {
        cin >> from >> to >> w;
        graph.AddEdge(from, to, w);
    }
    cin >> from >> to;
    int answer = prim(graph, from, to);
    cout << answer << endl;

    return 0;
}
