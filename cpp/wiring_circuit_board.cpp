// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::queue;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

struct Graph_vertex;

bool bfs(Graph_vertex* s);

// @include
struct Graph_vertex {
    int d = -1;
    vector<Graph_vertex*> edges;
};

bool is_any_placement_feasible(vector<Graph_vertex>* G)
{
    for (Graph_vertex& v : *G) {
        if (v.d == -1) {  // Unvisited vertex.
            v.d = 0;
            if (!bfs(&v)) {
                return false;
            }
        }
    }
    return true;
}

bool bfs(Graph_vertex* s)
{
    queue<Graph_vertex*> q;
    q.emplace(s);

    while (!q.empty()) {
        for (Graph_vertex*& t : q.front()->edges) {
            if (t->d == -1) {  // Unvisited vertex.
                t->d = q.front()->d + 1;
                q.emplace(t);
            } else if (t->d == q.front()->d) {
                return false;
            }
        }
        q.pop();
    }
    return true;
}
// @exclude

bool dfs(Graph_vertex* s)
{
    for (Graph_vertex*& t : s->edges) {
        if (t->d == -1) {
            t->d = !s->d;
            if (!dfs(t)) {
                return false;
            }
        } else if (t->d == s->d) {
            return false;
        }
    }
    return true;
}

bool is_two_colorable(vector<Graph_vertex>* G)
{
    for (Graph_vertex& v : *G) {
        v.d = -1;
    }

    for (Graph_vertex& v : *G) {
        if (v.d == -1) {
            v.d = 0;
            if (!dfs(&v)) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    default_random_engine gen((random_device()) ());
    for (int times = 0; times < 9000; ++times) {
        int n;
        if (argc == 2) {
            n = atoi(argv[1]);
        } else {
            uniform_int_distribution<int> dis(2, 101);
            n = dis(gen);
        }
        vector<Graph_vertex> G(n);
        uniform_int_distribution<int> dis(1, n * (n - 1) / 2);
        int m = dis(gen);
        cout << times << ' ' << n << ' ' << m << "\n";
        vector<deque<bool>> is_edge_exist(n, deque<bool>(n, false));
        while (m-- > 0) {
            uniform_int_distribution<int> dis(0, n - 1);
            int a, b;
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
        bool res = is_any_placement_feasible(&G);
        cout << boolalpha << res << "\n";
        assert(res == is_two_colorable(&G));
    }
    return 0;
}
