// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <limits>
#include <stack>
#include <vector>

using std::max;
using std::stack;
using std::vector;

struct Graph_vertex;

stack<Graph_vertex*> BuildTopologicalOrdering(vector<Graph_vertex>* G);

int FindLongestPath(stack<Graph_vertex*>* vertex_order);

void DFS(Graph_vertex* cur, stack<Graph_vertex*>* vertex_order);

// @include
struct Graph_vertex {
    vector<Graph_vertex*> edges;
    int max_distance = 1;
    bool visited = false;
};

int FindLargestNumberTeams(vector<Graph_vertex>* G)
{
    stack<Graph_vertex*> vertex_order(BuildTopologicalOrdering(G));
    return FindLongestPath(&vertex_order);
}

stack<Graph_vertex*> BuildTopologicalOrdering(vector<Graph_vertex>* G)
{
    stack<Graph_vertex*> vertex_order;
    for (auto& g : *G) {
        if (!g.visited) {
            DFS(&g, &vertex_order);
        }
    }
    return vertex_order;
}

int FindLongestPath(stack<Graph_vertex*>* vertex_order)
{
    int max_distance = 0;
    while (!vertex_order->empty()) {
        Graph_vertex* u = vertex_order->top();
        max_distance = max(max_distance, u->max_distance);
        for (Graph_vertex*& v : u->edges) {
            v->max_distance = max(v->max_distance, u->max_distance + 1);
        }
        vertex_order->pop();
    }
    return max_distance;
}

void DFS(Graph_vertex* cur, stack<Graph_vertex*>* vertex_order)
{
    cur->visited = true;
    for (Graph_vertex* next : cur->edges) {
        if (!next->visited) {
            DFS(next, vertex_order);
        }
    }
    vertex_order->emplace(cur);
}
// @exclude

int main(int argc, char* argv[])
{
    vector<Graph_vertex> G(3);
    G[0].edges.emplace_back(&G[2]);
    G[1].edges.emplace_back(&G[2]);
    assert(2 == FindLargestNumberTeams(&G));
    return 0;
}
