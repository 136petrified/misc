#pragma once
#include <queue>
#include <vector>

using Vertex = int;
using VertexList = std::vector<Vertex>;

class Edge {
private:
    Vertex u, v;
    int weight;
public:
    Edge();
    ~Edge() {}
};

using EdgeList = std::vector<Edge>;

class Graph {
public:
    Graph();
    ~Graph();
};

class MinHeap {
public:
    MinHeap();
    ~MinHeap();
};

class PriorityQueue : public MinHeap {
public:
    PriorityQueue();
    ~PriorityQueue();
};

EdgeList & a_star(const Vertex &start, const Vertex &end);