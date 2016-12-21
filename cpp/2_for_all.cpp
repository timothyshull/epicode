// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::min;
using std::numeric_limits;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;
using std::vector;

struct GraphVertex;

bool has_bridge(GraphVertex*, GraphVertex*, int);

// @include
struct GraphVertex {
    int d, l;  // Discovery and leaving time.
    vector<GraphVertex*> edges;

    // @exclude
    GraphVertex() : d(0), l(numeric_limits<int>::max()) {}
    // @include
};

bool is_graph_fault_tolerant(vector<GraphVertex>* G)
{
    if (!G->empty()) {
        return has_bridge(&G->front(), nullptr, 0);
    }
    return true;
}

bool has_bridge(GraphVertex* cur, GraphVertex* pre, int time)
{
    cur->d = ++time, cur->l = numeric_limits<int>::max();
    for (GraphVertex*& next : cur->edges) {
        if (next != pre) {
            if (next->d != 0) {  // Back edge.
                cur->l = min(cur->l, next->d);
            } else {  // Forward edge.
                if (!has_bridge(next, cur, time)) {
                    return false;
                }
                cur->l = min(cur->l, next->l);
            }
        }
    }
    return (pre == nullptr || cur->l < cur->d);
}
// @exclude

void dfs_exclusion(GraphVertex* cur, GraphVertex* a, GraphVertex* b)
{
    cur->d = 1;
    for (GraphVertex*& next : cur->edges) {
        if (next->d == 0 &&
            ((cur != a && cur != b) || (next != a && next != b))) {
            dfs_exclusion(next, a, b);
        }
    }
}

// O(n^2) check answer.
bool check_answer(vector<GraphVertex>* G)
{
    // marks all vertices as white.
    for (GraphVertex& n : *G) {
        n.d = 0;
    }

    for (GraphVertex& g : *G) {
        for (GraphVertex*& t : g.edges) {
            dfs_exclusion(&g, &g, t);
            int count = 0;
            for (GraphVertex& n : *G) {
                if (n.d == 1) {
                    ++count;
                    n.d = 0;
                }
            }
            if (count != G->size()) {
                return false;
            }
        }
    }
    return true;
}

void test_triangle()
{
    vector<GraphVertex> G(3);
    G[0].edges.emplace_back(&G[1]);
    G[1].edges.emplace_back(&G[0]);
    G[1].edges.emplace_back(&G[2]);
    G[2].edges.emplace_back(&G[1]);
    G[2].edges.emplace_back(&G[0]);
    G[0].edges.emplace_back(&G[2]);
    bool result = is_graph_fault_tolerant(&G);
    assert(result);
}

void test_two_triangles()
{
    vector<GraphVertex> G(6);
    G[0].edges.emplace_back(&G[1]);
    G[1].edges.emplace_back(&G[0]);
    G[1].edges.emplace_back(&G[2]);
    G[2].edges.emplace_back(&G[1]);
    G[2].edges.emplace_back(&G[0]);
    G[0].edges.emplace_back(&G[2]);

    G[3].edges.emplace_back(&G[4]);
    G[4].edges.emplace_back(&G[3]);
    G[4].edges.emplace_back(&G[5]);
    G[5].edges.emplace_back(&G[4]);
    G[5].edges.emplace_back(&G[3]);
    G[3].edges.emplace_back(&G[5]);

    // bridge edge
    G[0].edges.emplace_back(&G[3]);
    G[3].edges.emplace_back(&G[0]);

    bool result = is_graph_fault_tolerant(&G);
    assert(!result);
}

void test_two_triangles_bridged()
{
    vector<GraphVertex> G(6);
    G[0].edges.emplace_back(&G[1]);
    G[1].edges.emplace_back(&G[0]);
    G[1].edges.emplace_back(&G[2]);
    G[2].edges.emplace_back(&G[1]);
    G[2].edges.emplace_back(&G[0]);
    G[0].edges.emplace_back(&G[2]);

    G[3].edges.emplace_back(&G[4]);
    G[4].edges.emplace_back(&G[3]);
    G[4].edges.emplace_back(&G[5]);
    G[5].edges.emplace_back(&G[4]);
    G[5].edges.emplace_back(&G[3]);
    G[3].edges.emplace_back(&G[5]);

    G[0].edges.emplace_back(&G[3]);
    G[3].edges.emplace_back(&G[0]);

    G[0].edges.emplace_back(&G[4]);
    G[4].edges.emplace_back(&G[0]);

    bool result = is_graph_fault_tolerant(&G);
    assert(result);
}

int main(int argc, char* argv[])
{
    test_triangle();
    test_two_triangles();
    test_two_triangles_bridged();
    random_device rd;
    default_random_engine gen(rd());
    for (int times = 0; times < 1000; ++times) {
        vector<GraphVertex> G;
        int n;
        if (argc == 2) {
            n = stoi(argv[1]);
        } else {
            uniform_int_distribution<int> dis(2, 101);
            n = dis(gen);
        }
        for (int i = 0; i < n; ++i) {
            G.emplace_back(GraphVertex());
        }
        uniform_int_distribution<int> dis(1, n * (n - 1) / 2);
        int m = dis(gen);
        vector<deque<bool>> is_edge_exist(n, deque<bool>(n, false));
        // Make the graph become connected.
        for (int i = 1; i < n; ++i) {
            G[i - 1].edges.emplace_back(&G[i]);
            G[i].edges.emplace_back(&G[i - 1]);
            is_edge_exist[i - 1][i] = is_edge_exist[i][i - 1] = true;
        }

        // Generate edges randomly.
        m -= (n - 1);
        while (m-- > 0) {
            int a, b;
            uniform_int_distribution<int> dis(0, n - 1);
            do {
                a = dis(gen), b = dis(gen);
            } while (a == b || is_edge_exist[a][b] == true);
            is_edge_exist[a][b] = is_edge_exist[b][a] = true;
            G[a].edges.emplace_back(&G[b]);
            G[b].edges.emplace_back(&G[a]);
        }

        /*
        for (int i = 0; i < G.size(); ++i) {
          cout << i << "\n";
          for (int j = 0; j < G[i].edges.size(); ++j) {
            cout << ' ' << G[i].edges[j];
          }
          cout << "\n";
        }
        */

        bool res = is_graph_fault_tolerant(&G);
        cout << boolalpha << res << "\n";
        assert(check_answer(&G) == res);
    }
    return 0;
}
