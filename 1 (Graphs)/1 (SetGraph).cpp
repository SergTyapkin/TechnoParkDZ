#include "AbstractGraph.h"

#include <vector>
#include <unordered_set>
using std::vector;


class SetGraph : public AbstractGraph {
public:
    SetGraph(int vertexCount);
    SetGraph(const AbstractGraph& graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;
    virtual vector<int> GetNextVertices(int vertex) const override;
    virtual vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<std::unordered_set<int>> adjacencyLists;
};

SetGraph::SetGraph(int vertexCount) {
    adjacencyLists.resize(vertexCount);
}

SetGraph::SetGraph(const AbstractGraph& graph) {
    adjacencyLists.resize(graph.VerticesCount());
    for (int from = 0; from < graph.VerticesCount(); from++)
        for (auto to: graph.GetNextVertices(from))
            adjacencyLists[from].insert(to);
}

void SetGraph::AddEdge(int from, int to) {
    if ((from < 0 || from >= adjacencyLists.size()) ||
        (to < 0 || to >= adjacencyLists.size()))
        return;

    adjacencyLists[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return adjacencyLists.size();
}

vector<int> SetGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjacencyLists.size())
        throw std::exception();

    vector<int> result;
    for(auto i: adjacencyLists[vertex])
        result.push_back(i);
    return result;
}

vector<int> SetGraph::GetPrevVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjacencyLists.size())
        throw std::exception();

    vector<int> result;
    for (int i = 0; i < adjacencyLists.size(); i++)
        if (adjacencyLists[i].find(vertex) != adjacencyLists[i].end())
            result.push_back(i);
    return result;
}
