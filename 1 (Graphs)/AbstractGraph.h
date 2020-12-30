#ifndef _INLUDE_ABSTRACT_GRAPH
#define _INLUDE_ABSTRACT_GRAPH

#include <vector>

struct AbstractGraph {
    virtual ~AbstractGraph() {;}
	// Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif // _INLUDE_ABSTRACT_GRAPH
