#include "AbstractGraph.h"

#include <vector>
using std::vector;


class MatrixGraph : public AbstractGraph {
public:
    MatrixGraph(int vertexCount);
    MatrixGraph(const AbstractGraph& graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;
    virtual vector<int> GetNextVertices(int vertex) const override;
    virtual vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<vector<bool>> adjacencyList;
};

MatrixGraph::MatrixGraph(int vertexCount) {
    adjacencyList.resize(vertexCount);
    for (int i; i < vertexCount; i++)
        adjacencyList[i].resize(vertexCount);
}


MatrixGraph::MatrixGraph(const AbstractGraph& graph) {
    int vertexCount = graph.VerticesCount();
    adjacencyList.resize(vertexCount);
    for (int i; i < vertexCount; i++)
        adjacencyList[i].resize(vertexCount);

    for (int from = 0; from < adjacencyList.size(); from++) {
        for (auto to: graph.GetNextVertices(from)) {
            adjacencyList[from][to] = true;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    if ((from < 0 || from >= adjacencyList.size()) ||
        (to < 0 || to >= adjacencyList.size()))
        return;

    adjacencyList[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return adjacencyList.size();
}

vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjacencyList.size())
        throw std::exception();

    vector<int> result;
    for (int from = 0; from < adjacencyList.size(); from++)
        if (adjacencyList[vertex][from] > 0)
            result.push_back(from);
    return result;
}

vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjacencyList.size())
        throw std::exception();

    vector<int> result;
    for (int to = 0; to < adjacencyList.size(); to++)
        if (adjacencyList[to][vertex] > 0)
            result.push_back(to);
    return result;
}
