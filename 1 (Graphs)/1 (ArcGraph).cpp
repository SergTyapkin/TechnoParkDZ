#include "AbstractGraph.h"

#include <vector>
using std::vector;


class ArcGraph : public AbstractGraph {
public:
    ArcGraph(int vertexCount);
    ArcGraph(const AbstractGraph& graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;
    virtual vector<int> GetNextVertices(int vertex) const override;
    virtual vector<int> GetPrevVertices(int vertex) const override;

private:
    int verticesCount;
    vector<std::pair<int, int>> adjacencyLists;
};

ArcGraph::ArcGraph(int vertexCount) {
    adjacencyLists.resize(vertexCount);
}

ArcGraph::ArcGraph(const AbstractGraph& graph) {
    for (int from = 0; from < graph.VerticesCount(); from++)
        for (auto to: graph.GetNextVertices(from))
            adjacencyLists.emplace_back(from, to);
    verticesCount = graph.VerticesCount();
}

void ArcGraph::AddEdge(int from, int to) {
    if ((from < 0 || from >= adjacencyLists.size()) ||
        (to < 0 || to >= adjacencyLists.size()))
        return;

    bool found = true;
    for (int i = 0; i < adjacencyLists.size(); i++)
        if (adjacencyLists[i] == std::pair<int, int>(from, to)) {
            found = false;
            break;
        }
    if (found)
        adjacencyLists.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return verticesCount;
}

vector<int> ArcGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjacencyLists.size())
        throw std::exception();

    vector<int> result;
    for (auto i: adjacencyLists)
        if (i.first == vertex)
            result.push_back(i.second);
    return result;
}

vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjacencyLists.size())
        throw std::exception();

    vector<int> result;
    for (auto i: adjacencyLists)
        if (i.second == vertex)
            result.push_back(i.first);
    return result;
}
