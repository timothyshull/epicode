// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <deque>
#include <iostream>
#include <random>

struct Graph_vertex;

void dfs(Graph_vertex& cur, int time, std::vector<Graph_vertex*>& contacts);

// @include
struct Graph_vertex {
    int visit_time = -1;
    std::vector<Graph_vertex*> edges; // can use std::reference_wrapper but this is more straightforward
    std::vector<Graph_vertex*> extended_contacts;
};

void transitive_closure(std::vector<Graph_vertex>& g)
{
    // Build extended contacts for each vertex.
    for (auto i = 0; i < g.size(); ++i) {
        g[i].visit_time = i;
        dfs(g[i], i, g[i].extended_contacts);
    }
}

void dfs(Graph_vertex& cur, int time, std::vector<Graph_vertex*>& contacts)
{
    for (auto& next : cur.edges) {
        if (next->visit_time != time) {
            next->visit_time = time;
            contacts.emplace_back(next);
            dfs(*next, time, contacts);
        }
    }
}
// @exclude

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::size_t n;
    if (argc == 2) {
        n = std::stoul(argv[1]);
    } else {
        std::uniform_int_distribution<std::size_t> dis{1, 1000};
        n = dis(gen);
    }
    std::vector<Graph_vertex> g(n, Graph_vertex{});
    //std::fill_n(std::back_inserter(g), n, Graph_vertex());
    std::cout << g.size() << "\n";
    std::uniform_int_distribution<std::size_t> dis{1, n * (n - 1) / 2};
    auto m = dis(gen);
    std::vector<std::deque<bool>> does_edge_exist(n, std::deque<bool>(n, false));
    /*
    // Make the graph become connected
    for (int i = 1; i < n; ++i) {
    G[i - 1].edges.emplace_back(i);
    G[i].edges.emplace_back(i - 1);
    is_edge_exist[i - 1][i] = is_edge_exist[i][i - 1] = true;
    }
     */

    // Generate edges randomly
    dis = std::uniform_int_distribution<std::size_t>{0, n - 1};
    while (m-- > 0) {
        std::size_t a;
        std::size_t b;
        do {
            a = dis(gen);
            b = dis(gen);
        } while (a == b || does_edge_exist[a][b] == true);
        does_edge_exist[a][b] = does_edge_exist[b][a] = true;
        g[a].edges.emplace_back(&g[b]);
        g[b].edges.emplace_back(&g[a]);
    }

    transitive_closure(g);
    /*
    for (int i = 0; i < G.size(); ++i) {
      cout << i << "\n" << '\t';
      for (Graph_vertex* &e : G[i].extended_contacts) {
        cout << e << ' ';
      }
      cout << "\n";
    }
    for (int i = 0; i < G.size(); ++i) {
      cout << i << "\n";
      for (int j = 0; j < G[i].edges.size(); ++j) {
        cout << ' ' << G[i].edges[j];
      }
      cout << "\n";
    }
    */
    return 0;
}
